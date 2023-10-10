#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

// g++ *.cpp -lGL -lGLU -lglut

struct Point
{
    float x = 0.0, y = 0.0;

    Point(float X = 0.0, float Y = 0.0) : x(X), y(Y) {}

    Point operator+(const Point &p)
    {
        Point res;
        res.x = x + p.x;
        res.y = y + p.y;
        return res;
    }

    Point operator-(const Point &p)
    {
        Point res;
        res.x = x - p.x;
        res.y = y - p.y;
        return res;
    }

    Point operator*(const float &f)
    {
        Point res;
        res.x = x * f;
        res.y = y * f;
        return res;
    }
};

Point P0, P1, d_P0, d_P1;

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float t, h1, h2, h3, h4;

    glBegin(GL_POINTS);
    for (t = 0.0f; t <= 1.0f; t += 0.001f)
    {
        h1 = 2 * t * t * t - 3 * t * t + 1;
        h2 = t * t * t - 2 * t * t + t;
        h3 = -2 * t * t * t + 3 * t * t;
        h4 = t * t * t - t * t;

        Point P = P0 * h1 + d_P0 * h2 + P1 * h3 + d_P1 * h4;

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(P.x, P.y);
    }
    glEnd();

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(P0.x, P0.y);
    glVertex2f(P1.x, P1.y);
    glEnd();
    glPointSize(1);

    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the value of P0 : ";
    cin >> P0.x >> P0.y;
    cout << "Enter the value of P0' : ";
    cin >> d_P0.x >> d_P0.y;
    cout << "Enter the value of P1 : ";
    cin >> P1.x >> P1.y;
    cout << "Enter the value of P1' : ";
    cin >> d_P1.x >> d_P1.y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Hermite Curve");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
