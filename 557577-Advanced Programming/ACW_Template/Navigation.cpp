#include "Navigation.h"
#include "Places.h"
#include "Links.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>

vector<Links*> Links_count;
vector< Places*> Places_count;

using namespace std;

// Converts latitude/longitude into eastings/northings
extern void LLtoUTM(const double Lat, const double Long, double &UTMNorthing, double &UTMEasting);

Navigation::Navigation() : _outFile("Output.txt")
{
	
}

Navigation::~Navigation()
{
}



bool Navigation::ProcessCommand(const string& commandString)
{
	istringstream inString(commandString);
	
	char line[255];

	if (inString.fail()) return false;

	while (inString.good())
	{
       
		inString.getline(line, 255, ' ');
		const string command = string(line);
	


	
	    if (command == "MaxDist")
	   {
			_outFile<<command<<endl;
		MaxDistance();
	    }

	    if (command == "MaxLink")
		{
			_outFile << command << endl;
		MaxLink();
	    }

	    if (command == "FindDist")
	    {
			int first_id;
			int last_id;
			const bool use = false;
			inString.getline(line, 255, ' ');
			
			istringstream s_command(line);

			s_command >> first_id;

			_outFile << command<<' '<<first_id << ' ';

		
			inString.getline(line, 255, ' ');
			istringstream s_command2(line);

			s_command2 >> last_id;
			_outFile << last_id << ' '<<endl;


			
		    FindDist(first_id,last_id,use);
	    }

		if (command == "FindNeighbour")
		{
			inString.getline(line, 255, ' ');

			istringstream s_command(line);
			int id_number;

			s_command >> id_number;


			_outFile << command << " " << id_number << endl;
			FindNeighbour(id_number);
		}

		if (command == "Check")
		{
			inString.getline(line, 255, ' ');
			istringstream s_transport(line);
			string transport;

			s_transport >> transport;
			
			inString.getline(line, 255, ' ');
			istringstream s_first_stop(line);
			int first_stop;

			s_first_stop>>first_stop;

			inString.getline(line, 255, ' ');
			istringstream s_second_stop(line);
			int second_stop;

			s_second_stop >> second_stop;
		 
			inString.getline(line, 255, ' ');
			istringstream s_third_stop(line);
			int third_stop;
		
			s_third_stop >> third_stop;
		
			inString.getline(line, 255, ' ');
			istringstream s_fourth_stop(line);
			int fourth_stop;

			s_fourth_stop >> fourth_stop;


			_outFile << command << " " << first_stop << " " << second_stop << " " << third_stop << " " << fourth_stop << endl;
			Check(transport, first_stop, second_stop, third_stop, fourth_stop);
		}

		if (command == "FindRoute")
		{
			inString.getline(line, 255, ' ');
			istringstream s_transport(line);
			string transport;

			s_transport >> transport;

			inString.getline(line, 255, ' ');
			istringstream s_start_location(line);
			int start_location;

			s_start_location >> start_location;


			inString.getline(line, 255, ' ');
			istringstream s_last_location(line);
			int final_location;

			s_last_location >> final_location;

			_outFile << command << " " << transport << " " << start_location << " " << final_location << endl;

			FindRoute(transport, start_location, final_location);
		}

		if (command == "FindShortestRoute")
		{
			inString.getline(line, 255, ' ');
			istringstream s_transport(line);
			string transport;

			s_transport >> transport;

			inString.getline(line, 255, ' ');
			istringstream s_start_location(line);
			int start_location;

			s_start_location >> start_location;


			inString.getline(line, 255, ' ');
			istringstream s_last_location(line);
			int final_location;

			s_last_location >> final_location;


			_outFile << command << " " << transport << " " << start_location << " " << final_location << endl;
			FindShortestRoute(transport, start_location, final_location);
		}


	}
	

	return true;
}

#pragma region Useless Maths 

