#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

float r, h, k;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    float theta, x, y, steps = 1;

    while (theta < 360)
    {
        x = h + r * cos(theta);
        y = k + r * sin(theta);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
        theta += steps;
    }

    glFlush();
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Parametric circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}