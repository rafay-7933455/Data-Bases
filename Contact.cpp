#include"Contact.h"
/*
*	Implement a constructor that initializes all the Contact parts, including address. Call the setter to set values
*	as they have the logic to check correct input
*	Declaration is given in Contact.h
*/
Contact::Contact() {
	first_name = last_name = mobile_number = email_address = "";
	address = 0;
	search_count = 0;
	birth_date.day = birth_date.month = birth_date.year = "";
}
Contact::Contact(string f_name, string l_name, string m_number, string em_address, Address* address1, string id, Date d) {
	first_name = f_name;
	last_name = l_name;
	mobile_number = m_number;
	email_address = em_address;
	address = address1;
	ID = id;
	search_count = 0;
	birth_date = d;
}
void Contact::SetContact(string first_name, string last_name, string mobile_number, string email_address, Address* address1, string id, Date d) {
	SetAddress(address1);
	SetEmail(email_address);
	SetFirstName(first_name);
	SetLastName(last_name);
	SetMobileNumber(mobile_number);
	SetID(id);
	SetBirth(d);
}
/*
*	Implement getter/setters for all the member variables of Contact. Also declare them in the Contact.h header file
*	In each setter, do not set value if string is empty ("" 0 size).
*   Check in phone number setter, Phone number must be 11 digits
*/

void Contact::SetAddress(Address* a) {
	address = a;
}
Address* Contact::GetAddress() {
	return address;
}
void Contact::SetEmail(string a) {
	email_address = a;
}
string Contact::GetEmail() {
	return email_address;
}
void Contact::SetFirstName(string a) {
	first_name = a;
}
string Contact::GetFirstName() {
	return first_name;
}
void Contact::SetLastName(string a) {
	last_name = a;
}
string Contact::GetLastName() {
	return last_name;
}
void Contact::SetMobileNumber(string a) {
	mobile_number = a;
}
string Contact::GetMobileNumber() {
	return mobile_number;
}
void Contact::SetID(string id) {
	ID = id;
}
string Contact::GetID() {
	return ID;
}
/*
*	Implement the Equals function(as declared in header file) that takes a
*   Contact object and checks if it is equal to current object refered by (this pointer).
*   Compare all the attributes.
*   For comparing address of contact you can call the Equals function of the Address object;
*   For example: this.address.Equals
*/
bool Contact::Equals(Contact c) {
	if (first_name == c.GetFirstName()) {
		if (last_name == c.GetLastName()) {
			if (email_address == c.GetEmail()) {
				if (mobile_number == c.GetMobileNumber()) {
					if (address->Equals(*(c.GetAddress()))) {
						if (birth_date.day == c.GetBirth().day) {
							if (birth_date.month == c.GetBirth().month) {
								if (birth_date.year == c.GetBirth().year) return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void Contact::IncreaseSearchCount() {
	search_count++;
}

int Contact::GetSearchCount() {
	return search_count;
}

Contact& Contact::CopyContact() {
	/*
		Return a new object(deep copy of "this"[due to Address pointer, which should also be copied])
	*/
	Contact* c = new Contact(*this);
	Address* newAddress = new Address;
	//To make a deep copy of address of *this in C(object)
	*newAddress = (this->GetAddress()->CopyAddress());
	c->address = newAddress;
	return *c;
}
Contact Contact:: operator = (Contact c) {
	first_name = c.GetFirstName();
	last_name = c.GetLastName();
	mobile_number = c.GetMobileNumber();
	email_address = c.GetEmail();
	address = c.GetAddress();
	ID = c.GetID();
	birth_date = c.GetBirth();
	return Contact(first_name, last_name, mobile_number, email_address, address, ID, birth_date);
}
bool Contact::operator == (Contact c) {
	if (first_name == c.GetFirstName()) {
		if (last_name == c.GetLastName()) {
			if (email_address == c.GetEmail()) {
				if (mobile_number == c.GetMobileNumber()) {
					if (address->Equals(*(c.GetAddress()))) {
						if (birth_date.day == c.GetBirth().day) { 
							if (birth_date.month == c.GetBirth().month) {
								if (birth_date.year == c.GetBirth().year) return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void Contact::PrintContact() {
	cout << this->GetID() << " " << this->GetFirstName() << " " << this->GetLastName() << " " << this->GetMobileNumber() << " " << this->GetEmail() << endl;
	this->GetAddress()->PrintAddress();
	cout << endl;
}
//Contact::~Contact() {}

void Contact::SetBirth(Date d) {
	birth_date = d;
}

Date Contact::GetBirth() {
	return birth_date;
}