// Window to View port Transformations
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

float Pw[3][10], Pv[3][10], T[3][3], T1[3][3], T2[3][3], S[3][3];
float Xwmin, Xwmax, Ywmin, Ywmax;
float Xvmin, Xvmax, Yvmin, Yvmax;
float sx, sy;

void matrixMult1(float A[3][3], float B[3][3], float C[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            C[j][i] = A[j][0] * B[0][i] + A[j][1] * B[1][i] + A[j][2] * B[2][i];
}

void matrixMult2(float A[3][3], float B[3][10], float C[3][10])
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 3; j++)
            C[j][i] = A[j][0] * B[0][i] + A[j][1] * B[1][i] + A[j][2] * B[2][i];
}

void display1()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Window
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(Xwmin, Ywmin);
    glVertex2f(Xwmin, Ywmax);
    glVertex2f(Xwmax, Ywmax);
    glVertex2f(Xwmax, Ywmin);
    glEnd();

    // Shapes
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(Pw[0][0], Pw[1][0]);
    glVertex2f(Pw[0][1], Pw[1][1]);
    glVertex2f(Pw[0][2], Pw[1][2]);
    glVertex2f(Pw[0][3], Pw[1][3]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(Pw[0][4], Pw[1][4]);
    glVertex2f(Pw[0][5], Pw[1][5]);
    glVertex2f(Pw[0][6], Pw[1][6]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(Pw[0][7], Pw[1][7]);
    glVertex2f(Pw[0][8], Pw[1][8]);
    glVertex2f(Pw[0][9], Pw[1][9]);
    glEnd();

    glFlush();
}

void display2()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    matrixMult2(T, Pw, Pv);

    // Viewport
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(Xvmin, Yvmin);
    glVertex2f(Xvmin, Yvmax);
    glVertex2f(Xvmax, Yvmax);
    glVertex2f(Xvmax, Yvmin);
    glEnd();

    // Shapes
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(Pv[0][0], Pv[1][0]);
    glVertex2f(Pv[0][1], Pv[1][1]);
    glVertex2f(Pv[0][2], Pv[1][2]);
    glVertex2f(Pv[0][3], Pv[1][3]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(Pv[0][4], Pv[1][4]);
    glVertex2f(Pv[0][5], Pv[1][5]);
    glVertex2f(Pv[0][6], Pv[1][6]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(Pv[0][7], Pv[1][7]);
    glVertex2f(Pv[0][8], Pv[1][8]);
    glVertex2f(Pv[0][9], Pv[1][9]);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    // Some random shapes

    // Rectangle
    Pw[0][0] = 110;
    Pw[1][0] = 110;
    Pw[2][0] = 1;
    Pw[0][1] = 110;
    Pw[1][1] = 200;
    Pw[2][1] = 1;
    Pw[0][2] = 250;
    Pw[1][2] = 200;
    Pw[2][2] = 1;
    Pw[0][3] = 250;
    Pw[1][3] = 110;
    Pw[2][3] = 1;

    // Triangle 1
    Pw[0][4] = 300;
    Pw[1][4] = 150;
    Pw[2][4] = 1;
    Pw[0][5] = 350;
    Pw[1][5] = 300;
    Pw[2][5] = 1;
    Pw[0][6] = 400;
    Pw[1][6] = 200;
    Pw[2][6] = 1;

    // Triangle 2
    Pw[0][7] = 150;
    Pw[1][7] = 300;
    Pw[2][7] = 1;
    Pw[0][8] = 50;
    Pw[1][8] = 400;
    Pw[2][8] = 1;
    Pw[0][9] = 250;
    Pw[1][9] = 350;
    Pw[2][9] = 1;

    Xwmin = 100;
    Xwmax = 450;
    Ywmin = 100;
    Ywmax = 470;
    Xvmin = 200;
    Xvmax = 400;
    Yvmin = 200;
    Yvmax = 400;

    //    cout<<"Enter Window Coordinates (Xwmin, Xwmax, Ywmin, Ywmax) :\n";
    //    cin>>Xwmin>>Xwmax>>Ywmin>>Ywmax;
    //    cout<<"Enter Viewport Coordinates (Xvmin, Xvmax, Yvmin, Yvmax) :\n";
    //    cin>>Xvmin>>Xvmax>>Yvmin>>Yvmax;

    sx = (Xvmax - Xvmin) / (Xwmax - Xwmin);
    sy = (Yvmax - Yvmin) / (Ywmax - Ywmin);

    T1[0][0] = 1;
    T1[0][1] = 0;
    T1[0][2] = -Xwmin;
    T1[1][0] = 0;
    T1[1][1] = 1;
    T1[1][2] = -Ywmin;
    T1[2][0] = 0;
    T1[2][1] = 0;
    T1[2][2] = 1;

    S[0][0] = sx;
    S[0][1] = 0;
    S[0][2] = 0;
    S[1][0] = 0;
    S[1][1] = sy;
    S[1][2] = 0;
    S[2][0] = 0;
    S[2][1] = 0;
    S[2][2] = 1;

    T2[0][0] = 1;
    T2[0][1] = 0;
    T2[0][2] = Xvmin;
    T2[1][0] = 0;
    T2[1][1] = 1;
    T2[1][2] = Yvmin;
    T2[2][0] = 0;
    T2[2][1] = 0;
    T2[2][2] = 1;

    T[0][0] = 1;
    T[0][1] = 0;
    T[0][2] = 0;
    T[1][0] = 0;
    T[1][1] = 1;
    T[1][2] = 0;
    T[2][0] = 0;
    T[2][1] = 0;
    T[2][2] = 1;

    float temp[3][3];
    matrixMult1(T2, S, temp);
    matrixMult1(temp, T1, T);

    //    T[0][0] = sx; T[0][1] = 0; T[0][2] = Xvmin - sx * Xwmin;
    //    T[1][0] = 0; T[1][1] = sy; T[1][2] = Yvmin - sy * Ywmin;
    //    T[2][0] = 0; T[2][1] = 0; T[2][2] = 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Window");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display1);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("View port");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display2);

    glutMainLoop();
    return 0;
}