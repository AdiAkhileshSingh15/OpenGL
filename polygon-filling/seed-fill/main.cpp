#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <queue>
#include <algorithm>

using namespace std;
using ll = long long;
using ld = long double;

bool vis[5001][5001];
int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};
int start_x, start_y;

vector<pair<int, int>> m_vertices;

void floodfill(int x, int y)
{
    if (vis[x][y])
        return;
    vis[x][y] = 1;
    glVertex2i(x, y);
    for (int i = 0; i < 4; i++)
    {
        floodfill(x + dx[i], y + dy[i]);
    }
}

void line(int X0, int Y0, int X1, int Y1)
{

    float dx = X1 - X0;
    float dy = Y1 - Y0;

    int steps = abs(dx);
    if (abs(dy) > steps)
    {
        steps = abs(dy);
    }

    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    ld X = X0;
    ld Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
        int X1 = X;
        int Y1 = Y;
        glVertex2i(X1, Y1);
        vis[X1][Y1] = 1;
        X += Xinc;
        Y += Yinc;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int i = 0; i < m_vertices.size() - 1; i++)
    {
        // auto [x1, y1] = m_vertices[i];
        int x1 = m_vertices[i].first;
        int y1 = m_vertices[i].second;
        // auto [x2, y2] = m_vertices[i+1];
        int x2 = m_vertices[i + 1].first;
        int y2 = m_vertices[i + 1].second;
        line(x1, y1, x2, y2);
    }
    floodfill(start_x, start_y);
    glEnd();
    glFlush();
}

void take_input(void)
{
    int n = 4;
    m_vertices.push_back({100, 100});
    m_vertices.push_back({100, 400});
    m_vertices.push_back({400, 400});
    m_vertices.emplace_back(400, 100);

    start_x = 175, start_y = 150;
    m_vertices.push_back(m_vertices[0]);
}

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // glColor3f(0.0, 0.0, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

int main(int argc, char **argv)
{

    take_input();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Flood Fill");
    myInit();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}