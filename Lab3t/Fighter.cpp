#include "Fighter.h"



bool Fighter::SearchWay(int count)
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
				mmap->SyncPowers(id-1,5);
				break;
			case 1:
				mmap->SyncPowers(id-1,5);
				break;
			case 2:
				mmap->SyncPowers(id-1,10);
				break;
			case 3:
				mmap->SyncPowers(id-1,1);
				break;
		}
	 
	return changing;
}

int Fighter::Seq(int i)
{
	if(i==0)
		return 2;
	else if(i==2)
		return 0;
	else 
		return i;
}


