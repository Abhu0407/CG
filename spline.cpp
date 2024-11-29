#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

const int MAX_POINTS = 100;
GLfloat ctrlPoints[MAX_POINTS][3];
int numPoints = 0;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void drawSpline() {
    if (numPoints < 2) return;

    glEnable(GL_MAP1_VERTEX_3);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, numPoints, &ctrlPoints[0][0]);

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++) {
        glEvalCoord1f((GLfloat)i / 100.0);
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSpline();

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < numPoints; i++) {
        glVertex3fv(ctrlPoints[i]);
    }
    glEnd();

    for (int i = 0; i < numPoints; i++) {
        glRasterPos3f(ctrlPoints[i][0], ctrlPoints[i][1], ctrlPoints[i][2]);
        string label = to_string(i);
        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && numPoints < MAX_POINTS) {
        GLfloat px = (GLfloat)(x - 400) / 40.0;
        GLfloat py = -((GLfloat)(y - 400) / 40.0);

        ctrlPoints[numPoints][0] = px;
        ctrlPoints[numPoints][1] = py;
        ctrlPoints[numPoints][2] = 0.0;
        numPoints++;

        cout << "Added control point: (" << px << ", " << py << ", 0.0)" << endl;

        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && numPoints > 0) {
        numPoints--;
        cout << "Removed control point. Total now: " << numPoints << endl;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Spline with Control Points and Labels");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}

