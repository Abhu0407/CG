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

//Bresenham’s circle drawing algorithm
void circleBres(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y);
    while (y >= x) {
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        x++;
        drawCircle(xc, yc, x, y);
    }
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 200, yc = 200, r = 100;

    glColor3f(1.0, 0.0, 0.0);

    circleBres(xc, yc, r);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);      
    glutInitWindowPosition(100, 100);  
    glutCreateWindow("Bresenham's Circle Drawing Algorithm");

    glClearColor(0.0, 0.0, 0.0, 0.0);  
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); 

    glutDisplayFunc(display);  

    glutMainLoop(); 

    return 0;
}

