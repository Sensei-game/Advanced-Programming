#pragma once

#include <fstream>
#include <string>

class Navigation
{
	std::ofstream _outFile;

	// Add your code here

public:
	Navigation();
	~Navigation();

	bool BuildNetwork(const std::string& fileNamePlaces, const std::string& fileNameLinks)const;
	bool ProcessCommand(const std::string& commandString);
	double FindDist(const int first_id, const int last_id,const bool used);
	bool MaxLink();
	bool MaxDistance();
	bool FindNeighbour(const int id_number);
	bool Check (const std::string& Transport,const int first_place_id,const int second_place_id,const int third_place_id,const int fourth_place_id);
	bool FindRoute(const std::string& Transport, const int start_location_id, const int final_location_id);
	bool FindShortestRoute(const std::string& Transport, const int start_location_id, const int final_location_id);
	// Add your code here
	

};