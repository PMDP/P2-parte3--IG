#include "Lapiz.h"


Lapiz::Lapiz(){
	_pos = new PV2D(0.0, 0.0, 0);
	_dir = 0.0;
}
Lapiz::Lapiz(PV2D* p, GLdouble d){
	_pos = p->clona();
	_dir = d;
}

Lapiz::~Lapiz()
{
	delete _pos;
}

void Lapiz::moveTo(PV2D* p, bool draw){
	PV2D* p_ant = _pos->clona();;
	_pos = p->clona();
	if (draw){
		glBegin(GL_LINES);
		glVertex2d(p_ant->getX(), p_ant->getY());
		glVertex2d(_pos->getX(), _pos->getY());
		glEnd();
	}
}

void Lapiz::turnTo(GLdouble a){
	_dir = a*M_PI/180;
}

void Lapiz::turn(GLdouble a){
	_dir += a*M_PI/180;
}

void Lapiz::forward(GLdouble dist, bool draw){
	PV2D* p_ant = _pos->clona();
	_pos->setX(_pos->getX() + dist*cos(_dir));
	_pos->setY(_pos->getY() + dist*sin(_dir));
	if (draw){
		glBegin(GL_LINES);
		glVertex2d(p_ant->getX(), p_ant->getY());
		glVertex2d(_pos->getX(), _pos->getY());
		glEnd();
	}
}

GLdouble Lapiz::getDir(){
	return _dir;
}

PV2D* Lapiz::getPos(){
	return _pos->clona();
}
