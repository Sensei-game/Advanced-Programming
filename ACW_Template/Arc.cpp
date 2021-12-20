#include "Arc.h"
#include "Node.h"



Arc::Arc()
{
}


Arc::~Arc()
{
}

Arc::Arc(float startRef, float endRef, string Transport_Type) : m_GetStartRef(startRef), m_GetEndRef(endRef), m_GetTransportType(Transport_Type) {

}


float Arc::GetStartRef(void)const {
	return m_GetStartRef;
}

float Arc::GetEndRef(void)const {
	return m_GetEndRef;
}

string Arc::GetTransport_Type(void)const {
	return m_GetTransportType;
}

void Arc::setDestination(Node* n) {
	m_destination = n;
}

Node* Arc::getDestination() {
	return m_destination;
}