#pragma once
#include "MyMap.h"

class Standart
{
protected:

	int id;
	bool disabled;
	MyMap *mmap;

public:
	Standart(){};
	Standart(MyMap*,int);
	bool SearchWay(int);
};

