#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

int h, k, a, b;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + h, y + k);
    glEnd();
}

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
}

void midPointEllipseAlgo()
{
    int X = 0;
    int Y = b;
    float d = b * b - a * a * b + (a * a) / 4;

    while (X <= ((Y * a * a) / (b * b)))
    {

        plot(X, Y);
        plot(-X, Y);
        plot(-X, -Y);
        plot(X, -Y);
        if (d < 0)
        {
            X++;
            d += b * b * (2 * X + 3);
        }
        else
        {
            Y--;
            X++;
            d += b * b * (2 * X + 3) - 2 * a * a * Y + 2 * a * a;
        }
    }

    X = a;
    Y = 0;
    d = b * b - a * a * b + (a * a) / 4;

    while (X > ((Y * a * a) / (b * b)))
    {

        plot(X, Y);
        plot(-X, Y);
        plot(-X, -Y);
        plot(X, -Y);
        if (d < 0)
        {
            Y++;
            d += a * a * (2 * Y + 3);
        }
        else
        {
            Y++;
            X--;
            d += a * a * (2 * Y + 3) - 2 * b * b * X + 2 * b * b;
        }
    }
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);

    midPointEllipseAlgo();

    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the semi-major axis : ";
    cin >> a;
    cout << "Enter the semi-minor axis : ";
    cin >> b;
    cout << "Enter the x-coordinate of center: ";
    cin >> h;
    cout << "Enter the y-coordinate of center: ";
    cin >> k;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mid Point Ellipse");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();

    return 0;
}