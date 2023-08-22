#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

float a, b, h, k;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    float X = 0, Y, steps = 1;

    while (X <= a)
    {
        Y = b * sqrt(1 - (X * X) / (a * a));
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(X + h, Y + k);
        glVertex2f(-X + h, Y + k);
        glVertex2f(X + h, -Y + k);
        glVertex2f(-X + h, -Y + k);
        glEnd();
        X += steps;
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
    glutCreateWindow("Polynomial ellipse");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}