#include "healer.h"


healer::healer(int id, int arrTime, int power, int Speed, int RP, double health) :Enemy(id, arrTime)
{
	SetPower(power);
	SetSpeed(Speed);
	SetRelPeriod(RP);
	SetHealth(health);
	SetOrgHealth(health);
	SetType(HEALER);
	SetStatus(INAC);
	RelTime = RP;
	//direction = false; //move towrd the castle  
	heal = 0;
	SetDirection(false);
}

void healer::Move()
{
	int k = getK();
	int s = GetSpeed(); // speed 

	if ((Distance > MinDistance) && (k == 0.5) && (GetDirection() == false))
	{
		s = s / 2;//dec the speed to half bec the health < 0.5 org helath
		Distance -= s; // dec the distance 
	}
	else if ((Distance > MinDistance) && (k == 1) && (GetDirection() == false))
	{
		Distance -= s; // dec th edistace by normal speed 
	}

	if (Distance < MinDistance) // if it exceed the limit return to it
	{
		Distance = MinDistance;
		SetDirection(true); // change the direction
		return;
	}


	/////// will move in the oppsite direction
	if ((Distance < MaxDistance) && (k == 0.5) && (GetDirection() == true))
	{
		s = s / 2;//dec the speed to half bec the health < 0.5 org helath
		Distance += s; // dec the distance 
	}
	else if ((Distance < MaxDistance) && (k == 1) && (GetDirection() == true))
	{
		Distance += s; // dec th edistace by normal speed 
	}

	if (Distance > MaxDistance) // if it exceed the limit return to it
	{
		Distance = MaxDistance;
		SetDirection( false); // change direction 
		return;

	}

}

void healer::Act()
{
	
	if (RelPeriod == RelTime)//ready to shot
	{
		float d, h, l; // d-> distance h ->distance between them l ->health of the enemy 


		if (status == ACTV)
		{
			RelTime--;// dec the relod time 
			d = Distance - E->GetDistance(); // distance between them 
			if (d<2 && d>-2)
			{
				h = 2;// for distance between them
				if (E->GetHealth() <= E->GetOrgHealth())
					l = 2; // health of the enemy
				else
					l = 1;


				heal = Power * (h * l * getK()/Distance);
				E->SetHealth(E->GetHealth() + heal);
			}
			else if (d == 2 || d == -2)
			{
				h = 1;// for distance between them
				if (E->GetHealth() <= E->GetOrgHealth())
					l = 2; // health of the enemy
				else
					l = 1;
				heal = Power * (h * l * getK()/Distance);
				E->SetHealth(E->GetHealth() + heal);
			}
		}
	}
	else  // still in relod time 
	{
		RelTime--; // dec the relod time 
		if (RelTime == -1)
		{
			RelTime=RelPeriod; // next time will be ready to shoot
		}
	}


}
void healer::IsActivated(int time)
{
	if (time == ArrvTime)
	{
		status = ACTV; // arrive time so set it to active state 
	}
}
void healer::sethealead(Enemy * ptr)
{
	E = ptr;
}
Enemy* healer::gethealed()
{
	return E;
}
healer::~healer(void)
{
}

bool healer::GetDirection()
{
	return direction;
}

void healer::SetDirection(bool dir)
{
	direction = dir;
}