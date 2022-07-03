#include "fighter.h"


fighter::fighter(int id, int arrTime, int power, int Speed, int RP,double health):Enemy(id,arrTime)
{
	SetPower(power);
	SetSpeed(Speed);
	SetRelPeriod(RP);
	SetHealth(health);
	SetOrgHealth(health);
	SetType(FIGHTER);
	SetStatus(INAC);
	RelTime=RP;
	
}

void fighter:: Move()
{
	MovForward();

}

void fighter:: Act()
{
	if (RelPeriod==RelTime)//ready to shot
	{
		 
		
		if (status==ACTV)
		{
			float k = getK();
			float d = GetDistance();
			float x = k / d;
			fire = (x * Power);
			//fire = ((getK()/ GetDistance())*Power);
			 c->DecHealth( fire)     ;  //function dec the castle health by fire value 
			 RelTime--;  
		}
	}
else  // still in relod time 
{
	RelTime--; // dec the relod time 
	if (RelTime==-1)
	{
		RelTime=RelPeriod; // next time will be eready to shoot
	}
}

}
void  fighter::IsActivate(int time)
{
	if ( time ==ArrvTime)
	{
		status =ACTV ; // arrive time so set it to active state 
	}
}


 int fighter::GetPrio()
 {
	 int state ;
	 if (GetStatus() ==ACTV )
	{
		state = 1;
	}
	 else if (GetStatus() ==FRST)
	 {
		 state= 0.5;
	 }
	 else 
		 state=0;
	 prio=(GetPower()*getK()*state/GetDistance());
	 return prio;


 }

 void fighter::setCastlePtr(Castle* ptr)
{
	c = ptr;
}
Castle* fighter::getCastlePtr()
{
	return c;
}
fighter::~fighter(void)
{
}