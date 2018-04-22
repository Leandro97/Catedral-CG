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


GLdouble centerX = 0, centerY = 0, centerZ = 0, phi = PI/2, theta = 0, radius = 5;
GLfloat angle, fAspect;
//double inc = std::fmod(5*PI/180, PI/2);
double inc = 5*PI/180;
//bool isRotate;

GLUquadricObj *obj = gluNewQuadric();

void drawColuna(float x, float y, float z, float radius, float size){
  glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0 );
    glTranslatef(x, y, z);
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluCylinder(obj, radius, radius, size, 100, 100);
  glPopMatrix();
}

void drawDiskYZ(float x, float y, float z, float radiusIn, float radiusOut){
  glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 0.0, 1.0, 0.0 );
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glPopMatrix();
}

void drawDiskXZ(float x, float y, float z, float radiusIn, float radiusOut, float rotate){
  glPushMatrix();
    glTranslatef(x, y, z);
        glRotatef(-90, 1.0, 0.0, 0.0 );

    gluQuadricDrawStyle(obj, GLU_LINE);
    gluDisk(obj, radiusIn, radiusOut, 100, 100);
  glPopMatrix();
}

// Função callback chamada para fazer o desenho
void Display(void) {
    glPushMatrix();
    glRotatef(-90, 0.0, 1.0, 0.0 );
    glClear(GL_COLOR_BUFFER_BIT);

    //Chão
    glBegin(GL_POLYGON);    
        glColor3f(0.5, 0.5, 0.5); 
        glVertex3f(1.0, 0.0, -0.6);      
        glVertex3f(1.0, 0.0, 0.6);      
        glVertex3f(-1.0, 0.0, 0.6);      
        glVertex3f(-1.0, 0.0, -0.6);      
    glEnd();

    
    //Parede direita - andar 1
    glColor3f(0.96, 0.87, 0.7); //https://sistemas.riopomba.ifsudestemg.edu.br/dcc/materiais/926330044_Cores.pdf
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, 0.4 ,0.5);
        glVertex3f(-1.0, 0.0 ,0.5);
        glVertex3f(0.6, 0.0, 0.5);
        glVertex3f(0.6, 0.4 ,0.5);
    glEnd();

    glColor3f( 0.94, 1.0, 0.94);
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, 0.4, 0.49);
        glVertex3f(-1.0, 0.0, 0.49);
        glVertex3f(0.6, 0.0, 0.49);
        glVertex3f(0.6, 0.4, 0.49);
    glEnd();


       
    //Parede esquerda - andar 1
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 0.4,  -0.5 );
        glVertex3f(-1.0, 0.4, -0.5);
        glVertex3f(-1.0, 0.0, -0.5);
        glVertex3f(0.6, 0.0 ,-0.5);
    glEnd();

    glColor3f( 0.94, 1.0, 0.94);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 0.4 , -0.49);
        glVertex3f(-1.0, 0.4 ,-0.49);
        glVertex3f(-1.0, 0.0, -0.49);
        glVertex3f(0.6, 0.0, -0.49);
    glEnd();

    //Parede fundo - andar 1
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, 0.4, -0.5);
        glVertex3f(-1.0, 0.4, 0.5);
        glVertex3f(-1.0, 0.0, 0.5);
        glVertex3f(-1.0, 0.0, -0.5);
    glEnd();

    glColor3f( 0.94, 1.0, 0.94);
    glBegin(GL_POLYGON);
        glVertex3f(-0.99, 0.4, -0.5);
        glVertex3f(-0.99, 0.4, 0.5);
        glVertex3f(-0.99, 0.0, 0.5);
        glVertex3f(-0.99, 0.0, -0.5);
    glEnd();
    
    //Teto - andar 1 - camada 1 // Falta fechar os lados
    glColor3f( 0.87,  0.72, 0.53);
    glBegin(GL_POLYGON);
        glVertex3f(0.605, 0.4, -0.505);
        glVertex3f(-1.005, 0.4, -0.505);
        glVertex3f(-1.005, 0.4, 0.505);
        glVertex3f(0.605, 0.4, 0.505);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(0.605, 0.405, -0.505);
        glVertex3f(-1.005, 0.405, -0.505);
        glVertex3f(-1.005, 0.405, 0.505);
        glVertex3f(0.605, 0.405, 0.505);
    glEnd();
    
    
    //Teto - andar 1 - camada 2 // Falta fechar os lados
    glBegin(GL_POLYGON);
        glVertex3f(0.61,  0.405, -0.51);
        glVertex3f(-1.01, 0.405,  -0.51);
        glVertex3f(-1.01, 0.405, 0.51);
        glVertex3f(0.61, 0.405, 0.51);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(0.61, 0.41, -0.51);
        glVertex3f(-1.01, 0.41,  -0.51);
        glVertex3f(-1.01, 0.41, 0.51);
        glVertex3f(0.61, 0.41, 0.51);
    glEnd();

    
    //Parede direita - andar 2
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 0.75, 0.5);
        glVertex3f(-1.0, 0.75, 0.5);
        glVertex3f(-1.0, 0.41, 0.5);
        glVertex3f(0.6, 0.41, 0.5);
    glEnd();

    glColor3f( 0.94, 1.0, 0.94);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 0.75, 0.49);
        glVertex3f(-1.0, 0.75, 0.49);
        glVertex3f(-1.0, 0.41, 0.49);
        glVertex3f(0.6, 0.41, 0.49);
    glEnd();

    
    //Parede esquerda - andar 2
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 0.75, -0.5);
        glVertex3f(-1.0, 0.75, -0.5);
        glVertex3f(-1.0, 0.41, -0.5);
        glVertex3f(0.6, 0.41, -0.5);
    glEnd();

    glColor3f( 0.94, 1.0, 0.94);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 0.75, -0.49);
        glVertex3f(-1.0, 0.75, -0.49);
        glVertex3f(-1.0, 0.41, -0.49);
        glVertex3f(0.6, 0.41, -0.49);
    glEnd();

    //Parede fundo - andar 2
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, 0.75, -0.5);
        glVertex3f(-1.0, 0.75, 0.5);
        glVertex3f(-1.0, 0.41, 0.5);
        glVertex3f(-1.0, 0.41, -0.5);
    glEnd();

    glColor3f( 0.94, 1.0, 0.94);
    glBegin(GL_POLYGON);
        glVertex3f(-0.99, 0.75, -0.5);
        glVertex3f(-0.99, 0.75, 0.5);
        glVertex3f(-0.99, 0.41, 0.5);
        glVertex3f(-0.99, 0.41, -0.5);
    glEnd();

    //Teto - andar 2 - camada 1 // Falta fechar os lados
    glColor3f( 0.87,  0.72, 0.53);
    glBegin(GL_POLYGON);
        glVertex3f(0.605, 0.75,  -0.505);
        glVertex3f(-1.005, 0.75, -0.505);
        glVertex3f(-1.005, 0.75, 0.505);
        glVertex3f(0.605, 0.75, 0.505);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(0.605, 0.755,  -0.505);
        glVertex3f(-1.005, 0.755, -0.505);
        glVertex3f(-1.005, 0.755, 0.505);
        glVertex3f(0.605, 0.755, 0.505);
    glEnd();
    

    //Teto - andar 2 - camada 2 // Falta fechar os lados
    glBegin(GL_POLYGON);
        glVertex3f(0.61, 0.755, -0.51);
        glVertex3f(-1.01, 0.755, -0.51);
        glVertex3f(-1.01, 0.755, 0.51);
        glVertex3f(0.61, 0.755, 0.51);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(0.61, 0.76, -0.51);
        glVertex3f(-1.01, 0.76, -0.51);
        glVertex3f(-1.01, 0.76, 0.51);
        glVertex3f(0.61, 0.76, 0.51);
    glEnd();
    
      
    //Parede direita - andar 3
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 1.0, 0.5);
        glVertex3f(0.3, 1.0, 0.5);
        glVertex3f(0.3, 0.76, 0.5);
        glVertex3f(0.6, 0.76, 0.5);
    glEnd();

    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 1.0, -0.5);
        glVertex3f(0.3, 1.0, -0.5);
        glVertex3f(0.3, 0.76, -0.5);
        glVertex3f(0.6, 0.76, -0.5);
    glEnd();

    
    //Parede fundo - andar 3
    glBegin(GL_POLYGON);
        glVertex3f(0.3, 1.0, -0.5);
        glVertex3f(0.3, 1.0, 0.5);
        glVertex3f(0.3, 0.76, 0.5);
        glVertex3f(0.3, 0.76, -0.5);
    glEnd();


    //Parede frente - andar 3
    glBegin(GL_POLYGON);
        glVertex3f(0.6, 1.0, -0.5);
        glVertex3f(0.6, 1.0, 0.5);
        glVertex3f(0.6, 0.76, 0.5);
        glVertex3f(0.6, 0.76, -0.5);
    glEnd();

    
    //Teto - andar 3 - camada 1 // Falta fechar os lados
    glColor3f( 0.87,  0.72, 0.53);
    glBegin(GL_POLYGON);
        glVertex3f(0.61, 1.0, -0.51);
        glVertex3f(0.28, 1.0, -0.51);
        glVertex3f(0.28, 1.0, 0.5);
        glVertex3f(0.61, 1.0, 0.51);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(0.61, 1.01, -0.51);
        glVertex3f(0.28, 1.01, -0.51);
        glVertex3f(0.28, 1.01, 0.5);
        glVertex3f(0.61, 1.01, 0.51);
    glEnd();


    //Parede direita - andar 4 - torre direita
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.56, 1.01, 0.48);
        glVertex3f(0.30, 1.01, 0.48);
        glVertex3f(0.30, 1.15, 0.48);
        glVertex3f(0.56, 1.15, 0.48);
    glEnd();

    //Parede fundo - andar 4 - torre direita
    glBegin(GL_POLYGON);
        glVertex3f(0.30, 1.01, 0.18);
        glVertex3f(0.30, 1.01, 0.48);
        glVertex3f(0.30, 1.15, 0.48);
        glVertex3f(0.30, 1.15, 0.18);
    glEnd();

    //Parede frente - andar 4 - torre direita
    glBegin(GL_POLYGON);
        glVertex3f(0.56, 1.01, 0.18);
        glVertex3f(0.56, 1.01, 0.48);
        glVertex3f(0.56, 1.15, 0.48);
        glVertex3f(0.56, 1.15, 0.18);
    glEnd();

    //Teto - andar 4 - torre direita
    glColor3f( 0.87,  0.72, 0.53);
    glBegin(GL_POLYGON);
        glVertex3f(0.5605, 1.155, 0.1805);
        glVertex3f(0.3005, 1.155, 0.1805);
        glVertex3f(0.3005, 1.155, 0.4805);
        glVertex3f(0.5605, 1.155, 0.4805);
    glEnd();

    //Parede direita - andar 4 - torre esquerda
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.56, 1.01, -0.48);
        glVertex3f(0.30, 1.01, -0.48);
        glVertex3f(0.30, 1.15, -0.48);
        glVertex3f(0.56, 1.15, -0.48);
    glEnd();

     //Parede esquerda - andar 4 - torre esquerda
    glBegin(GL_POLYGON);
        glVertex3f(0.56, 1.01, -0.18);
        glVertex3f(0.30, 1.01, -0.18);
        glVertex3f(0.30, 1.15, -0.18);
        glVertex3f(0.56, 1.15, -0.18);
    glEnd();

    //Parede fundo - andar 4 - torre esquerda
    glBegin(GL_POLYGON);
        glVertex3f(0.30, 1.01, -0.18);
        glVertex3f(0.30, 1.01, -0.48);
        glVertex3f(0.30, 1.15, -0.48);
        glVertex3f(0.30, 1.15, -0.18);
    glEnd();

    //Parede frente - andar 4 - torre esquerda
    glBegin(GL_POLYGON);
        glVertex3f(0.56, 1.01, -0.18);
        glVertex3f(0.56, 1.01, -0.48);
        glVertex3f(0.56, 1.15, -0.48);
        glVertex3f(0.56, 1.15, -0.18);
    glEnd();

        //Teto - andar 4 - torre esquerda
    glColor3f( 0.87,  0.72, 0.53);
    glBegin(GL_POLYGON);
        glVertex3f(0.5605, 1.15, -0.1805);
        glVertex3f(0.3005, 1.15, -0.1805);
        glVertex3f(0.3005, 1.15, -0.4805);
        glVertex3f(0.5605, 1.15, -0.4805);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(0.5605, 1.155, -0.1805);
        glVertex3f(0.3005, 1.155, -0.1805);
        glVertex3f(0.3005, 1.155, -0.4805);
        glVertex3f(0.5605, 1.155, -0.4805);
    glEnd();

    //Parede direita - andar 5 - torre direita 
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.53, 1.15, -0.45);
        glVertex3f(0.33, 1.15, -0.45);
        glVertex3f(0.33, 1.35, -0.45);
        glVertex3f(0.53, 1.35, -0.45);
    glEnd();

    //Parede esquerda - andar 5 - torre direita
    glBegin(GL_POLYGON);
        glVertex3f(0.53, 1.15, -0.21);
        glVertex3f(0.33, 1.15, -0.21);
        glVertex3f(0.33, 1.35, -0.21);
        glVertex3f(0.53, 1.35, -0.21);
    glEnd();

    //Parede fundo - andar 5 - torre direita
    glBegin(GL_POLYGON);
        glVertex3f(0.33, 1.15, -0.21);
        glVertex3f(0.33, 1.15, -0.45);
        glVertex3f(0.33, 1.35, -0.45);
        glVertex3f(0.33, 1.35, -0.21);
    glEnd();

    //Parede frente - andar 5 - torre direita
    glBegin(GL_POLYGON);
        glVertex3f(0.53, 1.15, -0.21);
        glVertex3f(0.53, 1.15, -0.45);
        glVertex3f(0.53, 1.35, -0.45);
        glVertex3f(0.53, 1.35, -0.21);
    glEnd();

    //Parede direita - andar 5 - torre esquerda 
    glColor3f( 0.96, 0.87, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(0.53, 1.15, 0.45);
        glVertex3f(0.33, 1.15, 0.45);
        glVertex3f(0.33, 1.35, 0.45);
        glVertex3f(0.53, 1.35, 0.45);
    glEnd();

    //Parede esquerda - andar 5 - torre esquerda
    glBegin(GL_POLYGON);
        glVertex3f(0.53, 1.15, 0.21);
        glVertex3f(0.33, 1.15, 0.21);
        glVertex3f(0.33, 1.35, 0.21);
        glVertex3f(0.53, 1.35, 0.21);
    glEnd();

    //Parede fundo - andar 5 - torre esquerda
    glBegin(GL_POLYGON);
        glVertex3f(0.33, 1.15, 0.21);
        glVertex3f(0.33, 1.15, 0.45);
        glVertex3f(0.33, 1.35, 0.45);
        glVertex3f(0.33, 1.35, 0.21);
    glEnd();

    //Parede frente - andar 5 - torre esquerda
    glBegin(GL_POLYGON);
        glVertex3f(0.53, 1.15, 0.21);
        glVertex3f(0.53, 1.15, 0.45);
        glVertex3f(0.53, 1.35, 0.45);
        glVertex3f(0.53, 1.35, 0.21);
    glEnd();
 

    //Colunas
    glColor3f(0.96, 0.96, 0.86);
    drawColuna(0.59, 0.5, 0.0, 0.015, 1.4);
    drawColuna(0.59, -0.5, 0.0, 0.015, 1.4);
    drawColuna(0.59, 0.16, 0.41, 0.010, 1.0);
    drawColuna(0.59, -0.16, 0.41, 0.010, 1.0);


  glPopMatrix();  
  glFlush();
  glutSwapBuffers();
 }

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle=45;
    
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    gluLookAt(0,0,radius, 0,0,0, 0,1,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(angle,fAspect,0.5,500);

    PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

// Callback para gerenciar eventos do teclado para teclas especiais (F1, PgDn, entre outras)
void SpecialKeys(int key, int x, int y)
        {
        printf("%f\n", phi);

        glLoadIdentity();
        switch (key) {
            case 0:
                phi = PI/2;
                theta = 0;
                break;
            case GLUT_KEY_LEFT : 
                //isRotate = true;
                theta += inc;
                break;
            case GLUT_KEY_RIGHT :
                //isRotate = true; 
                theta -= inc;
                break;
            case GLUT_KEY_DOWN:
                //isRotate = true;
                if(phi + inc <= PI/2) phi += inc;  
                break;
            case GLUT_KEY_UP: 
                //isRotate = true;
                if(phi - inc >= 0) phi -= inc;
                break;
            case 'z' :
                radius -= 0.1;
                //isRotate = false;
                //walkZ -= 5;
                //centerZ -= 5;
                break;
            case 'x' : 
                radius += 0.1;
                //isRotate = false;
                //walkZ += 5;
                //centerZ += 5;
                break;
            // case GLUT_KEY_HOME :
            //     isRotate = false;
            //     walkX -= 5;
            //     //centerX -= 5;
            //     break;
            // case GLUT_KEY_END : 
            //     isRotate = false;
            //     walkX += 5;
            //     //centerX += 5;
            //     break;
                
        }

        phi = std::fmod(phi, 2*PI);
        // printf("Theta: %f. Phi: %f.\n", theta, phi);
        // printf("%f, %f, %f\n", radius*sin(theta)*sin(phi),radius*cos(phi),radius*cos(theta)*sin(phi));
        

        //if(isRotate) {
            gluLookAt(radius*sin(theta)*sin(phi),radius*cos(phi),radius*cos(theta)*sin(phi), centerX,centerY,centerZ, 0,1,0);
            //gluLookAt(radius*cos(phi),radius*cos(theta)*sin(phi)*-1, radius*sin(theta)*sin(phi), centerX,centerY,centerZ, 0,1,0);

        // } else {
        //     gluLookAt(X, 0, radius + walkZ, walkX,0,walkZ, 0,1,0);
        // }

        glutPostRedisplay();
        }

// Programa Principal
int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Catedral");

    glutDisplayFunc(Display);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutSpecialFunc(SpecialKeys);
    Inicializa();
    glutMainLoop();
}

