/*
4. Draw a color cube and allow the user to move the camera suitably to experiment
with perspective viewing.
*/

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

float points[][3] = { { -1,1,-1 },{ -1,-1,-1 },{ 1,-1,-1 },{ 1,1,-1 },{ -1,1,1 },{ -1,-1,1 },{ 1,-1,1 },{ 1,1,1 } };
float colors[][3] = { { 1,0,0 },{ 0,1,0 },{ 0,0,1 },{ 1,1,0 },{ 0,1,1 },{ 1,0,1 },{ 0.5,0.5,0.5 },{ 0.75,0.25,1 } };
float theta[3] = { 0,0,0 };
int flag = 2;

void display();
void myinit();
void keyboardFunc(unsigned char key, int x, int y);
void reshape(int w, int h);
void mouseFunc(int button, int status, int x, int y);
void drawPolygon(int a, int b, int c, int d);
void colorCube();

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, 2, 20);
	glMatrixMode(GL_MODELVIEW);
}
int viewer[3] = { 0,0,2 };

void keyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'x') viewer[0]--;
	if (key == 'X') viewer[0]++;
	if (key == 'y') viewer[1]--;
	if (key == 'Y') viewer[1]++;
	if (key == 'z') viewer[2]--;
	if (key == 'Z') viewer[2]++;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glFrustum(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, 2, 20);
	else
		glFrustum(-2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -2, 2, 2, 20);
	glMatrixMode(GL_MODELVIEW);
}

void mouseFunc(int button, int status, int x, int y)
{
	if (status == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
			flag = 2;
		if (button == GLUT_MIDDLE_BUTTON)
			flag = 1;
		if (button == GLUT_RIGHT_BUTTON)
			flag = 0;
	}
	theta[flag]++;
	if (theta[flag] >= 360)theta[flag] = 0;
	glutPostRedisplay();
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
	glColor3f(1, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
	glRotatef(theta[0], 1, 0, 0);//x
	glRotatef(theta[1], 0, 1, 0);//y
	glRotatef(theta[2], 0, 0, 1);//z
	colorCube();
	glFlush();
	glutSwapBuffers();
}

int main(int argc,char** argv){
glutInit( &argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cube with camera movement");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(keyboardFunc);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
