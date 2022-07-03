#include "Battle.h"
#include <time.h>
#include<string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Enemies/healer.h"
#include "Enemies/fighter.h"
#include "Enemies/freezer.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>


Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	FrostedFightersCount = 0;
	FrostedFreezersCount = 0;
	FrostedHealersCount = 0;
	ActiveFightersCount = 0;
	ActiveHealersCount = 0;
	ActiveFreezersCount = 0;
	KilledFightersCount = 0;
	KilledFreezersCount = 0;
	KilledHealersCount = 0;
		
	//DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
}

//void Battle::AddtoDemoList(Enemy* Ptr)
//{
//	DemoList[DemoListCount++] = Ptr;
//
//	// Note that this function doesn't allocate any enemy objects
//	// It just enqueue a pointer that is already allocated into the queue
//}


Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PlayGame();
}


void Battle::StartGame()
{

	//----------------------------------------Reading Data-----------------------------------------------------//

	string inputfileName;					     // Interactive/Step by step/Silent    
	bool FileLoaded;

	pGUI->PrintMessage("Please Enter The Input File Name!");
	inputfileName = pGUI->GetString();
	FileLoaded = ReadInput(inputfileName + ".txt");
	
	if (FileLoaded)
	{
		CurrentTimeStep = 0;
		int ArrivalTime = 1;

		pGUI->PrintMessage("Input accepted. Please click to continue.");
		pGUI->waitForClick();

		/*pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), ActiveFightersCount, ActiveHealersCount, ActiveFreezersCount, ActiveCount,
			FrostedFightersCount, FrostedHealersCount, FrostedFreezersCount, FrostedCount, KilledFightersCount, KilledFreezersCount, KilledHealersCount, KilledCount);

		pGUI->PrintMessage("File Loading...click to open.");
		pGUI->waitForClick();*/
	}

	else
		return;
}
void Battle::SetGameSTATUS(string Game_STATUS)
{
	Game_STATUS = Game_STATUS;
}
string Battle::GetGameSTATUS()
{
	return Game_STATUS;
}

bool Battle::ReadInput(string inputfileName)//Nadeen
{
	int CH;     // Castle Health
	int N;      // Maximum number of enemies a castle can attack     
	int CP;     // Castle Power

	int ID;    // Enemy ID
	int TYP;   // Enemy Type
	int AT;    // Arrival Time
	double H;  // Enemy Health
	int POW;   // Enemy Power
	int RLD;   // Reload Time
	int SPD;   // Enemy Speed

	ifstream inFile(inputfileName);
	if (!inFile.is_open())
	{
		pGUI->PrintMessage("File is not found!");
		return false;
	}

	if (inFile.is_open())
	{
		//************************************* Loading Castle Data ********************************************//

		inFile >> CH >> N >> CP;
		BCastle.SetCastleHealth(CH);
		BCastle.SetMaxNumberofAttacks(N);
		BCastle.SetPowerShot(CP);

		//************************************** Load Enemies Data ********************************************//

		inFile >> EnemyCount;
		Enemy* ptrEnemy = nullptr;

		for (int i = 0; i < EnemyCount; i++)
		{
			inFile >> ID;
			inFile >> TYP;
			inFile >> AT >> H >> POW >> RLD >> SPD;

			//************************************ Types Switchs ***********************************************//
			if (TYP == 0)
			{
				ptrEnemy = new fighter(ID, AT, POW, SPD, RLD, H);
				ptrEnemy->SetStatus(INAC);
				AddtoINAC(ptrEnemy);
				ptrEnemy->setCastlePtr(&BCastle);
			}

			else if (TYP == 1)
			{
				ptrEnemy = new healer(ID, AT, POW, SPD, RLD, H);
				ptrEnemy->SetStatus(INAC);
				AddtoINAC(ptrEnemy);
				ptrEnemy->setCastlePtr(&BCastle);
			}

			else
			{
				ptrEnemy = new freezer(ID, AT, POW, SPD, RLD, H);
				ptrEnemy->SetStatus(INAC);
				AddtoINAC(ptrEnemy);
				ptrEnemy->setCastlePtr(&BCastle);
			}


		}
	}
}

