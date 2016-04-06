#include "MyMap.h"


MyMap::MyMap(int x, int y):n(x),m(y)
{
	powers=new int[3];
	disable=new bool[3];
	doubl=new bool[2];
	doubl[0]=false;
	doubl[1]=false;
	for(int i(0);i<3;++i)
	{
		disable[i]=false;
		powers[i]=1;
	}
	res.push_back("gold");
	res.push_back("silver");
	res.push_back("copper");
	res.push_back("-------");
}

void MyMap::Generate()
{
	srand(time(NULL));
	for(int i(0); i<n; ++i)
	{
		std::vector<std::pair<std::string, int> > buf;
		for(int j(0); j<m; ++j)
		{
			std::pair<std::string, int> p_buf;
			p_buf.first=res[3];
			p_buf.second=0;
			buf.push_back(p_buf);
		}
		mas.push_back(buf);
	}

	for(int i(0); i<n; ++i)
        for(int j(0); j<m; ++j)
        {
            int c=rand()%10;

			switch (c)
			{
				case 7:
					mas[i][j].first=res[0];
					break;
				case 8:
					mas[i][j].first=res[1];
					break;
				case 9:
					mas[i][j].first=res[2];
					break;
			}
  
        }
}

std::ostream& operator<<(std::ostream& out, MyMap* mmap)
{
	for(int i(0); i<mmap->n; ++i, std::cout<<std::endl)
		for(int j(0); j<mmap->m; ++j, std::cout<<"\t")
			if(mmap->mas[i][j].second==1)
				mmap->SetCol(12,mmap->mas[i][j].first, out);
			else if(mmap->mas[i][j].second==2)
				mmap->SetCol(9,mmap->mas[i][j].first, out);
			else if(mmap->mas[i][j].second==3)
				mmap->SetCol(10,mmap->mas[i][j].first, out);
			else if(mmap->mas[i][j].first=="-------")
				mmap->SetCol(15,mmap->mas[i][j].first, out);
			else if(mmap->mas[i][j].first=="gold")
				mmap->SetCol(14,mmap->mas[i][j].first, out);
			else if(mmap->mas[i][j].first=="silver")
				mmap->SetCol(8,mmap->mas[i][j].first, out);
			else if(mmap->mas[i][j].first=="copper")
				mmap->SetCol(6,mmap->mas[i][j].first, out);
	std::cout<<mmap->powers[0]<<' '<<mmap->powers[1]<<' '<<mmap->powers[2];
	return out;
}

void  MyMap::SetCol(unsigned int a, std::string c, std::ostream& out)
{
     HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(handle, a);
	 out<<c;
	 SetConsoleTextAttribute(handle, 15);
}

std::string MyMap::GetRes(int count)const
{
	return res[count];
}

void MyMap::SyncPowers(int numb,int count)
{
	/*int c;
	c=powers[numb]+count;
	if(c<0)
		powers[numb]=0;
	else*/
		powers[numb]+=count;
}

bool MyMap::SyncDisabling(int hero)const
{
	return disable[hero];
}

void MyMap::UnDisabling(int hero)
{
	disable[hero]=false;
}

bool MyMap::GetDoubl(int x)
{
	return doubl[x];;
}
	
std::pair<std::string, int> MyMap::GetField(int n,int m)const
{
	return mas[n][m];
}

std::pair<int, int> MyMap::GetSize()const
{
	std::pair<int, int> buf;
	buf.first=n;
	buf.second=m;
	return buf;
}

bool MyMap::ChangeOwner(std::pair<int,int> coords, int hero)
{
	if(coords.first==1000&&coords.second==1000)
		return false;
	mas[coords.first][coords.second].second=hero;
	return true;
}

std::pair<int,int> MyMap::CheckRange(int i,int j, int hero)
{
	if(i<n-1)
		if(mas[i+1][j].second==hero)
		{
			std::pair<int,int> buf;
			buf.first=i+1;
			buf.second=j;
			return buf;
		}
	if(i>0)
		if(mas[i-1][j].second==hero)
		{
			std::pair<int,int> buf;
			buf.first=i-1;
			buf.second=j;
			return buf;
		}
	if(j<m-1)
		if(mas[i][j+1].second==hero)
		{
			std::pair<int,int> buf;
			buf.first=i;
			buf.second=j+1;
			return buf;
		}
	if(j>0)
		if(mas[i][j-1].second==hero)
		{
			std::pair<int,int> buf;
			buf.first=i;
			buf.second=j-1;
			return buf;
		}

	std::pair<int,int> buf;
	buf.first=1000;
	buf.second=1000;
	return buf;
}

