#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    float x, y;
};

float isLeft(const Point& p0, const Point& p1, const Point& p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

int windingNumber(const vector<Point>& polygon, const Point& p) {
    int wn = 0;
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        const Point& p0 = polygon[i];
        const Point& p1 = polygon[(i + 1) % n];
        if (p0.y <= p.y) {
            if (p1.y > p.y) {
                if (isLeft(p0, p1, p) > 0) {
                    wn++;
                }
            }
        } else {
            if (p1.y <= p.y) {
                if (isLeft(p0, p1, p) < 0) {
                    wn--;
                }
            }
        }
    }
    return wn;
}

vector<Point> polygon = {{2.0f, 1.0f}, {3.0f, 3.0f}, {5.0f, 2.0f}, {4.0f, 5.0f}, {3.0f, 4.0f}, {2.0f, 5.0f}, {1.0f, 3.0f}};

Point testPoint = {0.0f, 0.0f};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
  
    glBegin(GL_LINE_LOOP);
    for (const auto& p : polygon) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (const auto& p : polygon) {
        glVertex2f(p.x, p.y);  
    }
    glVertex2f(testPoint.x, testPoint.y);
    glEnd();
    
    int wn = windingNumber(polygon, testPoint);
    if (wn != 0) {
        cout << "Point is inside the polygon" << endl;
    } else {
        cout << "Point is outside the polygon" << endl;
    }
    
    glFlush();
}

void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glOrtho(0.0f, 6.0f, 0.0f, 6.0f, -1.0f, 1.0f);  
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        testPoint.x = (float)x / 100.0f; 
        testPoint.y = 6.0f - (float)y / 100.0f; 
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Winding Number Test");
    initOpenGL();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

