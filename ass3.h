/*****************************************************************
*	CSCI262 Assignment 3 
*	ass3.h
*	last Modified: zs 17/10/15
******************************************************************/

#ifndef _ASS3_H
#define _ASS3_H
#include <iostream>
#include <random> //normal_distribution, default_random_engine
#include <cmath> //sqrt()
#include <vector>
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

// Generator for random number weighted
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
*	name:value:units
*		...
*
*******************************************************************************/

void logGenerate(Event event[], int days, std::ofstream & out)
{
	std::cout << "Log generation started...\n";
	out << event.size() << std::endl;
	for(int i=0;i<days;i++)
	{
		std::cout << "Day " << i << std::endl;
		out << "Day " << i << std::endl;
		for(int j=0;j<event.size();j++)
		{
			//check event type
			if(event[i].cde=='C')
			{
				Generator g(event[i].mean, event[i].stdDev, event[i].minimum, event[i].maximum);
				out << event[i].name << ':' <<  g() << ':' << event[i].units << std::endl;
			}
			else if(event[i].cde=='D')
			{
				Generator g(event[i].mean, event[i].stdDev, event[i].minimum, 999999);
				out << event[i].name << ':' <<  g() << ':' << event[i].units << std::endl;				
			}
			else if(event[i].cde=='E')
			{
				Generator g(event[i].mean, event[i].stdDev, -999999, 999999);
				out << event[i].name << ':' <<  g() << ':' << event[i].units << std::endl;
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
	double * values; // one index = one day
	double total;
	double mean;
	double stddev;
	Statistics(int n) {values = new double[n];}
	~Statistics {delete [] values;}
};

void analysisEngine(std::ifstream & in, std::ofstream & out, int days)
{
	std::cout << "\nAnalysis started...\n";
	int n; // = number of events
	in >> n; // get top line
	std::vector<Statistics> logs(n, Statistics(days));
	for(int i =0; i<days;i++)
	{
		string temp;
		int dayN;
		in >> temp >> dayN;
		if(temp!="Day" || dayN!= (i-1))
		{
			std::cout << "Error reading file\n"; 				return;
		}

		//iterate through events;
		for(int j = 0; j<n;j++)
		{
			getline(in,logs[j].name,':');
			in.ignore();
			getline(in,logs[j].values[i],':')
			in.ignore();
			getline(in,logs[j].units,':')
		}
	}
	//calculate;
	std::cout << "Calculating statistics...\n";
	out << n << std::endl;
	for(int i =0; i<n;i++)
	{
		logs[i].total = Total(logs[i].values,n);
		logs[i].mean = mean(logs[i].values,n);
		logs[i].stddev = stdDev(logs[i].values,n);
		//print to file
		//format: name:total:mean:stdDev based on Stats.txt
		out << logs[i].name << ":" << logs[i].total << ":" << logs[i].mean << ":" << logs[i].stddev << std::endl;
	}
	std::cout << "Saved to file\n";
		
}
//-----------  Stat functions  -------------
double stdDev(double data[], int n) //
{
	double mean=0.0, sum_deviation=0.0;
	for(int i=0; i<n;++i)
	{
		mean+=data[i];
	}
	mean=mean/n;

	for(int i=0; i<n;++i)
		sum_deviation+=(data[i]-mean)*(data[i]-mean);

	return sqrt(sum_deviation/n);           
}

double mean(double data[], int n)
{
	double mean=0.0;
	for(int i=0; i<n;++i)
	{
		mean+=data[i];
	}
	mean=mean/n;
	return mean;           
}


double Total(double data[],int n)
{	
	double total;
	for(int i=0; i<n;++i)
	{
		total+=data[i];
	}
	return total;
}
//-------------------------------------------
#endif