/*
9. Develop a menu driven program to fill the polygon using scan line algorithm
*/

#include<stdio.h>
#include<glut.h>

void display();
void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void edgeDetect(float x1, float y1, float x2, float y2, int *le, int *re);
void drawPoint(int x, int y);

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	float x1 = 200, y1 = 200, x2 = 100, y2 = 300, x3 = 200, y3 = 400, x4 = 300, y4 = 300;


	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
	scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	int le[500], re[500];
	for (int i = 0; i < 500; i++)
	{
		le[i] = 500;
		re[i] = 0;
	}

	edgeDetect(x1, y1, x2, y2, le, re);
	edgeDetect(x2, y2, x3, y3, le, re);
	edgeDetect(x3, y3, x4, y4, le, re);
	edgeDetect(x4, y4, x1, y1, le, re);

	for (int y = 0; y < 500; y++)
		if (le[y] <= re[y])
			for (int i = le[y]; i < re[y]; i++)
				drawPoint(i, y);
}

void edgeDetect(float x1, float y1, float x2, float y2, int *le, int *re)
{
	float mx, temp;
	if (y2 < y1)
	{
		temp = y2; y2 = y1; y1 = temp;
		temp = x2; x2 = x1; x1 = temp;
	}

	mx = (x2 - x1) / (y2 - y1);
	float x = x1;
	for (int i = (int)y1; i < y2; i++)
	{
		if (x < le[i])
		{
			le[i] = (int)x;
		}

		if (x > re[i])
		{
			re[i] = (int)x;
		}

		x += mx;
	}
}

void drawPoint(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void menu(int choice)
{
	switch (choice)
	{
	case 0:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case 1:
		glColor3f(0.0, 1.0, 0.0);
		break;
	case 2:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case 3:
		exit(0);
	}
	glutPostRedisplay();
}

int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Title");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glColor3f(1.0, 0.0, 0.0);

	glutCreateMenu(menu);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutDisplayFunc(display);
	glutMainLoop();
}
