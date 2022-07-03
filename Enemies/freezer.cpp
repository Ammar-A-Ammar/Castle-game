#include "freezer.h"



freezer::freezer(int id, int arrTime, int power, int Speed, int RP, double health) :Enemy(id, arrTime)
{
	SetPower(power);
	SetSpeed(Speed);
	SetRelPeriod(RP);
	SetHealth(health);
	SetOrgHealth(health);
	SetType(FREEZER);
	SetStatus(INAC);
	RelTime = RP;
}
void freezer::Move()
{
	MovForward();
}
void freezer::Act()
{
	if ( C->GetCstatues()==FROZEN) // if castle already frozen dont affect on it 
	{
		return;
	}
	if (RelPeriod == RelTime)//ready to shot
	{

		if (status == ACTV)
		{
			 
			float x = getK() / Distance;
			ice = (x * Power); //function hena han70t ice 3ala  castlel7ad level mo3yn l7ad ma tfrezze
			C->Addice(ice);  // add ice on the castle
			RelTime--; // dec the relod timee                      
		}
	}
	else  // still in relod time 
	{
		RelTime--; // dec the relod time 
		if (RelTime == -1)
		{
			RelTime=RelPeriod; // next time will be eready to shoot
		}
	}

}
void  freezer::IsActivated(int time)
{
	if (time == ArrvTime)
	{
		status = ACTV; // arrive time so set it to active state 
	}
}
void freezer::setCastlePtr(Castle* ptr)
{
	C = ptr;
}
Castle* freezer::getCastlePtr()
{
	return C;
}

freezer::~freezer(void)
{
}