void Battle::AddtoINAC(Enemy* ptrEnemy)
{
	Q_Inactive.enqueue(ptrEnemy);
}


void Battle::PlayGame()
{

	PROG_MODE	mode = pGUI->getGUIMode();       // To switch between modes
	StartGame();

	if (mode != MODE_SLNT)
	{
		AddAllListsToDrawingList();

		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetCastleHealth(), BCastle.GetCstatues(),
			ActiveFightersCount, ActiveHealersCount, ActiveFreezersCount, ActiveCount,
			FrostedFightersCount, FrostedHealersCount, FrostedFreezersCount, FrostedCount,
			KilledFightersCount, KilledFreezersCount, KilledHealersCount, KilledCount);


		//pGUI->PrintMessage("File Loading...click to open.");
		//pGUI->waitForClick();


		// As long as Active and Frosted lists not empty yet

		while (BCastle.GetCastleHealth() > 0 && EnemyCount != KilledCount)
		{
			CurrentTimeStep++;
			
			EnemiesActivation(CurrentTimeStep);
			
			MoveEnemies(CurrentTimeStep);
			
			ActEnemies(CurrentTimeStep);
			
			DefrostEnemies();

			ActCastle(CurrentTimeStep);	

			checkKilled();

			pGUI->ResetDrawingList();
			AddAllListsToDrawingList();

			GetAddCountStatistics();   //calculate counts and add to interface

			pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetCastleHealth(), BCastle.GetCstatues(),
				ActiveFightersCount, ActiveHealersCount, ActiveFreezersCount, ActiveCount,
				FrostedFightersCount, FrostedHealersCount, FrostedFreezersCount, FrostedCount,
				KilledFightersCount, KilledFreezersCount, KilledHealersCount, KilledCount);

			
			//pGUI->waitForClick();

			//******************************************* SWITCH MODES ***********************************************/


			if (mode == MODE_INTR)
			{
				pGUI->waitForClick();
			}

			else if (mode == MODE_STEP)
			{
				Sleep(1000);
			}

			pGUI->ResetDrawingList();
		}

	}

	else if (mode == MODE_SLNT)
	{
		// As long as Active and Frosted lists not empty yet

		while (BCastle.GetCastleHealth() > 0 && EnemyCount != KilledCount)
		{
			CurrentTimeStep++;
			
			EnemiesActivation(CurrentTimeStep);
			
			MoveEnemies(CurrentTimeStep);
			
			ActEnemies(CurrentTimeStep);
			
			DefrostEnemies();

			ActCastle(CurrentTimeStep);	

			checkKilled();

			GetAddCountStatistics();    //calculate counts and add to interface

			pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetCastleHealth(), BCastle.GetCstatues(),
				ActiveFightersCount, ActiveHealersCount, ActiveFreezersCount, ActiveCount,
				FrostedFightersCount, FrostedHealersCount, FrostedFreezersCount, FrostedCount,
				KilledFightersCount, KilledFreezersCount, KilledHealersCount, KilledCount);
			
			break;
		}

	}

	writeResult();
	pGUI->PrintMessage("Simulation Done ");
	Sleep(1000);

}

//-------------------------------------------- SAVING FUNCTION ------------------------------------------------//

