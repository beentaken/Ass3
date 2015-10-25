/*****************************************************************
*	CSCI262 Assignment 3
*	ass3.h
*	last Modified: zs 17/10/15
******************************************************************/

#ifndef _ASS3_H
#define _ASS3_H
#include <iostream>
#include <fstream>
#include <cmath> //sqrt(), log()
#include <cstdlib> //rand(), srand()
#include <vector>
#include <ctime> //time()
#include "event.h"

/*****************************************************************
*	Psuedocode for Initial Input & Activity Engine/Log Gen
*
*	read in stats and events;
*		check for discrepencies
*		ie(different events,mean is out of range(min, max)
*
*	create objects with data;
*	create Array of event objects;
*	iterate number of days
*		irterate through array;
*			randomise values according to
*			distrubution (normal distrib)
*			->save to log;
*	LOG FORMAT
*
*	day:name:[CDE]:value:units
******************************************************************/

//Now non c++11 friendly
//Box muller method get rand num based on a normal distribution
double generate(double mean, double stddev, double min, double max)
{
	static double n2 = 0.0;
	static int n2_cached = 0;
	if (!n2_cached)
	{
		double x, y, r;
		do //choose a point x,y in the unit circle uniformly at random
		{
			x = 2.0*rand()/RAND_MAX - 1;
			y = 2.0*rand()/RAND_MAX - 1;

			r = x*x + y*y;
		}
		while (r == 0.0 || r > 1.0);
		{
			//apply box-muller transform on x and y
    			double d = sqrt(-2.0*log(r)/r);
    			double n1 = x*d;
			n2 = y*d;
			//scale and translate to our mean,stddev
			double result = n1*stddev + mean;
			n2_cached = 1;
			if(result > max || result < min)
				generate(mean,stddev,min,max);
			else
				return result;
		}
	}
	else
	{
		//cache result to reduce comp time
		n2_cached = 0;
		if((n2*stddev + mean) > max || (n2*stddev + mean) < min)
			generate(mean,stddev,min,max);
		else
			return n2*stddev + mean;
	}
}

/******************************************************************************
*
*	ACTIVITY ENGINE - LOG GENERATION
*	Arguments: array of events, days, output stream
*	Uses 'Generator' class
*
*	Output: write to ostream in format
*
*	Day x
*	name:value:units
*		...
*
*******************************************************************************/

void activityEngine(Event event[],int eventCount, int days, std::fstream & out)
{
	srand(time(NULL)); // for generate
	std::cout << "Log generation started...\n";
	out << eventCount << std::endl;
	for(int day=0;day<days;day++)
	{
		std::cout << "Day " << day+1 << std::endl;
		out << "Day " << day+1 << std::endl;
		for(int eventNum=0;eventNum<eventCount;eventNum++)
		{
			//check event type
			if(event[eventNum].getCDE() == 'C')
			{
				double g = generate(event[eventNum].mean, event[eventNum].stdDevation, event[eventNum].minimum, event[eventNum].maximum);
				out << event[eventNum].name << ':' <<  g << '\n'; //<< event[eventNum].unit << std::endl;
			}
			else if(event[eventNum].getCDE() == 'D')
			{
				double g = generate(event[eventNum].mean, event[eventNum].stdDevation, event[eventNum].minimum, 999999);
				out << event[eventNum].name << ':' <<  (int)g << std::endl;
			}
			else if(event[eventNum].getCDE() == 'E')
			{
				double g = generate(event[eventNum].mean, event[eventNum].stdDevation, -999999, 999999);
				out << event[eventNum].name << ':' <<  g << '\n';// << event[eventNum].unit << std::endl;
			}
			else
				out << "Error log entry" << std::endl;
		}
	}
	std::cout << "Completed.\n";
}

/******************************************************************************
*
*	ANALYSIS ENGINE
*	Arguments: in file - intput stream, save output stream
*
*	read in -> calculate stats for each day -> save
*
*	Format for read in:
*	-No of types of events
*	-Day x
*	-name:value:units
*		...
*
*******************************************************************************/
struct Statistics
{
	public:
	std::string name;
	std::string units;
	std::vector<double> values; // one index = one day
	//double total;
	double mean;
	double stddev;
};

double stdDev(Statistics data[], int n, int j);
double mean(Statistics data[], int n, int j);
//double Total(double data[],int n);

