#pragma once
#include "..\Defs.h"
//#include "..\GUI\GUI.h"

#include <fstream>
class Castle
{
	/*GUI* pGUI;*/
	double Health;
	double PowerShot;
	double SameShotTime;
	//
	// TODO: Add More Data Members As Needed
	//
	int CH;   // starting health of castle
	int MaxAttacks;  // maximum no. of enemies
	int CP;  // castle power
	int M; //  total number of enemies

	//ofstream Ofile;
	//string name;  //name of input file
	double orgHealth; // orginal health of the castle 
	CASTLE_STATUS Cstatues; // statues of the castle 
	int threshold;// amount of ice that can frezze the castle 
	float ice; // ice throw by the enemy 
	int freezingTime; // time the catsle get frezzed 
public:
	void SetPowerShot(double PS);
	void SetSameShotTime(double St);
	double GetPowerShot() const;
	double GetSameShotTime() const;
	void SetMaxNumberofAttacks(int N);
	int GetMaxNumberOfAttacks();
	void SetCastleHealth(double h);
	double GetCastleHealth() const;
	//void LoadFile(); // loading input data from file
	
	void SetCastleOrgHealth(double h);
	double GetCastleOrgHealth();
	 
	CASTLE_STATUS GetCstatues();
	void SetCastlestatues(CASTLE_STATUS s);
	void DecHealth(float fire);
	void Addice(float ice);
	int GetThreshold();
	void defrostCastle();

	void randomshot();
	void increaseHealth();
	void freezeEnimes(int id);
	//void ActCastle(PriQueue<Enemy*>& PQ_ActiveFighters, Stack<Enemy*>& S_ActiveHealers, Queue<Enemy*>& Q_ActiveFreezers, int CurrentTimeStep);
};

