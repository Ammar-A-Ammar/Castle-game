#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Castle\Castle.h"
class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:

	Castle* ptrC; // pointer to the castle 

	const int ID;         //Each enemy has a unique ID (sequence number)

	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	ENMY_TYPE Type;
	int Distance;	//Horizontal distance between enemy & the tower of its region
					//Always positive (ranges from 2 to 60)
	double Health;	//Enemy health

	int OrgHealth;
	int Power;
	int speed;
	float K; // equation of the figther damage 
	////////////////////
	int FirstShotDelay;
	int KillDelay;
	int LifeTime;
	//////////
	int RelTime; //reloed time
	int RelPeriod; // input rel time
	int FrezzingTime;
	int actTime; //arrival time
	bool firstshotted; // its the first shot or not 
	///////////////
	const int ArrvTime;	//arrival time (time it starts to join battle)
	int FirstShotTime;
	int killedtime;
	int KilledAt;
	/////////////////
	double Priority; // priority of the fighter 

public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	Enemy(int id, int arrTime, ENMY_TYPE type, double H, int P, int RelTime, int speed);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);

	void DecrementDist();

	void SetDistance(int);
	int GetDistance() const;

	int GetArrvTime() const;
	/////////////////////////////////////////////////////////////////////////////

	virtual void setCastlePtr(Castle* ptr);//
	virtual Castle* getCastlePtr();//

	void SetType(ENMY_TYPE Type); // set of type
	ENMY_TYPE GetType(); // get of the type 

	void SetOrgHealth(int health); // set of orginal health 
	int GetOrgHealth(); // get of the orginal heath 


	void SetPower(int power); // set of power 
	int GetPower(); // get of the power


	void SetSpeed(int speed); // set the speed 
	int GetSpeed(); // get the speed 



	void SetRelPeriod(int Time); // set the relod Period
	int GetRelPeriod(); // get the relod Period



	void SetFirstShotDelay(); // set firstshot delay 
	int GetFirdtSHotDelay(); // get first shot delay

	void SetKTS(int num);
	int GetKTS();
	void CheckKTS(int TimeStep);

	void SetKilledDelay(); //set killed delay 
	int GetKilledDelay(); // get killed elay

	void SetLifeTime(); // get life time 
	int GetLIfeTime(); // get life time 

	void SetPriority();
	double GetPriority();

	void SetHealth(double Health); // set helath 
	int GetHealth(); // get health


	void setK(); // set k for equation
	float getK();// get K for Equation

	// Virtual Functions: ----------------

	virtual void Move() = 0;	//All enemies can move
	virtual void Act() = 0;	//Acting means fighting or healing


	void getAttacked(float h, int timestep);// attacked by the castle n from catsle power
	void getFreezed(int t, int timestep);// freezed by the castle T time of freezing
	void deforsted(); // defrost ice 
	bool isKilled(); // check its killed or not 
	void MovForward(); // move forword
};

