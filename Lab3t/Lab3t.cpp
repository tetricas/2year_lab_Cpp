// Lab3t.cpp: определяет точку входа для консольного приложения.
//

#include "Game.h"


int main()
{
	int speed;
	std::cout<<"Choose speed(ms): ";
	std::cin>>speed;
	Game game(10,5);
	while(game.Turn(speed)){;}
		
	system("PAUSE");
	return 0;
}

