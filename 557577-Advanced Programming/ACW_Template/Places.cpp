#include "Places.h"
#include "Links.h"





Places::~Places(){}

Places::Places(const string& location,const int id_number,const float latitude,const float longitude): m_location(location),m_id_number(id_number),m_latitude(latitude),m_longitude(longitude){}

const string& Places::GetLocationName(void)const
{
	return m_location;
}


int Places::Get_id_number(void)const
{
	return m_id_number;
}

float Places::GetLatitude(void)const
{
	return m_latitude;
}

float Places::GetLongitude(void)const
{
	return m_longitude;
}

void Places::setLink(Links* const links)
{
	m_Links.push_back(links);
}

const vector<Links*>& Places::GetLinks(void)const
{
	return m_Links;
}