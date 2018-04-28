#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
    #include <GLUT/glut.h>
#elif __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glext.h>
    #include <GL/glut.h>
#endif 

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#define PI 3.14159265


GLdouble eyeX = 0, eyeY = 0.4, eyeZ = 11, phi = PI/2, theta = 0, radius = 10;
GLdouble centerX =0, centerY = 0, centerZ = 0;
GLfloat doorAngle, angle, fAspect;
bool openingDoor = false; 
double inc = 2*PI/180;
bool isRotate;

GLUquadricObj *obj = gluNewQuadric();

void drawColumnY(float x, float y, float z, float radius, float size){
  glPushMatrix();
  glRotatef(-90, 1.0, 0.0, 0.0 );
  glTranslatef(x, y, z);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluCylinder(obj, radius, radius, size, 100, 100);
  glPopMatrix();
}

void drawColumnZ(float x, float y, float z, float radius, float size){
  glPushMatrix();
  glTranslatef(x, y, z);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluCylinder(obj, radius, radius, size, 100, 100);
  glPopMatrix();
}

void drawDiskXY(float x, float y, float z, float radiusIn, float radiusOut){
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(-90, 0.0, 1.0, 0.0 );
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glPopMatrix();
}

void drawDiskZY(float x, float y, float z, float radiusIn, float radiusOut){
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(-90, 0.0, 0.0, 1.0 );
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glPopMatrix();
}

void drawSemiDiskXY(float x, float y, float z, float radiusIn, float radiusOut){
  GLdouble eqnBottom[4] = {0.0, 1.0, 0.0, 0};
  
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(-90, 0.0, 1.0, 0.0 );
  glClipPlane (GL_CLIP_PLANE0, eqnBottom);
  glEnable (GL_CLIP_PLANE0);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glDisable(GL_CLIP_PLANE0);
  glPopMatrix();
}

void drawSemiDiskZY(float x, float y, float z, float radiusIn, float radiusOut){
  GLdouble eqnBottom[4] = {0.0, 1.0, 0.0, 0};

  glPushMatrix();
  glTranslatef(x, y, z);

  glClipPlane (GL_CLIP_PLANE0, eqnBottom);
  glEnable (GL_CLIP_PLANE0);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glDisable(GL_CLIP_PLANE0);
  glPopMatrix();
}

void drawDoor(float angle){
  glPushMatrix();    
  glRotatef(angle, 0.0, 1.0, 0.0);
  glTranslatef(0,0,0.1);
  glScalef(0.001, 0.2, 0.1);

  glutSolidCube(1.0f);
  glPopMatrix();
}

void drawSemiSphere(float radius) {
    glBegin(GL_POINTS); 
        for(float thetaT = 0; thetaT < 2*PI; thetaT += 0.01) {
            for(float phiT = 0; phiT < PI/2; phiT += 0.01) {
                glVertex3f(radius*sin(thetaT)*sin(phiT), radius*cos(phiT), radius*cos(thetaT)*sin(phiT));
            }
        }
    glEnd();
}


