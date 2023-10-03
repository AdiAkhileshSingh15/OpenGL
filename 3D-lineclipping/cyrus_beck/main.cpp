#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

struct vertex
{
    float x;
    float y;
    float z;
} p0, p1;

float max(float a, float b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

float min(float a, float b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

bool clipp = false;

float tin = 0, tout = 1;

void drawAxes()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0); // Red X-axis
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1000.0, 0.0, 0.0);

    glColor3f(0.0, 0.0, 0.0); // Green Y-axis
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1000.0, 0.0);

    glColor3f(0.0, 0.0, 0.0); // Blue Z-axis
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1000.0);
    glEnd();
}

void drawCube()
{
    glBegin(GL_LINE_STRIP);
    // Front face (Blue)
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glEnd();

    // Right face (Green)
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    // Top face (Red)
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glVertex3f(0, 1, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 1, 1);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glEnd();
}

void drawLine(float tin, float tout)
{
    float x0 = p0.x + tin * (p1.x - p0.x);
    float y0 = p0.y + tin * (p1.y - p0.y);
    float z0 = p0.z + tin * (p1.z - p0.z);
    float x1 = p0.x + tout * (p1.x - p0.x);
    float y1 = p0.y + tout * (p1.y - p0.y);
    float z1 = p0.z + tout * (p1.z - p0.z);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
    glEnd();
}

void Cyrus_Beck()
{
    float normal[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
    for (auto n : normal)
    {
        float numerator, denominator;
        if (n[0] < 0 || n[1] < 0 || n[2] < 0)
        {
            numerator = (float)(-p0.x * n[0]) + (-p0.y * n[1]) + (-p0.z * n[2]);
            denominator = (float)(p1.x - p0.x) * n[0] + (p1.y - p0.y) * n[1] + (p1.z - p0.z) * n[2];

            if (denominator < 0)
            {
                float k = numerator / denominator;

                tin = max(tin, k);
            }
            else if (denominator > 0)
            {
                float k = numerator / denominator;
                tout = min(tout, k);
            }
            else
            {
                if (numerator <= 0)
                {
                    tin = 1, tout = 0;
                    return;
                }
            }
        }
        else
        {
            denominator = (float)(p1.x - p0.x) * n[0] + (p1.y - p0.y) * n[1] + (p1.z - p0.z) * n[2];
            numerator = (float)(1 - p0.x) * n[0] + (1 - p0.y) * n[1] + (1 - p0.z) * n[2];

            if (denominator < 0)
            {
                float k = numerator / denominator;
                tin = max(k, tin);
            }
            else if (denominator > 0)
            {
                float k = numerator / denominator;
                tout = min(k, tout);
            }
            else
            {
                if (numerator <= 0)
                {
                    tin = 1, tout = 0;
                    return;
                }
            }
        }
    }
}

void Main()
{
    // Set background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the view matrix (camera)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 2.0,  // Eye position
              0.0, 0.0, 0.0,  // Look-at position
              0.0, 0.0, 1.0); // Up vector

    // Set up the perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

    // Draw the X, Y, Z axes...
    drawAxes();

    // Draw a 3D cube
    drawCube();

    drawLine(0, 1);

    glutSwapBuffers();
}

void Main2()
{
    // Set background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the view matrix (camera)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 2.0,  // Eye position
              0.0, 0.0, 0.0,  // Look-at position
              0.0, 0.0, 1.0); // Up vector

    // Set up the perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

    // Draw the X, Y, Z axes...
    drawAxes();

    // Draw a 3D cube
    drawCube();

    Cyrus_Beck();
    if (tin < tout)
        drawLine(tin, tout);

    glutSwapBuffers();
    tin = 0, tout = 1;
}

int main(int argc, char **argv)
{
    cout << "Enter the starting cooridnates of the line:\n";
    cin >> p0.x >> p0.y >> p0.z;
    cout << "Enter the ending coordinates of the line:\n";
    cin >> p1.x >> p1.y >> p1.z;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    // glutCreateWindow("3D Scene with Axes and Cube");

    // glutDisplayFunc(Main);

    glutCreateWindow("3D Scene");
    glutDisplayFunc(Main);

    glutCreateWindow("3D clipped Scene");
    glutDisplayFunc(Main2);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}
