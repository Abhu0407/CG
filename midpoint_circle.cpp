#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void drawCircle(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// Midpoint Circle Drawing Algorithm
void circleMidpoint(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;  
    drawCircle(xc, yc, x, y);
    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        drawCircle(xc, yc, x, y);
    }
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 250, yc = 250, r = 100;

    glColor3f(1.0, 0.0, 0.0);  

    circleMidpoint(xc, yc, r);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);      
    glutInitWindowPosition(100, 100);  
    glutCreateWindow("Midpoint Circle Drawing Algorithm");

    glClearColor(0.0, 0.0, 0.0, 0.0);  
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); 

    glutDisplayFunc(display);  

    glutMainLoop();  

    return 0;
}