void Battle::writeResult()
{
	fstream outFile;
	string outputfileName;

	pGUI->PrintMessage("Please enter the output file name: ");
	outputfileName = pGUI->GetString();
	outFile.open(outputfileName + ".txt", std::ofstream::out | std::ofstream::trunc);

	if (!outFile.is_open())
	{
		pGUI->PrintMessage("Not available, click to exit.");
		pGUI->waitForClick();
		return;
	}

	Enemy* Eptr;
	Queue<Enemy*> Q_temp;
	//DecideGameStatus();
	if (BCastle.GetCastleHealth() == 0)
	{
		outFile << "Game is LOSS"<< endl;
		outFile << "KTS" << setw(5) << "ID" << setw(7) << "FD" << setw(5) << "KD" << setw(5) << "LT" << endl;
		outFile << "-----------------------------------" << endl;
		outFile << "-----------------------------------" << endl;
		outFile << "Number of alive enemies " << setw(5) << EnemyCount - KilledCount  << endl;
	}
	else if (EnemyCount == KilledCount)
	{
		outFile << "Game is WIN" << endl;
		outFile << "KTS" << setw(5) << "ID" << setw(7) << "FD" << setw(5) << "KD" << setw(5) << "LT" << endl;
		outFile << "-----------------------------------" << endl;
		outFile << "-----------------------------------" << endl;
	}
	else
	{
		outFile << "Game is DRAWN"<< endl;
		outFile << "KTS" << setw(5) << "ID" << setw(7) << "FD" << setw(5) << "KD" << setw(5) << "LT" << endl;
		outFile << "-----------------------------------" << endl;
		outFile << "-----------------------------------" << endl;
	}
	

	double AverageFirstShotDelay = 0.0, AverageKillDelay = 0.0;

	while (!Q_KilledEnemies.isEmpty())
	{
		Q_KilledEnemies.dequeue(Eptr);
		outFile << Eptr->GetKTS() << setw(5) << Eptr->GetID() << setw(7) << Eptr->GetFirdtSHotDelay() << setw(5) << Eptr->GetKilledDelay() << setw(5) << Eptr->GetLIfeTime() << endl;
		Q_temp.enqueue(Eptr);

		AverageFirstShotDelay += Eptr->GetFirdtSHotDelay();
		AverageKillDelay += Eptr->GetKilledDelay();
	}

	while (!Q_temp.isEmpty())
	{
		Q_temp.dequeue(Eptr);
		Q_KilledEnemies.enqueue(Eptr);
	}

	


	

	if (KilledCount != 0 && AverageFirstShotDelay != 0)
	{
		AverageFirstShotDelay = AverageFirstShotDelay / KilledCount;
		outFile << "Average First-Shot Delay" << setw(5) << "=" << AverageFirstShotDelay << endl;
	}

	if (KilledCount != 0 && AverageKillDelay != 0)
	{
		AverageKillDelay = AverageKillDelay / KilledCount;
		outFile << "Average Kill Delay" << setw(5) << "=" << AverageKillDelay << endl;
	}

	pGUI->PrintMessage("Output file created successfully, click to continue");
	pGUI->waitForClick();
	outFile.close();
}

