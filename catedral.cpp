#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

double rotate_y=0; 
double rotate_x=0;
double rotate_z=0;

GLUquadricObj *obj = gluNewQuadric();

void drawColuna(float x, float y, float z, float radius, float size){
  glPushMatrix();
    glTranslatef(x, y, z);
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluCylinder(obj, radius, radius, size, 100, 100);
  glPopMatrix();
}

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  	glRotatef( rotate_y, 0.0, 1.0, 0.0 );
  	glRotatef( rotate_z , 0.0, 0.0, 1.0 );
 
 	//Chão
  	glBegin(GL_POLYGON);	
		glColor3f(0.9, 0.9, 0.9); 
  		glVertex3f(  1.0, -0.6, -0.5 );      
		glVertex3f(  1.0,  0.6, -0.5 );      
 		glVertex3f( -1.0,  0.6, -0.5 );      
 		glVertex3f( -1.0, -0.6, -0.5 );      
  	glEnd();


  	//Parede direita - andar 1
  	glColor3f( 0.96, 0.87, 0.7); //https://sistemas.riopomba.ifsudestemg.edu.br/dcc/materiais/926330044_Cores.pdf
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.5, -0.1 );
	 	glVertex3f(  -1.0,  0.5, -0.1 );
	 	glVertex3f(  -1.0,  0.5, -0.5 );
	 	glVertex3f(  0.6, 	0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.49, -0.1 );
	 	glVertex3f(  -1.0,  0.49, -0.1 );
	 	glVertex3f(  -1.0,  0.49, -0.5 );
	 	glVertex3f(  0.6, 	0.49, -0.5 );
	glEnd();
	 
	//Parede esquerda - andar 1
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.5, -0.1 );
	 	glVertex3f(  -1.0,  -0.5, -0.1 );
	 	glVertex3f(  -1.0,  -0.5, -0.5 );
	 	glVertex3f(  0.6,   -0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.49, -0.1 );
	 	glVertex3f(  -1.0,  -0.49, -0.1 );
	 	glVertex3f(  -1.0,  -0.49, -0.5 );
	 	glVertex3f(  0.6, 	-0.49, -0.5 );
	glEnd();

	//Parede fundo - andar 1
	glBegin(GL_POLYGON);
	 	glVertex3f(  -1.0, 	-0.5, -0.1 );
	 	glVertex3f(  -1.0,  0.5, -0.1 );
	 	glVertex3f(  -1.0,  0.5, -0.5 );
	 	glVertex3f(  -1.0,   -0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  -0.79, 	-0.5, -0.1 );
	 	glVertex3f(  -0.79,  0.5, -0.1 );
	 	glVertex3f(  -0.79,  0.5, -0.5 );
	 	glVertex3f(  -0.79,   -0.5, -0.5 );
	glEnd();


	//Teto - andar 1 - camada 1 // Falta fechar os lados
	glColor3f( 0.87,  0.72, 0.53);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.605,   -0.505, -0.1 );
	 	glVertex3f(  -1.005,  -0.505, -0.1 );
	 	glVertex3f(  -1.005,  0.505, -0.1 );
	 	glVertex3f(  0.605,   0.505, -0.1 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.605, 	-0.505, -0.101 );
	 	glVertex3f(  -1.005,  -0.505, -0.101 );
	 	glVertex3f(  -1.005,  0.505, -0.101 );
	 	glVertex3f(  0.605,   0.005, -0.101 );
	glEnd();
	

	//Teto - andar 1 - camada 2 // Falta fechar os lados
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.61, -0.51, -0.109 );
	 	glVertex3f(  -1.01,  -0.51, -0.101 );
	 	glVertex3f(  -1.01,  0.51, -0.101 );
	 	glVertex3f(  0.61,  0.51, -0.101 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.61, -0.51, -0.09 );
	 	glVertex3f(  -1.01,  -0.51, -0.09 );
	 	glVertex3f(  -1.01,  0.51, -0.09 );
	 	glVertex3f(  0.61,  0.51, -0.09 );
	glEnd();

	//Parede direita - andar 2
  	glColor3f( 0.96, 0.87, 0.7);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.5, 0.25 );
	 	glVertex3f(  -1.0,  0.5, 0.25 );
	 	glVertex3f(  -1.0,  0.5, -0.09 );
	 	glVertex3f(  0.6, 	0.5, -0.09 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.49, 0.25 );
	 	glVertex3f(  -1.0,  0.49, 0.25 );
	 	glVertex3f(  -1.0,  0.49, -0.09 );
	 	glVertex3f(  0.6, 	0.49, -0.09 );
	glEnd();

	//Parede esquerda - andar 2
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.5, 0.25 );
	 	glVertex3f(  -1.0,  -0.5, 0.25 );
	 	glVertex3f(  -1.0,  -0.5, -0.09 );
	 	glVertex3f(  0.6,   -0.5, -0.09 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.49, 0.25 );
	 	glVertex3f(  -1.0,  -0.49, 0.25 );
	 	glVertex3f(  -1.0,  -0.49, -0.09 );
	 	glVertex3f(  0.6, 	-0.49, -0.09);
	glEnd();

	//Parede fundo - andar 1
	glBegin(GL_POLYGON);
	 	glVertex3f(  -1.0, 	-0.5, 0.25 );
	 	glVertex3f(  -1.0,  0.5, 0.25 );
	 	glVertex3f(  -1.0,  0.5, -0.09 );
	 	glVertex3f(  -1.0,   -0.5, -0.09 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  -0.79, 	-0.5, 0.25 );
	 	glVertex3f(  -0.79,  0.5, 0.25);
	 	glVertex3f(  -0.79,  0.5, -0.09 );
	 	glVertex3f(  -0.79,   -0.5, -0.09 );
	glEnd();

	//Teto - andar 2 - camada 1 // Falta fechar os lados
	glColor3f( 0.87,  0.72, 0.53);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.605, 	-0.505, 0.25 );
	 	glVertex3f(  -1.005,  -0.505, 0.25 );
	 	glVertex3f(  -1.005,  0.505, 0.25 );
	 	glVertex3f(  0.605,   0.505, 0.25 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.605, 	-0.505, 0.255 );
	 	glVertex3f(  -1.005,  -0.505, 0.2501 );
	 	glVertex3f(  -1.005,  0.505, 0.2501 );
	 	glVertex3f(  0.605,   0.505, 0.2501 );
	glEnd();
	
	//Teto - andar 2 - camada 2 // Falta fechar os lados
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.61, 	-0.51, 0.2501 );
	 	glVertex3f(  -1.01,  -0.51, 0.2501 );
	 	glVertex3f(  -1.01,  0.51, 0.2501 );
	 	glVertex3f(  0.61,   0.51, 0.2501 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.61, 	-0.51, 0.26 );
	 	glVertex3f(  -1.01,  -0.51, 0.26 );
	 	glVertex3f(  -1.01,  0.51, 0.26 );
	 	glVertex3f(  0.61,   0.51, 0.26 );
	glEnd();
	
	//Parede direita - andar 3
  	glColor3f( 0.96, 0.87, 0.7);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.5, 0.5 );
	 	glVertex3f(  0.3,  0.5, 0.5 );
	 	glVertex3f(  0.3,  0.5, 0.26 );
	 	glVertex3f(  0.6, 	0.5, 0.26 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.49, 0.5 );
	 	glVertex3f(  0.3,  0.49, 0.5 );
	 	glVertex3f(  0.3,  0.49, 0.26 );
	 	glVertex3f(  0.6, 	0.49, 0.26 );
	glEnd();

	//Parede esquerda - andar 3
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.5, 0.5 );
	 	glVertex3f(  0.3,  -0.5, 0.5 );
	 	glVertex3f(  0.3,  -0.5, 0.26 );
	 	glVertex3f(  0.6,  -0.5, 0.26 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.49, 0.5 );
	 	glVertex3f(  0.3,  -0.49, 0.5 );
	 	glVertex3f(  0.3,  -0.49, 0.26 );
	 	glVertex3f(  0.6,  -0.49, 0.26 );
	glEnd();

	//Parede fundo - andar 3
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.3, -0.5, 0.5 );
	 	glVertex3f(  0.3,  0.5, 0.5 );
	 	glVertex3f(  0.3,  0.5, 0.26 );
	 	glVertex3f(  0.3,  -0.5, 0.26 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  2.9, -0.5, 0.5);
	 	glVertex3f(  2.9,  0.5, 0.5);
	 	glVertex3f(  2.9,  0.5, 0.26 );
	 	glVertex3f(  2.9,  -0.5, 0.26 );
	glEnd();
	
	//Teto - andar 3 - camada 1 // Falta fechar os lados
	glColor3f( 0.87,  0.72, 0.53);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.61, 	-0.51, 0.5 );
	 	glVertex3f(  0.28,  -0.51, 0.5 );
	 	glVertex3f(  0.28,  0.51, 0.5 );
	 	glVertex3f(  0.61,   0.51, 0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.61, 	-0.51, 0.51 );
	 	glVertex3f(  0.28,  -0.51, 0.51 );
	 	glVertex3f(  0.28,  0.51, 0.51 );
	 	glVertex3f(  0.61,   0.51, 0.51 );
	glEnd();

	//Parede direita - andar 4 - torre direita
  	glColor3f( 0.96, 0.87, 0.7);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.56, 	0.48, 0.51 );
	 	glVertex3f(  0.34,  0.48, 0.51 );
	 	glVertex3f(  0.34,  0.48, 0.65 );
	 	glVertex3f(  0.56, 	0.48, 0.65 );
	glEnd();


	//Parede esquerda - andar 4 - torre direita
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.56,  0.18, 0.51 );
	 	glVertex3f(  0.34,  0.18, 0.51 );
	 	glVertex3f(  0.34,  0.18, 0.65 );
	 	glVertex3f(  0.56,  0.18, 0.65 );
	glEnd();

	
	//Parede fundo - andar 4 - torre direita
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.34,  0.18, 0.51 );
	 	glVertex3f(  0.34,  0.48, 0.51 );
	 	glVertex3f(  0.34,  0.48, 0.65 );
	 	glVertex3f(  0.34,  0.18, 0.65 );
	glEnd();

	
	//Parede frente - andar 4 - torre direita
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.56,  0.18, 0.51 );
	 	glVertex3f(  0.56,  0.48, 0.51 );
	 	glVertex3f(  0.56,  0.48, 0.65 );
	 	glVertex3f(  0.56,  0.18, 0.65 );
	glEnd();

	//Teto - andar 4 - torre direita
	glColor3f( 0.87,  0.72, 0.53);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.5605, 	0.1805, 0.65 );
	 	glVertex3f(  0.3405,  0.1805, 0.65 );
	 	glVertex3f(  0.3405,  0.4805, 0.65 );
	 	glVertex3f(  0.5605,   0.4805, 0.65 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.5605, 	0.1805, 0.655 );
	 	glVertex3f(  0.3405,  0.1805, 0.655 );
	 	glVertex3f(  0.3405,  0.4805, 0.655 );
	 	glVertex3f(  0.5605,   0.4805, 0.655 );
	glEnd();
	
	//Parede direita - andar 4 - torre esquerda
  	glColor3f( 0.96, 0.87, 0.7);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.56, 	-0.48, 0.51 );
	 	glVertex3f(  0.34,  -0.48, 0.51 );
	 	glVertex3f(  0.34,  -0.48, 0.65 );
	 	glVertex3f(  0.56, 	-0.48, 0.65 );
	glEnd();

	//Parede esquerda - andar 4 - torre esquerda
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.56,  -0.18, 0.51 );
	 	glVertex3f(  0.34,  -0.18, 0.51 );
	 	glVertex3f(  0.34,  -0.18, 0.65 );
	 	glVertex3f(  0.56,  -0.18, 0.65 );
	glEnd();

	//Parede fundo - andar 4 - torre esquerda
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.34,  -0.18, 0.51 );
	 	glVertex3f(  0.34,  -0.48, 0.51 );
	 	glVertex3f(  0.34,  -0.48, 0.65 );
	 	glVertex3f(  0.34,  -0.18, 0.65 );
	glEnd();


	//Parede frente - andar 4 - torre esquerda
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.56,  -0.18, 0.51 );
	 	glVertex3f(  0.56,  -0.48, 0.51 );
	 	glVertex3f(  0.56,  -0.48, 0.65 );
	 	glVertex3f(  0.56,  -0.18, 0.65 );
	glEnd();

	//Teto - andar 4 - torre esquerda
	glColor3f( 0.87,  0.72, 0.53);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.5605, 	-0.1805, 0.65 );
	 	glVertex3f(  0.3405,  -0.1805, 0.65 );
	 	glVertex3f(  0.3405,  -0.4805, 0.65 );
	 	glVertex3f(  0.5605,   -0.4805, 0.65 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.5605, 	-0.1805, 0.655 );
	 	glVertex3f(  0.3405,  -0.1805, 0.655 );
	 	glVertex3f(  0.3405,  -0.4805, 0.655 );
	 	glVertex3f(  0.5605,   -0.4805, 0.655 );
	glEnd();
	


	//Colunas
	glColor3f( 0.96, 0.96, 0.86);
	drawColuna(0.59, 0.5, -0.5, 0.015, 1.3);
	drawColuna(0.59, -0.5, -0.5, 0.015, 1.3);
	drawColuna(0.59, 0.16,  -0.11, 0.010, 1.0);
	drawColuna(0.59, -0.16, -0.11, 0.010, 1.0);


  glFlush();
  glutSwapBuffers();

 
}



void specialKeys( int key, int x, int y ) {
 
  //  Seta direita - aumenta rotação em 5 graus
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
 
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
  
  else if (key == 'z')
    rotate_z += 5;
  
  else if (key == 'x')
    rotate_z -= 5;

  glutPostRedisplay();
 
}

int main(int argc, char* argv[]){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Catedral");
	glutSpecialFunc(specialKeys);

	init();
	glEnable(GL_DEPTH_TEST);
   	glutDisplayFunc(display);
	glutMainLoop();
  
  	return 0;
}