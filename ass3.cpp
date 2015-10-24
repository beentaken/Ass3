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
	Event* eventList;

	Event::readEvents(eventsFile,n,eventList);
	Event::readStats(statsFile,n,eventList);

	//eventsFile >> n;

	//...
	//Event eventArray[n]
	eventsFile.close();
	statsFile.close();

//------Activity Engine (zach) ------------------------------------
	ofstream temp("logs.dat"); //HACK to ensure file exists
	temp.close();
	fstream logs("logs.dat",ios::out|ios::in);
	if (!logs.is_open())
	{
		cout << "Activity Engine Error: The file could not be opened\n";
	}
	else
	{
		activityEngine(eventList,n,days,logs);
	}
	logs.close();

//------Analysis Engine (zach) ------------------------------------
	logs.open("logs.dat");
	ofstream logStats("logStats.txt");

	analysisEngine(logs, logStats, days);

	logs.close();

//------Alert Engine (ben) ----------------------------------------



	cout << "Please enter statistics file"<< endl;
	//For each day generated you need to report on whether there is an intrusion detected by comparing
	//an anomaly counter with a threshold.




	logStats.close();
	return 0;
}