void analysisEngine(std::fstream & in, std::ofstream & out, int days)
{
	std::cout << "\nAnalysis started...\n";
	int n = 0; // = number of events
	in >> n; // get top line
	in.ignore(2,'\n');
	Statistics logs[n];
	for(int i =0; i<days;i++)
	{
		string temp;
		int dayN;
		in >> temp >> dayN;
		if(temp!="Day" || dayN!= (i+1))
		{
			std::cout << "Error reading file\n";
			return;
		}
		//iterate through events;
		for(int j = 0; j<n;j++)
		{
			getline(in,logs[j].name,':');
			double temp;
			in >> temp;
			logs[j].values.push_back(temp);
			//getline(in,logs[j].units,':');
			//std::cout << logs[j].units << "\n";
			in.ignore();
		}
	}
	//calculate
	std::cout << "\nCalculating statistics...\n";
	out << n;
	for(int i =0; i<n;i++)
	{
		//logs[i].total = Total(logs[i].values,n);
		logs[i].mean = mean(logs,n, i);
		logs[i].stddev = stdDev(logs, n, i);
		//print to file
		//format: name:mean:stdDev based on Stats.txt
		out << logs[i].name << ":" << logs[i].mean << ":" << logs[i].stddev << std::endl; //logs[i].total << ":"
	}
	std::cout << "\nLog Stats complete\n";

    //SEND STATISTICS ARRAY LOCAL logs (mean,stddev)
}
//-----------  Stat functions  -------------
double stdDev(Statistics data[], int n, int j)
{
	//std::cout << "stddev\n";
	double mean=0.0, sum_deviation=0.0;
	for(int i=0; i<n;++i)
	{
		mean+=data[j].values[i];
	}
	mean=mean/n;

	for(int i=0; i<n;++i)
		sum_deviation+=(data[j].values[i]-mean)*(data[j].values[i]-mean);

	return sqrt(sum_deviation/n);
}

double mean(Statistics data[], int n, int j)
{
	//std::cout << "mean\n";
	double mean=0.0;
	for(int i=0; i<n;++i)
	{
		mean+=data[j].values[i];
	}
	mean=mean/n;
	return mean;
}

/*
double Total(double data[],int n,int j)
{
	double total;
	for(int i=0; i<n;++i)
	{
		total+=data[i];
	}
	return total;
}
*/
//-------------------------------------------
/******************************************************************************
*
*	ALERT ENGINE
*	Arguments:  Events List, void array of ints/doubles
*
*	get stats -> compare local stats with new stats -> output significant alerts
*
*	Format for read in:
*	-No of types of events
*	-name:mean:standar devation
*		...
*
*******************************************************************************/


int anomaly_value(double value, Statistics input, int weight);

/**
calcualte the anomaly counter by adding up the weighted
number of standard deviations each specific tested event value is from the mean for that event, where
the standard deviation and mean are those you have generated from the base data and reported, and the
weight is taken from the original Events.txt file.
return true if theres an inturion for a particular day
else returns false.
*/

int alert_engine(std::vector<Statistics>& inputStats, std::ifstream& in, int* weights, int count)
{
	int anomaly_counter = 0;
	double value = 0;

	//for every event
	for(int i = 0; i < count; ++i)
	{
		in.ignore(999,':');	//ignore name
		in >>value;			//read value for comparison
		in.ignore(999,'\n');	//ignore endline
		//caclulate anomaly value and add it to the counter
		anomaly_counter += anomaly_value(value,inputStats[i],weights[i]);
	}
	return anomaly_counter;
}


//anomaly value is the number of standard deveations the value is from the expected mean multiplied by weight
int anomaly_value(double value, Statistics input, int weight)
{
	double	Upper = input.mean;
	double	Lower = value;
	int		devations = 0;

	if(Upper < Lower)
		std::swap(Upper,Lower);

	while(Upper > Lower)
	{
		Upper -= input.stddev;
		++devations;
	}
	return devations * weight;
}

bool StatsFromFile(std::ifstream& in, string fileName, std::vector<Statistics>& stats)
{
	int size = 0;
	in.open(fileName.c_str());
	if(!in.is_open())
		return false;
	in >> size;

	for(int i = 0; i < size; ++i)
	{
		in.ignore(999,':');
		in >> stats[i].mean;
		in.clear(); in.ignore();
		in >> stats[i].stddev;
		in.ignore(2,'\n');
	}
	in.close();
	return true;
}

#endif

