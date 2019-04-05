#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <GL/glut.h>

 
#define GL_WIN_SIZE_X 800
#define GL_WIN_SIZE_Y 800
#define ANGLE_INITIAL 90.0f

using namespace std;

GLint winID=0;

double rotate_value=ANGLE_INITIAL;
float posX = 0.0f, posY = 0.0f, angle = 0.0f;    
float velocity = 0.5f;

float zoom_value=-5.0f;
float zoom_steps=0.1f;


float x_offset=0.0f;
float y_offset=0.0f;






void keyPress(int key, int xpos, int ypos)
{

  if (key == GLUT_KEY_UP) {    
    posX +=  (cos( rotate_value )) * velocity;
    posY += -(sin( rotate_value)) * velocity;
  }
  else if (key == GLUT_KEY_DOWN) {
    posX -=  (cos( rotate_value ))  * velocity;
    posY -= -(sin( rotate_value  )) * velocity;
  }
  else if (key == GLUT_KEY_RIGHT) {
    if (rotate_value == 360) rotate_value=.0f; 
    rotate_value+=0.5f;
  }
  else if (key == GLUT_KEY_LEFT) {
    if (rotate_value == 0) rotate_value=360; 
    rotate_value-=0.5f;
  }

  
  glutPostRedisplay();
}

void init()
{
  glClearColor(0.0f, 0.0f, 0.0f, zoom_value);    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-GL_WIN_SIZE_X, GL_WIN_SIZE_X, -GL_WIN_SIZE_Y, GL_WIN_SIZE_Y);
}


void handleResize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,                  
      (double)w / (double)h, 
      0.0,                   
      1.0);                
}

static void drawline(float x1, float y1, float x2, float y2)
{
  glLineWidth(2.0);
  glBegin (GL_LINES);
  glVertex3f(x1, y1, zoom_value);
  glVertex3f(x2, y2, zoom_value);
  glEnd();
}


static void drawGrid()
{
  float size_w = GL_WIN_SIZE_X;
  float size_h = GL_WIN_SIZE_Y;
  float size_offset = 0.8;

  glColor3f(1.0, 1.0, 1.0);
  glLoadIdentity();
  
  glTranslatef(posX, posY, zoom_value); 
    glRotatef(rotate_value, 0.0f, 0.0f, 1.0f);   //Z
  //glTranslatef(0.0f, posY, zoom_value); 
  

  glLineWidth(1.5);
  for (float x1=-size_w; x1<size_w; x1 += size_offset)
  {
    drawline(size_w, x1, -size_w, x1);
  }
  for (float y1=-size_h; y1<size_h; y1 += size_offset)
  {
    drawline(y1,  size_h,  y1, -size_h);
  }

}

static void drawObj()
{
  glColor3d(1.0, 0.0, 0.0);
  glLoadIdentity();

  glTranslatef(-posX, -posY, 0.0f); 
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex3f( posX,     posY,    zoom_value);
    glEnd();

  
}




void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  drawGrid();
  drawObj();
  glFlush();
}


int main(int argc,char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);

  winID = glutCreateWindow("Test");

  init();

  glutDisplayFunc(display);
  glutSpecialFunc(keyPress);
  glutReshapeFunc(handleResize);

  glutMainLoop();


}