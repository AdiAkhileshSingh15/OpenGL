#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

// g++ *.cpp -lGL -lGLU -lglut

struct Point
{
    float x = 0.0, y = 0.0;

    Point(float X = 0.0, float Y = 0.0): x(X), y(Y) {}

    Point operator + (const Point &p)
    {
        Point res;
        res.x = x + p.x;
        res.y = y + p.y;
        return res;
    }

    Point operator - (const Point &p)
    {
        Point res;
        res.x = x - p.x;
        res.y = y - p.y;
        return res;
    }

    Point operator * (const float &f)
    {
        Point res;
        res.x = x * f;
        res.y = y * f;
        return res;
    }
};

int factorial(int n)
{
    return (n==1 || n==0) ? 1: n * factorial(n - 1);
}

int nCr(int n, int r)
{
    return factorial(n) / (factorial(n-r) * factorial(r));
}

int n;
float x, y;
vector<int> C;
vector<Point> P;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float t, B[n+1];

    glBegin(GL_POINTS);
        for(t=0.0f ; t<=1.0f ; t += 0.001f)
        {
            Point Pt = {0.0, 0.0};

            for(int i=0; i<=n; i++)
            {
                B[i] = C[i] * pow(1-t, n-i) * pow(t, i);
                Pt = Pt + P[i]*B[i];
            }

            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(Pt.x, Pt.y);
        }
    glEnd();

    glPointSize(3);
    glBegin(GL_POINTS);
        for(int i=0; i<=n; i++)
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(P[i].x, P[i].y);
        }
    glEnd();
    glPointSize(1);

    for(int i=0; i<n; i++)
    {
        glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(P[i].x, P[i].y);
            glVertex2f(P[i+1].x, P[i+1].y);
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv)
{
    cout<<"Enter the order of Bezier Curve: ";
    cin>> n;

    cout<<"Enter the set of Control Points\n";
    for(int i=0; i<=n; i++)
    {
        cout<<"P"<<i<<": ";
        cin>> x >> y;
        P.push_back(Point(x, y));
    }

    for(int i=0; i<=n; i++)
        C.push_back(nCr(n, i));

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bezier Curve");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