//void Navigation::LLtoUTM(const double Lat, const double Long, double & UTMNorthing, double & UTMEasting)
//{
//	const double RADIUS = 6378137.0;
//	const double FLATTENING = 0.00335281068; /* GRS80 or WGS84 */
//	const double K_NOT = 0.9996;     /* UTM scale factor */
//	const double DEGREES_TO_RADIANS = 0.01745329252; /*0.01745329*/
//	const double RADIANS_TO_DEGREES = 57.29577951;
//	//const double FALSE_EASTING = 500000.0;
//	//const double FALSE_NORTHING = 10000000.0;
//
//	//zone can be calculated
//	const double zone = 31 + (Long / 6);
//
//	double Long_temp = Long - 180;
//	double LongRad = Long_temp * DEGREES_TO_RADIANS;
//	double LatRad = Lat * DEGREES_TO_RADIANS;
//
//	/* first compute the necessary geodetic parameters and constants */
//
//
//
//	double lambda_not = ((-180.0 + zone * 6.0) - 3.0) /*/ DEGREES_TO_RADIANS*/;
//	double lambda_rad = lambda_not * DEGREES_TO_RADIANS;
//
//
//	double e_squared = 2.0 * FLATTENING - FLATTENING * FLATTENING;
//	double e_fourth = e_squared * e_squared;
//	double e_sixth = e_fourth * e_squared;
//	double e_prime_sq = e_squared / (1.0 - e_squared);
//
//	double sin_phi = sin(LatRad);
//	double tan_phi = tan(LatRad);
//	double cos_phi = cos(LatRad);
//
//	double N = RADIUS / sqrt(1.0 - e_squared * sin_phi*sin_phi);
//	double T = tan_phi * tan_phi;
//	double C = e_prime_sq * cos_phi*cos_phi;
//	double M = RADIUS * ((1.0 - e_squared * 0.25 - 0.046875*e_fourth - 0.01953125*e_sixth)*LatRad -
//		(0.375*e_squared + 0.09375*e_fourth +
//			0.043945313*e_sixth)*sin(2.0*LatRad) +
//			(0.05859375*e_fourth + 0.043945313*e_sixth)*sin(4.0*LatRad) -
//		(0.011393229 * e_sixth)*sin(6.0*LatRad));
//
//	double A = (LongRad - lambda_rad)*cos_phi;
//	double A_sq = A * A;
//	double A_fourth = A_sq * A_sq;
//
//	/* now go ahead and compute X and Y */
//
//	UTMEasting = K_NOT * N*(A + (1.0 - T + C)*A_sq*A / 6.0 +
//		(5.0 - 18.0*T + T * T + 72.0*C -
//			58.0*e_prime_sq)*A_fourth*A / 120.0);
//
//	/* note:  specific to UTM, vice general trasverse mercator.
//	since the origin is at the equator, M0, the M at phi_0,
//	always equals zero, and I won't compute it   */
//
//	UTMNorthing = K_NOT * (M + N * tan_phi*(A_sq / 2.0 +
//		(5.0 - T + 9.0*C + 4.0*C*C)*A_fourth / 24.0 +
//		(61.0 - 58.0*T + T * T + 600.0*C -
//			330.0*e_prime_sq)*A_fourth*A_sq / 720.0));
//
//	/* now correct for false easting and northing */
//
//	if (Lat < 0)
//	{
//		UTMNorthing += 10000000.0;
//	}
//	UTMEasting += 500000;
//
//
//	
//	//return true;
//}

#pragma endregion

