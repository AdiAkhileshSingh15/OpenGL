#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

int h, k, r;

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

void midPointCircleAlgo()
{
    int x = 0;
    int y = r;
    float decision = 5 / 4 - r;
    plot(x, y);

    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2 * x + 1;
        }
        else
        {
            y--;
            x++;
            decision += 2 * (x - y) + 1;
        }
        plot(x, y);
        plot(x, -y);
        plot(-x, y);
        plot(-x, -y);
        plot(y, x);
        plot(-y, x);
        plot(y, -x);
        plot(-y, -x);
    }
}

void myDisplay(void)
{
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);

    midPointCircleAlgo();

    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the radius: ";
    cin >> r;
    cout << "Enter the x-coordinate of center: ";
    cin >> h;
    cout << "Enter the y-coordinate of center: ";
    cin >> k;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mid Point Circle");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();

    return 0;
}