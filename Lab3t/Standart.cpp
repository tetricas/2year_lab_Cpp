#include "Standart.h"


Standart::Standart(MyMap* m, int hero)
{
	mmap=m;
	id=hero;
	disabled=false;
	srand(time(NULL));

	while(1)
	{
		int x=rand()%mmap->GetSize().first, y=rand()%mmap->GetSize().second;
		if(mmap->GetField(x,y).first=="-------"&&mmap->GetField(x,y).second==0)
		{
			std::pair<int,int> coords;
			coords.first=x;
			coords.second=y;
			if(mmap->ChangeOwner(coords,id))
				break;
		}
	}
}

bool Standart::SearchWay(int count)
{	
	if(disabled)
	{
		mmap->SyncPowers(id-1,30);
		mmap->UnDisabling(id-1);
		disabled =false;
	}

	if(mmap->SyncDisabling(id-1))
	{
		disabled=true;
		mmap->SyncPowers(id-1,-30);
	}

	bool changing = mmap->ChangeOwner(mmap->SearchField(id,mmap->GetRes(count)),id);
	if(changing)
		switch (count)
		{
			case 0:
				mmap->SyncPowers(id-1,10);
				break;
			case 1:
				mmap->SyncPowers(id-1,5);
				break;
			case 2:
				mmap->SyncPowers(id-1,5);
				break;
			case 3:
				mmap->SyncPowers(id-1,1);
				break;
		}


	 
	return changing;
}