bool Navigation::BuildNetwork(const string &fileNamePlaces, const string &fileNameLinks)const
{
	ifstream finPlaces(fileNamePlaces);
	ifstream finLinks(fileNameLinks);

	if (finPlaces.fail() || finLinks.fail()) return false;

	// Add your code here
	char line[255];
	string location;
	int id_number;
	float latitude;
	float longitude;

	int first_id;
	int last_id;
	string transport;

	
	while (!finPlaces.eof()) {

		finPlaces.getline(line, 255, ',');
		location = string(line);
		
		//_outFile << location << " " ;

		finPlaces.getline(line, 255, ',');
		istringstream s_place(line);

		s_place >> id_number;

	//	_outFile << id_number << " " ;

		finPlaces.getline(line, 255, ',');
		istringstream s_place2(line);

		s_place2 >> latitude;

	//	_outFile << latitude << " " ;

		finPlaces.getline(line, 255, '\n');
		istringstream s_place3(line);

		s_place3 >> longitude;
	//	_outFile << longitude << " " << endl;
		//variables are in place all is needed are Places to load them in identities

		   Places* const place =  new Places(location, id_number, latitude, longitude);
		   Places_count.push_back(place);



		   //_outFile << "Places separated and placed into values succesfully!" << endl;

	}
	
	while (!finLinks.eof()) {

		finLinks.getline(line, 255, ',');
		istringstream s_place(line);
		
		s_place >> first_id;
		//_outFile << first_id<<" ";

		finLinks.getline(line, 255, ',');
		istringstream s_place2(line);

		s_place2 >> last_id;
		//_outFile << last_id<<" ";

		finLinks.getline(line, 255, '\n');
		const istringstream s_place3(line);

		transport = string(line);

		//_outFile << transport << " " << endl;
	//	_outFile << "LINKS separated and placed into values succesfully!" << endl;
		
		//variables are in place just make the Links claas and identity
		Links* const links = new Links(first_id, last_id, transport);
		Links_count.push_back(links);
	}
	
	for (int i = 0; i < Links_count.size(); i++)
	{
		for (int j = 0; j < Places_count.size(); j++)
		{
			if (Links_count[i]->Get_first_id() == Places_count[j]->Get_id_number())
			{
				Links_count[i]->setFirstLocation(Places_count[j]);
				Places_count[j]->setLink(Links_count[i]);
				//_outFile << Places_count[j]->GetLocationName() << endl;
				for (int k = 0; k < Places_count.size(); k++)
				{
					if (k!=j && Places_count[k]->Get_id_number() == Links_count[i]->Get_last_id())
					{
						Links_count[i]->setLastLocation(Places_count[k]);
						//Places_count[j]->setLink(Links_count[i]);
						Places_count[k]->setLink(Links_count[i]);
						//_outFile << "points to " << Places_count[k]->GetLocationName() << endl << endl;
						//return true;
					}
				}
			}
	    }

	}


	return true;
}

// Add your code here

double Navigation::FindDist(const int first_id,const int last_id,const bool used)
{
	double first_northings = 0;
	double first_easting = 0;

	double second_northings = 0;
	double second_eastings = 0;

	double MaxDistance = 0;
	string first_placeName;
	string second_placeName;

	for (int i = 0; i < Places_count.size(); i++)
	{
		
		if (Places_count[i]->Get_id_number() == first_id)
		{
			const float x1 = Places_count[i]->GetLatitude();
			const float y1 = Places_count[i]->GetLongitude();
			LLtoUTM(x1, y1, first_northings, first_easting);

			
			for (int j = i + 1; j < Places_count.size(); j++)
			{
				if (Places_count[j]->Get_id_number() == last_id)
				{
					const float x2 = Places_count[j]->GetLatitude();
					const float y2 = Places_count[j]->GetLongitude();
					LLtoUTM(x2, y2, second_northings, second_eastings);

					const double x_result = (first_easting - second_eastings)* (first_easting - second_eastings);
					const double y_result = (first_northings - second_northings)*(first_northings - second_northings);
					double result = x_result + y_result;
					result = sqrt(result);

					if ((result / 1000) > MaxDistance)
					{
						first_placeName = Places_count[i]->GetLocationName();
						second_placeName = Places_count[j]->GetLocationName();
						MaxDistance = result / 1000;
					}
				}
			}
			
		}
	}
	if(used==true){return MaxDistance;}
	else
	{
		_outFile << first_placeName << " " << second_placeName << " " << MaxDistance << endl << endl;
	}
	
}


bool Navigation::MaxLink()
{
	double first_northings;
	double first_eastings;

	double second_northings;
	double second_eastings;

	double MaxDistance = 0;
	int PlaceName_1;
	int PlaceName_2;

	for (int i = 0; i < Links_count.size(); i++)
	{
		for (int j = 0; j < Places_count.size(); j++)
		{
			if (Links_count[i]->Get_first_id() == Places_count[j]->Get_id_number())
			{
				float const x1 = Places_count[j]->GetLatitude();
				float const y1 = Places_count[j]->GetLongitude();
				LLtoUTM(x1, y1, first_northings, first_eastings);

					for (int k = 0; k < Places_count.size(); k++)
					{
						if (Places_count[k]->Get_id_number() == Links_count[i]->Get_last_id())
						{
							float const x2 = Places_count[k]->GetLatitude();
							float const y2 = Places_count[k]->GetLongitude();
							LLtoUTM(x2, y2, second_northings, second_eastings);
						
							double const x_result = (second_eastings - first_eastings)*(second_eastings - first_eastings);
							double const y_result = (second_northings - first_northings)*(second_northings - first_northings);
						
							double const result = x_result + y_result;
							double const final_result = sqrt(result);

							if (final_result / 1000 > MaxDistance)
							{
								PlaceName_1 = Places_count[j]->Get_id_number();
								PlaceName_2 = Places_count[k]->Get_id_number();
								MaxDistance = final_result / 1000;


							}
						}
					}
			}
		}
	}
	_outFile << PlaceName_2 << " " << PlaceName_1 << " " << MaxDistance << endl<<endl;
	return true;
}

