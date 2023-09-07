#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits.h>

using namespace std;
using ll = long long;
using ld = long double;

vector<pair<int, int>> m_vertices;
int x_min = 1e9, y_min = 1e9, x_max = INT_MIN, y_max = INT_MIN;

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

void scan(int y, vector<int> &intervals)
{

    for (int i = 0; i < int(m_vertices.size()) - 1; i++)
    {
        // auto [x1, y1] = m_vertices[i];
        // auto [x2, y2] = m_vertices[i+1];
        int x1 = m_vertices[i].first;
        int y1 = m_vertices[i].second;
        // auto [x2, y2] = m_vertices[i+1];
        int x2 = m_vertices[i + 1].first;
        int y2 = m_vertices[i + 1].second;

        if (y2 < y1)
        {
            swap(y1, y2);
            swap(x1, x2);
        }
        int N = m_vertices.size();
        if (y >= y1 and y <= y2)
        {
            int x = x1;
            if (y1 != y2)
            {
                x += ((x2 - x1) * (y - y1)) / (y2 - y1);
            }
            if (x <= x_max and x >= x_min)
            {
                if ((x == x2 && y2 == y))
                {
                    int x3 = m_vertices[(i + 2) % N].first;
                    int y3 = m_vertices[(i + 2) % N].second;
                    if ((y - y1) * (y - y3) < 0)
                    {
                    }
                    else
                    {
                        intervals.push_back(x);
                    }
                }
                else
                {
                    intervals.push_back(x);
                }
            }
        }
    }
}

void fill(int y, vector<int> &intervals)
{
    for (int i = 0; i < int(intervals.size()); i += 2)
    {
        for (int x = intervals[i]; x <= intervals[i + 1]; x++)
        {
            glVertex2i(x, y);
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    for (int y = y_min; y < y_max; y++)
    {
        vector<int> intervals;
        scan(y, intervals);
        sort(intervals.begin(), intervals.end());
        fill(y, intervals);
    }

    glEnd();
    glFlush();
}

void take_input(void)
{
    m_vertices.push_back({250, 200});
    m_vertices.push_back({150, 300});
    m_vertices.push_back({250, 400});
    m_vertices.push_back({350, 300});
    // m_vertices.push_back({75,200});
    // m_vertices.push_back({200,0});
    m_vertices.push_back(m_vertices[0]);
}

void calc(void)
{
    for (auto it : m_vertices)
    {
        int x = it.first;
        int y = it.second;
        x_min = min(x_min, x);
        x_max = max(x_max, x);
        y_max = max(y_max, y);
        y_min = min(y_min, y);
    }
}

int main(int argc, char **argv)
{

    take_input();
    calc();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Scan Fill");
    myInit();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}