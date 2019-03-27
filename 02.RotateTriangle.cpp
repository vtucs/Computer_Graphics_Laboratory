#include<stdio.h>
#include<math.h>
#include<glut.h>

int xr, yr;
float angle;
float vertex[3][2] = { { 20, 20 }, { 40,60 }, { 60,20 } };
void drawTriangle();
void display();

void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(vertex[0]);
	glVertex2fv(vertex[1]);
	glVertex2fv(vertex[2]);
	glEnd();
	glFlush();
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	drawTriangle();

	for (int i = 0; i < 3; i++)
	{
		int x = vertex[i][0];
		int y = vertex[i][1];
		vertex[i][0] = xr + (x - xr) * cos(angle) - (y - yr) * sin(angle);
		vertex[i][1] = yr + (x - xr) * sin(angle) + (y - yr) * cos(angle);
	}

	glColor3f(0, 1, 0);
	drawTriangle();
}

int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Rotate Triangle");
	gluOrtho2D(0, 150, 0, 150);

	printf("Enter Reference Point: ");
	scanf_s("%d %d", &xr, &yr);
	printf("Enter Angle in Degree: ");
	scanf_s("%f", &angle);

	angle = ((angle * 22) / 7) / 180; // Coverting to Radian
	glutDisplayFunc(display);
	glutMainLoop();
}
