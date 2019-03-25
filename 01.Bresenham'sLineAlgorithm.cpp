#include<stdio.h>
#include<math.h>
#include<glut.h>

int xStart, yStart, xEnd, yEnd;

void myInit();
void display();
void setPixel(int x, int y);
void bresenhamLine(int x1, int y1, int x2, int y2);
void drawLineLow(int x1, int y1, int x2, int y2);
void drawLineHigh(int x1, int y1, int x2, int y2);

void myInit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void bresenhamLine(int x1, int y1, int x2, int y2)
{
	if (abs(y2 - y1) < abs(x2 - x1))
	{
		if (x1 > x2)
			drawLineLow(x2, y2, x1, y1);
		else
			drawLineLow(x1, y1, x2, y2);
	}
	else
	{
		if (y1 > y2)
			drawLineHigh(x2, y2, x1, y1);
		else
			drawLineHigh(x1, y1, x2, y2);
	}
}

void drawLineLow(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int iy = 1;

	if (dy < 0)
	{
		iy = -1;
		dy = -dy;
	}

	int P = 2 * dy - dx;

	int y = y1;

	for (int x = x1; x <= x2; x++)
	{
		setPixel(x, y);
		if (P >= 0)
		{
			y = y + iy;
			P = P - 2 * dx;
		}
		P = P + 2 * dy;
	}
}

void drawLineHigh(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int ix = 1;

	if (dx < 0)
	{
		ix = -1;
		dx = -dx;
	}

	int P = 2 * dx - dy;

	int x = x1;

	for (int y = y1; y <= y2; y++)
	{
		setPixel(x, y);
		if (P >= 0)
		{
			x = x + ix;
			P = P - 2 * dy;
		}
		P = P + 2 * dx;
	}
}

void display()
{

	glClearColor(1, 1, 1, 1);	//Specifies a background RGB color for a display window.
	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window.
	glColor3f(1, 0, 0);  // Set color to red.
	glPointSize(2);
	bresenhamLine(xStart, yStart, xEnd, yEnd);
	glFlush();	// Process all OpenGL routines as quickly as possible.
}

int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);	// Set display mode.
	glutInitWindowPosition(100, 100);	// Set top-left display-window position.
	glutInitWindowSize(500, 500);	// Set display-window width and height.
	glutCreateWindow("Bresenham's Line Drawing Algorthm");	// Create display window.
	myInit();	// Execute initialization procedure.

	printf("Enter co-ordinates of first point: ");
	scanf_s("%d %d", &xStart, &yStart);

	printf("Enter co-ordinates of second point: ");
	scanf_s("%d %d", &xEnd, &yEnd);

	glutDisplayFunc(display);				//Invokes a function to create a picture within the current display window.
	glutMainLoop();							 //Executes the computer-graphics program.
}
