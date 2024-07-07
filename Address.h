#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Address {
private:
	string house;
	string street;
	string city;
	string country;

public:
	bool Equals(const Address& address);
	void PrintAddress();
	Address CopyAddress();

	Address(string house, string street, string city, string country);
	Address();

	~Address();

	void SetHouse(string house1);
	void SetStreet(string street1);
	void SetCity(string city1);
	void SetCountry(string country1);

	string GetHouse();
	string GetStreet();
	string GetCity();
	string GetCountry();

	Address operator = (Address);
	bool operator == (Address);
};
