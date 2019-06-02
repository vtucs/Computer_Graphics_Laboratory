/*
7. Design, develop and implement recursively subdivide a tetrahedron to form 3D
sierpinski gasket. The number of recursive steps is to be specified by the user.
*/

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

struct Point
{
	float x, y, z;

	Point()
	{
		x = y = z = 0;
	}

	Point(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

int n;
Point points[4] = { Point(0,1,0), Point(0.5,-0.5,0), Point(-0.5,-0.5,0), Point(0,0,1) };

void myInit();
void display();
void drawTriangle(Point a, Point b, Point c);
void divideTriangle(Point a, Point b, Point c, int n);
Point midPoint(Point a, Point b);

void myInit()
{
	glMatrixMode(GL_PROJECTION);	//Specifies current matrix for geometric-viewing transformations
	glLoadIdentity();		//Sets current matrix to identity.
	glOrtho(-2, 2, -2, 2, -2, 2);	//Specifies parameters for a clipping window and the near and far clipping planes 
	glMatrixMode(GL_MODELVIEW);
}

void drawTriangle(Point a, Point b, Point c)
{
	glBegin(GL_POLYGON);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(c.x, c.y, c.z);
	glEnd();
}

void divideTriangle(Point a, Point b, Point c, int n)
{
	if (n > 0)
	{
		Point midAB = midPoint(a, b);
		Point midBC = midPoint(b, c);
		Point midCA = midPoint(c, a);

		divideTriangle(a, midAB, midCA, n - 1);
		divideTriangle(midAB, b, midBC, n - 1);
		divideTriangle(midCA, midBC, c, n - 1);
	}
	else
		drawTriangle(a, b, c);
}

Point midPoint(Point a, Point b)
{
	Point mid;
	mid.x = (a.x + b.x) / 2;
	mid.y = (a.y + b.y) / 2;
	mid.z = (a.z + b.z) / 2;
	return mid;
}

void display()
{

	glClearColor(1, 1, 1, 1);		//Specifies a background RGB color for a display window.
	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window.
	glColor3f(1, 0, 0);		//Set current color to red
	divideTriangle(points[0], points[1], points[2], n);
	glColor3f(0, 1, 0);
	divideTriangle(points[3], points[2], points[0], n);
	glColor3f(0, 0, 1);
	divideTriangle(points[3], points[0], points[1], n);
	glColor3f(1, 0, 1);
	divideTriangle(points[3], points[1], points[2], n);
	glFlush();			// Process all OpenGL routines as quickly as possible.
}

int main(int argc,char** argv){
	glutInit( &argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);// sets buffering and color mode for a display window
	glutInitWindowPosition(100, 100);	    //Specifies coordinates for the top-left corner of a display window.
	glutInitWindowSize(500, 500);		    //Specifies width and height for a display window.
	glutCreateWindow("3D SIERPINSKI PATTERN");  //Creates a display window & specify a display-window title
	printf("Enter the value of n: ");
	scanf_s("%d", &n);
	myInit();				   // Execute initialization procedure.
	glutDisplayFunc(display);		   //Invokes a function to create a picture within the current display window.
	glutMainLoop();				   //Executes the computer-graphics program.
}
