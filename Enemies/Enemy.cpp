#include "Enemy.h"



Enemy::Enemy(int id, int arrTime, int d) :ID(id), ArrvTime(arrTime)
{
	SetDistance(d);
}
Enemy::~Enemy()
{
}
Enemy::Enemy(int id, int arrTime, ENMY_TYPE type, double Health, int Power, int RelPeriod, int speed) : ID(id), ArrvTime(arrTime)
{
	SetSpeed(speed);
	SetRelPeriod(RelPeriod);
	SetPower(Power);
	SetHealth(Health);
	SetType(type);
	actTime = arrTime;
	firstshotted = true;
	RelTime = RelPeriod;
}




void Enemy::setCastlePtr(Castle* ptr)
{
	ptrC = ptr;
}
Castle* Enemy::getCastlePtr()
{
	return ptrC;
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}







void Enemy::SetType(ENMY_TYPE type)
{

	Type = type;

}// set of type
ENMY_TYPE Enemy::GetType()
{
	return Type;

}// get of the type 



void Enemy::SetOrgHealth(int health)
{
	if (health > 0) // vaildation 
	{
		OrgHealth = health;
	}
	else
		OrgHealth = 0;
}// set of orginal health 
int Enemy::GetOrgHealth()
{
	return OrgHealth;
}// get of the orginal heath 


void Enemy::SetPower(int power1)
{
	if (power1 > 0) // valadtion 
	{
		Power = power1;
	}
	else
		Power = 0;

}// set of power 
int Enemy::GetPower()
{
	return Power;

}// get of the power


void Enemy::SetSpeed(int speed1)
{
	if (speed1 > 0) //validation
		speed = speed1;
	else speed = 0;

}// set the speed 
int Enemy::GetSpeed()
{
	return speed;

}// get the speed 



void Enemy::SetRelPeriod(int Time)
{
	if (Time > 0) // validation
		RelPeriod = Time;
	else RelTime = 0;
}	// set the relod time 
int Enemy::GetRelPeriod()
{
	return RelPeriod;
}// get the relod time 



void Enemy::SetFirstShotDelay()
{
	FirstShotDelay = FirstShotTime - ArrvTime;
}	// set firstshot delay 
int Enemy::GetFirdtSHotDelay()
{
	return FirstShotDelay;
}// get first shot delay



void Enemy::SetKilledDelay()
{
	KillDelay = killedtime - FirstShotTime;
}//set killed delay 
int Enemy::GetKilledDelay()
{
	return KillDelay;
}	// get killed elay



void Enemy::SetLifeTime()
{
	LifeTime = killedtime - ArrvTime;
}
// get life time 
int Enemy::GetLIfeTime()
{
	return LifeTime;
}// get life time 



void  Enemy::SetHealth(double Health1)
{
	if (Health1 > 0)
		Health = Health1;
	else
		Health = 0;
}// set helath 
int  Enemy::GetHealth()
{
	return Health;
}// get health



void Enemy::setK() // K for equation of fighter
{
	K = 1;
}
float  Enemy::getK()
{
	if (Health < 0.5 * OrgHealth)
		return 0.5;
	else
		return 1;

}


void Enemy::SetKTS(int num)
{
	KilledAt = num;
}

int Enemy::GetKTS()
{
	return KilledAt;
}

void Enemy::CheckKTS(int TimeStep)
{

	if (isKilled() == true)
	{
		KilledAt = TimeStep;
	}

}

void Enemy::SetPriority()
{
	int k;

	if (GetStatus() == ACTV)
		k = 3;

	else if (GetStatus() == FRST)
		k = 2;

	else if (GetStatus() == KILD)
		k = 1;

	Priority = ((Health * k) / Distance) + Power;
}

double Enemy::GetPriority()
{
	return Priority;
}

void Enemy::getAttacked(float h, int timestep)
{
	if (firstshotted) // if it is the first shot (Y-> timestep = fisrtshotTime )
	{
		FirstShotTime = timestep;
		firstshotted = false;
	}
	Health = Health - h; // dec the health
	if (Health <= 0)
	{
		status = KILD;//killed
		killedtime = timestep; // time that the enmey get killed 
	}


}

void Enemy::getFreezed(int t, int timestep)
{
	if (status == FRST) // if its alraedy frosted no effect
		return;

	if (firstshotted) // if it is the first shot (Y-> timestep = fisrtshotTime )
	{
		FirstShotTime = timestep;
		firstshotted = false;
	}

	status = FRST; // change the status 

	FrezzingTime = t; // set  freezing time 
	return;

}



void Enemy::deforsted() // defrost the ice 
{
	if (status == FRST)
	{
		if (FrezzingTime > 0)
		{
			FrezzingTime--; // dec by 1 
		}
		else
			status = ACTV; // frezzing time ==0 so set to active 
	}
	return;
}


bool Enemy::isKilled() // check if the enemy killed 
{
	if (status == KILD)
		return true;
	return false;
}


void  Enemy::MovForward() // move forword 
{
	int k = getK();
	int s = GetSpeed(); // speed 

	if ((Distance > MinDistance) && (k = 0.5))
	{
		s = s / 2;//dec the speed to half bec the health < 0.5 org helath
		Distance -= s; // dec the distance 
	}
	else if ((Distance > MinDistance) && (k = 1))
	{
		Distance -= s; // dec th edistace by normal speed 
	}

	if (Distance < MinDistance) // if it exceed the limit return to it
	{
		Distance = MinDistance;
	}


}

