#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

typedef double Matrix[4][4];
Matrix matComposite;
float finalCoordinates[8][3];

float initialCoordinates[8][3] = {
    {40, 40, -50},
    {90, 40, -50},
    {90, 90, -50},
    {40, 90, -50},
    {30, 30, 0},
    {80, 30, 0},
    {80, 80, 0},
    {30, 80, 0},
};

void Axes(void)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2s(-1000, 0);
    glVertex2s(1000, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2s(0, -1000);
    glVertex2s(0, 1000);
    glEnd();
}

void Draw(float a[8][3])
{
    int i;
    glColor3f(0.7, 0.4, 0.7);
    glBegin(GL_POLYGON);
    glVertex3s(a[0][0], a[0][1], a[0][2]);
    glVertex3s(a[1][0], a[1][1], a[1][2]);
    glVertex3s(a[2][0], a[2][1], a[2][2]);
    glVertex3s(a[3][0], a[3][1], a[3][2]);
    glEnd();
    i = 0;
    glColor3f(0.8, 0.6, 0.5);
    glBegin(GL_POLYGON);
    glVertex3s(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
    glVertex3s(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
    glVertex3s(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
    glVertex3s(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
    glEnd();
    glColor3f(0.2, 0.4, 0.7);
    glBegin(GL_POLYGON);
    glVertex3s(a[0][0], a[0][1], a[0][2]);
    glVertex3s(a[3][0], a[3][1], a[3][2]);
    glVertex3s(a[7][0], a[7][1], a[7][2]);
    glVertex3s(a[4][0], a[4][1], a[4][2]);
    glEnd();
    i = 1;
    glColor3f(0.5, 0.4, 0.3);
    glBegin(GL_POLYGON);
    glVertex3s(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
    glVertex3s(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
    glVertex3s(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
    glVertex3s(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
    glEnd();
    i = 2;
    glColor3f(0.5, 0.6, 0.2);
    glBegin(GL_POLYGON);
    glVertex3s(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
    glVertex3s(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
    glVertex3s(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
    glVertex3s(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
    glEnd();
    i = 4;
    glColor3f(0.7, 0.3, 0.4);
    glBegin(GL_POLYGON);
    glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
    glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
    glVertex3f(a[2 + i][0], a[2 + i][1], a[2 + i][2]);
    glVertex3f(a[3 + i][0], a[3 + i][1], a[3 + i][2]);
    glEnd();
}

void setIdentity(Matrix matIdentity)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matIdentity[i][j] = (i == j);
        }
    }
}

void translationFunction(double tx, double ty, double tz)
{
    matComposite[0][3] = tx;
    matComposite[1][3] = ty;
    matComposite[2][3] = tz;
}
void scaleFunction(double sx, double sy, double sz)
{
    matComposite[0][0] = sx;
    matComposite[1][1] = sy;
    matComposite[2][2] = sz;
}
void reflection3d(int x, int y, int z)
{
    matComposite[0][0] = x;
    matComposite[1][1] = y;
    matComposite[2][2] = z;
}
void rotateFunction(double theta, int x, int y, int z)
{
    if (x)
    {
        matComposite[1][1] = cos(theta);
        matComposite[1][2] = -sin(theta);
        matComposite[2][1] = sin(theta);
        matComposite[2][2] = cos(theta);
    }
    else if (y)
    {
        matComposite[0][0] = cos(theta);
        matComposite[0][2] = sin(theta);
        matComposite[3][0] = -sin(theta);
        matComposite[3][2] = cos(theta);
    }
    else
    {
        matComposite[0][0] = cos(theta);
        matComposite[0][1] = -sin(theta);
        matComposite[1][0] = sin(theta);
        matComposite[1][1] = cos(theta);
    }
}

void shearFunction(double shx, double shy, double shz, int x, int y, int z)
{
    if (x)
    {
        matComposite[1][0] = shy;
        matComposite[2][0] = shz;
    }
    else if (y)
    {
        matComposite[0][1] = shx;
        matComposite[2][1] = shz;
    }
    else
    {
        matComposite[0][2] = shx;
        matComposite[1][2] = shy;
    }
}

void TransformPoints(void)
{
    int i, k;
    float tmp;
    for (k = 0; k < 8; k++)
        for (i = 0; i < 3; i++)
            finalCoordinates[k][i] = matComposite[i][0] *
                                         initialCoordinates[k][0] +
                                     matComposite[i][1] *
                                         initialCoordinates[k][1] +
                                     matComposite[i][2] *
                                         initialCoordinates[k][2] +
                                     matComposite[i][3];
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Axes();
    glColor3f(1.0, 0.0, 0.0);
    Draw(initialCoordinates);
    setIdentity(matComposite);

    const int n = 8;
    int choice;

    cout << "Enter your choice for operation: " << endl;
    cout << "\t1 : Translate" << endl;
    cout << "\t2 : Shear" << endl;
    cout << "\t3 : Scale" << endl;
    cout << "\t4 : Rotate" << endl;
    cout << "\t5 : Reflection" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        double tx, ty, tz;
        cout << "Translation in X: ";
        cin >> tx;
        cout << "Translation in Y: ";
        cin >> ty;
        cout << "Translation in Z: ";
        cin >> tz;
        translationFunction(tx, ty, tz);
        TransformPoints();
        Draw(finalCoordinates);
        glFlush();
        break;
    }
    case 2:
    {
        double shx, shy, shz;
        cout << "Shear in X: ";
        cin >> shx;
        cout << "Shear in Y: ";
        cin >> shy;
        cout << "Shear in Z: ";
        cin >> shz;

        int c;
        cout << "Enter your choice for Shearing along axis:\n";
        cout << "1.along X-axis\n";
        cout << "2.along Y-axis\n";
        cout << "3.along Z-axis\n";
        cin >> c;

        if (c == 1)
        {
            shearFunction(shx, shy, shz, 1, 0, 0);
        }
        else if (c == 2)
        {
            shearFunction(shx, shy, shz, 0, 1, 0);
        }
        else
        {
            shearFunction(shx, shy, shz, 0, 0, 1);
        }
        TransformPoints();
        Draw(finalCoordinates);
        glFlush();
        break;
    }
    case 3:
    {
        double sx, sy, sz;
        cout << "Scaling in X: ";
        cin >> sx;
        cout << "Scaling in Y: ";
        cin >> sy;
        cout << "Scaling in Z: ";
        cin >> sz;

        scaleFunction(sx, sy, sz);
        TransformPoints();
        Draw(finalCoordinates);
        glFlush();
        break;
    }
    case 4:
    {
        double theta;

        cout << "Theta in radins ";
        cin >> theta;

        int c;
        cout << "Enter your choice for Rotation about axis:\n";
        cout << "1.about X-axis\n";
        cout << "2.about Y-axis\n";
        cout << "3.about Z-axis\n";
        cin >> c;

        if (c == 1)
        {
            rotateFunction(theta, 1, 0, 0);
        }
        else if (c == 2)
        {
            rotateFunction(theta, 0, 1, 0);
        }
        else
        {
            rotateFunction(theta, 0, 0, 1);
        }

        TransformPoints();
        Draw(finalCoordinates);
        glFlush();
        break;
    }
    case 5:
    {
        int c;
        cout << "Enter your choice for Reflection about axis:\n";
        cout << "1.parallel to X-axis\n";
        cout << "2.parallel to Y-axis\n";
        cout << "3.parallel to Z-axis\n";
        cin >> c;

        if (c == 1)
        {
            reflection3d(-1, 1, 1);
        }
        else if (c == 2)
        {
            reflection3d(1, -1, 1);
        }
        else
        {
            reflection3d(1, 1, -1);
        }

        TransformPoints();
        Draw(finalCoordinates);
        glFlush();
        break;
    }
    default:
        cout << "Invalid Input" << endl;
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1362, 750);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Geometric Transformations");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(-454.0, 454.0, -250.0, 250.0, -250.0, 250.0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutMainLoop();
}