bool Navigation::MaxDistance()
{
	double first_northings = 0;
	double first_easting = 0;

	double second_northings = 0;
	double second_easting = 0;

	double MaxDistance = 0;

	double x_result;
	double y_result;

	double result ;
	double final_Result ;

	string PlaceName_1;
	string PlaceName_2;

	for (int i = 0; i < Places_count.size(); i++)
	{
		float const x1 = Places_count[i]->GetLatitude();
		float const y1 = Places_count[i]->GetLongitude();
		LLtoUTM(x1, y1, first_northings, first_easting);

		for (int j=i+1; j<Places_count.size();j++)
		{
			float const x2 = Places_count[j]->GetLatitude();
			float const y2 = Places_count[j]->GetLongitude();
			LLtoUTM(x2, y2, second_northings, second_easting);

			x_result = (second_easting - first_easting)*(second_easting - first_easting);
			y_result = (second_northings - first_northings)*(second_northings - first_northings);

			result = x_result + y_result;
			final_Result = sqrt(result);

			if (final_Result / 1000 > MaxDistance)
			{
				PlaceName_1 = Places_count[i]->GetLocationName();
				PlaceName_2 = Places_count[j]->GetLocationName();

				MaxDistance = final_Result / 1000;

			}

		}
	}
	_outFile << PlaceName_1 << " " << PlaceName_2 << " " << MaxDistance<<endl<<endl;
	return true;
}

bool Navigation::FindNeighbour(const int id_number)
{
	vector<Links*> result;
	Places* Neighbour;

	for(int i = 0; i < Places_count.size();i++)
	{
		if (Places_count[i]->Get_id_number() == id_number)
		{
			_outFile << "Place Location is : " << Places_count[i]->GetLocationName()<<endl;

			 result = Places_count[i]->GetLinks();
			
			 for (int j = 0; j < result.size(); j++)
			 {
				 if (result[j]->getFirstLocation() ==Places_count[i] )
				 {
					  Neighbour = result[j]->getLastLocation();
					  _outFile <<"Neighbours are: " <<Neighbour->GetLocationName()<<" "<<Neighbour->Get_id_number()<<endl;
				 }
				 else
					 if (result[j]->getLastLocation() == Places_count[i])
					 {
						 Neighbour = result[j]->getFirstLocation();
						 _outFile << "Neighbours are: " << Neighbour->GetLocationName()<<" "<< Neighbour->Get_id_number() <<endl;
				     }
			 }


		}
	}
	_outFile << endl;
	return true;

}