bool MyMap::Fight(std::pair<int, int> coords,int i, int j, int hero)
{
	if(coords.first==1000)
		return false;
	if(doubl[1]&&hero==3)
		goto ga;
	if(mas[i][j].second==0)
	{
		if(!doubl[0]&&hero==2)
			doubl[0]=true;
		else if(hero==2)
			doubl[0]=false;
		return true;
	} 

	if(doubl[0]&&hero==2)
	{
		doubl[0]=false;
		return false;
	}
	ga:
	if(!doubl[1]&&hero==3)
		doubl[1]=true;
	else if(hero==3)
		doubl[1]=false;

	int a, b;
	a=powers[mas[coords.first][coords.second].second-1];
	b=powers[mas[i][j].second-1];

	double x;
	if(a+b>0)
		x=rand()%(a+b);
	else
		x=a > b ? a : b;
	if(b<(a+b)/10)
		b=(int)(a+b)/10;
	if(x>b)
	{
		disable[mas[i][j].second-1]=true;
		powers[mas[i][j].second-1]-=Losing(i,j);
		return true;
	}
	else
	{
		disable[mas[coords.first][coords.second].second-1]=true;
		return false;
	}
}

int MyMap::Losing(int i,int j)
{
	switch (mas[i][j].second-1)
		{
			case 0:
				if(mas[i][j].first=="-------")
					return 1;
				else if (mas[i][j].first=="gold")
					return 10;
				else if (mas[i][j].first=="silver")
					return 5;
				else if (mas[i][j].first=="copper")
					return 5;

			break;
			case 1:
				if(mas[i][j].first=="-------")
					return 1;
				else if (mas[i][j].first=="gold")
					return 5;
				else if (mas[i][j].first=="silver")
					return 10;
				else if (mas[i][j].first=="copper")
					return 5;

			break;
			case 2:
				if(mas[i][j].first=="-------")
					return 1;
				else if (mas[i][j].first=="gold")
					return 5;
				else if (mas[i][j].first=="silver")
					return 5;
				else if (mas[i][j].first=="copper")
					return 10;

			break;
		}
}

std::pair<int,int> MyMap::SearchField(int hero,std::string field)
{
	int count=0;
	srand(time(NULL));
	if(field=="-------")
		while(1)
		{
			//std::cout<<"IT`S A TRAP";
			count++;
			if(count==n*m)
			{
				goto ga;
			}
			int x=rand()%n, y=rand()%m;
			if(mas[x][y].first==field&&mas[x][y].second!=hero&&Fight(CheckRange(x,y,hero),x,y,hero))
			{
				std::pair<int,int> buf;
				buf.first=x;
				buf.second=y;
				return buf;
			}
		}
	ga:
	count=0;
	for(int i(0); i<n; ++i)
		for(int j(0); j<m; ++j)
		{
			if(mas[i][j].first==field&&mas[i][j].second!=hero&&Fight(CheckRange(i,j,hero),i,j,hero))
			{
				std::pair<int,int> buf;
				buf.first=i;
				buf.second=j;
				return buf;
			}
			count++;
			if(count==n*m)
			{
				std::pair<int,int> buf;
				buf.first=1000;
				buf.second=1000;
				return buf;
			}
		}
}

bool MyMap::GetEnding()const
{
	int count1=0,count2=0,count3=0;
	for(int i(0); i<n; ++i)
		for(int j(0); j<m; ++j)
		{
			if(mas[i][j].second==1)
				count1++;
			else if(mas[i][j].second==2)
				count2++;
			else if(mas[i][j].second==3)
				count3++;
		}
	if(count1==n*m)
	{
		std::cout<<"Red won!"<<std::endl;
		return true;
	} else if(count2==n*m)
	{
		std::cout<<"Blue won!"<<std::endl;
		return true;
	} else if(count3==n*m)
	{
		std::cout<<"Green won!"<<std::endl;
		return true;
	}
	else
		return false;
}