#pragma once
#include "Invadar.h"
#include "Fighter.h"

class Game
{
	MyMap *mmap;
	Standart *stand;
	Invadar *inv;
	Fighter *fig;

public:
	Game(int,int);
	bool Turn(int);
};


