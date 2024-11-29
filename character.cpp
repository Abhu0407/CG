#include <GL/glut.h>
#include <string>

struct TextAttributes {
    std::string text;
    float color[3];
    float sizeX, sizeY;
    float orientation;
    float thickness;
};

TextAttributes characters[4] = {
    {"ABHI", {0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.0f, 3.0f},
};

void renderCharacter(const TextAttributes& attr, float x, float y, void* font) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(attr.orientation, 0.0f, 0.0f, 1.0f);
    glColor3f(attr.color[0], attr.color[1], attr.color[2]);
    glLineWidth(attr.thickness);
    glScalef(attr.sizeX, attr.sizeY, 1.0f);
    
    for (char c : attr.text) {
        glutStrokeCharacter(font, c);
    }
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float x = -200.0f;
    float y = 150.0f;
    
    for (int i = 0; i < 4; ++i) {
        void* font = (i % 2 == 0) ? GLUT_STROKE_ROMAN : GLUT_STROKE_MONO_ROMAN;
        renderCharacter(characters[i], x, y - i * 100.0f, font);
    }

    glFlush();
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Stroke Text Rendering with Distinct Styles");

    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

