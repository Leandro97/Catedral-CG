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
#include "draw.cpp"
#include <SFML/Graphics.hpp>


GLdouble eyeX = 0, eyeY = 0.4, eyeZ = 11, phi = PI/2 - 0.4, theta = 0, radius = 12;
GLdouble centerX = 0, centerY = 0, centerZ = 0;
GLfloat doorAngle, angle, fAspect;
bool openingDoor = false; 
double inc = 2*PI/180;
bool isRotate;

GLuint texture_handle[20]; //Vetor que armazena as texturas


void loadTexture(GLuint texture, const char* filename){
  sf::Image img;
    img.loadFromFile(filename); //Carrega o arquivo da textura

   glBindTexture(GL_TEXTURE_2D, texture); //Atribui a textura carregada a uma posição no vetor de texturas

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 }

// inicia parâmetros de rendering
 void init(void) {   
  // Define a cor de fundo da janela de visualização como branca
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    

  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Habilita o uso de iluminação
  glEnable(GL_LIGHTING);  

  // Habilita a luz de número 0
  glEnable(GL_LIGHT0);

  // Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);

  // Habilita o modelo de colorização de Gouraud
  glShadeModel(GL_SMOOTH);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  int n = 14;
  glGenTextures(n, texture_handle); 
  loadTexture(texture_handle[0], "parede.jpg");
  loadTexture(texture_handle[1], "chaoInt.jpg");
  loadTexture(texture_handle[2], "porta.jpg");
  loadTexture(texture_handle[3], "telhado.jpg");
  loadTexture(texture_handle[4], "detalhe.jpg");
  loadTexture(texture_handle[5], "janela.jpg");
  loadTexture(texture_handle[6], "chaoExt.jpg");
  loadTexture(texture_handle[7], "paredeInt.jpeg");
  loadTexture(texture_handle[8], "fundoInt.jpg");
  loadTexture(texture_handle[9], "teto.jpeg");
  loadTexture(texture_handle[10], "paredeMeio.jpeg");
  loadTexture(texture_handle[11], "detalhearco.jpg");
  loadTexture(texture_handle[12], "escuro.jpg");
  loadTexture(texture_handle[13], "door.jpeg");
  // Inicializa a variável que especifica o ângulo da projeção
  angle=45;
}

// Função usada para especificar aspectos de iluminação
void setLight(void) {
  GLfloat luzAmbiente[4]={0.35, 0.35, 0.35, 1.0}; 
  GLfloat luzDifusa[4]={0.6,0.6,0.6,1.0}; // "cor" 
  GLfloat luzEspecular[4]={0.2, 0.2, 0.2, 1.0}; // "brilho" 
  GLfloat posicaoLuz[4]={50.0, 50.0, 50.0, 1.0};
  //GLfloat posicaoLuz[4]={50.0, 0.0, 0.0, 1.0};

  // Capacidade de brilho do material
  //GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
  //GLint especMaterial = 0;

  // Define a refletância do material 
  //glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

  // Ativa o uso da luz ambiente 
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

  // Define os parâmetros da luz de número 0
  glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
  glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);   
}

// Função usada para especificar a posição do observador virtual
void setCam(void) {
    // Especifica sistema de coordenadas do modelo
  glMatrixMode(GL_MODELVIEW);
    // init sistema de coordenadas do modelo
  glLoadIdentity();
  setLight();
    // Especifica posição do observador e do alvo


    //Cãmera 1
  gluLookAt(radius*sin(theta)*sin(phi), radius*cos(phi) + 1, radius*cos(theta)*sin(phi), 0, 1, 0, 0,1,0);

    //Câmera 2
    //gluLookAt(radius*sin(theta)*sin(phi), radius*cos(phi) + 0.4, radius*cos(theta)*sin(phi) + radius, radius*sin(theta)*sin(phi), radius*cos(phi) + 0.4, radius*cos(theta)*sin(phi), 0,1,0);

}

// Função usada para especificar o volume de visualização
void viewParameters(void) {
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
    case 'q' : 
    exit(0);
    break;

  }

  phi = std::fmod(phi, 2*PI);
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
    glutPostRedisplay();
  }else if(!openingDoor && doorAngle > 0){
    doorAngle -= 5;
    glutPostRedisplay();
  }

  
  glutTimerFunc(33,Timer, 1);
}