// Função callback chamada para fazer o desenho
void Display(void) {
  glPushMatrix();

  glRotatef(-90, 0.0, 1.0, 0.0);

    //Translação para câmera 2
    //glTranslatef(10,0,0);

  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glScalef(3.5,3.5,2);

      //Chão
  glPushMatrix();glBegin(GL_POLYGON);    
  glColor3f(0.4, 0.4, 0.4); 
  glVertex3f(1.0, 0.0, -1.0);      
  glVertex3f(1.0, 0.0, 1.0);      
  glVertex3f(-1.0, 0.0, 1.0);      
  glVertex3f(-1.0, 0.0, -1.0);      
  glEnd();glPopMatrix();


      //Andar 1
      //Parede direita - andar 1
      glColor3f(0.96, 0.87, 0.7); //https://sistemas.riopomba.ifsudestemg.edu.br/dcc/materiais/926330044_Cores.pdf
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(-1.0, 0.75 ,0.5);
      glVertex3f(-1.0, 0.0 ,0.5);
      glVertex3f(0.6, 0.0, 0.5);
      glVertex3f(0.6, 0.75 ,0.5);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(-1.0, 0.75, 0.49);
      glVertex3f(-1.0, 0.0, 0.49);
      glVertex3f(0.6, 0.0, 0.49);
      glVertex3f(0.6, 0.75, 0.49);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 1
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 0.75,  -0.5 );
      glVertex3f(-1.0, 0.75, -0.5);
      glVertex3f(-1.0, 0.0, -0.5);
      glVertex3f(0.6, 0.0 ,-0.5);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 0.75 , -0.49);
      glVertex3f(-1.0, 0.75 ,-0.49);
      glVertex3f(-1.0, 0.0, -0.49);
      glVertex3f(0.6, 0.0, -0.49);
      glEnd();glPopMatrix();

      //Parede fundo - andar 1
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(-1.0, 0.75, -0.5);
      glVertex3f(-1.0, 0.75, 0.5);
      glVertex3f(-1.0, 0.0, 0.5);
      glVertex3f(-1.0, 0.0, -0.5);
      glEnd();glPopMatrix();

      glColor3f(0.69, 0.93, 0.93);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(-0.99, 0.75, -0.5);
      glVertex3f(-0.99, 0.75, 0.5);
      glVertex3f(-0.99, 0.0, 0.5);
      glVertex3f(-0.99, 0.0, -0.5);
      glEnd();glPopMatrix();

      // Parede frente - andar 1 - superior
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 0.75, -0.5);
      glVertex3f(0.6, 0.75, 0.5);
      glVertex3f(0.6, 0.2, 0.5);
      glVertex3f(0.6, 0.2, -0.5);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.59, 0.75, -0.5);
      glVertex3f(0.59, 0.75, 0.5);
      glVertex3f(0.59, 0.2, 0.5);
      glVertex3f(0.59, 0.2, -0.5);
      glEnd();glPopMatrix();

      //Parede frente - andar 1 - inferior esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 0.2, 0.4);
      glVertex3f(0.6, 0.2, 0.5);
      glVertex3f(0.6, 0.0, 0.5);
      glVertex3f(0.6, 0.0, 0.4);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.59, 0.2, 0.4);
      glVertex3f(0.59, 0.2, 0.5);
      glVertex3f(0.59, 0.0, 0.5);
      glVertex3f(0.59, 0.0, 0.4);
      glEnd();glPopMatrix();

       //Parede frente - andar 1 - inferior direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 0.2, -0.4);
      glVertex3f(0.6, 0.2, -0.5);
      glVertex3f(0.6, 0.0, -0.5);
      glVertex3f(0.6, 0.0, -0.4);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.59, 0.2, -0.4);
      glVertex3f(0.59, 0.2, -0.5);
      glVertex3f(0.59, 0.0, -0.5);
      glVertex3f(0.59, 0.0, -0.4);
      glEnd();glPopMatrix();
      
      //Parede frente - andar 1 - inferior centro direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 0.2, -0.2);
      glVertex3f(0.6, 0.2, -0.1);
      glVertex3f(0.6, 0.0, -0.1);
      glVertex3f(0.6, 0.0, -0.2);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.59, 0.2, -0.2);
      glVertex3f(0.59, 0.2, -0.1);
      glVertex3f(0.59, 0.0, -0.1);
      glVertex3f(0.59, 0.0, -0.2);
      glEnd();glPopMatrix();

      //Parede frente - andar 1 - inferior centro esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 0.2, 0.2);
      glVertex3f(0.6, 0.2, 0.1);
      glVertex3f(0.6, 0.0, 0.1);
      glVertex3f(0.6, 0.0, 0.2);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.59, 0.2, 0.2);
      glVertex3f(0.59, 0.2, 0.1);
      glVertex3f(0.59, 0.0, 0.1);
      glVertex3f(0.59, 0.0, 0.2);
      glEnd();glPopMatrix();

      //Interior
      //Essas paredes são uma translação da frente da catedral, a entrada
      //Parede interior - superior
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.4, 0.4, -0.5);
      glVertex3f(0.4, 0.4, 0.5);
      glVertex3f(0.4, 0.2, 0.5);
      glVertex3f(0.4, 0.2, -0.5);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.39, 0.4, -0.5);
      glVertex3f(0.39, 0.4, 0.5);
      glVertex3f(0.39, 0.2, 0.5);
      glVertex3f(0.39, 0.2, -0.5);
      glEnd();glPopMatrix();

      //Parede interior - inferior esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.4, 0.2, 0.4);
      glVertex3f(0.4, 0.2, 0.5);
      glVertex3f(0.4, 0.0, 0.5);
      glVertex3f(0.4, 0.0, 0.4);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.39, 0.2, 0.4);
      glVertex3f(0.39, 0.2, 0.5);
      glVertex3f(0.39, 0.0, 0.5);
      glVertex3f(0.39, 0.0, 0.4);
      glEnd();glPopMatrix();

       //Parede interior - inferior direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.4, 0.2, -0.4);
      glVertex3f(0.4, 0.2, -0.5);
      glVertex3f(0.4, 0.0, -0.5);
      glVertex3f(0.4, 0.0, -0.4);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.39, 0.2, -0.4);
      glVertex3f(0.39, 0.2, -0.5);
      glVertex3f(0.39, 0.0, -0.5);
      glVertex3f(0.39, 0.0, -0.4);
      glEnd();glPopMatrix();
      
      //Parede interior - inferior centro direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.4, 0.2, -0.2);
      glVertex3f(0.4, 0.2, -0.1);
      glVertex3f(0.4, 0.0, -0.1);
      glVertex3f(0.4, 0.0, -0.2);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.39, 0.2, -0.2);
      glVertex3f(0.39, 0.2, -0.1);
      glVertex3f(0.39, 0.0, -0.1);
      glVertex3f(0.39, 0.0, -0.2);
      glEnd();glPopMatrix();

      //Parede frente - inferior centro esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.4, 0.2, 0.2);
      glVertex3f(0.4, 0.2, 0.1);
      glVertex3f(0.4, 0.0, 0.1);
      glVertex3f(0.4, 0.0, 0.2);
      glEnd();glPopMatrix();
      glColor3f(0.96, 0.87, 0.87);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.39, 0.2, 0.2);
      glVertex3f(0.39, 0.2, 0.1);
      glVertex3f(0.39, 0.0, 0.1);
      glVertex3f(0.39, 0.0, 0.2);
      glEnd();glPopMatrix();

      //Parede interior corredor direita 
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.59, 0.75, 0.15);
      glVertex3f(0.39, 0.75, 0.15);
      glVertex3f(0.39, 0.0, 0.15);
      glVertex3f(0.59, 0.0, 0.15);
      glEnd();glPopMatrix();
      
      //Parede interior corredor esquerda 
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.59, 0.75, -0.15);
      glVertex3f(0.39, 0.75, -0.15);
      glVertex3f(0.39, 0.0, -0.15);
      glVertex3f(0.59, 0.0, -0.15);
      glEnd();glPopMatrix();

      //Varanda - andar 1 - camada 1 // Falta fechar os lados
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.605, 0.4, -0.505);
      glVertex3f(0.4, 0.4, -0.505);
      glVertex3f(0.4, 0.4, 0.505);
      glVertex3f(0.605, 0.4, 0.505);
      glEnd();glPopMatrix();

      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.605, 0.405, -0.505);
      glVertex3f(0.4, 0.405, -0.505);
      glVertex3f(0.4, 0.405, 0.505);
      glVertex3f(0.605, 0.405, 0.505);
      glEnd();glPopMatrix();
      
      //Varanda - andar 1 - camada 2 // Falta fechar os lados
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.61,  0.405, -0.51);
      glVertex3f(0.4, 0.405,  -0.51);
      glVertex3f(0.4, 0.405, 0.51);
      glVertex3f(0.61, 0.405, 0.51);
      glEnd();glPopMatrix();

      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.61, 0.41, -0.51);
      glVertex3f(0.4, 0.41,  -0.51);
      glVertex3f(0.4, 0.41, 0.51);
      glVertex3f(0.61, 0.41, 0.51);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 1 - camada 1 // Falta fechar os lados
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.605, 0.75,  -0.505);
      glVertex3f(-1.005, 0.75, -0.505);
      glVertex3f(-1.005, 0.75, 0.505);
      glVertex3f(0.605, 0.75, 0.505);
      glEnd();glPopMatrix();

      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.605, 0.755,  -0.505);
      glVertex3f(-1.005, 0.755, -0.505);
      glVertex3f(-1.005, 0.755, 0.505);
      glVertex3f(0.605, 0.755, 0.505);
      glEnd();glPopMatrix();
      
      //Teto - andar 1 - camada 2 // Falta fechar os lados
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.61, 0.755, -0.51);
      glVertex3f(-1.01, 0.755, -0.51);
      glVertex3f(-1.01, 0.755, 0.51);
      glVertex3f(0.61, 0.755, 0.51);
      glEnd();glPopMatrix();

      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.61, 0.76, -0.51);
      glVertex3f(-1.01, 0.76, -0.51);
      glVertex3f(-1.01, 0.76, 0.51);
      glVertex3f(0.61, 0.76, 0.51);
      glEnd();glPopMatrix();
      
      //Andar 2  
      //Parede direita - andar 2
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 1.0, 0.5);
      glVertex3f(0.3, 1.0, 0.5);
      glVertex3f(0.3, 0.76, 0.5);
      glVertex3f(0.6, 0.76, 0.5);
      glEnd();glPopMatrix();

       //Parede esquerda - andar 2
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 1.0, -0.5);
      glVertex3f(0.3, 1.0, -0.5);
      glVertex3f(0.3, 0.76, -0.5);
      glVertex3f(0.6, 0.76, -0.5);
      glEnd();glPopMatrix();
      
      //Parede fundo - andar 2
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.3, 1.0, -0.5);
      glVertex3f(0.3, 1.0, 0.5);
      glVertex3f(0.3, 0.76, 0.5);
      glVertex3f(0.3, 0.76, -0.5);
      glEnd();glPopMatrix();

      //Parede frente - andar 2
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.6, 1.0, -0.5);
      glVertex3f(0.6, 1.0, 0.5);
      glVertex3f(0.6, 0.76, 0.5);
      glVertex3f(0.6, 0.76, -0.5);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 2 - camada 1 // Falta fechar os lados
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.61, 1.0, -0.51);
      glVertex3f(0.28, 1.0, -0.5);
      glVertex3f(0.28, 1.0, 0.5);
      glVertex3f(0.61, 1.0, 0.51);
      glEnd();glPopMatrix();

      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.61, 1.01, -0.51);
      glVertex3f(0.28, 1.01, -0.5);
      glVertex3f(0.28, 1.01, 0.5);
      glVertex3f(0.61, 1.01, 0.51);
      glEnd();glPopMatrix();

      //Andar 3
      //Parede direita - andar 3 - torre esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.56, 1.01, 0.48);
      glVertex3f(0.30, 1.01, 0.48);
      glVertex3f(0.30, 1.08, 0.48);
      glVertex3f(0.56, 1.08, 0.48);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 3 - torre esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.56, 1.01, 0.18);
      glVertex3f(0.30, 1.01, 0.18);
      glVertex3f(0.30, 1.08, 0.18);
      glVertex3f(0.56, 1.08, 0.18);
      glEnd();glPopMatrix();

      //Parede fundo - andar 3 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.30, 1.01, 0.18);
      glVertex3f(0.30, 1.01, 0.48);
      glVertex3f(0.30, 1.08, 0.48);
      glVertex3f(0.30, 1.08, 0.18);
      glEnd();glPopMatrix();

      //Parede frente - andar 3 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.56, 1.01, 0.18);
      glVertex3f(0.56, 1.01, 0.48);
      glVertex3f(0.56, 1.08, 0.48);
      glVertex3f(0.56, 1.08, 0.18);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 3 - torre esquerda
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.5605, 1.08, 0.1805);
      glVertex3f(0.3005, 1.08, 0.1805);
      glVertex3f(0.3005, 1.08, 0.4805);
      glVertex3f(0.5605, 1.08, 0.4805);
      glEnd();glPopMatrix();

      //Parede direita - andar 3 - torre direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.56, 1.01, -0.48);
      glVertex3f(0.30, 1.01, -0.48);
      glVertex3f(0.30, 1.08, -0.48);
      glVertex3f(0.56, 1.08, -0.48);
      glEnd();glPopMatrix();

       //Parede esquerda - andar 3 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.56, 1.01, -0.18);
      glVertex3f(0.30, 1.01, -0.18);
      glVertex3f(0.30, 1.08, -0.18);
      glVertex3f(0.56, 1.08, -0.18);
      glEnd();glPopMatrix();

      //Parede fundo - andar 3 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.30, 1.01, -0.18);
      glVertex3f(0.30, 1.01, -0.48);
      glVertex3f(0.30, 1.08, -0.48);
      glVertex3f(0.30, 1.08, -0.18);
      glEnd();glPopMatrix();

      //Parede frente - andar 3 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.56, 1.01, -0.18);
      glVertex3f(0.56, 1.01, -0.48);
      glVertex3f(0.56, 1.08, -0.48);
      glVertex3f(0.56, 1.08, -0.18);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 3 - torre direita
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.5605, 1.08, -0.1805);
      glVertex3f(0.3005, 1.08, -0.1805);
      glVertex3f(0.3005, 1.08, -0.4805);
      glVertex3f(0.5605, 1.08, -0.4805);
      glEnd();glPopMatrix();

      //Andar 4
      //Parede direita - andar 4 - torre direita 
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.08, -0.45);
      glVertex3f(0.33, 1.08, -0.45);
      glVertex3f(0.33, 1.20, -0.45);
      glVertex3f(0.53, 1.20, -0.45);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 4 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.08, -0.21);
      glVertex3f(0.33, 1.08, -0.21);
      glVertex3f(0.33, 1.20, -0.21);
      glVertex3f(0.53, 1.20, -0.21);
      glEnd();glPopMatrix();

      //Parede fundo - andar 4 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.33, 1.08, -0.21);
      glVertex3f(0.33, 1.08, -0.45);
      glVertex3f(0.33, 1.20, -0.45);
      glVertex3f(0.33, 1.20, -0.21);
      glEnd();glPopMatrix();

      //Parede frente - andar 4 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.08, -0.21);
      glVertex3f(0.53, 1.08, -0.45);
      glVertex3f(0.53, 1.20, -0.45);
      glVertex3f(0.53, 1.20, -0.21);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 4 - torre direita
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.20, -0.21);
      glVertex3f(0.53, 1.20, -0.45);
      glVertex3f(0.33, 1.20, -0.45);
      glVertex3f(0.33, 1.20, -0.21);
      glEnd();glPopMatrix();
      
      //Parede direita - andar 4 - torre esquerda 
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.08, 0.45);
      glVertex3f(0.33, 1.08, 0.45);
      glVertex3f(0.33, 1.20, 0.45);
      glVertex3f(0.53, 1.20, 0.45);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 4 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.08, 0.21);
      glVertex3f(0.33, 1.08, 0.21);
      glVertex3f(0.33, 1.20, 0.21);
      glVertex3f(0.53, 1.20, 0.21);
      glEnd();glPopMatrix();

      //Parede fundo - andar 4 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.33, 1.08, 0.21);
      glVertex3f(0.33, 1.08, 0.45);
      glVertex3f(0.33, 1.20, 0.45);
      glVertex3f(0.33, 1.20, 0.21);
      glEnd();glPopMatrix();

      //Parede frente - andar 4 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.08, 0.21);
      glVertex3f(0.53, 1.08, 0.45);
      glVertex3f(0.53, 1.20, 0.45);
      glVertex3f(0.53, 1.20, 0.21);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 4 - torre esquerda
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.53, 1.20, 0.21);
      glVertex3f(0.53, 1.20, 0.45);
      glVertex3f(0.33, 1.20, 0.45);
      glVertex3f(0.33, 1.20, 0.21);
      glEnd();glPopMatrix();
      
      //Pirâmides 
      //Andar 5
      //Parede direita - andar 5 - torre direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.20, -0.425);
      glVertex3f(0.355, 1.20, -0.425);
      glVertex3f(0.355, 1.22, -0.425);
      glVertex3f(0.505, 1.22, -0.425);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 5 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.20, -0.24);
      glVertex3f(0.355, 1.20, -0.24);
      glVertex3f(0.355, 1.22, -0.24);
      glVertex3f(0.505, 1.22, -0.24);
      glEnd();glPopMatrix();

      //Parede frente - andar 5 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.20, -0.24);
      glVertex3f(0.505, 1.20, -0.425);
      glVertex3f(0.505, 1.22, -0.425);
      glVertex3f(0.505, 1.22, -0.24);
      glEnd();glPopMatrix();
      
      //Parede traz - andar 5 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.355, 1.20, -0.24);
      glVertex3f(0.355, 1.20, -0.425);
      glVertex3f(0.355, 1.22, -0.425);
      glVertex3f(0.355, 1.22, -0.24);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 5 - torre direita
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.22, -0.24);
      glVertex3f(0.505, 1.22, -0.425);
      glVertex3f(0.355, 1.22, -0.425);
      glVertex3f(0.355, 1.22, -0.24);
      glEnd();glPopMatrix();

      //Parede direita - andar 5 - torre esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.20, 0.425);
      glVertex3f(0.355, 1.20, 0.425);
      glVertex3f(0.355, 1.22, 0.425);
      glVertex3f(0.505, 1.22, 0.425);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 5 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.20, 0.24);
      glVertex3f(0.355, 1.20, 0.24);
      glVertex3f(0.355, 1.22, 0.24);
      glVertex3f(0.505, 1.22, 0.24);
      glEnd();glPopMatrix();

      //Parede frente - andar 5 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.20, 0.24);
      glVertex3f(0.505, 1.20, 0.425);
      glVertex3f(0.505, 1.22, 0.425);
      glVertex3f(0.505, 1.22, 0.24);
      glEnd();glPopMatrix();
      
      //Parede traz - andar 5 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.355, 1.20, 0.24);
      glVertex3f(0.355, 1.20, 0.425);
      glVertex3f(0.355, 1.22, 0.425);
      glVertex3f(0.355, 1.22, 0.24);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 5 - torre direita
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.505, 1.22, 0.24);
      glVertex3f(0.505, 1.22, 0.425);
      glVertex3f(0.355, 1.22, 0.425);
      glVertex3f(0.355, 1.22, 0.24);
      glEnd();glPopMatrix();
      
      //Parede direita - andar 6 - torre direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.22, -0.395);
      glVertex3f(0.38, 1.22, -0.395);
      glVertex3f(0.38, 1.24, -0.395);
      glVertex3f(0.48, 1.24, -0.395);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 6 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.22, -0.265);
      glVertex3f(0.38, 1.22, -0.265);
      glVertex3f(0.38, 1.24, -0.265);
      glVertex3f(0.48, 1.24, -0.265);
      glEnd();glPopMatrix();

      //Parede frente - andar 6 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.22, -0.265);
      glVertex3f(0.48, 1.22, -0.395);
      glVertex3f(0.48, 1.24, -0.395);
      glVertex3f(0.48, 1.24, -0.265);
      glEnd();glPopMatrix();
      
      //Parede traz - andar 6 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.38, 1.22, -0.265);
      glVertex3f(0.38, 1.22, -0.395);
      glVertex3f(0.38, 1.24, -0.395);
      glVertex3f(0.38, 1.24, -0.265);
      glEnd();glPopMatrix();

      //Teto - andar 6 - torre direita
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.24, -0.265);
      glVertex3f(0.48, 1.24, -0.395);
      glVertex3f(0.38, 1.24, -0.395);
      glVertex3f(0.38, 1.24, -0.265);
      glEnd();glPopMatrix();

    //Parede direita - andar 6 - torre esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.22, 0.395);
      glVertex3f(0.38, 1.22, 0.395);
      glVertex3f(0.38, 1.24, 0.395);
      glVertex3f(0.48, 1.24, 0.395);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 6 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.22, 0.265);
      glVertex3f(0.38, 1.22, 0.265);
      glVertex3f(0.38, 1.24, 0.265);
      glVertex3f(0.48, 1.24, 0.265);
      glEnd();glPopMatrix();

      //Parede frente - andar 6 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.22, 0.265);
      glVertex3f(0.48, 1.22, 0.395);
      glVertex3f(0.48, 1.24, 0.395);
      glVertex3f(0.48, 1.24, 0.265);
      glEnd();glPopMatrix();
      
      //Parede traz - andar 6 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.38, 1.22, 0.265);
      glVertex3f(0.38, 1.22, 0.395);
      glVertex3f(0.38, 1.24, 0.395);
      glVertex3f(0.38, 1.24, 0.265);
      glEnd();glPopMatrix();

      //Teto - andar 6 - torre esquerda
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.48, 1.24, 0.265);
      glVertex3f(0.48, 1.24, 0.395);
      glVertex3f(0.38, 1.24, 0.395);
      glVertex3f(0.38, 1.24, 0.265);
      glEnd();glPopMatrix();

      //Andar 7
      //Parede direita - andar 7 - torre direita
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.24, -0.365);
      glVertex3f(0.405, 1.24, -0.365);
      glVertex3f(0.405, 1.26, -0.365);
      glVertex3f(0.455, 1.26, -0.365);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 7 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.24, -0.295);
      glVertex3f(0.405, 1.24, -0.295);
      glVertex3f(0.405, 1.26, -0.295);
      glVertex3f(0.455, 1.26, -0.295);
      glEnd();glPopMatrix();

      //Parede frente - andar 7 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.24, -0.295);
      glVertex3f(0.455, 1.24, -0.365);
      glVertex3f(0.455, 1.26, -0.365);
      glVertex3f(0.455, 1.26, -0.295);
      glEnd();glPopMatrix();
      
      //Parede traz - andar 7 - torre direita
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.405, 1.24, -0.295);
      glVertex3f(0.405, 1.24, -0.365);
      glVertex3f(0.405, 1.26, -0.365);
      glVertex3f(0.405, 1.26, -0.295);
      glEnd();glPopMatrix();

      //Teto
      //Teto - andar 7 - torre direita
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.26, -0.295);
      glVertex3f(0.455, 1.26, -0.365);
      glVertex3f(0.405, 1.26, -0.365);
      glVertex3f(0.405, 1.26, -0.295);
      glEnd();glPopMatrix();
      
      //Parede direita - andar 7 - torre esquerda
      glColor3f( 0.96, 0.87, 0.7);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.24, 0.365);
      glVertex3f(0.405, 1.24, 0.365);
      glVertex3f(0.405, 1.26, 0.365);
      glVertex3f(0.455, 1.26, 0.365);
      glEnd();glPopMatrix();

      //Parede esquerda - andar 7 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.24, 0.295);
      glVertex3f(0.405, 1.24, 0.295);
      glVertex3f(0.405, 1.26, 0.295);
      glVertex3f(0.455, 1.26, 0.295);
      glEnd();glPopMatrix();

      //Parede frente - andar 7 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.24, 0.295);
      glVertex3f(0.455, 1.24, 0.365);
      glVertex3f(0.455, 1.26, 0.365);
      glVertex3f(0.455, 1.26, 0.295);
      glEnd();glPopMatrix();
      
      //Parede traz - andar 7 - torre esquerda
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.405, 1.24, 0.295);
      glVertex3f(0.405, 1.24, 0.365);
      glVertex3f(0.405, 1.26, 0.365);
      glVertex3f(0.405, 1.26, 0.295);
      glEnd();glPopMatrix();

      //Teto - andar 7 - torre esquerda
      glColor3f( 0.87,  0.72, 0.53);
      glPushMatrix();glBegin(GL_POLYGON);
      glVertex3f(0.455, 1.26, 0.295);
      glVertex3f(0.455, 1.26, 0.365);
      glVertex3f(0.405, 1.26, 0.365);
      glVertex3f(0.405, 1.26, 0.295);
      glEnd();glPopMatrix();


    //Portas da esquerda
      glColor3f( 0.82,  0.71, 0.55);
      glPushMatrix();
        glTranslatef(0.6, 0.1, 0.15);
        drawDoor(-doorAngle);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.6, 0.1, 0.45);
        glRotatef(180,0,1,0);
        drawDoor(doorAngle);
      glPopMatrix();

    //Portas do meio
      glPushMatrix();
        glTranslatef(0.6, 0.1, -0.15);
        drawDoor(-doorAngle);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.6, 0.1, 0.15);
        glRotatef(180,0,1,0);
        drawDoor(doorAngle);
      glPopMatrix();

      //Portas da direita
      glPushMatrix();
        glTranslatef(0.6, 0.1, -0.45);
        drawDoor(-doorAngle);
      glPopMatrix();  

      glPushMatrix();
        glTranslatef(0.6, 0.1, -0.15);
        glRotatef(180,0,1,0);
        drawDoor(doorAngle);
      glPopMatrix();

      //Colunas
      glEnable(GL_DEPTH_TEST);
      glColor3f(0.96, 0.96, 0.86);
      drawColumnY(0.59, 0.5, 0.0, 0.015, 1.2);
      drawColumnY(0.59, -0.5, 0.0, 0.015, 1.2);
      drawColumnY(0.62, 0.16, 0.41, 0.010, 0.8);
      drawColumnY(0.62, -0.16, 0.41, 0.010, 0.8);
      drawColumnY(0.59, 0, 1.0, 0.015, 0.3);

      drawColumnY(0.585, 0, 1.3, 0.008, 0.07);
      drawColumnZ(0.585, 1.35, -0.035, 0.005, 0.07);

    glPopMatrix(); //Aqui acaba a matriz de objetos afetados pela escala


    //Arcos superiores as portas 
    glColor3f( 0.87,  0.72, 0.53);  
    drawSemiDiskXY(2.12, 0.8, 0.0, 0.2, 0.28);
    drawSemiDiskXY(2.12, 0.8, 0.6, 0.2, 0.28);
    drawSemiDiskXY(2.12, 0.8, -0.6, 0.2, 0.28);

    glColor3f( 0.48, 0.63, 0.36); 
    drawSemiDiskXY(2.12, 0.8, 0.0, 0.0, 0.15);
    drawSemiDiskXY(2.12, 0.8, 0.6, 0.0, 0.15);
    drawSemiDiskXY(2.12, 0.8, -0.6, 0.0, 0.15);

    //Arco Teto
    glColor3f( 0.87,  0.72, 0.53);  
    drawSemiDiskXY(2.12, 3.50, 0.0, 0.0, 0.4);
    drawSemiDiskXY(1.82, 3.50, 0.0, 0.0, 0.4);
    
    //Circunferências do segundo andar
    glColor3f( 0.87,  0.72, 0.53);
    drawDiskXY(2.12, 3.1, 0.0, 0.15, 0.2);
    drawDiskXY(2.12, 3.1, 0.65, 0.1, 0.15);
    drawDiskXY(2.12, 3.1, -0.65, 0.1, 0.15);

    drawDiskZY(1.6, 3.1, 1.01, 0.1, 0.15);
    drawDiskZY(1.6, 3.1, -1.01, 0.1, 0.15);

    glColor3f( 0.66, 0.66, 0.66); 
    drawDiskXY(2.12, 3.1, 0.0, 0.0, 0.15);
    drawDiskXY(2.12, 3.1, 0.65, 0.0, 0.1);
    drawDiskXY(2.12, 3.1, -0.65, 0.0, 0.1);

    drawDiskZY(1.6, 3.1, 1.01, 0.0, 0.1);
    drawDiskZY(1.6, 3.1, -1.01, 0.0, 0.1);

  //Cruz
    //Horizontal
    glPushMatrix();
    glColor3f(0.4,0.2,0);
    glTranslatef(-3.0, 2, 0);
    glScalef(0.5,0.198,2.48);
    glutSolidCube(0.2);
    glPopMatrix();  

    //Vertical
    glPushMatrix();
    glColor3f(0.4,0.2,0);
    glTranslatef(-3.0, 1.8, 0);
    glScalef(0.4,4.5,0.5);
    glutSolidCube(0.2);
    glPopMatrix();  
  //  

    //Altar
    glPushMatrix();
    glColor3f(0.65,0.65,0.65);
    glTranslatef(-2.70, 0.235, 0);
    glScalef(1,2.3,5);
    glutSolidCube(0.2);
    glPopMatrix();   

    //Lustres
    for(int i = 0; i < 2; i++) {
      //Lustres direitos
      //Haste
      glPushMatrix();
      glColor3f(1,0.8,0.4);
      glTranslatef(-2.70 + 3.2 * i, 2.3, -0.7);
      glScalef(0.03,3,0.03);
      glutSolidCube(0.2);
      glPopMatrix(); 

      //Lâmpada
      glPushMatrix();
      glColor3f(1,1,0.4);
      glTranslatef(-2.70 + 3.2 * i, 2.0, -0.7);
      glutSolidSphere(0.09, 50, 50);
      glPopMatrix(); 

      //Detalhe superior
      glPushMatrix();
      glColor3f(0,0,0.4);
      glTranslatef(-2.70 + 3.2 * i, 2, -0.7);
      drawSemiSphere(0.1);
      glPopMatrix(); 

      //Lustres esquerdos
      glPushMatrix();
      glColor3f(1,0.8,0.4);
      glTranslatef(-2.70 + 3.2 * i, 2.3, 0.7);
      glScalef(0.03,3,0.03);
      glutSolidCube(0.2);
      glPopMatrix(); 

      glPushMatrix();
      glColor3f(1,1,0.4);
      glTranslatef(-2.70 + 3.2 * i, 2, 0.7);
      glutSolidSphere(0.09, 50, 50);
      glPopMatrix();

      //Detalhe superior
      glPushMatrix();
      glColor3f(0,0,0.4);
      glTranslatef(-2.70 + 3.2 * i, 2, 0.7);
      drawSemiSphere(0.1);
      glPopMatrix(); 
    }

    //Bancos
    for(int i = 0; i < 5; i++) {
      //Esquerda
      //Assento
      glPushMatrix();
      glColor3f(0.4,0.2,0);
      glTranslatef(-1 + (0.5 * i), 0.13, 0.5);
      glScalef(0.5,0.198,2.48);
      glutSolidCube(0.2);
      glPopMatrix();  

      //Encosto
      glPushMatrix();
      glColor3f(0.2,0.1,0);
      glTranslatef(-0.95 + (0.5 * i), 0.2, 0.5);
      glRotatef(90,0,0,1);
      glScalef(0.5,0.198,2.48);
      glutSolidCube(0.2);
      glPopMatrix();

      //Pés
      for(int j = 0; j < 2; j++) {
        glPushMatrix();
          glColor3f(0.2,0.1,0);
          glTranslatef(-1 + (0.5 * i), 0.06, 0.695 - 0.39*j);
          glScalef(0.2,1,0.2);
          glutSolidCube(0.1);
        glPopMatrix(); 

        glPushMatrix();
          glColor3f(0.2,0.1,0);
          glTranslatef(-1 + (0.5 * i), 0.015, 0.695 - 0.39*j);
          glScalef(1.8,0.1,0.2);
          glutSolidCube(0.1);
        glPopMatrix(); 
      }

      //Direita
      //Assento
      glPushMatrix();
      glColor3f(0.4,0.2,0);
      glTranslatef(-1 + (0.5 * i), 0.13, -0.5);
      glScalef(0.5,0.198,2.48);
      glutSolidCube(0.2);
      glPopMatrix();  

      //Encosto
      glPushMatrix();
      glColor3f(0.2,0.1,0);
      glTranslatef(-0.95 + (0.5 * i), 0.2, -0.5);
      glRotatef(90,0,0,1);
      glScalef(0.5,0.198,2.48);
      glutSolidCube(0.2);
      glPopMatrix();

      //Pés
      for(int j = 0; j < 2; j++) {
        glPushMatrix();
          glColor3f(0.2,0.1,0);
          glTranslatef(-1 + (0.5 * i), 0.06, -0.695 + 0.39*j);
          glScalef(0.2,1,0.2);
          glutSolidCube(0.1);
        glPopMatrix(); 

        glPushMatrix();
          glColor3f(0.2,0.1,0);
          glTranslatef(-1 + (0.5 * i), 0.015, -0.695 + 0.39*j);
          glScalef(1.8,0.1,0.2);
          glutSolidCube(0.1);
        glPopMatrix(); 
      }
    }

    glPopMatrix();  
    glClear(GL_DEPTH_BUFFER_BIT);
    glFlush();
    glutSwapBuffers();
  }

