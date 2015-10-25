#include <iostream>
#include <fstream>
#include "ass3.h"
#include "event.h"
using namespace std;

int main(int argc,  char** argv)
{
//------Initial input (ben) ---------------------------------------
	if(argc != 5)
	{
		cout << "Invalid arguments, syntax is" << endl;
		cout << "IDS Events.txt Username Stats.txt Days" << endl;
		return 0;
	}

	ifstream eventsFile(argv[1]);
	ifstream statsFile(argv[3]);
	//read into event array[];
	int days = atoi(argv[4]);
	int n;
	Event* eventList;

	if(!Event::readEvents(eventsFile,n,eventList)) return 0;
	if(!Event::readStats(statsFile,n,eventList)) return 0;

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

	vector<Statistics> localStats(n);
	vector<Statistics> inputStats(n);
	//localStats.resize(n);
	int * weights = new int[n];
	int threshold;
	int alert = 0;
	int alertCount = 0;
	ifstream in;
	string fileName;

	//get weights
	//calculate threshold;
	//The threshold for detecting an intrusion is 2∗(Sums of weights) where the weights are taken from
	//Events.txt.
	for(int i = 0; i < n; ++i)
	{
		weights[i] = eventList[i].getWeight();
		threshold += weights[i];
	}
	threshold *= 2;

	while(fileName != "q")
	{
		//prompt for file
		cout << "please enter stats file or type 'q' to quit: ";
		cin >> fileName;
		if(fileName == "q")
			break;
		//get input stats from  given file
		if(!StatsFromFile(in,fileName,inputStats))
		{
			cerr << "File not found, try again" << endl;
		}
		else
		{
			//for each day
			in.open("logs.dat");
			in.ignore(999,'\n');
			cout << "Threshold: " << threshold << endl;
			cout<< "Day \tAlert Level" << endl;
			for(int i = 0; i < days; ++i)
			{
				in.ignore(999,'\n');	//ignore Day
				alert = alert_engine(inputStats,in,weights,n);
				cout << i+1 << ":\t" << alert;
				if (alert >= threshold)
				{
					cout << " Alert!";
					++alertCount;
				}
				cout << endl;
			}
		}		
	}

	logStats.close();
	delete [] weights;
	return 0;
}

