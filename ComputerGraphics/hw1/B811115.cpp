#include "B811115.h"
#include "pch.h"
void B811115::drawLine() {

	GLfloat xLine[] = { 0.0, 1.0, 0.0 };
	GLfloat yLine[] = { 1.0, 0.0, 0.0 };
	GLfloat zLine[] = { 0.0, 0.0, 1.0 };

	glBegin(GL_LINES);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, xLine);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-10.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yLine);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, -10.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, zLine);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -10.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}
void B811115::drawSphere() {

	glColor3f(0.0, 0.0, 1.0);
	GLfloat sphereColor[] = { 0.2, 0.2, 0.8 }; // �ֺ��� �л걤 �ݻ籤 ����
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sphereColor);

	glBegin(GL_TRIANGLE_FAN); // �ո�
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // ����
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // �޸�
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // �Ʒ���
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // ����
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN); // ����
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();
}
void B811115::lightOn() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT6); //���� 2,6 ON

	GLfloat light2_pos[] = { 0.0f, 0.0f, 1.0f, 1.0f };			// LIGHT2 (0,0,1)�� ����
	GLfloat light2_spot_direction[] = { 0.0f, 0.0f, -1.0f };	// LIGHT2 �� ����
	GLfloat light2_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };		// LIGHT2 �� diffuse ��

	GLfloat light6_pos[] = { 3.0f, 3.0f, 6.0f, 1.0f };
	GLfloat light6_spot_direction[] = { 0.0, 0.0, 0.0 };
	GLfloat light6_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light6_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };

	GLfloat light1_pos[] = { 3.0f, 3.0f , 6.0f, 1.0f };
	GLfloat light1_spot_direction[] = { 0.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);					// LIGHT2�� ��ġ
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_spot_direction);	// LIGHT2�� ����
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);				// LIGHT2�� DIFFUSE ����

	glLightfv(GL_LIGHT6, GL_POSITION, light6_pos);					// LIGHT6�� ��ġ
	glLightfv(GL_LIGHT6, GL_AMBIENT, light6_ambient);				// LIGHT6�� AMBIENT��
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);				// LIGHT6�� DIFFUSE��

	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);					// LIGHT1�� ��ġ
	glLightfv(GL_LIGHT1, GL_AMBIENT, light6_ambient);				// LIGHT1�� AMBIENT��
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light6_diffuse);				// LIGHT1�� DIFFUSE��
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 5.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);



}


void B811115::lightOff_spotOn() {
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT6);
	glEnable(GL_LIGHT1);
}


void B811115::initialize() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}