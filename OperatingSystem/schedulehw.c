//
// CPU Schedule Simulator Homework
// Student Number :
// Name :
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <limits.h>

#define SEED 10

// process states
#define S_IDLE 0			
#define S_READY 1
#define S_BLOCKED 2
#define S_RUNNING 3
#define S_TERMINATE 4

int NPROC, NIOREQ, QUANTUM;

struct ioDoneEvent {
	int procid;
	int doneTime;
	int len;
	struct ioDoneEvent *prev;
	struct ioDoneEvent *next;
} ioDoneEventQueue, *ioDoneEvent;

struct process {
	int id;
	int len;		// for queue
	int targetServiceTime;
	int serviceTime;
	int startTime;
	int endTime;
	char state;
	int priority;
	int saveReg0, saveReg1;
	struct process *prev;
	struct process *next;
} *procTable;

struct process idleProc;
struct process readyQueue;
struct process blockedQueue;
struct process *runningProc;

int cpuReg0, cpuReg1;
int currentTime = 0;
int *procIntArrTime, *procServTime, *ioReqIntArrTime, *ioServTime;

void compute() {
	// DO NOT CHANGE THIS FUNCTION
	cpuReg0 = cpuReg0 + runningProc->id;
	cpuReg1 = cpuReg1 + runningProc->id;
	//printf("In computer proc %d cpuReg0 %d\n",runningProc->id,cpuReg0);
}

void initProcTable() {
	int i;
	for(i=0; i < NPROC; i++) {
		procTable[i].id = i;
		procTable[i].len = 0;
		procTable[i].targetServiceTime = procServTime[i];
		procTable[i].serviceTime = 0;
		procTable[i].startTime = 0;
		procTable[i].endTime = 0;
		procTable[i].state = S_IDLE;
		procTable[i].priority = 0;
		procTable[i].saveReg0 = 0;
		procTable[i].saveReg1 = 0;
		procTable[i].prev = NULL;
		procTable[i].next = NULL;
	}
}

void blockedQueue_push(struct process* proc) {
	proc->state = S_BLOCKED;
	if (blockedQueue.len == 0) {
		blockedQueue.next = proc;
		proc->prev = &blockedQueue;
		proc->next = NULL;
	}
	else {
		struct process* iter = &blockedQueue;
		while (iter->next != NULL) {
			iter = iter->next;
		}
		iter->next = proc;
		proc->prev = iter;
		proc->next = NULL;
	}
	blockedQueue.len++;
}
void blockedQueue_pop(struct process* proc) {
	struct process* back = &blockedQueue;
	struct process* front;
	while (back != proc) {
		front = back;
		back = back->next;
	}
	if (back->next == NULL) {
		front->next = NULL;
		back->prev = back->next = NULL;
	}
	else {
		struct process* temp = back->next;
		temp->prev = front;
		front->next = temp;
		back->prev = back->next = NULL;
	}
	blockedQueue.len--;
	if (blockedQueue.len == 0) {
		blockedQueue.next = blockedQueue.prev = &blockedQueue;
	}
	return;
}
void readyQueue_push(struct process* proc) {
	proc->state = S_READY;
	if (readyQueue.len == 0) {
		readyQueue.next = proc;
		proc->prev = &readyQueue;
		proc->next = NULL;
	}
	else {
		struct process* iter = &readyQueue;
		while (iter->next != NULL) {
			iter = iter->next;
		}
		iter->next = proc;
		proc->prev = iter;
		proc->next = NULL;
	}
	readyQueue.len++;
	return;
}

