#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"
class freezer :public Enemy
{
private:

	float ice;
	Castle *C;

public:
	freezer(int id, int arrTime, int power, int Speed, int RP, double health);\
		void Move();
	void Act();
	void IsActivated(int t);
	 void setCastlePtr(Castle* ptr);
	 Castle* getCastlePtr();
	~freezer(void);

};
