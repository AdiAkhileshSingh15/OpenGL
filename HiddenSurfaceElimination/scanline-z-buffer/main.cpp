#include<bits/stdc++.h>
#include <GL/glut.h>

using namespace std;
float xRot = 0.0;
float yRot = 0.0;


void init(){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("Scanline_ZBuffer");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void DrawCube(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, -200, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-150, -150, -150, 0,0,0, 0,0,1);

    glPushMatrix();

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3i(50, 50, 50);
    glVertex3i(-50, 50, 50);
    glVertex3i(-50, -50, 50);
    glVertex3i(50, -50, 50);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3i(50, 50, -50);
    glVertex3i(50, 50, 50);
    glVertex3i(50, -50, 50);
    glVertex3i(50, -50, -50);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3i(50, -50, -50);
    glVertex3i(-50, -50, -50);
    glVertex3i(-50, 50, -50);
    glVertex3i(50, 50, -50);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3i(-50, 50, 50);
    glVertex3i(-50, 50, -50);
    glVertex3i(-50, -50, -50);
    glVertex3i(-50, -50, 50);

    glColor3f(0.0, 1.0, 1.0);
    glVertex3i(50, 50, -50);
    glVertex3i(-50, 50, -50);
    glVertex3i(-50, 50, 50);
    glVertex3i(50, 50, 50);

    glColor3f(1.0, 0.0, 1.0);
    glVertex3i(50, -50, 50);
    glVertex3i(-50, -50, 50);
    glVertex3i(-50, -50, -50);
    glVertex3i(50, -50, -50);

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}


void SpecialKeys(int key, int x, int y)
{
   if (key == GLUT_KEY_UP)
       xRot -= 5.0;
   else if (key == GLUT_KEY_DOWN)
       xRot += 5.0;
   else if (key == GLUT_KEY_RIGHT)
       yRot -= 5.0;
   else if (key == GLUT_KEY_LEFT)
       yRot += 5.0;
   else
       exit(0);
   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   init();
   glutSpecialFunc(SpecialKeys);
   glutDisplayFunc(DrawCube);
   glutMainLoop();
    return 0;
}