// Função callback chamada para fazer o desenho
void Display(void) {
  glPushMatrix();

  glRotatef(-90, 0.0, 1.0, 0.0);

  glClear(GL_COLOR_BUFFER_BIT); 
  setLight();
  glPushMatrix();
  glScalef(3.5,3.5,2);

  //Chão
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[6]);
  drawPlaneTC(1.0, 0.0, -1.0, -1.3, 0.0, 1.0, 1);
  glDisable (GL_TEXTURE_2D);

  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[1]);
  drawPlaneTC(0.6, 0.001, -0.5, -1, 0.001, 0.5, 1);
  glDisable (GL_TEXTURE_2D);

  // frente, cima, direita: -1. fundo, baixo, esquerda: 1
  // Andar 1
  //Parede direita - andar 1
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[10]);
  drawPlaneED(-1.0, 0.1 , 0.48, 0.6, 0.0, 0.48, -1);
  glDisable (GL_TEXTURE_2D);

  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[7]);
  drawPlaneED(-1.0, 0.76 , 0.49, 0.6, 0.0, 0.49, -1);
  glDisable (GL_TEXTURE_2D);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneED(-1.0, 0.76 , 0.5, 0.6, 0.0, 0.5, 1);
  glDisable (GL_TEXTURE_2D);
  
  //Parede esquerda - andar 1
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[10]);
  drawPlaneED(0.6, 0.1, -0.48, -1.0, 0.0, -0.48, -1);
  glDisable (GL_TEXTURE_2D);

  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[7]);
  drawPlaneED(0.6, 0.76, -0.49, -1.0, 0.0, -0.49, -1);
  glDisable (GL_TEXTURE_2D);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneED(0.6, 0.76, -0.5, -1.0, 0.0, -0.5, -1);
  glDisable (GL_TEXTURE_2D);
  
  //Parede fundo - andar 1
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[8]);
  drawPlaneFF(-0.99, 0.76, -0.5, -0.99, 0.0, 0.5, 1);
  glDisable (GL_TEXTURE_2D);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneFF(-1, 0.76, -0.5, -1, 0.0, 0.5, 1);
  glDisable (GL_TEXTURE_2D);
  
  // Parede frente - andar 1 - superior
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[7]);
  glBegin(GL_POLYGON);
  glNormal3f(-1,0,0);

  glTexCoord2f(0.0, 0.0);  glVertex3f(0.59, 0.76, -0.5);
  glTexCoord2f(0.0, 10.0);  glVertex3f(0.59, 0.76, 0.5);
  glTexCoord2f(10.0, 10.0);  glVertex3f(0.59, 0.2, 0.5);
  glTexCoord2f(10.0, 0.0);  glVertex3f(0.59, 0.2, -0.5);
  
  glEnd();
  //drawPlaneFF(0.59, 0.76, -0.5, 0.59, 0.2, 0.5, 1);
  glDisable (GL_TEXTURE_2D);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneFF(0.6, 0.76, -0.5, 0.6, 0.2, 0.5, -1);
  glDisable (GL_TEXTURE_2D);
  
  //Parede frente - andar 1 - inferior esquerda
  drawPlaneFF(0.59, 0.2, 0.4, 0.59, 0.0, 0.5, -1);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneFF(0.6, 0.2, 0.4, 0.6, 0.0, 0.5, -1);
  glDisable (GL_TEXTURE_2D);
  
  //Parede frente - andar 1 - inferior direita
  drawPlaneFF(0.59, 0.2, -0.4, 0.59, 0.0, -0.5, -1);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneFF(0.6, 0.2, -0.4, 0.6, 0.0, -0.5, -1);
  glDisable (GL_TEXTURE_2D);
  

  //Parede frente - andar 1 - inferior centro direita
  drawPlaneFF(0.59, 0.2, -0.2, 0.59, 0.0, -0.1, -1);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneFF(0.6, 0.2, -0.2, 0.6, 0.0, -0.1, -1);
  glDisable (GL_TEXTURE_2D);
  
  
  //Parede frente - andar 1 - inferior centro esquerda
  drawPlaneFF(0.59, 0.2, 0.2, 0.59, 0.0, 0.1, -1);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  drawPlaneFF(0.6, 0.2, 0.2, 0.6, 0.0, 0.1, -1);
  glDisable (GL_TEXTURE_2D);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
  drawPlaneED(0.6, 0.42, -0.5005, -1, 0.39, -0.5, -1);
  drawPlaneED(0.6, 0.42, 0.5005, -1, 0.39, 0.5, 1);
  drawPlaneFF(0.6005, 0.42, -0.5, 0.6005, 0.39, 0.5, -1);

  drawPlaneED(0.6, 0.46, -0.5005, -1, 0.45, -0.5, -1);
  drawPlaneED(0.6, 0.46, 0.5005, -1, 0.45, 0.5, 1);
  drawPlaneFF(0.6005, 0.46, -0.5, 0.6005, 0.45, 0.5, -1);
  glDisable (GL_TEXTURE_2D);

  //Interior
  //Essas paredes são uma translação da frente da catedral, a entrada
  //Parede interior - superior
  drawPlaneTC(0.39, 0.4, -0.5, 0.39, 0.2, 0.5, 1);
  drawPlaneTC(0.4, 0.4, -0.5, 0.4, 0.2, 0.5, 1);

  //Parede interior - inferior esquerda
  drawPlaneFF(0.39, 0.2, 0.4, 0.39, 0.0, 0.5, 1);
  drawPlaneFF(0.4, 0.2, 0.4, 0.4, 0.0, 0.5, 1);

  //Parede interior - inferior direita
  drawPlaneFF(0.39, 0.2, -0.4, 0.39, 0.0, -0.5, 1);
  drawPlaneFF(0.4, 0.2, -0.4, 0.4, 0.0, -0.5, 1);   

  //Parede interior - inferior centro direita
  drawPlaneFF(0.39, 0.2, -0.2, 0.39, 0.0, -0.1, 1);
  drawPlaneFF(0.4, 0.2, -0.2, 0.4, 0.0, -0.1, 1);

  //Parede frente - inferior centro esquerda
  drawPlaneFF(0.39, 0.2, 0.2, 0.39, 0.0, 0.1, 1);
  drawPlaneFF(0.4, 0.2, 0.2, 0.4, 0.0, 0.1, 1);

  //Parede interior corredor direita 
  drawPlaneED(0.59, 0.76, 0.15, 0.39, 0.0, 0.15, 1);

  //Parede interior corredor esquerda 
  drawPlaneED(0.59, 0.76, -0.15, 0.39, 0.0, -0.15, 1);  

  //Varanda - andar 1 - camada 1 // Falta fechar os lados
  drawPlaneTC(0.6, 0.4, -0.5, 0.4, 0.4, 0.5, 1);
  drawPlaneTC(0.6, 0.405, -0.5, 0.4, 0.405, 0.5, 1);

  //Varanda - andar 1 - camada 2 // Falta fechar os lados
  drawPlaneTC(0.6,  0.405, -0.5, 0.4, 0.405, 0.5, 1);
  drawPlaneTC(0.6,  0.41, -0.5, 0.4, 0.41, 0.5, 1);

  //Teto
  //Teto - andar 1 - camada 1 // Falta fechar os lados
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[9]);
  drawPlaneTC(0.6, 0.76, -0.50, -1.00, 0.76, 0.50, 1);
  glDisable (GL_TEXTURE_2D);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[3]);
  drawPlaneTC(0.6, 0.76005, -0.50, -1.00, 0.76005, 0.50, 1);
  glDisable (GL_TEXTURE_2D);
  
  //Andar 2  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  //Parede direita - andar 2
  drawPlaneED(0.6, 1.0, 0.5, 0.3, 0.76, 0.5, 1);
  //Parede esquerda - andar 2
  drawPlaneED(0.6, 1.0, -0.5, 0.3, 0.76, -0.5, -1);
  //Parede fundo - andar 2
  drawPlaneFF(0.3, 1.0, -0.5, 0.3, 0.76, 0.5, 1);
  //Parede frente - andar 2  
  drawPlaneFF(0.6, 1.0, -0.5, 0.6, 0.76, 0.5, -1);
  glDisable (GL_TEXTURE_2D);

  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
  //Parede direita - andar 2
  drawPlaneED(0.6, 0.78, -0.5005, 0.3, 0.76, -0.5, -1);
  //Parede esquerda - andar 2
  drawPlaneED(0.6, 0.78, 0.5005, 0.3, 0.76, 0.5, 1);
  //Parede frente - andar 2
  drawPlaneFF(0.6005, 0.78, -0.5, 0.6005, 0.76, 0.5, -1);
  glDisable (GL_TEXTURE_2D);

  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
  //Parede direita - andar 2
  drawPlaneED(0.6, 0.82, -0.5005, 0.3, 0.81, -0.5, -1);
  //Parede esquerda - andar 2
  drawPlaneED(0.6, 0.82, 0.5005, 0.3, 0.81, 0.5, 1);
  //Parede frente - andar 2
  drawPlaneFF(0.6005, 0.82, -0.5, 0.6005, 0.81, 0.5, -1);
  glDisable (GL_TEXTURE_2D);


  //Portas do segundo andar 
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[5]); 
  drawPlaneFF(0.6005, 0.62, -0.075, 0.6005, 0.46, 0.075, -1); 
  drawPlaneFF(0.6005, 0.58,  0.285, 0.6005, 0.46, 0.385, -1);
  drawPlaneFF(0.6005, 0.58,  -0.285, 0.6005, 0.46, -0.385, -1);
  glDisable (GL_TEXTURE_2D);

  //Teto
  //Teto - andar 2 
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
  drawPlaneTC(0.61, 1.0, -0.51, 0.28, 1.0, 0.5, -1);
  glDisable (GL_TEXTURE_2D);

  //Andar 3
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
  //Parede direita - andar 3 - torre esquerda
  drawPlaneED(0.56, 1.0, 0.48, 0.30, 1.08, 0.48, 1);

  //Parede esquerda - andar 3 - torre esquerda
  drawPlaneED(0.56, 1.0, 0.18, 0.30, 1.08, 0.18, -1);

  //Parede fundo - andar 3 - torre esquerda
  drawPlaneFF(0.30, 1.0, 0.18, 0.30, 1.08, 0.48, 1);

  //Parede frente - andar 3 - torre esquerda
  drawPlaneFF(0.56, 1.0, 0.18, 0.56, 1.08, 0.48, -1);

  //Teto - andar 3 - torre esquerda
  drawPlaneTC(0.5605, 1.08, 0.1805, 0.3005, 1.08, 0.4805, -1);

  //Parede direita - andar 3 - torre direita
  drawPlaneED(0.56, 1.0, -0.48, 0.30, 1.08, -0.48, -1);

  //Parede esquerda - andar 3 - torre direita
  drawPlaneED(0.56, 1.0, -0.18, 0.30, 1.08, -0.18, 1);

  //Parede fundo - andar 3 - torre direita
  drawPlaneFF(0.30, 1.0, -0.18, 0.30, 1.08, -0.48, 1);

  //Parede frente - andar 3 - torre direita
  drawPlaneFF(0.56, 1.0, -0.18, 0.56, 1.08, -0.48, -1);

  //Teto - andar 3 - torre direita
  drawPlaneTC(0.5605, 1.08, -0.1805, 0.3005, 1.08, -0.4805, -1);

  //Andar 4
  //Parede direita - andar 4 - torre direita 
  drawPlaneED(0.53, 1.08, -0.45, 0.33, 1.20, -0.45, -1);

  //Parede esquerda - andar 4 - torre direita
  drawPlaneED(0.53, 1.08, -0.21, 0.33, 1.20, -0.21, 1);

  //Parede fundo - andar 4 - torre direita
  drawPlaneFF(0.33, 1.08, -0.21, 0.33, 1.20, -0.45, 1);

  //Parede frente - andar 4 - torre direita
  drawPlaneFF(0.53, 1.08, -0.21, 0.53, 1.20, -0.45, -1);

  //Teto - andar 4 - torre direita
  drawPlaneTC(0.53, 1.20, -0.21, 0.33, 1.20, -0.45, -1);

  //Parede direita - andar 4 - torre esquerda 
  drawPlaneED(0.53, 1.08, 0.45, 0.33, 1.20, 0.45, 1);

  //Parede esquerda - andar 4 - torre esquerda
  drawPlaneED(0.53, 1.08, 0.21, 0.33, 1.20, 0.21, -1);

  //Parede fundo - andar 4 - torre esquerda
  drawPlaneFF(0.33, 1.08, 0.21, 0.33, 1.20, 0.45, 1);

  //Parede frente - andar 4 - torre esquerda
  drawPlaneFF(0.53, 1.08, 0.21, 0.53, 1.20, 0.45, -1);

  //Teto - andar 4 - torre esquerda
  drawPlaneTC(0.53, 1.20, 0.21, 0.33, 1.20, 0.45, -1);

  //Pirâmides 
  //Andar 5
  //Parede direita - andar 5 - torre direita
  drawPlaneED(0.505, 1.20, -0.425, 0.355, 1.22, -0.425, -1);

  //Parede esquerda - andar 5 - torre direita
  drawPlaneED(0.505, 1.20, -0.24, 0.355, 1.22, -0.24, 1);

  //Parede frente - andar 5 - torre direita
  drawPlaneFF(0.505, 1.20, -0.24, 0.505, 1.22, -0.425, -1);

  //Parede traz - andar 5 - torre direita
  drawPlaneFF(0.355, 1.20, -0.24, 0.355, 1.22, -0.425, 1);

  //Teto - andar 5 - torre direita
  drawPlaneTC(0.505, 1.22, -0.24, 0.355, 1.22, -0.425, -1);

  //Parede direita - andar 5 - torre esquerda
  drawPlaneED(0.505, 1.20, 0.425, 0.355, 1.22, 0.425, 1);

  //Parede esquerda - andar 5 - torre esquerda
  drawPlaneED(0.505, 1.20, 0.24, 0.355, 1.22, 0.24, -1);

  //Parede frente - andar 5 - torre esquerda
  drawPlaneFF(0.505, 1.20, 0.24, 0.505, 1.22, 0.425, -1);

  //Parede fundo - andar 5 - torre esquerda
  drawPlaneFF(0.355, 1.20, 0.24, 0.355, 1.22, 0.425, 1);

  //Teto - andar 5 - torre direita
  drawPlaneTC(0.505, 1.22, 0.24, 0.355, 1.22, 0.425, -1);

  //Parede direita - andar 6 - torre direita
  drawPlaneED(0.48, 1.22, -0.395, 0.38, 1.24, -0.395, -1);

  //Parede esquerda - andar 6 - torre direita
  drawPlaneED(0.48, 1.22, -0.265, 0.38, 1.24, -0.265, 1);

  //Parede frente - andar 6 - torre direita
  drawPlaneFF(0.48, 1.22, -0.265, 0.48, 1.24, -0.395, -1);

  //Parede fundo - andar 6 - torre direita
  drawPlaneFF(0.38, 1.22, -0.265, 0.38, 1.24, -0.395, 1);

  //Teto - andar 6 - torre direita
  drawPlaneTC(0.48, 1.24, -0.265, 0.38, 1.24, -0.395, -1);

  //Parede direita - andar 6 - torre esquerda
  drawPlaneED(0.48, 1.22, 0.395, 0.38, 1.24, 0.395, 1);

  //Parede esquerda - andar 6 - torre esquerda
  drawPlaneED(0.48, 1.22, 0.265, 0.38, 1.24, 0.265, -1);

  //Parede frente - andar 6 - torre esquerda
  drawPlaneFF(0.48, 1.22, 0.265, 0.48, 1.24, 0.395, -1);

  //Parede fundo - andar 6 - torre esquerda
  drawPlaneFF(0.38, 1.22, 0.265, 0.38, 1.24, 0.395, 1);

  //Teto - andar 6 - torre esquerda
  drawPlaneTC(0.48, 1.24, 0.265, 0.38, 1.24, 0.395, -1);

  //Andar 7
  //Parede direita - andar 7 - torre direita
  drawPlaneED(0.455, 1.24, -0.365, 0.405, 1.26, -0.365, -1);

  //Parede esquerda - andar 7 - torre direita
  drawPlaneED(0.455, 1.24, -0.295, 0.405, 1.26, -0.295, 1);

  //Parede frente - andar 7 - torre direita
  drawPlaneFF(0.455, 1.24, -0.295, 0.455, 1.26, -0.365, -1);

  //Parede fundo - andar 7 - torre direita
  drawPlaneFF(0.405, 1.24, -0.295, 0.405, 1.26, -0.365, 1);

  //Teto - andar 7 - torre direita
  drawPlaneTC(0.455, 1.26, -0.295, 0.405, 1.26, -0.365, -1);

  //Parede direita - andar 7 - torre esquerda
  drawPlaneED(0.455, 1.24, 0.365, 0.405, 1.26, 0.365, 1);

  //Parede esquerda - andar 7 - torre esquerda
  drawPlaneED(0.455, 1.24, 0.295, 0.405, 1.26, 0.295, -1);

  //Parede frente - andar 7 - torre esquerda
  drawPlaneFF(0.455, 1.24, 0.295, 0.455, 1.26, 0.365, -1);

  //Parede fundo - andar 7 - torre esquerda
  drawPlaneFF(0.405, 1.24, 0.295, 0.405, 1.26, 0.365, 1);

  //Teto - andar 7 - torre esquerda
  drawPlaneTC(0.455, 1.26, 0.295, 0.405, 1.26, 0.365, -1);

  glDisable (GL_TEXTURE_2D);


  for(int i = 0; i < 3; i ++) {

    //Esquerda
    glPushMatrix();
    glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_handle[13]);
    glTranslatef(0.6, 0.1, 0.4 - 0.3*i);
    glRotatef(180,0,1,0);
    drawDoor(doorAngle);
    glPopMatrix();  

    //Direita
    glPushMatrix();
    glTranslatef(0.6, 0.1, 0.2 -0.3*i);
    drawDoor(-doorAngle);
    glDisable (GL_TEXTURE_2D);
    glPopMatrix();

  }

  //Colunas
  glPushMatrix();
  glEnable(GL_DEPTH_TEST);
  glColor3f(0.96, 0.96, 0.86);
  drawColumnY(0.605, 0.5, 0.0, 0.015, 1.2);
  drawColumnY(0.605, -0.5, 0.0, 0.015, 1.2);
  drawColumnY(0.62, 0.16, 0.41, 0.010, 0.8);
  drawColumnY(0.62, -0.16, 0.41, 0.010, 0.8);
  
  drawColumnY(0.59, 0, 1.0, 0.015, 0.3);
  drawColumnY(0.585, 0, 1.3, 0.008, 0.07);
  drawColumnZ(0.585, 1.35, -0.035, 0.005, 0.07);
  glPopMatrix();

  glPopMatrix(); //Aqui acaba a matriz de objetos afetados pela escala

   //Arco Teto
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
  
  drawSemiDiskXY(2.13, 3.50, 0.0, 0.0, 0.4, -1);
  drawSemiDiskXY(2.00, 3.50, 0.0, 0.0, 0.4, -1);
  
  glDisable (GL_TEXTURE_2D);

  //Arcos superiores às portas 
  //Primeiro andar
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
  
  drawSemiDiskXY(2.105, 0.8, 0.0, 0.2, 0.28, -1);
  drawSemiDiskXY(2.105, 0.8, 0.6, 0.2, 0.28, -1);
  drawSemiDiskXY(2.105, 0.8, -0.6, 0.2, 0.28, -1);
  
  glDisable (GL_TEXTURE_2D);
  
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[11]);
  
  drawSemiDiskXY(2.105, 0.8, 0.0, 0.0, 0.15, 1);
  drawSemiDiskXY(2.105, 0.8, 0.6, 0.0, 0.15, 1);
  drawSemiDiskXY(2.105, 0.8, -0.6, 0.0, 0.15, 1);

  glDisable (GL_TEXTURE_2D);

  //Segundo andar 
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[11]);
  
  drawSemiDiskXY(2.105, 2.170 , 0.0, 0, 0.15, 1);
  drawSemiDiskXY(2.105, 2.03, 0.667, 0, 0.10, 1);
  drawSemiDiskXY(2.105, 2.03, -0.667, 0, 0.10, 1);
  
  glDisable (GL_TEXTURE_2D);

  //Circunferências do segundo andar
  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[4]);

  drawDiskXY(2.105, 3.1, 0.0, 0.15, 0.2, 1);
  drawDiskXY(2.105, 3.1, 0.65, 0.1, 0.15, 1);
  drawDiskXY(2.105, 3.1, -0.65, 0.1, 0.15, 1);
  
  drawDiskZY(1.6, 3.1, 1.01, 0.1, 0.15, 1);
  drawDiskZY(1.6, 3.1, -1.01, 0.1, 0.15, 1);
  glDisable (GL_TEXTURE_2D);

  glEnable (GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_handle[11]);

  drawDiskXY(2.105, 3.1, 0.0, 0.0, 0.15, 1);
  drawDiskXY(2.105, 3.1, 0.65, 0.0, 0.1, 1);
  drawDiskXY(2.105, 3.1, -0.65, 0.0, 0.1, 1);

  glPushMatrix();
    glRotatef(90, 0,0,1);
    glTranslatef(1.5, -4.7, 0);
    drawDiskZY(1.6, 3.1, 1.01, 0.0, 0.1, 1);
    drawDiskZY(1.6, 3.1, -1.01, 0.0, 0.1, 1);
  glPopMatrix();
  glDisable (GL_TEXTURE_2D);

  glPushMatrix(); // Matriz dos objetos internos
  //Cruz
  //Horizontal
  glPushMatrix();
  glColor3f(0.4,0.2,0);
  glTranslatef(-3.4, 2, 0);
  glScalef(0.5,0.198,2.48);
  glutSolidCube(0.2);
  glPopMatrix();  

  //Vertical
  glPushMatrix();
  glColor3f(0.4,0.2,0);
  glTranslatef(-3.4, 1.8, 0);
  glScalef(0.4,4.5,0.5);
  glutSolidCube(0.2);
  glPopMatrix();  
  // Fim da cruz  

  //Altar
  glPushMatrix();
  glColor3f(0.65,0.65,0.65);
  glTranslatef(-2.70, 0.235, 0);
  glScalef(1,2.3,5);
  glutSolidCube(0.2);
  glPopMatrix();   
  
  //Tapete altar
  glColor3f(1, 0, 0); 
  drawPlaneTC(0.41, 0.002, -0.09, -0.75, 0.002, 0.09, 1);  

  //Lustres
  for(int i = 0; i < 2; i++) {
    //Lustres direitos
    //Haste
    glPushMatrix();
    glColor3f(0.58,0.58,0.72);
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
    glColor3f(0.58,0.58,0.72);
    glTranslatef(-2.70 + 3.2 * i, 2, -0.7);
    drawSemiSphere(0.101);
    glPopMatrix(); 

    //Lustres esquerdos
    //Haste
    glPushMatrix();
    glColor3f(0.58,0.58,0.72);
    glTranslatef(-2.70 + 3.2 * i, 2.3, 0.7);
    glScalef(0.03,3,0.03);
    glutSolidCube(0.2);
    glPopMatrix(); 

    //Lâmpada
    glPushMatrix();
    glColor3f(1,1,0.4);
    glTranslatef(-2.70 + 3.2 * i, 2, 0.7);
    glutSolidSphere(0.09, 50, 50);
    glPopMatrix();

    //Detalhe superior
    glPushMatrix();
    glColor3f(0.58,0.58,0.72);
    glTranslatef(-2.70 + 3.2 * i, 2, 0.7);
    drawSemiSphere(0.101);
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
  glPopMatrix();  

  glClear(GL_DEPTH_BUFFER_BIT);
  glColor3f(1, 1, 1);
  glFlush();
  glutSwapBuffers();
}

// Programa Principal
int main(int argc, char** argv) {
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
