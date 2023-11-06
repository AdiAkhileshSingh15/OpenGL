#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 100.0);
    glTranslatef(0.0, 0.0, -2.0);
    glMatrixMode(GL_MODELVIEW);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(-0.7, -0.5, 0.0);
        glVertex3f(0.7, -0.5, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(600, 450);
    glutCreateWindow("Z-Buffer");
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
