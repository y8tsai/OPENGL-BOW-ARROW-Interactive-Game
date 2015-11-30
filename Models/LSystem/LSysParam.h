#ifndef __LSYSPARAM_H__
#define __LSYSPARAM_H__

#include <string>
#include <map>
#include "math3d.h"

typedef std::map<char, std::string> RuleMap;
enum Grammar {
	DRAW = 'F',
	NOOP = 'X',
	TURNLEFT = '+',
	TURNRIGHT = '-',
	ROLLLEFT = '&',
	ROLLRIGHT = '^',
	SAVE = '[',
	RESTORE = ']'
};

struct LSysParam {
	LSysParam();

	int iterations;
	float length;
	float yawMin;
	float yawMax;

	float radius;
	int segments;

	RuleMap rules;
	char startRule;
};
#endif
