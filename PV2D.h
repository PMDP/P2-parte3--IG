#pragma once
#include <GL/glut.h>

class PV2D {
private:
	GLdouble _x, _y;
	int _pv; // Si pv = 0 --> punto, si pv = 1 --> vector

public:
	PV2D() : _pv(1), _x(0), _y(0) {}
	PV2D(GLdouble x, GLdouble y, int pv);

	void normaliza();
	PV2D* clona();
	GLdouble productoEscalar(PV2D* v);
	//PV2D* productoVectorial(PV2D* v);

	GLdouble getX() { return _x; }
	GLdouble getY() { return _y; }

	void setX(GLdouble x) { _x = x; }
	void setY(GLdouble y) { _y = y; }
};