bool Navigation::Check(const string& Transport, const int first_place_id, const int second_place_id, const int third_place_id, const int fourth_place_id)
{
	int confirm = 0;

	for (int i = 0; i < Links_count.size(); i++)
	{
		if(Links_count[i]->GetTransport() == Transport)
		{
			//case 1
				if (Links_count[i]->Get_first_id() == first_place_id && Links_count[i]->Get_last_id() == second_place_id   )
				{
					confirm++;
					
					_outFile << Links_count[i]->Get_first_id()<<" "<<Links_count[i]->Get_last_id()<<" PASS ";
					
				}
				//case 2
				else if (Links_count[i]->Get_first_id() == second_place_id && Links_count[i]->Get_last_id() == first_place_id )
				{
					confirm++;

					_outFile << Links_count[i]->Get_last_id() << " " << Links_count[i]->Get_first_id() << " PASS ";
					
				}
		 }
		
	}
	//FIRST STAGE


	if (confirm == 0)
	{
		_outFile << first_place_id<<" "<< second_place_id<<" FAIL " << endl<<endl;
		return false;
	}
	//FAIL

	if (confirm == 1)
	{
		for (int j = 0; j < Links_count.size(); j++)
		{
			if(Links_count[j]->GetTransport() == Transport)
			{
			//case 1
			
				if (Links_count[j]->Get_first_id() == second_place_id && Links_count[j]->Get_last_id() == third_place_id  )
			
				
				{
				
					confirm++;
				   _outFile << Links_count[j]->Get_first_id() <<" "<< Links_count[j]->Get_last_id() <<  " PASS ";
				
				
			
				}
			//case 2
			
				else if (Links_count[j]->Get_first_id() == third_place_id && Links_count[j]->Get_last_id() == second_place_id )
					{
						confirm++;
						_outFile << Links_count[j]->Get_last_id() << " " << Links_count[j]->Get_first_id() << " PASS ";
				
						
					}
			}
			
		}
	}   
	//SECOND STAGE
	

	if (confirm == 1)
	{
		_outFile << second_place_id<<" "<< third_place_id<<" FAIL " << endl<<endl;
		return false;
	}
	//FAIL

	if (confirm == 2)
	{
		for (int z = 0; z<Links_count.size(); z++)
		{
			if(Links_count[z]->GetTransport() == Transport)
			{ 
			//case 1
				if (Links_count[z]->Get_first_id() == third_place_id && Links_count[z]->Get_last_id() == fourth_place_id  )
				{
					confirm++;
				
					_outFile << Links_count[z]->Get_first_id() << " " <<Links_count[z]->Get_last_id() << " PASS "<<endl;
					
				}
			//case 2
				else if (Links_count[z]->Get_first_id() == fourth_place_id && Links_count[z]->Get_last_id() == third_place_id )
					{
						confirm++;
				
						_outFile << Links_count[z]->Get_last_id() << " " << Links_count[z]->Get_first_id() << " PASS " << endl;
						
			
					}
			}
		}
	}
	//THIRD STAGE



	if (confirm == 2)
	{
		_outFile << third_place_id << " " << fourth_place_id << " FAIL " << endl<<endl;
		return false;
	}
	//FAIL



	_outFile << endl;
		return true;


}

bool Navigation::FindRoute(const string& Transport, const int start_location_id, const int final_location_id)
{
	vector<int> found_places;
	int confirm = 0;
	
	

	for (int i = 0; i < Links_count.size(); i++)
	{

		if (Links_count[i]->GetTransport() == Transport) {



			//caz 1
			if (Links_count[i]->Get_first_id() == start_location_id && confirm == 0)
			{
				confirm++;
				found_places.push_back(Links_count[i]->Get_first_id());
				found_places.push_back(Links_count[i]->Get_last_id());
				_outFile << Links_count[i]->Get_first_id() << endl << Links_count[i]->Get_last_id() << endl;
				i = Links_count.size()-1;

			}
			//caz 2
			else if (Links_count[i]->Get_last_id() == start_location_id && confirm == 0)
			{
				confirm++;
				found_places.push_back(Links_count[i]->Get_last_id());
				found_places.push_back(Links_count[i]->Get_first_id());
				_outFile << Links_count[i]->Get_last_id() << endl << Links_count[i]->Get_first_id() << endl;
				i = Links_count.size() - 1;
			}

		}

	}
	if(confirm==1)
	{
	
		for (int j = 0; j < Links_count.size(); j++)
		{
			if (Links_count[j]->GetTransport() == Transport)
			{
				//case 1
				if (found_places.back() == Links_count[j]->Get_first_id())
				{
					for (int t=0;t <found_places.size();t++ )
					{
						if (Links_count[j]->Get_last_id()== final_location_id)
						{
							_outFile << Links_count[j]->Get_last_id()<<endl;
							return true;
						}
						else
						if (found_places[t] != Links_count[j]->Get_last_id())
						{

							_outFile<< Links_count[j]->Get_last_id() <<endl<<endl;
							found_places.push_back(Links_count[j]->Get_last_id());
							break;
						}

						

						
					}
		
			
				}
		
			
				else
			
					//case2
					if (found_places.back() == Links_count[j]->Get_last_id())
			
					{
				
						for (int t = 0; t <found_places.size() ; t++)	
						{
							if (Links_count[j]->Get_first_id() == final_location_id)
							{
								_outFile<<Links_count[j]->Get_first_id()<<endl<<endl;
								return true;
							}
							else
							if (found_places[t] != Links_count[j]->Get_first_id())
					
							{
								_outFile << Links_count[j]->Get_first_id() << endl;
								found_places.push_back(Links_count[j]->Get_first_id());

								break;
							}
							


				
						}
                  
			
					}
			
		
			}
	
		}

	}

	else
	{
		_outFile << " Fail "<<endl<<endl;
		return false;
	}



}


