#define __win32


#ifdef __win32
	#include <Windows.h>
	#include <gl/GL.h>
	#include <gl/GLU.h>
#elif
	#include <GL/gl.h>
	#include <GL/glut.>
#endif

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "Lapiz.h"
#include "PV2D.h"
#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 1000, HEIGHT= 750;

// Scene visible area size
GLdouble xLeft= 0.0, xRight= 500.0, yBot= 0.0, yTop= 250.0;

// Scene variables
GLdouble xTriangle= 100.0, yTriangle= 100.0;
GLdouble triangleWidth= 100.0, triangleHeight= 50.0;

Lapiz* l;
int numRec = 0; //Número de rectángulos a pintar
GLdouble a = xRight-100; //Longitud del lado largo del rectángulo
GLdouble b = 2*a/(1+sqrt(5)); //Longitud del lado corto
GLdouble incrX = 50, incrY = 5; //Margenes de la esquina inferior izquierda del rectángulo
bool ojoCentro=false;
bool baldosas = false;
void drawScene();

void embaldosar(int nCol){
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	GLdouble h = w / SVAratio;
	int i = 0;
	for (GLint c = 0; c<nCol; c++){
		GLdouble currentH = 0;
		while ((currentH + h) <= HEIGHT){
			glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
			drawScene();
			currentH += h;

		}
	}
}
void desembaldosar() {
	glViewport(0, 0, WIDTH, HEIGHT);
}
void buildSceneObjects(){
	PV2D* origen = new PV2D(incrX, 5, 0);
	l = new Lapiz(origen,0);
}
void dibujaPuntos(){
	glBegin(GL_POINTS);
		glColor3f(0.0,1.0,0.0);
		glVertex2d(((a*a)/(2*a - b))+incrX, ((a*b - b*b)/(2*a - b))+incrY);//Ojo de Dios
		//glVertex2d((a*a)/(a+b), (b*b)/(a+b));
		glColor3f(1.0,0.0,0.0);
		glVertex2d((a/2)+incrX,(b/2)+incrY);//Centro del rectángulo
	glEnd();
}
void dibujaArco(PV2D* pIni, PV2D* pFin, GLdouble bAux, int i) {
	int N = 20;
	Lapiz* l2 = new Lapiz();
	PV2D* centro;
	l2->moveTo(pIni, 0);
	if (i % 4 == 0){
		l2->turnTo(0.0);
		l2->forward(bAux, 0);
	}
	else if (i % 4 == 1){
		l2->turnTo(-90);
		l2->forward(bAux, 0);
	}	
	else if (i % 4 == 2){
		l2->turnTo(0.0);
		l2->forward(-bAux, 0);
	}
	else if (i % 4 == 3){
		l2->turnTo(-90);
		l2->forward(-bAux, 0);
	}
	centro = l2->getPos();
	
	if (i % 4 == 0){
		l2->moveTo(pIni, 0);
	}
	else if (i % 4 == 1){
		l2->moveTo(pFin, 0);
	}
	else if (i % 4 == 2){
		l2->moveTo(pIni, 0);
	}
	else if (i % 4 == 3){
		l2->moveTo(pFin, 0);
	}
	for (int j = 1 ; j <= N; j++) {
		GLdouble alfa = ((M_PI / 2) / N) * j;
		GLdouble x = bAux * (cos(alfa));
		GLdouble y = bAux * (sin(alfa));
		
		if (i % 4 == 0) {
			x = -x;
		}
		else if (i % 4 == 1) {
		}
		else if (i % 4 == 2) {
			y = -y;
		}
		else if (i % 4 == 3) {
			x = -x;
			y = -y;
		}
	
		l2->moveTo(new PV2D(x + centro->getX(), y + centro->getY(),1),1);
	}
	//l2->moveTo(pFin, 1);
	delete l2;

}
void dibujaRectanguloAureo(int numRec){
	//Dibuja el primer rectángulo
	PV2D* origen = new PV2D(incrX, incrY, 0);
	l->moveTo(origen,false);
	l->turnTo(0.0);
	l->forward(a, true);
	l->turn(90);
	l->forward(b, true);
	l->turn(90);
	l->forward(a, true);
	l->turn(90);
	l->forward(b, true);

	GLdouble aAux = a;
	GLdouble bAux = b;
	PV2D* p = new PV2D(incrX,incrY,0);
	l->moveTo(p,0);
	PV2D* pIni;

	for(int i=0; i<numRec;i++){
		pIni = l->getPos();
		if(i%4 == 0){
			l->turnTo(0);
			l->forward(bAux,0);
			l->turnTo(90);
			l->forward(bAux,1);
		}
		else if(i%4 == 1){
			l->forward(-bAux,0);
			l->turnTo(0);
			l->forward(bAux,1);
		}
		else if(i%4 == 2){
			l->forward(-bAux,0);
			l->turnTo(-90);
			l->forward(bAux,1);
		}
		else if(i%4 == 3){
			l->forward(-bAux,0);
			l->turnTo(0);
			l->forward(-bAux,1);
		}

		dibujaArco(pIni, l->getPos(), bAux, i);

		GLdouble aAuxx = aAux;
		aAux = bAux;
		bAux = aAuxx - bAux;
	}
}
void intitGL(){

	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0); 

	glPointSize(4.0);
	glLineWidth(2.0);

	buildSceneObjects();
	
	// Viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    
	// Model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop);

 }