// init parâmetros de rendering
  void init (void)
  {   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle=45;

  }

// Função usada para especificar a posição do observador virtual
  void setCam(void)
  {
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // init sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    
    //Cãmera 1
    gluLookAt(radius*sin(theta)*sin(phi), radius*cos(phi) + 1, radius*cos(theta)*sin(phi), 0, 1, 0, 0,1,0);

    //Câmera 2
    //gluLookAt(radius*sin(theta)*sin(phi), radius*cos(phi) + 0.4, radius*cos(theta)*sin(phi) + radius, radius*sin(theta)*sin(phi), radius*cos(phi) + 0.4, radius*cos(theta)*sin(phi), 0,1,0);
    
  }

// Função usada para especificar o volume de visualização
  void viewParameters(void)
  {
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // init sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(angle,fAspect,0.5,500);

    setCam();
  }

// Função callback chamada quando o tamanho da janela é alterado 
  void reShape(GLsizei w, GLsizei h) {
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;
  
    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    viewParameters();
  }

//Câmera 1
//Callback para gerenciar eventos do teclado para teclas especiais (F1, PgDn, entre outras)
  void keyPressed(unsigned char key, int x, int y) {
    glLoadIdentity();
    switch (key) {
      case 'a' : 
      theta += inc;
      break;
      case 'd' :
      theta -= inc;
      break;
      case 'w' :
      if(phi + inc <= PI) phi += inc;  
      break;
      case 's' : 
      if(phi - inc >= 0) phi -= inc;
      break;
      case 'i' :
      radius -= 0.5;
      break;
      case 'k' : 
      radius += 0.5;
      break;

    }

    phi = std::fmod(phi, 2*PI);
    printf("%f %f %f %f\n", radius*sin(theta)*sin(phi),radius*cos(phi),radius*cos(theta)*sin(phi));
    gluLookAt(radius*sin(theta)*sin(phi), radius*cos(phi) + 1, radius*cos(theta)*sin(phi), 0, 1, 0, 0,1,0);

    glutPostRedisplay();
  }

  void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
     if (state == GLUT_DOWN) {
      openingDoor = !openingDoor;
    }
    glutPostRedisplay();
  }

  void Timer(int value){
    if(openingDoor && doorAngle < 90){
      doorAngle += 5;
    }else if(!openingDoor && doorAngle > 0){
      doorAngle -= 5;
    }

    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
  }

// Programa Principal
  int main(int argc, char** argv) 
  {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Catedral");

    glutDisplayFunc(Display);
    glutReshapeFunc(reShape);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mouseFunc);
    glutTimerFunc(33, Timer, 1);
    init();
    glutMainLoop();
  }