void Battle::DecideGameStatus()
{
	if (BCastle.GetCastleHealth() == 0)
	{
		SetGameSTATUS("LOSS");
		pGUI->PrintMessage("Game is LOSS");
	}else if (EnemyCount == KilledCount)
	{
		SetGameSTATUS("WIN");
	}
	else
	{
		SetGameSTATUS("DRAWN");
	}
	return;
}
void Battle::GetAddCountStatistics()
{
	ActiveCount = 0;
	FrostedCount = 0;
	KilledCount = 0;

	ActiveFightersCount = 0;
	ActiveHealersCount = 0;
	ActiveFreezersCount = 0;

	FrostedFightersCount = 0;
	FrostedHealersCount = 0;
	FrostedFreezersCount = 0;

	KilledFightersCount = 0;
	KilledFreezersCount = 0;
	KilledHealersCount = 0;

	PriQueue<Enemy*> tempPQ;
	Enemy* FighterEnemy;
	while (!PQ_ActiveFighters.isEmpty())
	{
		PQ_ActiveFighters.dequeue(FighterEnemy);
		int pri = FighterEnemy->GetPriority();
		tempPQ.enqueue(FighterEnemy, pri);
		//CheckStatus(FighterEnemy);
		if (FighterEnemy->GetStatus() == FRST)
		{
			FrostedFightersCount++;
			FrostedCount++;
		}
		else if (FighterEnemy->GetStatus() == ACTV)
		{
			ActiveFightersCount++;
			ActiveCount++;
		}
	}
	while (!tempPQ.isEmpty())
	{
		tempPQ.dequeue(FighterEnemy);
		int pri = FighterEnemy->GetPriority();
		PQ_ActiveFighters.enqueue(FighterEnemy, pri);
	}

	Queue<Enemy*> tempQ;
	Enemy* freezerEnemy;
	while (!Q_ActiveFreezers.isEmpty())
	{
		Q_ActiveFreezers.dequeue(freezerEnemy);
		tempQ.enqueue(freezerEnemy);

		if (freezerEnemy->GetStatus() == FRST)
		{
			FrostedFreezersCount++;
			FrostedCount++;
		}
		else if (freezerEnemy->GetStatus() == ACTV)
		{
			ActiveFreezersCount++;
			ActiveCount++;
		}
		else if (freezerEnemy->GetStatus() == KILD)
		{
			KilledFreezersCount++;
			KilledCount++;
		}

	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(freezerEnemy);
		Q_ActiveFreezers.enqueue(freezerEnemy);
	}


	Stack<Enemy*> tempS;
	Enemy* helerEnemy;
	while (!S_ActiveHealers.isEmpty())
	{
		helerEnemy = S_ActiveHealers.peek();
		S_ActiveHealers.pop();
		tempS.push(helerEnemy);
		if (helerEnemy->GetStatus() == FRST)
		{
			FrostedHealersCount++;
			FrostedCount++;
		}
		else if (helerEnemy->GetStatus() == ACTV)
		{
			ActiveHealersCount++;
			ActiveCount++;
		}
		else if (helerEnemy->GetStatus() == KILD)
		{
			KilledHealersCount++;
			KilledCount++;
		}
	}
	while (!tempS.isEmpty())
	{
		helerEnemy = tempS.peek();
		tempS.pop();
		S_ActiveHealers.push(helerEnemy);
	}

	


	Queue<Enemy*> tempK;
	Enemy* KilledEnemy;
	while (!Q_KilledEnemies.isEmpty())
	{
		Q_KilledEnemies.dequeue(KilledEnemy);
		tempK.enqueue(KilledEnemy);
		//KilledCount++;
		if (KilledEnemy->GetType() == HEALER)
		{
			KilledHealersCount++;
			KilledCount++;
		}
		else if (KilledEnemy->GetType() == FIGHTER)
		{
			KilledFightersCount++;
			KilledCount++;
		}
		else if (KilledEnemy->GetType() == FREEZER)
		{
			KilledFreezersCount++;
			KilledCount++;
		}
	}
	while (!tempK.isEmpty())
	{
		tempK.dequeue(KilledEnemy);
		Q_KilledEnemies.enqueue(KilledEnemy);
	}

}
//check the inactive listand activate all enemies that has arrivedand fill the fighter, healer, freezer
void Battle::EnemiesActivation(int CurrentTimeStep)
{
	Enemy* inactiveEnemy;
	while (!Q_Inactive.isEmpty())
	{
		Q_Inactive.peekFront(inactiveEnemy);
		if (inactiveEnemy->GetArrvTime() > CurrentTimeStep)
			//continue;//enemy not reached to arrival time to be active
			return;
		else
		{
			Q_Inactive.dequeue(inactiveEnemy);
			inactiveEnemy->SetStatus(ACTV);
		}
		//Add Active fighter to PQ_ActiveFighters priority queue
		if (inactiveEnemy->GetType() == FIGHTER)
		{
			int d = inactiveEnemy->GetPriority();
			PQ_ActiveFighters.enqueue(inactiveEnemy, d);
		}
		//add active healer to healer stack
		else if (inactiveEnemy->GetType() == HEALER)
		{
			S_ActiveHealers.push(inactiveEnemy);
			//ActiveHealersCount++;
		}
		//Add Active freezer to Active freezer queue
		else if (inactiveEnemy->GetType() == FREEZER)
		{
			Q_ActiveFreezers.enqueue(inactiveEnemy);
			//ActiveFreezerCount++;
		}
		
		
		//delete inactiveEnemy;	
	}
}
//make move  
void Battle::MoveEnemies(int CurrentTimeStep)
{
	//move active fighter
		PriQueue<Enemy*> PQ_temp;
		Enemy* Fighter;
		int pri;
		while (!PQ_ActiveFighters.isEmpty())
		{
			PQ_ActiveFighters.dequeue(Fighter);
			pri = Fighter->GetPriority();
			PQ_temp.enqueue(Fighter, pri);
			Fighter->Move();
		}
		while (!PQ_temp.isEmpty())
		{
			PQ_temp.dequeue(Fighter);
			pri = Fighter->GetPriority();
			PQ_ActiveFighters.enqueue(Fighter, pri);
		}
		//move active freezer
		Queue<Enemy*> Q_temp;
		Enemy* Freezer;
		while (!Q_ActiveFreezers.isEmpty())
		{
			Q_ActiveFreezers.dequeue(Freezer);
			Q_temp.enqueue(Freezer);
			Freezer->Move();
		}
		while (!Q_temp.isEmpty())
		{
			Q_temp.dequeue(Freezer);
			Q_ActiveFreezers.enqueue(Freezer);
		}
		//move active healer
		Stack<Enemy*> S_temp;
		Enemy* Healer;
		while (!S_ActiveHealers.isEmpty())
		{
			Healer = S_ActiveHealers.peek();
			S_ActiveHealers.pop();
			S_temp.push(Healer);
			Healer->Move();
		}
		while (!S_temp.isEmpty())
		{
			Healer = S_temp.peek();
			S_temp.pop();
			S_ActiveHealers.push(Healer);
		}

}

