#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

typedef double Matrix[4][4];
Matrix matComposite;
float finalCoordinates[8][3];
double theta, x1, x2, y2, z1, z2, x, y, z;
double y_1;
double a, b, c, abc;

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

void DrawArbLine()
{
    glBegin(GL_LINES);
    glVertex3s(x1 - a * 500, y_1 - b * 500, z1 - c * 500);
    glVertex3s(x2 + a * 500, y2 + b * 500, z2 + c * 500);
    glEnd();
}

void DrawParallelLine()
{
    glBegin(GL_LINES);
    glVertex3s(-1000, y, z);
    glVertex3s(1000, y, z);
    glEnd();
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
    cout << "\t1 : Rotation of a Cube about a line parallel to x-axis" << endl;
    cout << "\t2 : Rotation of a Cube about an arbitrary line " << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "Enter the angle of rotation: " << endl;
        cin >> theta;
        cout << "Enter the y and z coordinates through which line parallel to x-axis passes" << endl;
        cin >> y >> z;

        DrawParallelLine();

        translationFunction(0, -y, -z);
        TransformPoints();
        rotateFunction(theta, 1, 0, 0);
        TransformPoints();
        translationFunction(0, y, z);
        TransformPoints();

        Draw(finalCoordinates);
        glFlush();
        break;
    }
    case 2:
    {
        double theta1, theta2;

        cout << "Enter the angle of rotation: " << endl;
        cin >> theta;
        cout << "Enter the (two) x,y,z coordinates through which line passes" << endl;
        cin >> x1;
        cin >> y_1;
        cin >> z1;
        cin >> x2;
        cin >> y2;
        cin >> z2;
        // cin>>x2>>y2>>z2;
        //	new coordinates for p2
        a = (x2 - x1);
        b = y2 - y_1;
        c = z2 - z1;
        abc = sqrt(a * a + b * b + c * c);
        //	cosines for angle of line
        a /= abc;
        b /= abc;
        c /= abc;
        //	theta1 is angle from z axis in y-z projection
        theta1 = acos((double)c / (double)sqrt(b * b + c * c));
        //	theta2 is angle from xy plane --- azimuthal angle
        theta2 = acos(sqrt(b * b + c * c));

        DrawArbLine();

        translationFunction(-x1, -y_1, -z1);
        TransformPoints();
        rotateFunction(theta1, 1, 0, 0);
        TransformPoints();
        rotateFunction(theta2, 1, 0, 0);
        TransformPoints();
        rotateFunction(theta, 0, 0, 1);
        TransformPoints();
        rotateFunction(-theta2, 1, 0, 0);
        TransformPoints();
        rotateFunction(-theta1, 1, 0, 0);
        TransformPoints();
        translationFunction(x1, y_1, z1);
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
