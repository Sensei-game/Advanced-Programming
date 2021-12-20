#pragma once
#include <string>
using namespace std;

class Node;

class Arc
{
public:
	Arc();
	~Arc();
	Arc(float startRef, float endRef, string transport_Type);

	float GetStartRef(void)const;
	float GetEndRef(void)const;
	string GetTransport_Type(void)const;
	void setDestination(Node* n);
	Node* getDestination();

private:
	float m_GetStartRef;
	float m_GetEndRef;
	string m_GetTransportType;
	Node * m_destination;
};