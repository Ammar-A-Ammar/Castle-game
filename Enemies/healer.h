#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"
 
 
class healer :public Enemy
{
private:
	bool direction;
	Enemy* E;
	float heal;


public:
	healer(int id, int arrTime, int power, int Speed, int RP, double health);
	~healer(void);
	void Move();
	void Act();
	void sethealead(Enemy * ptr);
	Enemy* gethealed();
	void SetDirection(bool dir);
	bool GetDirection();
	void IsActivated(int time);

};
