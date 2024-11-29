#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;
int startX, startY, endX, endY; 
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Bresenham's Line Drawing Algorithm
void bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
   	 setPixel(x1, y1);
   	 if (x1 == x2 && y1 == y2) break;
   	 int e2 = 2 * err;
   	 if (e2 > -dy) {
   		 err -= dy;
   		 x1 += sx;
   	 }
   	 if (e2 < dx) {
   		 err += dx;
   		 y1 += sy;
   	 }
    }
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); 
	bresenham(startX, startY, endX, endY);
}
void inputCoordinates() {
	cout << "Enter the coordinates of the line (x1 y1 x2 y2): ";
	cin >> startX >> startY >> endX >> endY;
}

int main(int argc, char** argv) {
	inputCoordinates();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Breshenham Line Drawing Algorithm");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

