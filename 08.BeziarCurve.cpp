/*
8. Develop a menu driven program to animate a flag using Bezier Curve algorithm
*/

#include<stdio.h>
#include<math.h>
#include<glut.h>

#define PI 3.1416

GLsizei winWidth = 600, winHeight = 600;
GLfloat xMinWC = 0.0, xMaxWC = 130.0;
GLfloat yMinWC = 0.0, yMaxWC = 130.0;

struct Point3d
{
	GLfloat x, y, z;
};

void bino(GLint n, GLint C[]);
void computeBeziarPoint(GLfloat u, Point3d *beziarPoint, GLint nControlPoints, Point3d controlPoints[], GLint C[]);
void bezier(Point3d controlPoints[], GLint nControlPoints, GLint nBeziarCurvePoints);
void display();
void reshape(GLint w, GLint h);
void menu(int op);

void bino(GLint n, GLint C[])
{
	GLint k, j;
	for (k = 0; k <= n; k++)
	{
		C[k] = 1;
		for (j = n; j >= k + 1; j--)
			C[k] *= j;
		for (j = n - k; j >= 2; j--)
			C[k] /= j;
	}
}

void computeBeziarPoint(GLfloat u, Point3d *beziarPoint, GLint nControlPoints, Point3d controlPoints[], GLint C[])
{
	GLint k, n = nControlPoints - 1;
	GLfloat bezBlendFcn;
	beziarPoint->x = beziarPoint->y = beziarPoint->z = 0.0;
	for (k = 0; k < nControlPoints; k++)
	{
		bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
		beziarPoint->x += controlPoints[k].x * bezBlendFcn;
		beziarPoint->y += controlPoints[k].y * bezBlendFcn;
		beziarPoint->z += controlPoints[k].z * bezBlendFcn;
	}
}

void bezier(Point3d controlPoints[], GLint nControlPoints, GLint nBeziarCurvePoints)
{
	Point3d beziarCurvePoint;
	GLfloat u;
	GLint *C, k;
	C = new GLint[nControlPoints];
	bino(nControlPoints - 1, C);
	glBegin(GL_LINE_STRIP);
	for (k = 0; k <= nBeziarCurvePoints; k++)
	{
		u = GLfloat(k) / GLfloat(nBeziarCurvePoints);
		computeBeziarPoint(u, &beziarCurvePoint, nControlPoints, controlPoints, C);
		glVertex2f(beziarCurvePoint.x, beziarCurvePoint.y);
	}
	glEnd();
	delete[] C;
}

void display()
{
	GLint nCtrlPts = 4, nBezCurvePts = 20;
	static float theta = 0;
	Point3d ctrlPts[4] = {
		{ 20, 100, 0 },
	{ 30, 110, 0 },
	{ 50, 90, 0 },
	{ 60, 100, 0 } };
	ctrlPts[1].x += 10 * sin(theta * PI / 180.0);
	ctrlPts[1].y += 5 * sin(theta * PI / 180.0);
	ctrlPts[2].x -= 10 * sin((theta + 30) * PI / 180.0);
	ctrlPts[2].y -= 10 * sin((theta + 30) * PI / 180.0);
	ctrlPts[3].x -= 4 * sin((theta)* PI / 180.0);
	ctrlPts[3].y += sin((theta - 30) * PI / 180.0);
	theta += 0.1;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glPushMatrix();
	glLineWidth(5);


	for (int i = 0; i < 24; i++)
	{
		glTranslatef(0, -0.8, 0);
		bezier(ctrlPts, nCtrlPts, nBezCurvePts);
	}

	glPopMatrix();
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(20, 100);
	glVertex2f(20, 40);
	glEnd();
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xMinWC, xMaxWC, yMinWC, yMaxWC);
	glClear(GL_COLOR_BUFFER_BIT);
}

void menu(int op)
{
	if (op == 1)
		glColor3f(1.0, 0.0, 0.0);
	else if (op == 2)
		glColor3f(0.0, 1.0, 0.0);
	else if (op == 3)
		glColor3f(0.0, 0.0, 1.0);
	else if (op == 4)
		exit(0);
	glutPostRedisplay();
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Bezier Curve");

	glutCreateMenu(menu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
