#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int startX, startY;

double determinant(double a, double b, double c, double d) {
    return a * d - b * c;
}

vector<double> findIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double &ix, double &iy) {
    double A1 = y2 - y1;
    double B1 = x1 - x2;
    double C1 = A1 * x1 + B1 * y1;

    double A2 = y4 - y3;
    double B2 = x3 - x4;
    double C2 = A2 * x3 + B2 * y3;

    double det = determinant(A1, B1, A2, B2);

    if (det == 0) {
        return {0.0, 0.0}; 
    }

    ix = determinant(C1, B1, C2, B2) / det;
    iy = determinant(A1, C1, A2, C2) / det;

    return {ix, iy}; 
}

int check_point(double x, double y, vector<vector<double>>& all_coordinates, int n) {
    int ans = 0;

    double ix, iy;
    for (int i = 1; i < n; i++) {
        
        vector<double> v = findIntersection(0.0, 0.0, x, y, all_coordinates[i-1][0], all_coordinates[i-1][1], all_coordinates[i][0], all_coordinates[i][1], ix, iy);
		
		double min_x = min(all_coordinates[i-1][0],all_coordinates[i][0]);
		double max_x = max(all_coordinates[i-1][0],all_coordinates[i][0]);
		
		double min_y = min(all_coordinates[i-1][1],all_coordinates[i][1]);
		double max_y = max(all_coordinates[i-1][1],all_coordinates[i][1]);
		
        if (v[0] <= x && v[1] <= y && v[0] > 0 && v[1] > 0 && v[0] <= max_x && v[1] <= max_y && v[0] > min_x && v[1] > min_y) {
            ans+=1;
        }
    }
    
    vector<double> v = findIntersection(0.0, 0.0, x, y, all_coordinates[n-1][0], all_coordinates[n-1][1], all_coordinates[0][0], all_coordinates[0][1], ix, iy);
	
	double min_x = min(all_coordinates[n-1][0],all_coordinates[0][0]);
	double max_x = max(all_coordinates[n-1][0],all_coordinates[0][0]);
		
	double min_y = min(all_coordinates[n-1][1],all_coordinates[0][1]);
	double max_y = max(all_coordinates[n-1][1],all_coordinates[0][1]);
	
    if (v[0] <= x && v[1] <= y && v[0] > 0 && v[1] > 0 && v[0] <= max_x && v[1] <= max_y && v[0] > min_x && v[1] > min_y) {
        ans+=1;
    }

    return ans;
}


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

// Function to calculate the coordinates of the next point based on angle and length
vector<double> calculateCoordinates(int x, int y, int angle_degree, int length) {
    double angle_radians = angle_degree * M_PI / 180.0;
    double newX = x + length * cos(angle_radians);
    double newY = y + length * sin(angle_radians);
    return {newX, newY};
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    vector<vector<int>> line_orintestion = {{45, 70}, {-45, 70}, {90, 130}, {180, 100}};
    //vector<vector<int>> line_orintestion = {{0,70},{45,70},{-45,70},{90,130},{135,80},{-135,80},{180,80},{-90,80}};
    //vector<vector<int>> line_orintestion = {{0,70},{45,70},{-45,70},{90,130},{180,170}};
    
    
    int n = line_orintestion.size() + 1;

    bool concave;
    double x = startX, y = startY;
    
    vector<vector<double>> all_coordinates;
    all_coordinates.push_back({x, y});
    
    
    for (int i = 1; i < n; i++) {
        vector<double> coordinates = calculateCoordinates(x, y, line_orintestion[i-1][0], line_orintestion[i-1][1]);
        DDA(x, y, coordinates[0], coordinates[1]);

    

        x = coordinates[0];
        y = coordinates[1];

        all_coordinates.push_back({x, y});
    }
    DDA(x, y, startX, startY);
    
    while (1) {
        double point_x, point_y;
        cout<<"enter points :- ";
        cin >> point_x >> point_y;
        
        glColor3f(0.0, 1.0, 0.0);
        DDA(point_x, point_y, 0, 0);
        
        int ans = check_point(point_x, point_y, all_coordinates, n);
        
        if (ans % 2 == 0) {
            cout << "The point is outside the polygon." << endl;
        } else {
            cout << "The point is inside the polygon." << endl;
        }
        cout<<endl;
    }

    // Close the polygon
    
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

