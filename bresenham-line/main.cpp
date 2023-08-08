#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

int xa, ya, xb, yb;

void plotPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void display() {
    int x, y, dx, dy, p;
    dx = abs(xb-xa);
    dy = abs(yb-ya);
    x = xa, y = ya;
    p = 2*dy - dx;
    
    plotPoint(x, y);

    for (int k = 0; k < dx; k++) {
        if (p < 0) {
            plotPoint(x+1, y);
            x = x+1;
            p = p + 2*dy;
        }
        else {
            plotPoint(x+1, y+1);
            x = x+1, y = y+1;
            p = p + 2*dy - 2*dx;
        }
    }

    glFlush();
}

void myInit(void) {
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv) {

    std::cout << "Value of xa : ";
    std::cin >> xa;
    std::cout << "Value of ya : ";
    std::cin >> ya;
    std::cout << "Value of xb : ";
    std::cin >> xb;
    std::cout << "Value of yb : ";
    std::cin >> yb;

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line Drawing: ");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();

    return 0;
}