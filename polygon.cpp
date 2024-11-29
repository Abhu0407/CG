#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int startX, startY;

void DDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    float xIncrement, yIncrement, x = x1, y = y1;

    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    xIncrement = dx / static_cast<float>(steps);
    yIncrement = dy / static_cast<float>(steps);

    glBegin(GL_POINTS);
    for (int k = 0; k <= steps; k++) {
        glVertex2i(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
    glFlush();
}

bool find_type(double m1, double m2){
	double z = m2 - m1;

    if (z > 0) {
        return false;
    } else if (z < 0) {
        return true;
    } 
    return false;
}

vector<int> calculateCoordinates(int x, int y, int angle_degree, int length) {
    double angle_radians = angle_degree * M_PI / 180.0;
    int newX = x + length * cos(angle_radians);
    int newY = y + length * sin(angle_radians);
    return {newX, newY};
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

	//vector<vector<int>> line_orintestion = {{0,70},{45,70},{-45,70},{90,130},{180,170}};
	vector<vector<int>> line_orintestion = {{45,70},{-45,70},{90,130},{180,100}};
	//vector<vector<int>> line_orintestion = {{0,70},{45,70},{-45,70},{90,130},{135,80},{-135,80},{180,80},{-90,80}};
	int n;
	n=line_orintestion.size()+1;
	
	bool concave;
    int x = startX, y = startY;
    
    vector<vector<int>> all_coordinates;
    all_coordinates.push_back({x,y});
    
    for (int i = 1; i < n; i++) {

        vector<int> coordinates = calculateCoordinates(x, y, line_orintestion[i-1][0], line_orintestion[i-1][1]);
        DDA(x, y, coordinates[0], coordinates[1]);
        if(i>1){
        	concave = find_type(tan(line_orintestion[i-1][1]), tan(tan(line_orintestion[i-2][1])));
        }
		
        x = coordinates[0];
        y = coordinates[1];
        
        all_coordinates.push_back({x,y});
    }
    if(concave){
    	cout<<"given polygone is Concave polygon"<<endl;
    }
    else{
    	cout<<"given polygone is convex polygon"<<endl;
    }

    DDA(x, y, startX, startY);
}

void inputCoordinates() {
    
    startX = 100;
    startY = 100;
    
}

int main(int argc, char** argv) {
    inputCoordinates();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Drawing Polygon with n Edges");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

