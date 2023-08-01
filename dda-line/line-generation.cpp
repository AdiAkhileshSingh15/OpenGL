#include<stdlib.h>
#include<stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

float a, b, c, d;

void display(void) {
  float dy, dx, step, x, y, k, Xin, Yin;
  dx = b - a;
  dy = d - c;
  if (abs(dx) > abs(dy)) {
    step = abs(dx);
  } else
    step = abs(dy);
  Xin = dx / step;
  Yin = dy / step;
  x = a;
  y = c;
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
  for (k = 1; k <= step; k++) {
    x = x + Xin;
    y = y + Yin;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
  }
  glFlush();
}

void myInit (void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

// run using
// g++ *.cpp -lGL -lGLU -lglut

int main(int argc, char ** argv) {

  printf("Value of a : ");
  scanf("%f", & a);
  printf("Value of c : ");
  scanf("%f", & c);
  printf("Value of b : ");
  scanf("%f", & b);
  printf("Value of d : ");
  scanf("%f", & d);

  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("");
  myInit ();
  glutDisplayFunc(display);
  glutMainLoop();
}