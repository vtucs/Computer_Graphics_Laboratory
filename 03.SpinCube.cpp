/*
3. Draw a colour cube and spin it using OpenGL transformation matrices.
*/

#include <stdio.h>
#include <glut.h>

float points[][3] = { { -1,1,-1 },{ -1,-1,-1 },{ 1,-1,-1 },{ 1,1,-1 },{ -1,1,1 },{ -1,-1,1 },{ 1,-1,1 },{ 1,1,1 } };
float colors[][3] = { { 1,0,0 },{ 0,1,0 },{ 0,0,1 },{ 1,1,0 },{ 0,1,1 },{ 1,0,1 },{ 0.5,0.5,0.5 },{ 0.75,0.25,1 } };
int flag = 2;
float theta[] = { 0,0,0 };

void init();
void idleFunction();
void mouse(int key, int state, int x, int y);
void drawPolygon(int a, int b, int c, int d);
void colorCube();
void display();

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}

void idleFunction()
{
	++theta[flag];
	if (theta[flag] >= 360)
	{
		theta[flag] = 0;
	}
	for (int i = 0; i < 1000000; i++);
	glutPostRedisplay();
}

void mouse(int key, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (key == GLUT_LEFT_BUTTON)
			flag = 2;
		else if (key == GLUT_MIDDLE_BUTTON)
			flag = 1;
		else if (key == GLUT_RIGHT_BUTTON)
			flag = 0;
	}
}

void drawPolygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(points[a]);
	glColor3fv(colors[b]);
	glVertex3fv(points[b]);
	glColor3fv(colors[c]);
	glVertex3fv(points[c]);
	glColor3fv(colors[d]);
	glVertex3fv(points[d]);
	glEnd();
}

void colorCube()
{
	drawPolygon(0, 1, 2, 3);
	drawPolygon(4, 5, 6, 7);
	drawPolygon(5, 1, 2, 6);
	drawPolygon(4, 0, 3, 7);
	drawPolygon(6, 2, 3, 7);
	drawPolygon(5, 1, 0, 4);
}

void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	colorCube();
	glutSwapBuffers();
}

int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Rotate Cube");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idleFunction);
	glutMouseFunc(mouse);
	glutMainLoop();
}
