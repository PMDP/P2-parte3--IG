#include "PV2D.h"
#include <cmath>

PV2D::PV2D(GLdouble x, GLdouble y, int pv) {
	_x = x;
	_y = y;

	_pv = pv;
}

void PV2D::normaliza() {
	GLdouble modulo = sqrt(_x * _x + _y * _y);
	_x = _x / modulo;
	_y = _y / modulo;
}

PV2D* PV2D::clona() {
	PV2D *punto = new PV2D(); 

	punto->_x = _x;
	punto->_y = _y;
	punto->_pv = _pv;

	return punto;
}
GLdouble PV2D::productoEscalar(PV2D* v) {
	GLdouble escalar = _x * v->_x + _y * v->_y;
	return escalar;
}
//PV2D* PV2D::productoVectorial(PV2D* v) {
//	GLdouble x, y, z;
//	
//	x = _y*v->_z - _z*v->_y;
//	y = _z*v->_x - _x*v->_z;
//	z = _x*v->_y - _y*v->_x;
//
//	return new PV3D(x, y, z, 1);
//}
