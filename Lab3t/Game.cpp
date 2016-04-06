#include "Game.h"


Game::Game(int n,int m)
{
	system("cls");
	mmap = new MyMap(n,m);
	mmap->Generate();
	std::cout<<mmap;
	Sleep(1000);
	system("cls");
	stand= new Standart(mmap, 1);
	inv=new Invadar(mmap,2);
	fig=new Fighter(mmap,3);
	std::cout<<mmap;
}

bool Game::Turn(int speed)
{
	for(int i(0);i<4;++i)
		if(stand->SearchWay(i))
		{
			Sleep(speed);
			system("cls");
			std::cout<<mmap;
			ga:
			for(int j(0);j<4;++j)
				if(inv->SearchWay(inv->Seq(j)))
				{
					Sleep(speed);
					system("cls");
					std::cout<<mmap;
					if(mmap->GetDoubl(0))
						goto ga;
					else
					{
						gb:
						for(int k(0);k<4;++k)
							if(fig->SearchWay(fig->Seq(k)))
							{
								Sleep(speed);
								system("cls");
								std::cout<<mmap;
								if(mmap->GetDoubl(1))
									goto gb;
								else
									break;
							}
						break;
					}
					break;
				}
		}
	
	if(mmap->GetEnding())
		return false;
	return true;
}