bool Navigation::FindShortestRoute(const string& Transport, const int start_location_id, const int final_location_id)
{
	vector<int> found_places;
	int confirm = 0;
	const bool use = true;

	double FullDistance = FindDist(start_location_id, final_location_id,use);
	double Difference=0;

	int best_i;

	bool first = false;
	bool last = false;


	for (int i = 0; i < Links_count.size(); i++)
	{

		if (Links_count[i]->GetTransport() == Transport) {



			//case 1
			if (Links_count[i]->Get_first_id() == start_location_id && confirm == 0)
			{
				
				
				const double distance = FindDist(Links_count[i]->Get_first_id(), Links_count[i]->Get_last_id(),use);
				
				if (Difference < FullDistance - distance)
				{
					last = false;
					Difference = FullDistance - distance;
					 best_i = i;

					first = true;

				}
			}
			
			//case 2
			else if (Links_count[i]->Get_last_id() == start_location_id && confirm == 0)
			{
				

				const double distance = FindDist(Links_count[i]->Get_last_id(), Links_count[i]->Get_first_id(),use);

				if (Difference < FullDistance - distance)
				{
					first = false;
					Difference = FullDistance - distance;
					const int best_i = i;
					last = true;
					
				}


			}
		}
	}

	if (first == true)
	{
		found_places.push_back(Links_count[best_i]->Get_first_id());
		found_places.push_back(Links_count[best_i]->Get_last_id());
		_outFile << Links_count[best_i]->Get_first_id() << endl<< Links_count[best_i]->Get_last_id()<<endl;
		FullDistance= FindDist(Links_count[best_i]->Get_last_id(), final_location_id,use);
		confirm++;
	}
	else
		if (last == true)
		{
			
			found_places.push_back(Links_count[best_i]->Get_last_id());
			found_places.push_back(Links_count[best_i]->Get_first_id());
			_outFile << Links_count[best_i]->Get_last_id() << endl<< Links_count[best_i]->Get_first_id() <<endl;

			FullDistance= FindDist(Links_count[best_i]->Get_first_id(), final_location_id,use);
			confirm++;

		}


	if (confirm == 1)
	{
		
		for (int j = 0; j < Links_count.size(); j++)
		{
			Difference = 0;
			if (Links_count[j]->GetTransport() == Transport)
			{
				if (found_places.back() == Links_count[j]->Get_first_id())
				{
					const double distance = FindDist(Links_count[j]->Get_first_id(), Links_count[j]->Get_last_id(),use);
					if(Difference > FullDistance - distance)
					{
						Difference = FullDistance-distance;
					}
				
					else
					{ 
						for (int t = 0; t <found_places.size(); t++)
					
						{
						
							if (Links_count[j]->Get_last_id() == final_location_id)
						
							{
							
								_outFile << Links_count[j]->Get_last_id() << endl<<endl;
							
								return true;
					
							}
						
							else
						
								if (found_places[t] != Links_count[j]->Get_last_id())
							
								{
							
									_outFile << Links_count[j]->Get_last_id() << endl;
								
									found_places.push_back(Links_count[j]->Get_last_id());
								
									FullDistance = FindDist(Links_count[j]->Get_last_id(), final_location_id,use);

									break;
							
								}

					
						}
                    }

					
				}


				else

					if (found_places.back() == Links_count[j]->Get_last_id())

					{
						const double distance = FindDist(Links_count[j]->Get_last_id(),Links_count[j]->Get_first_id(),use);
						
						
						
						
							for (int t = 0; t <found_places.size(); t++)
						
							{
							
								if (Links_count[j]->Get_first_id() == final_location_id)
								{
								
									_outFile << Links_count[j]->Get_first_id() << endl<<endl;
								
									return true;
							
								}
						
								else
							
									if (found_places[t] != Links_count[j]->Get_first_id())
									{
								
										if (Difference > FullDistance - distance)						
										{
											Difference = FullDistance - distance;
										}
										else
										{
											_outFile << Links_count[j]->Get_first_id() << endl;

											found_places.push_back(Links_count[j]->Get_first_id());
											FullDistance = FindDist(Links_count[j]->Get_first_id(), final_location_id,use);
											break;
										}
										
								
									}



						
							}

						

					}


			}

		}

	}
	
	
	else
	
	{
		_outFile << " Fail " << endl<<endl;
		return false;
	
	}
	
}
		
	

	
	
	
	
	
	


