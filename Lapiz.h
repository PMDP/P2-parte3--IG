#pragma once
#include "PV2D.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>
class Lapiz
{
private:
	PV2D* _pos; //Posici�n actual
	GLdouble _dir; //Direcci�n actual
public:
	Lapiz();
	Lapiz(PV2D* p, GLdouble d);
	~Lapiz();
	void moveTo(PV2D* p, bool draw);
	void turnTo(GLdouble a);
	void turn(GLdouble a);
	void forward(GLdouble dist, bool draw);
	GLdouble getDir();
	PV2D* getPos();
};