void Battle::ActEnemies(int CurrentTimeStep)
{
		//act fighter
		//------------------
		PriQueue<Enemy*> PQ_temp;
		Enemy* Fighter;
		int pri;
		while (!PQ_ActiveFighters.isEmpty())
		{
			PQ_ActiveFighters.dequeue(Fighter);
			pri = Fighter->GetPriority();
			PQ_temp.enqueue(Fighter, pri);
			//Fighter->SetRelPeriod(CurrentTimeStep);
			Fighter->setCastlePtr(GetCastle());
			Fighter->Act();
		}
		while (!PQ_temp.isEmpty())
		{
			PQ_temp.dequeue(Fighter);
			pri = Fighter->GetPriority();
			PQ_ActiveFighters.enqueue(Fighter, pri);
		}
		//act healer
		//------------------
		Stack<Enemy*> S_temp;
		Enemy* healerEnemy;

		while (!S_ActiveHealers.isEmpty())
		{
			healerEnemy = S_ActiveHealers.peek();
			S_ActiveHealers.pop();
			S_temp.push(healerEnemy);
			healer* h = dynamic_cast<healer*>(healerEnemy);
			
			ActHealer(h);
		}
		while (!S_temp.isEmpty())
		{
			healerEnemy = S_temp.peek();
			S_temp.pop();
			S_ActiveHealers.push(healerEnemy);
		}
		//act freezer
		//---------------------
		Queue<Enemy*> Q_temp;
		Enemy* freezerEnemy;
		while (!Q_ActiveFreezers.isEmpty())
		{
			Q_ActiveFreezers.dequeue(freezerEnemy);
			Q_temp.enqueue(freezerEnemy);
			freezerEnemy->setCastlePtr(GetCastle());
			freezerEnemy->Act();
		}
		while (!Q_temp.isEmpty())
		{
			Q_temp.dequeue(freezerEnemy);
			Q_ActiveFreezers.enqueue(freezerEnemy);
		}

	}

	
