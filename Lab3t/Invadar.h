#pragma once
#include "Standart.h"

class Invadar :
	public Standart
{
public:
	Invadar(MyMap* m,int hero):Standart(m,hero){};
	bool SearchWay(int);
	int Seq(int);
};

