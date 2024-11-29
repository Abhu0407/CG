#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int startX, startY, endX, endY;

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

vector<int> find_cordinate(int xc, int yc, int r, double m){
	int x,y;
	vector<int> ans;
	x = xc + sqrt(r*r/(1+m*m));
	y = yc + m*sqrt(r*r/(1+m*m));
	ans.push_back(x);
	ans.push_back(y);
	
	x = xc - sqrt(r*r/(1+m*m));
	y = yc - m*sqrt(r*r/(1+m*m));
	ans.push_back(x);
	ans.push_back(y);
	
	return ans;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 250, yc = 250, r = 100;

    glColor3f(1.0, 0.0, 0.0);  

    circleMidpoint(xc, yc, r);
    
    int n;
    cout<<"number of lines :- ";
    cin>>n;
    
    for(int i=1;i<=n;i++){
    	double angle_degree;
    	cout<<"Enter the value of angle in dgree :- ";
    	cin>>angle_degree;
    	double angle_radians = angle_degree * M_PI / 180.0;
    	vector<int> coor = find_cordinate(xc,yc,r,tan(angle_radians));
    	DDA(coor[0], coor[1], coor[2], coor[3]);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);      
    glutInitWindowPosition(100, 100);  
    glutCreateWindow(" Draw circle divide by line with diffrent angle");

    glClearColor(0.0, 0.0, 0.0, 0.0);  
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); 

    glutDisplayFunc(display);  

    glutMainLoop();  

    return 0;
}