void Battle::ActHealer(healer* healerEnemy)
{
	double distance = healerEnemy->GetDistance();
	if (healerEnemy->GetDirection())
	{
		 
		Queue<Enemy*> Q_temp;
		Enemy* freezerEnemy;
		while (!Q_ActiveFreezers.isEmpty())
		{
			Q_ActiveFreezers.dequeue(freezerEnemy);
			if (distance - 2 >= freezerEnemy->GetDistance() && freezerEnemy->GetDistance() <= distance)
			{
				healerEnemy->sethealead(freezerEnemy);
				healerEnemy->Act();
			}
			Q_temp.enqueue(freezerEnemy);


		}
		while (!Q_temp.isEmpty())
		{
			Q_temp.dequeue(freezerEnemy);
			Q_ActiveFreezers.enqueue(freezerEnemy);
		}


		Stack<Enemy*> S_temp;
		Enemy* otherHealerEnemy;
		while (!S_ActiveHealers.isEmpty())
		{
			otherHealerEnemy = S_ActiveHealers.peek();
			S_ActiveHealers.pop();
			if (distance - 2 >= otherHealerEnemy->GetDistance() && otherHealerEnemy->GetDistance() <= distance)
			{
				healerEnemy->sethealead(otherHealerEnemy);
				healerEnemy->Act();
			}
			S_temp.push(otherHealerEnemy);

		}
		while (!S_temp.isEmpty())
		{
			otherHealerEnemy = S_temp.peek();
			S_temp.pop();
			S_ActiveHealers.push(otherHealerEnemy);
		}

		PriQueue<Enemy*> PQ_temp;
		Enemy* Fight;
		int pri;
		while (!PQ_ActiveFighters.isEmpty())
		{
			PQ_ActiveFighters.dequeue(Fight);
			pri = Fight->GetPriority();
			if (distance - 2 >= Fight->GetDistance() && Fight->GetDistance() <= distance)
			{
				healerEnemy->sethealead(Fight);
				healerEnemy->Act();
			}
			PQ_temp.enqueue(Fight, pri);

		}
		while (!PQ_temp.isEmpty())
		{
			PQ_temp.dequeue(Fight);
			pri = Fight->GetPriority();
			PQ_ActiveFighters.enqueue(Fight, pri);
		}
	}
	else
	{
	 
		Queue<Enemy*> Q_temp;
		Enemy* freezerEnemy;
		while (!Q_ActiveFreezers.isEmpty())
		{
			Q_ActiveFreezers.dequeue(freezerEnemy);
			if (distance + 2 >= freezerEnemy->GetDistance() && freezerEnemy->GetDistance() >= distance)
			{
				healerEnemy->sethealead(freezerEnemy);
				healerEnemy->Act();
			}

			Q_temp.enqueue(freezerEnemy);

		}
		while (!Q_temp.isEmpty())
		{
			Q_temp.dequeue(freezerEnemy);
			Q_ActiveFreezers.enqueue(freezerEnemy);
		}


		Stack<Enemy*> S_temp;
		Enemy* otherHealerEnemy;
		while (!S_ActiveHealers.isEmpty())
		{
			otherHealerEnemy = S_ActiveHealers.peek();
			S_ActiveHealers.pop();
			if (distance + 2 >= otherHealerEnemy->GetDistance() && otherHealerEnemy->GetDistance() >= distance)
			{
				healerEnemy->sethealead(otherHealerEnemy);
				healerEnemy->Act();
			}
			S_temp.push(otherHealerEnemy);

		}
		while (!S_temp.isEmpty())
		{
			otherHealerEnemy = S_temp.peek();
			S_temp.pop();
			S_ActiveHealers.push(otherHealerEnemy);
		}

		PriQueue<Enemy*> PQ_temp;
		Enemy* Fight;
		while (!PQ_ActiveFighters.isEmpty())
		{

			PQ_ActiveFighters.dequeue(Fight);
			int d = Fight->GetPriority();
			if (distance + 2 >= Fight->GetDistance() && Fight->GetDistance() >= distance)
			{
				healerEnemy->sethealead(Fight);
				healerEnemy->Act();
			}
			PQ_temp.enqueue(Fight, d);

		}
		while (!PQ_temp.isEmpty())
		{
			PQ_temp.dequeue(Fight);
			int d = Fight->GetPriority();
			PQ_ActiveFighters.enqueue(Fight, d);
		}
	}
}

