#pragma once
#include "Standart.h"

class Fighter :
	public Standart
{
public:
	Fighter(MyMap* m,int hero):Standart(m,hero){};
	bool SearchWay(int);
	int Seq(int);
};

