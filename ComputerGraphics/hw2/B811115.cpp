#include "pch.h"
#include "B811115.h"



void B811115::drawTriangle() {
	glDisable(GL_LIGHTING);
	GLfloat triColor[] = { 0.8, 0.2, 0.2 };
	glColor3fv(triColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, triColor);
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glVertex3f(0.1, 0, -2);
	glVertex3f(0.1, 0.5, 0);
	glVertex3f(0.1, -0.5, 0);
	glEnd();


	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.1, 0, -2);
	glVertex3f(-0.1, 0.5, 0);
	glVertex3f(-0.1, -0.5, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 0.1, -2);
	glVertex3f(1.0, 0.1, 0);
	glVertex3f(-1.0, 0.1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0, -1, 0);
	glVertex3f(0, -0.1, -2);
	glVertex3f(1.0, -0.1, 0);
	glVertex3f(-1.0, -0.1, 0);
	glEnd();
	glEnable(GL_LIGHTING);
}
void B811115::drawAxex() {
	glDisable(GL_LIGHTING);
	GLfloat xLine[] = { 0.0, 1.0, 0.0 };
	GLfloat yLine[] = { 1.0, 0.0, 0.0 };
	GLfloat zLine[] = { 0.0, 0.0, 1.0 };

	glBegin(GL_LINES);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, xLine);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-100.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yLine);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, -100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, zLine);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -100.0);
	glVertex3f(0.0, 0.0, 100.0);
	glEnd();
	glEnable(GL_LIGHTING);
}

void B811115::drawbkground() {
	glDisable(GL_LIGHTING);
	GLfloat star[] = { 1.0, 1.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, star);
	glColor3f(1.0, 1.0, 0);
	glPointSize(5.0f);

	for (int i = 0; i < 100; i += 10) {
		for (int j = 0; j <100; j += 10) {
			for (int k = 0; k < 100; k += 10) {
				glBegin(GL_POINTS);
				glVertex3f(i, j, k);
				glVertex3f(-i, j, k);
				glVertex3f(i, -j, k);
				glVertex3f(-i, -j, k);
				glVertex3f(i, j, -k);
				glVertex3f(-i, j, -k);
				glVertex3f(i, -j,-k);
				glVertex3f(-i, -j, -k);
				glEnd();
			}
		}
	}
	

	
	glEnable(GL_LIGHTING);
	
}