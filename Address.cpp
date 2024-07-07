#include"Address.h"
/*
*	Implement a constructor that initializes all the address parts
*
*/

Address::Address() {
	house = street = city = country = "Nil";
}

Address::Address(string house1, string street1, string city1, string country1) {
	house = house1;
	street = street1;
	city = city1;
	country = country1;
}

Address::~Address() {}
/*
*	Implement getter/setters for all the member variables of Address. Also declare them in the Address.h header file
*
*/
//setters
void Address::SetHouse(string house1) {
	house = house1;
}
void Address::SetStreet(string street1) {
	street = street1;
}
void Address::SetCity(string city1) {
	city = city1;
}
void Address::SetCountry(string country1) {
	country = country1;
}
//getters
string Address::GetHouse() {
	return house;
}
string Address::GetStreet() {
	return street;
}
string Address::GetCity() {
	return city;
}
string Address::GetCountry() {
	return country;
}
/*
*	Implement the Equals function that takes an Address object and checks if it is equal to
*	current object refered by (this pointer)
*	Two addresses are equal if all the attributes of addresses are equal
*/
bool Address::Equals(const Address& address)
{
	/*
	* Todo
	*/
	if (this->house == address.house) {
		if (this->street == address.street) {
			if (this->city == address.city) {
				if (this->country == address.country) {
					return true;
				}
			}
		}
	}
	return false;
}

void Address::PrintAddress()
{
	/*
	*	Print address on one line as
	*	House, Street, City, Country
	*/
	cout << house << "," << street << "," << city << "," << country << endl;
}

Address Address::CopyAddress()
{
	/*
		return a copy of this
	*/
	//Address* A = new Address(*this);
	//return Address(*A);
	return Address(*this);
}

Address Address::operator=(Address C) {
	house = C.GetHouse();
	street = C.GetStreet();
	city = C.GetCity();
	country = C.GetCountry();
	return *this;
}

bool Address::operator==(Address C) {
	return (house == C.GetHouse()) && (street == C.GetStreet()) && (city == C.GetCity()) && (country == C.GetCountry());
}