void readyQueue_pop(struct process* proc) {
	if (readyQueue.len != 0) {
		if (proc->next == NULL) {
			struct process* temp = proc->prev;
			temp->next = NULL;
			proc->next = proc->prev = NULL;
			return;
		}
		else {
			struct process* temp = &readyQueue;
			while (temp != proc) {
				temp = temp->next;
			}
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			temp->next = temp->prev = NULL;
		}
		readyQueue.len--;
		if (readyQueue.len == 0) {
			readyQueue.next = readyQueue.prev = &readyQueue;
		}
	}
	return;
}
void ioDoneEventQueue_push(struct ioDoneEvent* info) {
	struct ioDoneEvent* back = &ioDoneEventQueue;
	struct ioDoneEvent* front = back;
	if (ioDoneEventQueue.len != 0) {
		back = back->next;
		while (back != NULL && back->doneTime <= info->doneTime) {
			front = back;
			back = back->next;
		}
		if (back == NULL) {
			front->next = info;
			info->prev = front;
		}
		else {
			back->prev = info;
			info->next = back;
			front->next = info;
			info->prev = front;
		}
	}
	else {
		back->next = info;
		info->prev = back;
	}
	ioDoneEventQueue.len++;
	return;
}

struct ioDoneEvent* ioDoneEventQueue_pop() {
	if (ioDoneEventQueue.len != 0) {
		struct ioDoneEvent* tmp = ioDoneEventQueue.next;
		if (tmp->next == NULL) {
			ioDoneEventQueue.next = NULL;
		}
		else {
			struct ioDoneEvent* n_tmp = tmp->next;
			n_tmp->prev = &ioDoneEventQueue;
			ioDoneEventQueue.next = n_tmp;
		}
		tmp->next = tmp->prev = NULL;
		ioDoneEventQueue.len--;
		if (ioDoneEventQueue.len == 0) {
			ioDoneEventQueue.next = ioDoneEventQueue.prev = &ioDoneEventQueue;
		}
		return tmp;
	}
}


void procExecSim(struct process *(*scheduler)()) {
	int pid, qTime=0, cpuUseTime = 0, nproc=0, termProc = 0, nioreq=0;
	char schedule = 0, nextState = S_IDLE;
	int ioflag = 0;
	int nextForkTime, nextIOReqTime;
	idleProc.id = -1;
	nextForkTime = procIntArrTime[nproc];
	nextIOReqTime = ioReqIntArrTime[nioreq];
	runningProc = &idleProc;
	while(1) {
		currentTime++;
		runningProc->serviceTime++;
		ioflag = 0;
		nextState = S_IDLE;
		if (runningProc != &idleProc) {
			cpuReg0 = runningProc->saveReg0;
			cpuReg1 = runningProc->saveReg1;
			pid = runningProc->id;
			cpuUseTime++;
			qTime++;
		}
		// MUST CALL compute() Inside While loop
		compute(); 
		
		if (currentTime == nextForkTime) { /* CASE 2 : a new process created */
			procTable[nproc].startTime = currentTime;
			readyQueue_push(&procTable[nproc]);
			nproc++;
			nextForkTime = nextForkTime + procIntArrTime[nproc];
			nextState = S_READY;
			schedule = 1;
		}
		if (runningProc != &idleProc && qTime == QUANTUM ) { /* CASE 1 : The quantum expires */
			runningProc->priority--;
			nextState = S_READY;
			schedule = 1;
		}
		while (ioDoneEventQueue.next->doneTime == currentTime) { /* CASE 3 : IO Done Event */
			struct ioDoneEvent* Done = ioDoneEventQueue_pop();
			struct process* done_proc = &procTable[Done->procid];
			if (done_proc->state == S_BLOCKED) {
				done_proc->state = S_READY;
				blockedQueue_pop(done_proc);
				readyQueue_push(done_proc);
			}
			nextState = S_READY;
			schedule = 1;
		}
		if (cpuUseTime == nextIOReqTime) { /* CASE 5: reqest IO operations (only when the process does not terminate) */
			if (qTime < QUANTUM) {
				runningProc->priority++;
			}
			ioflag = 1;
			nioreq++;
			nextIOReqTime = nextIOReqTime + ioReqIntArrTime[nioreq];
			nextState = S_BLOCKED;
			schedule = 1;
		}
		if (runningProc->serviceTime == runningProc->targetServiceTime) { /* CASE 4 : the process job done and terminates */
			nextState = S_TERMINATE;
			schedule = 1;
		}
		// call scheduler() if needed
		if (runningProc != &idleProc) {
			if (schedule == 1) {
				qTime = 0;
				runningProc->saveReg0 = cpuReg0;
				runningProc->saveReg1 = cpuReg1;
			}
			if (nextState == S_READY) {
				runningProc->state = nextState;
				readyQueue_push(runningProc);
				runningProc = &idleProc;
			}
			else if (nextState == S_BLOCKED) {
				runningProc->state = nextState;
				blockedQueue_push(runningProc);
				ioDoneEvent[nioreq - 1].procid = runningProc->id;
				ioDoneEvent[nioreq - 1].doneTime = currentTime + ioServTime[nioreq - 1];
				ioDoneEventQueue_push(&ioDoneEvent[nioreq - 1]);
				runningProc = &idleProc;
			}
			else if (nextState == S_TERMINATE) {
				if (ioflag == 1) {
					ioDoneEvent[nioreq - 1].procid = runningProc->id;
					ioDoneEvent[nioreq - 1].doneTime = currentTime + ioServTime[nioreq - 1];
					ioDoneEventQueue_push(&ioDoneEvent[nioreq - 1]);
				}
				runningProc->state = nextState;
				runningProc->endTime = currentTime;
				runningProc = &idleProc;
				termProc++;
			}
		}

		if (termProc == NPROC) {
			return;
		}
		if (schedule == 1 && runningProc == &idleProc) {
			runningProc = scheduler();
			schedule = 0;
		}
		
	} // while loop
}

