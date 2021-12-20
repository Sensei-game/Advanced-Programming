#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Links.h"
using namespace std;

class Links;

class Places
{
public: 
	
	~Places();
	Places(const string& location, const int id_number, const float latitude, const float longitude);

	const string& GetLocationName(void)const;
	int Get_id_number(void)const;
	float GetLatitude(void)const;
	float GetLongitude(void)const;
	

	const vector<Links*>&  GetLinks(void)const;
    void setLink(Links* links);

private:
	string m_location;
	int m_id_number;
	float m_latitude;
	float m_longitude;
	vector<Links*> m_Links;



};