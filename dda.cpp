#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int startX, startY, endX, endY;

void DDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    float xIncrement, yIncrement, x = x1, y = y1;

    // Determine the number of steps required
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xIncrement = dx / (float)steps;
    yIncrement = dy / (float)steps;

    // Draw the line
    glBegin(GL_POINTS);
    for (int k = 0; k <= steps; k++) {
        glVertex2i(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); 
    DDA(startX, startY, endX, endY);
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
    glutCreateWindow("DDA Line Drawing Algorithm");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

