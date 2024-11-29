#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void drawEllipse(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y); // Quadrant 1
    glVertex2i(xc - x, yc + y); // Quadrant 2
    glVertex2i(xc + x, yc - y); // Quadrant 4
    glVertex2i(xc - x, yc - y); // Quadrant 3
    glEnd();
}

// Bresenham’s Ellipse Drawing Algorithm
void ellipseBresenham(int xc, int yc, int rx, int ry) {
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = 2 * ((ry * ry) / (rx * rx)) + 1 - 2 * ry;
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    while (dx < dy) {
        drawEllipse(xc, yc, x, y);

        if (d1 < 0) {
            d1 = d1 + 2 * ((ry * ry) / (rx * rx)) * (2 * x + 3);
            x++;
            dx = 2 * ry * ry * x;
        } else {
            d1 = d1 + 2 * ((ry * ry) / (rx * rx)) * (2 * x + 3) - 4 * (y -1);
            x++;
            y--;
            dx = 2 * ry * ry * x;
    		dy = 2 * rx * rx * y;
        }
    }

    // Initial decision parameter of region 2
    d2 = 2 * (rx * rx) * ((1-(y-1)*(y-1))/(ry*ry)) - (x*x) - (x+1)*(x+1);

    while (y >= 0) {
        drawEllipse(xc, yc, x, y);

        if (d2 > 0) {
            d2 = d2 - ((rx * rx) / (ry * ry)) * (4 * y - 6);
            y--;
        } else {
            d2 = d2 - ((rx * rx) / (ry * ry)) * (4 * y - 6) + 4 * (x +1);
            y--;
            x++;
        }
    }

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 250, yc = 250;  
    int rx = 100, ry = 50;  

    glColor3f(1.0, 0.0, 0.0);

    ellipseBresenham(xc, yc, rx, ry);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);      
    glutInitWindowPosition(100, 100);  
    glutCreateWindow("Midpoint Ellipse Drawing Algorithm");

    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set background color to black
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Set the coordinate system

    glutDisplayFunc(display);  // Register display callback handler for window repaint

    glutMainLoop();  // Enter the event-processing loop

    return 0;
}