//RR,SJF(Modified),SRTN,Guaranteed Scheduling(modified),Simple Feed Back Scheduling
struct process* RRschedule() {
	struct process* result = &idleProc;
	if (readyQueue.next != NULL) {
		result = readyQueue.next;
		readyQueue_pop(result);
		result->state = S_RUNNING;
	}
	return result;
}


struct process* SJFschedule() {
	struct process* result = &idleProc;
	if (readyQueue.next != NULL) {
		struct process* iter = readyQueue.next;
		struct process* target = iter;
		int min = iter->targetServiceTime;
		while (iter->next != NULL) {
			iter = iter->next;
			if (iter->targetServiceTime < min) {
				target = iter;
				min = iter->targetServiceTime;
			}
		}
		result = target;
		readyQueue_pop(result);
		result->state = S_RUNNING;
	}
	return result;
}


struct process* SRTNschedule() {
	struct process* result = &idleProc;
	if (readyQueue.next != NULL) {
		struct process* iter = readyQueue.next;
		struct process* target = iter;
		int min = iter->targetServiceTime - iter->targetServiceTime;
		while (iter->next != NULL) {
			iter = iter->next;
			if (iter->targetServiceTime - iter->targetServiceTime < min) {
				target = iter;
				min = iter->targetServiceTime - iter->targetServiceTime;
			}
		}
		result = target;
		readyQueue_pop(result);
		result->state = S_RUNNING;
	}
	return result;
}


struct process* GSschedule() {
	struct process* result = &idleProc;
	if (readyQueue.next != NULL) {

		struct process* iter = readyQueue.next;
		struct process* target = iter;
		double min = (double)iter->serviceTime / (double)iter->targetServiceTime;
		while (iter->next != NULL) {
			iter = iter->next;
			if ((double)iter->serviceTime / (double)iter->targetServiceTime < min) {
				target = iter;
				min = (double)iter->serviceTime / (double)iter->targetServiceTime;
			}
		}
		result = target;
		readyQueue_pop(result);
		result->state = S_RUNNING;
	}
	return result;
}

struct process* SFSschedule() {
	struct process* result = &idleProc;
	if (readyQueue.next != NULL) {
		struct process* iter = readyQueue.next;
		struct process* target = iter;
		int priority = iter->priority;
		while (iter->next != NULL) {
			iter = iter->next;
			if (iter->priority > priority) {
				target = iter;
				priority = iter->priority;
			}
		}
		result = target;
		readyQueue_pop(result);
		result->state = S_RUNNING;
	}
	return result;
}

