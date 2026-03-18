#ifndef VARS_H
#define VARS_H

#include <list>
#include <cstdint>
#include "console.h"
#include "sand.h"
#include "elements.h"
#define MAXPARAMETERS 1024
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct Var {
	char name[255];
	int value;
};

struct Varint {
	Varint(int value);
	Varint(char* value, int max = 32768);
	Varint(char* v, int max, int f);
	Varint();
	char* value;
	char* text;
	int fixedvalue;
	int val();
	int ok;
	~Varint();
	Varint* a;
	Varint* b;
	int function;
	Var* varvalue;
	int max;
	void* trigger;
	Varint** params;
};

std::list<Var*>* getVars();
uintptr_t setVar(char* name, int value, bool set = true);
int getVar(char* name, int* value);

extern int* parameters[MAXPARAMETERS + 1];
extern int parameterpos;
extern Var* debugparameter;
extern Var* debugvar;

inline void addparams(int* params) {
	if (debugparameter->value && params) {
		char tmp[512];
		snprintf(tmp, sizeof(tmp), "setting parameters: %i %i %i %i %i %i %i %i %i %i",
			params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9]);
		std::cout << tmp << std::endl;
	}
	if (parameterpos == MAXPARAMETERS) {
#if LOGLEVEL > 0
		error("PARAMETER ADD ERROR", 0);
#endif
		return;
	}
	parameters[++parameterpos] = params;
}

inline void removeparams(bool del = true) {
	if (parameterpos == -1) {
#if LOGLEVEL > 0
		error("PARAMETER REMOVE ERROR", 0);
#endif
		return;
	}
	int* param = parameters[parameterpos];
	if (del) delete (param);
	parameters[parameterpos--] = 0;
	if (debugparameter->value && param) {
		char tmp[512];
		snprintf(tmp, sizeof(tmp), "removing parameters to: %i %i %i %i %i %i %i %i %i %i",
			param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7], param[8], param[9]);
		std::cout << tmp << std::endl;
	}
}

#endif
