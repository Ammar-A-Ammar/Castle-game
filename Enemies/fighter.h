#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"
class fighter :public Enemy
{
private : 
	int prio  ;// priority of the fighter 
	ENMY_TYPE Fighter;
	float fire ;
	Castle *c;//pointer on the castle
public:
	fighter(int id, int arrTime, int power, int Speed, int RP,double health);
	~fighter(void);
	void Move(); 
	void Act();
	 void IsActivate(int time);
	 int GetPrio();
	  void setCastlePtr(Castle* c);
	   Castle* getCastlePtr();
};