void printResult() {
	// DO NOT CHANGE THIS FUNCTION
	int i;
	long totalProcIntArrTime=0,totalProcServTime=0,totalIOReqIntArrTime=0,totalIOServTime=0;
	long totalWallTime=0, totalRegValue=0;
	for(i=0; i < NPROC; i++) {
		totalWallTime += procTable[i].endTime - procTable[i].startTime;
		/*
		printf("proc %d serviceTime %d targetServiceTime %d saveReg0 %d\n",
			i,procTable[i].serviceTime,procTable[i].targetServiceTime, procTable[i].saveReg0);
		*/
		totalRegValue += procTable[i].saveReg0+procTable[i].saveReg1;
		/* printf("reg0 %d reg1 %d totalRegValue %d\n",procTable[i].saveReg0,procTable[i].saveReg1,totalRegValue);*/
	}
	for(i = 0; i < NPROC; i++ ) { 
		totalProcIntArrTime += procIntArrTime[i];
		totalProcServTime += procServTime[i];
	}
	for(i = 0; i < NIOREQ; i++ ) { 
		totalIOReqIntArrTime += ioReqIntArrTime[i];
		totalIOServTime += ioServTime[i];
	}
	
	printf("Avg Proc Inter Arrival Time : %g \tAverage Proc Service Time : %g\n", (float) totalProcIntArrTime/NPROC, (float) totalProcServTime/NPROC);
	printf("Avg IOReq Inter Arrival Time : %g \tAverage IOReq Service Time : %g\n", (float) totalIOReqIntArrTime/NIOREQ, (float) totalIOServTime/NIOREQ);
	printf("%d Process processed with %d IO requests\n", NPROC,NIOREQ);
	printf("Average Wall Clock Service Time : %g \tAverage Two Register Sum Value %g\n", (float) totalWallTime/NPROC, (float) totalRegValue/NPROC);
	
}

