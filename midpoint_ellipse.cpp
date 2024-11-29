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

// Midpoint Ellipse Drawing Algorithm
void ellipseMidpoint(int xc, int yc, int rx, int ry) {
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // Region 1
    while (dx < dy) {
        drawEllipse(xc, yc, x, y);

        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        } else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Initial decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    // Region 2
    while (y >= 0) {
        drawEllipse(xc, yc, x, y);

        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        } else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 250, yc = 250;  // Center of ellipse
    int rx = 230, ry = 100;  // Radii for x and y directions

    glColor3f(1.0, 0.0, 0.0);  // Red color for the ellipse

    ellipseMidpoint(xc, yc, rx, ry);
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

