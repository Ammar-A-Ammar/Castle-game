#pragma once

#include "Enemies/Enemy.h"
#include "Castle/Castle.h"
#include "Generic_DS/Queue.h"
#include "Generic_DS/PriQueue.h"
#include "Generic_DS/Stack.h"
#include "GUI/GUI.h"
#include "Enemies/healer.h"

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, ActiveFightersCount, ActiveHealersCount, ActiveFreezersCount; //no. of active enemies (total/Fighters/Freezers/Healers)
	int FrostedCount, FrostedFightersCount, FrostedFreezersCount, FrostedHealersCount;////no. of frosted enemies (Fighters/Freezers/Healers)
	int KilledCount, KilledFightersCount, KilledFreezersCount, KilledHealersCount; 	//no. of killed enemies (Fighters/Freezers/Healers)
	int CurrentTimeStep;
	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	
	Queue<Enemy*> Q_Inactive;			//Queue of inactive enemies
	PriQueue<Enemy*> PQ_ActiveFighters; //Active fighter priority queue
	Stack<Enemy*> S_ActiveHealers;		//healer stack
	Queue<Enemy*> Q_ActiveFreezers;		//Active freezer queue
	PriQueue<Enemy*> PQ_FrostedEnemies; //frosted priority queue
	Queue<Enemy*> Q_KilledEnemies;		//killed queue

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	//int DemoListCount;
	//Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo
	/// ==>


	//
	// TODO: Add More Data Members As Needed
	//
	string Game_STATUS;

public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();

	//---------------------------------------LOADING AND SAVING FUNTIONS-----------------------------------------------//
	bool ReadInput(string inputfileName);                  // Nadine
	void writeResult();                                    // Nadine   
	void DecideGameStatus();
	void AddtoINAC(Enemy* ptrEnemy);                       // Nadine

	void StartGame();                                      // Nadine
	void PlayGame();                                       // Nadine                                       

	void EnemiesActivation(int CurrentTimeStep);//salma check the inactive list and activate all enemies that has arrived and fill the fighter , healer, freezer
	void MoveEnemies(int CurrentTimeStep);                 // Salma
	void ActEnemies(int CurrentTimeStep);                  // Salma
	void ActHealer(healer* healerEnemy);                   // Salma
	void DefrostEnemies();                                 // Salma
	void ActCastle(int CurrentTimeStep);                   //  
	void checkKilled();                                    // Salma
	void GetAddCountStatistics();                          // Salma
	
	void SetGameSTATUS(string Game_STATUS);
	string GetGameSTATUS();
	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)
	//void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	//void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)

	//
	// TODO: Add More Member Functions As Needed
	//
};

