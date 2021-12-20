#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Links.h"
using namespace std;

class Places;

class Links {

public: 
	
	~Links();
	Links(const int first_id, const int last_id, const string& transport);
	int Get_first_id(void)const;
	int Get_last_id(void)const;
	const string& GetTransport(void)const;
	void setFirstLocation(Places* p);
	void setLastLocation(Places*p);
	Places* getFirstLocation()const;
	Places* getLastLocation()const;

private:


	int m_first_id;
	int m_last_id;
	 string m_transport;
	Places* m_first_location;
	Places* m_second_location;
	
};