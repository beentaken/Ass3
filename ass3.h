#ifndef _ASS3_H
#define _ASS3_H

/*Event name:[CDE]:minimum:maximum:units:weight:
class C 		//C = contin (eg Time online:C:0:1440:minutes:3:
)
{
	double min; // = 0
	double max;
	string units;
}
class D 		//D = discrete (eg Emails sent:D:0:::1:
)
{
	int min;	// = 0
	int max; 	//happens one at a time
	string units;
}
class E 		//E = discrete (eg Money made:E:::cents:2:)
{
	int min;
	int max;	//happens one at a time; can be -VE
	string units;
}
template <class eventType>
class Event
{
	string name;
	char type;
	eventType data; //either C D E contains min, max, units
	int weight; 	//always +VE
	//stats
	double mean;
	double stdDev;
}*/



/*****************************************************************
	Psuedocode for Initial Input & Activity Engine/Log Gen
	read in stats and events;
		check for discrepencies ie(number of events!=,mean is out of range(min, max) or stdDev > max

	create objects with data;
	create Array of event objects;
	iterate number of days
		irterate through array;
			randomise values according to distrubution (normal distrib)
			->save to log;
	LOG FORMAT

	day:name:[CDE]:value:units
******************************************************************/

#include <iostream>
#include <random>	//needs c++11 ie wont work on banshee

class Generator
{
	private:
		std::default_random_engine generator;
		std::normal_distribution<double> distribution;
		double min;
		double max;
	public:
		Generator(double mean, double stddev, double min, double max):
        distribution(mean, stddev), min(min), max(max) {}

	double operator ()()
	{
		while (true)
		{
			double number = this->distribution(generator);
			if (number >= this->min && number <= this->max)
				return number;
		}
	}
};


/******************************************************************************
*
*	ACTIVITY ENGINE - LOG GENERATION
*	Arguments: array of events, days, output stream
*	Uses 'Generator' class
*
*	Output: write to ostream in format
*
*	Day x
*	name:[CDE]:value:units
*		...
*
*******************************************************************************/

void logGenerate(Events event[], int days, ofstream & out)
{

	for(int i=0;i<days;++i)
	{
		out << "Day " << i << std::endl;
		for(int j=0;j<event.size();++j)
		{
			//check event type
			if(event[i].cde=='C')
			{
				Generator g(event[i].mean, event[i].stdDev, event[i].minimum, event[i].maximum);
				out << event[i].name << ':' << "C:" <<  g() << ':' << event[i].units << std::endl;
			}
			else if(event[i].cde=='D')
			{
				Generator g(event[i].mean, event[i].stdDev, event[i].minimum, 999999);
				out << event[i].name << ':' << "D:" <<  g() << ':' << event[i].units << std::endl;
			}
			else if(event[i].cde=='E')
			{
				Generator g(event[i].mean, event[i].stdDev, -999999, 999999);
				out << event[i].name << ':' << "E:" <<  g() << ':' << event[i].units << std::endl;
			}
			else
				out << "Error log entry" << std::endl;
		}
	}
}


#endif
