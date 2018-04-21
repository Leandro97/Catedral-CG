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
  	glRotatef( rotate_z, 0.0, 0.0, 1.0 );
 
 	//Chão
  	glBegin(GL_POLYGON);	
		glColor3f(0.9, 0.9, 0.9); 
  		glVertex3f(  0.8, -0.6, 0 );      
		glVertex3f(  0.8,  0.6, 0 );      
 		glVertex3f( -0.8,  0.6, 0 );      
 		glVertex3f( -0.8, -0.6, 0 );      
  	glEnd();


  	//Parede direita - andar 1
  	glColor3f( 0.96,  0.87, 0.7); //https://sistemas.riopomba.ifsudestemg.edu.br/dcc/materiais/926330044_Cores.pdf
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.5, 0.3 );
	 	glVertex3f(  -0.8,  0.5, 0.3 );
	 	glVertex3f(  -0.8,  0.5, 0 );
	 	glVertex3f(  0.6, 	0.5, 0 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.49, 0.3 );
	 	glVertex3f(  -0.8,  0.49, 0.3 );
	 	glVertex3f(  -0.8,  0.49, 0 );
	 	glVertex3f(  0.6, 	0.49, 0 );
	glEnd();
	 
	//Parede esquerda - andar 1
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.5, 0.3 );
	 	glVertex3f(  -0.8,  -0.5, 0.3 );
	 	glVertex3f(  -0.8,  -0.5, 0 );
	 	glVertex3f(  0.6,   -0.5, 0 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.49, 0.3 );
	 	glVertex3f(  -0.8,  -0.49, 0.3 );
	 	glVertex3f(  -0.8,  -0.49, 0 );
	 	glVertex3f(  0.6, 	-0.49, 0 );
	glEnd();

	//Parede fundo - andar 1
	glBegin(GL_POLYGON);
	 	glVertex3f(  -0.8, 	-0.5, 0.3 );
	 	glVertex3f(  -0.8,  0.5, 0.3 );
	 	glVertex3f(  -0.8,  0.5, 0 );
	 	glVertex3f(  -0.8,   -0.5, 0 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  -0.79, 	-0.5, 0.3 );
	 	glVertex3f(  -0.79,  0.5, 0.3 );
	 	glVertex3f(  -0.79,  0.5, 0 );
	 	glVertex3f(  -0.79,   -0.5, 0 );
	glEnd();


	//Teto - andar 1 - camada 1 // Falta fechar os lados
	glColor3f( 0.87,  0.72, 0.53);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6001, 	-0.5, 0.3 );
	 	glVertex3f(  -0.8,  -0.5, 0.3 );
	 	glVertex3f(  -0.8,  0.5, 0.3 );
	 	glVertex3f(  0.6001,   0.5, 0.3 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6001, 	-0.5, 0.301 );
	 	glVertex3f(  -0.8,  -0.5, 0.301 );
	 	glVertex3f(  -0.8,  0.5, 0.301 );
	 	glVertex3f(  0.6001,   0.5, 0.301 );
	glEnd();
	

	//Teto - andar 1 - camada 2 // Falta fechar os lados
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.601, -0.5, 0.301 );
	 	glVertex3f(  -0.8,  -0.5, 0.301 );
	 	glVertex3f(  -0.8,  0.5, 0.301 );
	 	glVertex3f(  0.601,  0.5, 0.301 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.601, -0.5, 0.31 );
	 	glVertex3f(  -0.8,  -0.5, 0.31 );
	 	glVertex3f(  -0.8,  0.5, 0.31 );
	 	glVertex3f(  0.601,  0.5, 0.31 );
	glEnd();

	//Teto - andar 1 - camada 3  // Falta fechar os lados
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.601, -0.5, 0.31 );
	 	glVertex3f(  -0.8,  -0.5, 0.31 );
	 	glVertex3f(  -0.8,  0.5, 0.31 );
	 	glVertex3f(  0.601,  0.5, 0.31 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.61, -0.5, 0.3101 );
	 	glVertex3f(  -0.8,  -0.5, 0.3101 );
	 	glVertex3f(  -0.8,  0.5, 0.3101 );
	 	glVertex3f(  0.61,  0.5, 0.3101 );
	glEnd();


	//Parede direita - andar 2
  	glColor3f( 0.96,  0.87, 0.7);
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.5, 0.6 );
	 	glVertex3f(  -0.8,  0.5, 0.6 );
	 	glVertex3f(  -0.8,  0.5, 0.31 );
	 	glVertex3f(  0.6, 	0.5, 0.31 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	0.49, 0.6 );
	 	glVertex3f(  -0.8,  0.49, 0.6 );
	 	glVertex3f(  -0.8,  0.49, 0.31 );
	 	glVertex3f(  0.6, 	0.49, 0.31 );
	glEnd();

		//Parede esquerda - andar 2
	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.5, 0.6 );
	 	glVertex3f(  -0.8,  -0.5, 0.6 );
	 	glVertex3f(  -0.8,  -0.5, 0.31 );
	 	glVertex3f(  0.6,   -0.5, 0.31 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  0.6, 	-0.49, 0.6 );
	 	glVertex3f(  -0.8,  -0.49, 0.6 );
	 	glVertex3f(  -0.8,  -0.49, 0.31 );
	 	glVertex3f(  0.6, 	-0.49, 0.31);
	glEnd();

	//Parede fundo - andar 1
	glBegin(GL_POLYGON);
	 	glVertex3f(  -0.8, 	-0.5, 0.6 );
	 	glVertex3f(  -0.8,  0.5, 0.6 );
	 	glVertex3f(  -0.8,  0.5, 0.31 );
	 	glVertex3f(  -0.8,   -0.5, 0.31 );
	glEnd();

	glBegin(GL_POLYGON);
	 	glVertex3f(  -0.79, 	-0.5, 0.6 );
	 	glVertex3f(  -0.79,  0.5, 0.6);
	 	glVertex3f(  -0.79,  0.5, 0.31 );
	 	glVertex3f(  -0.79,   -0.5, 0.31 );
	glEnd();

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