int main(int argc, char *argv[]) {
	// DO NOT CHANGE THIS FUNCTION
	int i;
	int totalProcServTime = 0, ioReqAvgIntArrTime;
	int SCHEDULING_METHOD, MIN_INT_ARRTIME, MAX_INT_ARRTIME, MIN_SERVTIME, MAX_SERVTIME, MIN_IO_SERVTIME, MAX_IO_SERVTIME, MIN_IOREQ_INT_ARRTIME;
	
	if (argc < 12) {
		printf("%s: SCHEDULING_METHOD NPROC NIOREQ QUANTUM MIN_INT_ARRTIME MAX_INT_ARRTIME MIN_SERVTIME MAX_SERVTIME MIN_IO_SERVTIME MAX_IO_SERVTIME MIN_IOREQ_INT_ARRTIME\n",argv[0]);
		exit(1);
	}
	
	SCHEDULING_METHOD = atoi(argv[1]);
	NPROC = atoi(argv[2]);
	NIOREQ = atoi(argv[3]);
	QUANTUM = atoi(argv[4]);
	MIN_INT_ARRTIME = atoi(argv[5]);
	MAX_INT_ARRTIME = atoi(argv[6]);
	MIN_SERVTIME = atoi(argv[7]);
	MAX_SERVTIME = atoi(argv[8]);
	MIN_IO_SERVTIME = atoi(argv[9]);
	MAX_IO_SERVTIME = atoi(argv[10]);
	MIN_IOREQ_INT_ARRTIME = atoi(argv[11]);
	
	printf("SIMULATION PARAMETERS : SCHEDULING_METHOD %d NPROC %d NIOREQ %d QUANTUM %d \n", SCHEDULING_METHOD, NPROC, NIOREQ, QUANTUM);
	printf("MIN_INT_ARRTIME %d MAX_INT_ARRTIME %d MIN_SERVTIME %d MAX_SERVTIME %d\n", MIN_INT_ARRTIME, MAX_INT_ARRTIME, MIN_SERVTIME, MAX_SERVTIME);
	printf("MIN_IO_SERVTIME %d MAX_IO_SERVTIME %d MIN_IOREQ_INT_ARRTIME %d\n", MIN_IO_SERVTIME, MAX_IO_SERVTIME, MIN_IOREQ_INT_ARRTIME);
	
	srandom(SEED);
	
	// allocate array structures
	procTable = (struct process *) malloc(sizeof(struct process) * NPROC);
	ioDoneEvent = (struct ioDoneEvent *) malloc(sizeof(struct ioDoneEvent) * NIOREQ);
	procIntArrTime = (int *) malloc(sizeof(int) * NPROC);
	procServTime = (int *) malloc(sizeof(int) * NPROC);
	ioReqIntArrTime = (int *) malloc(sizeof(int) * NIOREQ);
	ioServTime = (int *) malloc(sizeof(int) * NIOREQ);

	// initialize queues
	readyQueue.next = readyQueue.prev = &readyQueue;
	
	blockedQueue.next = blockedQueue.prev = &blockedQueue;
	ioDoneEventQueue.next = ioDoneEventQueue.prev = &ioDoneEventQueue;
	ioDoneEventQueue.doneTime = INT_MAX;
	ioDoneEventQueue.procid = -1;
	ioDoneEventQueue.len  = readyQueue.len = blockedQueue.len = 0;
	
	// generate process interarrival times
	for(i = 0; i < NPROC; i++ ) { 
		procIntArrTime[i] = random()%(MAX_INT_ARRTIME - MIN_INT_ARRTIME+1) + MIN_INT_ARRTIME;
	}
	
	// assign service time for each process
	for(i=0; i < NPROC; i++) {
		procServTime[i] = random()% (MAX_SERVTIME - MIN_SERVTIME + 1) + MIN_SERVTIME;
		totalProcServTime += procServTime[i];	
	}
	
	ioReqAvgIntArrTime = totalProcServTime/(NIOREQ+1);
	assert(ioReqAvgIntArrTime > MIN_IOREQ_INT_ARRTIME);
	
	// generate io request interarrival time
	for(i = 0; i < NIOREQ; i++ ) { 
		ioReqIntArrTime[i] = random()%((ioReqAvgIntArrTime - MIN_IOREQ_INT_ARRTIME)*2+1) + MIN_IOREQ_INT_ARRTIME;
	}
	
	// generate io request service time
	for(i = 0; i < NIOREQ; i++ ) { 
		ioServTime[i] = random()%(MAX_IO_SERVTIME - MIN_IO_SERVTIME+1) + MIN_IO_SERVTIME;
	}
	
#ifdef DEBUG
	// printing process interarrival time and service time
	printf("Process Interarrival Time :\n");
	for(i = 0; i < NPROC; i++ ) { 
		printf("%d ",procIntArrTime[i]);
	}
	printf("\n");
	printf("Process Target Service Time :\n");
	for(i = 0; i < NPROC; i++ ) { 
		printf("%d ",procTable[i].targetServiceTime);
	}
	printf("\n");
#endif
	
	// printing io request interarrival time and io request service time
	printf("IO Req Average InterArrival Time %d\n", ioReqAvgIntArrTime);
	printf("IO Req InterArrival Time range : %d ~ %d\n",MIN_IOREQ_INT_ARRTIME,
			(ioReqAvgIntArrTime - MIN_IOREQ_INT_ARRTIME)*2+ MIN_IOREQ_INT_ARRTIME);
			
#ifdef DEBUG		
	printf("IO Req Interarrival Time :\n");
	for(i = 0; i < NIOREQ; i++ ) { 
		printf("%d ",ioReqIntArrTime[i]);
	}
	printf("\n");
	printf("IO Req Service Time :\n");
	for(i = 0; i < NIOREQ; i++ ) { 
		printf("%d ",ioServTime[i]);
	}
	printf("\n");
#endif
	
	struct process* (*schFunc)();
	switch(SCHEDULING_METHOD) {
		case 1 : schFunc = RRschedule; break;
		case 2 : schFunc = SJFschedule; break;
		case 3 : schFunc = SRTNschedule; break;
		case 4 : schFunc = GSschedule; break;
		case 5 : schFunc = SFSschedule; break;
		default : printf("ERROR : Unknown Scheduling Method\n"); exit(1);
	}
	initProcTable();
	procExecSim(schFunc);
	printResult();
	
}