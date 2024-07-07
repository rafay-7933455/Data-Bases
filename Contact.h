#include <iostream>
#include <string>
#include <fstream>
#include"Address.h"
using namespace std;
struct Date {
	string day;
	string month;
	string year;
};
class Contact {
private:
	string first_name;
	string last_name;
	string mobile_number;
	string email_address;
	string ID;
	Address* address;
	Date birth_date;
	int search_count;
public:
	bool Equals(Contact contact);
	//setter/getters
	Address* GetAddress();
	void SetAddress(Address*);
	void SetEmail(string a);
	string GetEmail();
	void SetFirstName(string a);
	string GetFirstName();
	void SetLastName(string a);
	string GetLastName();
	void SetMobileNumber(string a);
	string GetMobileNumber();
	void SetID(string id);
	string GetID();
	void SetBirth(Date d);
	Date GetBirth();
	Contact& CopyContact();
	void SetContact(string first_name, string last_name, string mobile_number, string email_address, Address* address1, string id, Date d);

	void IncreaseSearchCount();
	int GetSearchCount();
	//contructors
	Contact();
	Contact(string first_name, string last_name, string mobile_number, string email_address, Address* address1, string id, Date d);
	//operators
	Contact operator = (Contact);
	bool operator == (Contact);
	//Display Contact
	void PrintContact();
	//destructor
	//~Conta//ct();
};