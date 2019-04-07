#include <iostream>
#include <GL/glut.h>
using namespace std;

int cx = 0;
int cy = 0;
int cz = 0;

int cn;

void theCube() {

 glPushMatrix();
 //glLoadIdentity();
 glColor3f(1, 1, 1);
 glTranslatef(cx, cy, cz);
 glutSolidCube(1);
 glPopMatrix();

}


void drawGrid() {

 int i;
 for (i = 0; i < 40; i++) {

  glPushMatrix();
  //glLoadIdentity();

  if (i < 20)
    glTranslatef(0, 0, i); 
  else{ 
    
    glTranslatef(i - 20, 0, 0);
    glRotatef(-90, 0, 1, 0);

  }

  
  glBegin(GL_LINES);
  glColor3f(1, 1, 1); 
  glLineWidth(1);
  glVertex3f(0, 0.0, 0); 
  glVertex3f(19, 0.0, 0);
  glEnd();
  glPopMatrix();
  
 }

}


void display() {

 glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glTranslatef(-15, 0, -50);
 glRotatef(40, 1, 1, 0);

 drawGrid();

 theCube();
 glutSwapBuffers();
}


void init() {

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 //gluPerspective(40, 1.0f, 0.0f, 100);
 glMatrixMode(GL_MODELVIEW);
 //glEnable(GL_DEPTH_TEST);
 glClearColor(0.2, 0.2, 0.2, 1);

}

void keyboard(unsigned char key, int x, int y) {

 if (key == 'w') {
  cz -= 1;
 }

 if (key == 's') {
  cz += 1;
 }

 if (key == 'a') {
  cx -= 1;
 }

 if (key == 'd') {
  cx += 1;
 }

 if (key == 'q') {
  cy += 1;
 }

 if (key == 'e') {
  cy -= 1;
 }

 glutPostRedisplay();
}

void mouseFunc(int x, int y){

}

int main(int argc, char **argv) {

 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE);
 glutInitWindowSize(800, 600);
 glutCreateWindow("test");

 init();
 glutDisplayFunc(display);

 glutKeyboardFunc(keyboard);
 glutMotionFunc(mouseFunc);


 glutMainLoop();

 return 0;


}
