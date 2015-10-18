#include <iostream>
#include <fstream>
#include "ass3.h"
#include "event.h"
using namespace std;

int main()
{
//------Initial input (ben) ---------------------------------------
	ifstream eventsFile("Events.txt");
	ifstream statsFile("Stats.txt");
	//read into event array[];
	int days = 10;
	int n;
	eventsFile >> n;

	//... 

	//Event eventArray[n]
	eventsFile.close();
	statsFile.close();

//------Activity Engine (zach) ------------------------------------
	fstream logs("logs.dat",iso::in|ios::out);
	if (!logStatFile.is_open())
	{
		cout << "Activity Engine Error: The file could not be opened\n";
	}
	else
	{
		activityEngine(eventArray, days, logStatFile);
	}

//------Analysis Engine (zach) ------------------------------------
	ofstream logStats("logStats.txt");

	analysisEngine(logs, logStats, days);

	logs.close();

//------Alert Engine (ben) ----------------------------------------






	logStats.close();
	return 0;
}