#include "Castle.h"


void Castle::SetCastleHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetCastleHealth() const
{
	return Health;
}
void Castle::SetCastleOrgHealth(double h)
{
	if (h > 0)
		orgHealth = h;
	else
		orgHealth = 0; // killed
}

double Castle::GetCastleOrgHealth()
{
	return orgHealth;
}
void Castle::SetPowerShot(double PS)
{
	if (PS > 0)
		PowerShot = PS;
}

double Castle::GetPowerShot() const
{
	return PowerShot;
}


void Castle::SetSameShotTime(double St)
{
	if (St > 0 && St < MaxEnemyCount)
		SameShotTime = St;
}

double Castle::GetSameShotTime() const
{
	return SameShotTime;
}

void Castle::SetMaxNumberofAttacks(int N)
{
	MaxAttacks = N;
}

int Castle::GetMaxNumberOfAttacks()
{
	return MaxAttacks;
}
CASTLE_STATUS Castle::GetCstatues() // get statues 
{
	return Cstatues;
}

void Castle::SetCastlestatues(CASTLE_STATUS s) // set the statues 
{
	Cstatues = s;
}
void Castle::DecHealth(float fire)
{
	SetCastleHealth(GetCastleHealth() - fire); // dec the health
	if (Health <= 0)
	{
		Cstatues = KILLED;  // if the castle killed 
	}
	return;
}
int Castle::GetThreshold()
{
	threshold = 300;
	return threshold;
}


void Castle::Addice(float ice1)
{
	ice = ice + ice1;
	if (ice == GetThreshold())
	{
		Cstatues = FROZEN;
		freezingTime = 1;
	}
	return;
}
void Castle::defrostCastle()
{
	if (freezingTime == 0)
	{
		Cstatues = ACTIVE; // frezzing time pass
	}
	if (Cstatues = FROZEN)
	{
		freezingTime--;
	}


	return;
}


void Castle::increaseHealth()
{
	SetCastleHealth(GetCastleHealth() * 0.03);
}

// enimes fight functions

/*
 void Castle::freezeEnimes(int id)
{
	Enemy *pE;
	ACTV.dequeue(pE);
	pE->SetStatus(FRST);

	//AddtoDemoList(pE);
}

void Castle::decreaseHealthEnimes(int id)
{
	Enmy.SetHealth()=Enemy.GetHealth()-PowerShot;
}
*/




/*
void Castle::ActCastle(PriQueue<Enemy*>& PQ_ActiveFighters,Stack<Enemy*>& S_ActiveHealers, Queue<Enemy*>& Q_ActiveFreezers, int CurrentTimeStep)
{
	//status of enemy (active=1),			(frosted=0)
	//health of enemy (more than 0.5 =5),   (less than 0.5 =0)
	// pirority equation= 0.45*(power shot of enemy)-0.25*(distance far from castle)+0.2(helath of enemy)+0.1*(status of enemy )

	for (int i=0; i<M ; i++)
		{

			if (GetStatus() == ACTV)
				stateEnemy =1;
			else if (GetStatus() == FRST)
				stateEnemy =0;

			MaxPeriority=0.45*GetPower()-0.25*GetDistance()+0.2*GetHealth()+0.1*stateEnemy;


			PriQueue<Enemy*> fp = PQ_ActiveFighters;
			fp.enqueue(activefighters, );
			S_ActiveHealers.push(activehealrs);
			Q_ActiveFreezers.enqueue(activefreezers);

			fp.toArray(countFigther);
			S_ActiveHealers.toArray(countHealer);
			Q_ActiveFreezers.toArray(countFreezer);

		}


	while (!PQ_ActiveFighters.isEmpty() || !S_ActiveHealers.isEmpty() || !Q_ActiveFreezers.isEmpty())
	{
			if (ENMY_TYPE==FIGHTER)
				{
					//attack fighter by pirority queue
					PQ_ActiveFighters.peekFront(enemy);
					randomshot();


				}

			else if ( (countFigther==0) && (ENMY_TYPE==FREEZER) )
				{
					//attack freezer by stack
					S_ActiveHealers.pop(enemy);
					randomshot();

				}

			else if ( (countFigther==0) && (countFreezer==0) && (ENMY_TYPE==HEALER) )
				{
				//attack healer by queue
					Q_ActiveFreezers.peekFront();
					randomshot();

				}

	}


}
*/