void drawScene() {
	glMatrixMode(GL_MODELVIEW);

	dibujaRectanguloAureo(numRec);
	dibujaPuntos();

}

void display(void){
  glClear( GL_COLOR_BUFFER_BIT );
  
  if (baldosas)
	  embaldosar(2);
  else
	  drawScene();
 

  glFlush();
  glutSwapBuffers();
}


void resize(int newWidth, int newHeight){
  //Resize Viewport
  WIDTH= newWidth;
  HEIGHT= newHeight;
  GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
  glViewport ( 0, 0, WIDTH, HEIGHT ) ;
  
  //Resize Scene Visible Area 
  //Se actualiza el área visible de la escena
  //para que su ratio coincida con ratioViewPort
  GLdouble SVAWidth= xRight-xLeft;
  GLdouble SVAHeight= yTop-yBot;
  GLdouble SVARatio= SVAWidth/SVAHeight;
  if (SVARatio >= RatioViewPort) {
	 // Increase SVAHeight
     GLdouble newHeight= SVAWidth/RatioViewPort;
	 GLdouble yMiddle= ( yBot+yTop )/2.0;
     yTop= yMiddle + newHeight/2.0;
     yBot= yMiddle - newHeight/2.0;
     }
  else {
     //Increase SVAWidth
     GLdouble newWidth= SVAHeight*RatioViewPort;
     GLdouble xMiddle= ( xLeft+xRight )/2.0;
	 xRight= xMiddle + newWidth/2.0;
     xLeft=  xMiddle - newWidth/2.0;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void zoom(GLdouble f, bool ojoCentro) {
	GLdouble anchoNew = (xRight - xLeft) / f;
	GLdouble altoNew = (yTop - yBot) / f;
	GLdouble centroX;
	GLdouble centroY;
	if (ojoCentro){
		centroX = ((a*a) / (2 * a - b)) + incrX;
		centroY = ((a*b - b*b) / (2 * a - b)) + incrY;
	}
	else{
		centroX = (a / 2) + incrX; // (xLeft + xRight) / 2.0; , 
		centroY = (b / 2) + incrY;// (yTop + yBot) / 2.0;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(centroX-anchoNew/2.0, centroX+anchoNew/2.0, centroY-altoNew/2.0, centroY+altoNew/2.0);
	display();
	xLeft = centroX - anchoNew / 2.0;
	xRight = centroX + anchoNew / 2.0;
	yBot = centroY - altoNew / 2.0;
	yTop = centroY + altoNew / 2.0;
}

void key(unsigned char key, int x, int y){
 
  bool need_redisplay = true;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;
  case 97://a
	  numRec++;
	  break;
  case 98://b
	  numRec--;
	  break;
  case 116://t
	  zoom(1.25,ojoCentro);
	  break;
  case 121://y
	  zoom(0.75,ojoCentro);
	  break;
  case 'd'://
	  ojoCentro = true;
	  break;
  case 'c'://
	  ojoCentro = false;
	  break;
	 case 111://o
	  baldosas = true;
	  break;
  case 112://p
	  baldosas = false;
	  desembaldosar();
	  break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}



int main(int argc, char *argv[]){
  cout<< "Starting console..." << endl;

  int my_window; //my window's identifier

  //Initialization
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (140, 140);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
  glutInit(&argc, argv);

  //Window construction
  my_window = glutCreateWindow( "Freeglut 2D-project" );
    
  //Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);

  //OpenGL basic setting
  intitGL();


  // Freeglut's main loop can be stopped executing (**)
  //while ( continue_in_main_loop )
  //  glutMainLoopEvent();

  // Classic glut's main loop can be stopped after X-closing the window,
  // using the following freeglut's setting (*)
  glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
    
  // Classic glut's main loop can be stopped in freeglut using (*)
  glutMainLoop(); 
  
  // We would never reach this point using classic glut
  system("PAUSE"); 
   
  return 0;
}
