#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

class MyMap
{ 
	std::vector<std::vector<std::pair<std::string, int> > > mas;
	int n,m;
	std::vector<std::string> res;
	int *powers;
	bool *disable;
	bool *doubl;

public:
	MyMap(int ,int);
	void Generate();
	friend std::ostream& operator<<(std::ostream& , MyMap*);
	void SetCol(unsigned int, std::string, std::ostream&);
	std::string GetRes(int)const;
	void SyncPowers(int,int);
	bool SyncDisabling(int)const;
	void UnDisabling(int);
	bool GetDoubl(int);
	std::pair<std::string, int> GetField(int ,int)const;
	std::pair<int, int> GetSize()const;
	bool ChangeOwner(std::pair<int,int>,int);
	std::pair<int,int> CheckRange(int,int, int);
	bool Fight(std::pair<int, int> ,int ,int, int);
	int Losing(int i,int j);
	std::pair<int,int> SearchField(int,std::string);
	bool GetEnding()const;
};
 
