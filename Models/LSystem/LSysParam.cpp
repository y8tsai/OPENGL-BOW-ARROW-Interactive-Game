#include "LSysParam.h"

LSysParam::LSysParam() {
	iterations = 5;
	length = 0.15f;
	yawMin = 15.0f;
	yawMax = 30.0f;

	radius = 0.05f;
	segments = 6;

	rules['X'] = "F-[[X]+X]+F[+FX]-X";
	rules['F'] = "FF";
	startRule = 'X';
}