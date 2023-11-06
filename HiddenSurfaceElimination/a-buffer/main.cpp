#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;

void init(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("A_Bufffer");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, 1);
}

void circle(int x, int y, int r){
    glBegin(GL_POLYGON);
    float conv = acos(-1)/180;
    for(int i = 0; i<720; i++){
        float th = i*conv/2;
        glVertex2i(round(x + r*cos(th)), round(y + r*sin(th)));
    }
    glEnd();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1.0, 0.0, 0.0, 0.9);
    circle(30, 0, 60);
    glColor4f(0.0, 1.0, 0.0, 0.9);
    circle(-30, 0, 60);
    glColor4f(0.0, 0.0, 1.0, 0.9);
    circle(0, 52, 60);
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}