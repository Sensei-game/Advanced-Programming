#include "Links.h"
#include "Places.h"



Links::~Links(){}

Links::Links(const int first_id, const int last_id, const string& transport) : m_first_id(first_id), m_last_id(last_id), m_transport(transport),m_first_location(),m_second_location()
{

}



int Links::Get_first_id(void)const
{
	return m_first_id;
}

int Links::Get_last_id(void)const
{
	return m_last_id;
}

const string& Links::GetTransport(void)const
{
	return m_transport;
}

void Links::setFirstLocation(Places* const p) 
{
	m_first_location = p;
}

Places* Links::getFirstLocation()const
{
	return m_first_location;
}



void Links::setLastLocation(Places* const p)
{
	m_second_location = p;
}

Places* Links::getLastLocation()const
{
	return m_second_location;
}


