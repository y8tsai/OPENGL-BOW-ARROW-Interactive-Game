#include "LSysParam.h"

LSysParam::LSysParam() {
	iterations = 1;
	length = 0.125f;
	yawMin = DEG2RAD(15.0f);
	yawMax = DEG2RAD(30.0f);

	radius = 0.01f;
	segments = 4;

	/*rules['X'] = "F-[[X]+X]+F[+FX]-X";
	rules['F'] = "FF";*/
	/*rules['X'] = "F+F-[[X]+X]-F";
	rules['F'] = "FF";*/
	rules['X'] = "F";
	startRule = 'X';
}