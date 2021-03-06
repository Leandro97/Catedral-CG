#ifdef __APPLE__
    #include <OpenGL/gl.h>
#elif __linux__
    #include <GL/gl.h>
#endif

#define PI 3.14159265
GLUquadricObj *obj = gluNewQuadric();

void drawColumnY(float x, float y, float z, float radius, float size){
  glPushMatrix();
  glRotatef(-90, 1.0, 0.0, 0.0 );
  glTranslatef(x, y, z);
  gluQuadricOrientation(obj, GLU_OUTSIDE);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluQuadricTexture(obj, true);
  gluCylinder(obj, radius, radius, size, 100, 100);
  glPopMatrix();
}

void drawColumnZ(float x, float y, float z, float radius, float size){
  glPushMatrix();
  glTranslatef(x, y, z);
  gluQuadricOrientation(obj, GLU_OUTSIDE);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluQuadricTexture(obj, true);
  gluCylinder(obj, radius, radius, size, 100, 100);
  glPopMatrix();
}

void drawDiskXY(float x, float y, float z, float radiusIn, float radiusOut, int mult){
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(90, 0.0, 1.0, 0.0 );

  if(mult == 1) {
    gluQuadricOrientation(obj, GLU_INSIDE);
  } else {
    gluQuadricOrientation(obj, GLU_OUTSIDE);
  }

  gluQuadricTexture(obj, true);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glPopMatrix();
}

void drawDiskZY(float x, float y, float z, float radiusIn, float radiusOut, int mult){
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(-90, 0.0, 0.0, 1.0);

  if(mult == 1) {
    gluQuadricOrientation(obj, GLU_INSIDE);
  } else {
    gluQuadricOrientation(obj, GLU_OUTSIDE);
  }

  gluQuadricTexture(obj, true);
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glPopMatrix();
}

void drawSemiDiskXY(float x, float y, float z, float radiusIn, float radiusOut, int mult){
  GLdouble eqnBottom[4] = {0.0, 1.0, 0.0, 0};
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(-90, 0.0, 1.0, 0.0);
  glClipPlane (GL_CLIP_PLANE0, eqnBottom);
  glEnable (GL_CLIP_PLANE0);

  if(mult == 1) {
    gluQuadricOrientation(obj, GLU_INSIDE);
  } else {
    gluQuadricOrientation(obj, GLU_OUTSIDE);
  }
  gluQuadricTexture(obj, true);
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
  gluQuadricTexture(obj, true);
  gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glDisable(GL_CLIP_PLANE0);
  glPopMatrix();
}

void drawDoor(float angle){
  glPushMatrix();   
  glNormal3f(-1,0,0);
  glRotatef(angle, 0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0, 0.0);  glVertex3f(0, 0.1, 0);
  glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0.1, 0.1);
  glTexCoord2f(1.0, 1.0);  glVertex3f(0, -0.1, 0.1);
  glTexCoord2f(1.0, 0.0);  glVertex3f(0, -0.1, 0);
  glEnd();
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

//Esquerda e direita
void drawPlaneED(float x1, float y1, float z1, float x2, float y2, float z2, float mult) {
  glBegin(GL_POLYGON);
  glNormal3f(0,0, 1*mult);

  glTexCoord2f(0.0, 0.0); glVertex3f(x1, y1, z1);
  glTexCoord2f(0.0, 10.0); glVertex3f(x2, y1, z1);
  glTexCoord2f(10.0, 10.0); glVertex3f(x2, y2, z2);
  glTexCoord2f(10.0, 0.0); glVertex3f(x1, y2, z2);
  
  glEnd();
}

//Teto e chão
void drawPlaneTC(float x1, float y1, float z1, float x2, float y2, float z2, float mult) {  
  glBegin(GL_POLYGON);
  glNormal3f(0, -1*mult,0);

  glTexCoord2f(0.0, 0.0);   glVertex3f(x1, y1, z1);
  glTexCoord2f(0.0, 20.0);   glVertex3f(x1, y1, z2);
  glTexCoord2f(20.0, 20.0);  glVertex3f(x2, y2, z2);
  glTexCoord2f(20.0, 0.0);   glVertex3f(x2, y2, z1);

  glEnd();
}

//Frente e fundo
void drawPlaneFF(float x1, float y1, float z1, float x2, float y2, float z2, float mult) {
  glBegin(GL_POLYGON);
  glNormal3f(-1*mult,0,0);

  glTexCoord2f(0.0, 0.0);  glVertex3f(x1, y1, z1);
  glTexCoord2f(0.0, 1.0);  glVertex3f(x2, y1, z2);
  glTexCoord2f(1.0, 1.0);  glVertex3f(x2, y2, z2);
  glTexCoord2f(1.0, 0.0);  glVertex3f(x1, y2, z1);
  
  glEnd();
}