void Battle::DefrostEnemies()
{
	//defrost Fighters
	PriQueue<Enemy*> PQ_temp;
	Enemy* Fight;
	int pri;
	while (!PQ_ActiveFighters.isEmpty())
	{
		PQ_ActiveFighters.dequeue(Fight);
		pri = Fight->GetPriority();
		PQ_temp.enqueue(Fight, pri);
		if (Fight->GetStatus() == FRST)
		{
			{
				Fight->deforsted();
			}
		}
	}
	while (!PQ_temp.isEmpty())
	{
		PQ_temp.dequeue(Fight);
		pri = Fight->GetPriority();
		PQ_ActiveFighters.enqueue(Fight, pri);
	}

	//defrost healer
	Stack<Enemy*> S_temp;
	Enemy* healerEnemy;
	while (!S_ActiveHealers.isEmpty())
	{
		healerEnemy = S_ActiveHealers.peek();
		S_ActiveHealers.pop();
		S_temp.push(healerEnemy);
		if (healerEnemy->GetStatus() == FRST)
		{
			{
				healerEnemy->deforsted();
			}
		}
	}
	while (!S_temp.isEmpty())
	{
		healerEnemy = S_temp.peek();
		S_temp.pop();
		S_ActiveHealers.push(healerEnemy);
	}

	//defrost freezer
	Queue<Enemy*> Q_temp;
	Enemy* freezerEnemy;
	while (!Q_ActiveFreezers.isEmpty())
	{
		Q_ActiveFreezers.dequeue(freezerEnemy);
		Q_temp.enqueue(freezerEnemy);
		if (freezerEnemy->GetStatus() == FRST)
		{
			{
				freezerEnemy->deforsted();
			}
		}
	}
	while (!Q_temp.isEmpty())
	{
		Q_temp.dequeue(freezerEnemy);
		Q_ActiveFreezers.enqueue(freezerEnemy);
	}

}
void Battle::ActCastle(int CurrentTimeStep) //Nadeen
{
}
void Battle::checkKilled()
{
	//check on fighter pri queu
	PriQueue<Enemy*> PQ_temp;
	Enemy* fighterEnemy;
	while (!PQ_ActiveFighters.isEmpty())
	{
		PQ_ActiveFighters.dequeue(fighterEnemy);
		if (fighterEnemy->isKilled())
		{
			Q_KilledEnemies.enqueue(fighterEnemy);
			KilledCount++;
		}
		else
		{
			int pri = fighterEnemy->GetPriority();
			PQ_temp.enqueue(fighterEnemy, pri);
		}
	}
	while (!PQ_temp.isEmpty())
	{
		PQ_temp.dequeue(fighterEnemy);
		int pri = fighterEnemy->GetPriority();
		PQ_ActiveFighters.enqueue(fighterEnemy, pri);
	}
	 
	//check on freezer quueu
	Queue<Enemy*> Q_temp;
	Enemy* freezerEnemy;
	while (!Q_ActiveFreezers.isEmpty())
	{
		Q_ActiveFreezers.dequeue(freezerEnemy);
		if (freezerEnemy->isKilled())
		{
			Q_KilledEnemies.enqueue(freezerEnemy);			 
			KilledCount++;
		}
		else
			Q_temp.enqueue(freezerEnemy);
	}
	while (!Q_temp.isEmpty())
	{
		Q_temp.dequeue(freezerEnemy);
		Q_ActiveFreezers.enqueue(freezerEnemy);
	}
	//check on healer stack
	Stack<Enemy*> S_temp;
	Enemy* healerEnemy;
	while (!S_ActiveHealers.isEmpty())
	{
		healerEnemy = S_ActiveHealers.peek();
		S_ActiveHealers.pop();
		if (healerEnemy->isKilled())
		{
			Q_KilledEnemies.enqueue(healerEnemy);
			
			KilledCount++;
		}
		else
			S_temp.push(healerEnemy);
	}
	while (!S_temp.isEmpty())
	{
		healerEnemy = S_temp.peek();
		S_temp.pop();
		S_ActiveHealers.push(healerEnemy);
	}
	

	

}
//salma end
//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
//void Battle::Just_A_Demo()
//{	
//	
//	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
//	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer
//
//	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
//	pGUI->waitForClick();
//
//	CurrentTimeStep = 0;
//	//
//	// THIS IS JUST A DEMO Function
//	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
//	//
//	 
//	srand(time(NULL));
//	int Enemy_id = 0;
//	int ArrivalTime=1;
//	Enemy* pE= NULL;
//	//Create Random enemies and add them all to inactive queue
//	for(int i=0; i<EnemyCount; i++)
//	{			
//		ArrivalTime += (rand()%3);	//Randomize arrival time
//		pE = new Enemy(++Enemy_id,ArrivalTime);
//		pE->SetStatus( INAC); //initiall all enemies are inactive
//		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
//	}	
//
//	AddAllListsToDrawingList();
//	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive
//
//	pGUI->waitForClick();
//	
//	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
//	{
//		CurrentTimeStep++;
//		ActivateEnemies();
//
//		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)
//
//		pGUI->ResetDrawingList();
//		AddAllListsToDrawingList();
//		pGUI->UpdateInterface(CurrentTimeStep);
//		Sleep(250);
//	}		
//}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const* enemyList = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
	{
		pGUI->AddToDrawingList(enemyList[i]);
	}

	//Add active fighters pri-queue to drawing list
	/*
	Enemy* const* ActiveFightersList = PQ_ActiveFighters.toArray(ActiveFightersCount);
	for (int i = 0; i < ActiveFightersCount; i++)
	{
		pGUI->AddToDrawingList(ActiveFightersList[i]);
	}
	*/
	PriQueue<Enemy*> pq_temp;
	Enemy* fighterEnemy;
	while (!PQ_ActiveFighters.isEmpty())
	{
		PQ_ActiveFighters.dequeue(fighterEnemy);
		int pri = fighterEnemy->GetPriority();
		pq_temp.enqueue(fighterEnemy, pri);
		pGUI->AddToDrawingList(fighterEnemy);
	}
	while (!pq_temp.isEmpty())
	{
		pq_temp.dequeue(fighterEnemy);
		int d = fighterEnemy->GetPriority();
		PQ_ActiveFighters.enqueue(fighterEnemy, d);
	}
	//Add Active Healers stack to drawing list

	Stack<Enemy*> S_temp;
	Enemy* ActiveHealer;
	while (!S_ActiveHealers.isEmpty())
	{
		ActiveHealer = S_ActiveHealers.peek();
		S_ActiveHealers.pop();
		S_temp.push(ActiveHealer);
		pGUI->AddToDrawingList(ActiveHealer);
	}
	while (!S_temp.isEmpty())
	{
		ActiveHealer = S_temp.peek();
		S_temp.pop();
		S_ActiveHealers.push(ActiveHealer);
	}
	//Add active freezer queue to drawing list

	Queue<Enemy*> tempQ;
	Enemy* F;
	while (!Q_ActiveFreezers.isEmpty())
	{
		Q_ActiveFreezers.dequeue(F);
		tempQ.enqueue(F);
		pGUI->AddToDrawingList(F);
	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(F);
		Q_ActiveFreezers.enqueue(F);
	}
	/*
	//Add frosted Enemies pri-queue to drawing list
	Enemy*const* FrostedEnemiesList = PQ_FrostedEnemies.toArray(FrostedCount);
	for (int i = 0; i < FrostedCount; i++)
	{
		pGUI->AddToDrawingList(FrostedEnemiesList[i]);
	}
	*/
	PriQueue<Enemy*> pq_frtemp;
	Enemy* frostedEnemy;
	while (!PQ_FrostedEnemies.isEmpty())
	{
		PQ_FrostedEnemies.dequeue(frostedEnemy);
		int pri = frostedEnemy->GetPriority();
		pq_frtemp.enqueue(frostedEnemy, pri);
		pGUI->AddToDrawingList(frostedEnemy);
	}
	while (!pq_frtemp.isEmpty())
	{
		pq_frtemp.dequeue(frostedEnemy);
		int d = frostedEnemy->GetPriority();
		PQ_FrostedEnemies.enqueue(frostedEnemy, d);
	}
	//Add Killed Enemies queue to drawing list	
	/*
	int KilledCount;
	Enemy* const* KilledEnemiesList = Q_KilledEnemies.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++)
	{
		pGUI->AddToDrawingList(KilledEnemiesList[i]);
	}
	*/
	Queue<Enemy*> tempK;
	Enemy* KilledEnemy;
	while (!Q_KilledEnemies.isEmpty())
	{
		Q_KilledEnemies.dequeue(KilledEnemy);
		tempK.enqueue(KilledEnemy);
		pGUI->AddToDrawingList(KilledEnemy);
	}
	while (!tempK.isEmpty())
	{
		tempK.dequeue(KilledEnemy);
		Q_KilledEnemies.enqueue(KilledEnemy);
	}
	
}
