#include "Group.h"
Group::Group() {
	group_name = "";
	group_member = new Contact[50];
	no_of_members = 0;
}
void Group::SetGroupName(string n) {
	group_name = n;
}
Contact* Group::GetMemberListCopy() {
	return group_member;
}
string Group::GetGroupName() {
	return group_name;
}
Group Group::operator = (Group* g) {
	no_of_members = g->GetNoOfMembers();
	for (int i = 0; i < no_of_members; i++) {
		group_member[i] = g->GetMemberListCopy()[i];
	}
	return *this;
}
void Group::AddContact(Contact* obj) {
	if (no_of_members >= 50) cout << "You have reached the limit of 50 contacts. Now, you can not add more contacts to this group.\n";
	//adding to contacts_list
	else {
		this->group_member[no_of_members].SetFirstName(obj->GetFirstName());
		this->group_member[no_of_members].SetLastName(obj->GetLastName());
		this->group_member[no_of_members].SetEmail(obj->GetEmail());
		this->group_member[no_of_members].SetMobileNumber(obj->GetMobileNumber());
		this->group_member[no_of_members].SetID(obj->GetID());
		this->group_member[no_of_members].SetAddress(obj->GetAddress());
		no_of_members++;
	}
}
int Group::GetNoOfMembers() {
	return no_of_members;
}
void Group::DisplayAllMembers() {
	if (no_of_members <= 0) {
		cout << RED << "The Group is Empty.\n";
	}
	else {
		for (int i = 0; i < no_of_members; i++) {
			cout << YELLOW;
			group_member[i].PrintContact();
		}
	}
}
//Delete Contact
void Group::RemoveContact(string id) {
	//finding index of required contact
	int index = -1;
	for (int i = 0; i < no_of_members; i++) {
		if (id == group_member[i].GetID()) {
			index = i;
			break;
		}
	}
	//removing here
	if (index != -1) {
		for (int i = index; i < (no_of_members - 1); i++) {
			group_member[i] = group_member[i + 1].CopyContact();
		}
		no_of_members--;
		cout << BLUE << "Removed from " << group_name << endl;
	}
	else cout << RED << "No Matches Found in " << group_name << "...\n";
}
//Load from File Function
void Group::LoadFromFile()
{
	/*
	*	Read contacts back from file in the same format
	*	Read the contacts_count, and run a loop for this contacts_count and read the
	*	contacts in the same format as you stored
	*	Add them to contact book (this.AddContact function can be used)
	*	Finally, close the file
	*/
	ifstream obj("Groups.txt");
	if (!obj)
	{
		cout << "Error opening file: " << "Groups.txt" << endl;
		return;
	}
	int count;
	obj >> count;
	obj.ignore();
	for (int i = 0; i < count; i++)
	{
		string identity, first_name, last_name, mobile_number, email_address, day, month, year;
		getline(obj, identity, ',');
		getline(obj, first_name, ',');
		getline(obj, last_name, ',');
		getline(obj, mobile_number, ',');
		getline(obj, email_address);
		getline(obj, day);
		getline(obj, month);
		getline(obj, year);
		Date d;
		d.day = day;
		d.month = month;
		d.year = year;
		string house1, street1, city1, country1;
		getline(obj, house1, ',');
		getline(obj, street1, ',');
		getline(obj, city1, ',');
		getline(obj, country1);
		Address* address1 = new Address(house1, street1, city1, country1);
		Contact* C = new Contact(first_name, last_name, mobile_number, email_address, address1, identity,d);
		AddContact(C);
	}
	obj.close();
}

void Group::SaveToFile(string file_name)
{
	/*
	*	In this function you will store all the contacts to a file
	*	On first line store contacts_count
	*	On next lines store contacts in the following format:
	*   2 lines for each contact
	*   On oneline write contact attributes(except address) in comma separated format. On second line
	*	store address atributes in the same format
	*	first_name,last_name,mobile_number,email_address
	*	house,street,city,country
	*	Close the file
	*/
	ofstream obj(file_name);
	obj << no_of_members << endl;
	for (int i = 0; i < no_of_members; i++) {
		//line 1
		obj << group_member[i].GetID() << "," << group_member[i].GetFirstName() << "," << group_member[i].GetLastName() << "," << group_member[i].GetMobileNumber() << "," << group_member[i].GetEmail() << endl;
		//line 2
		obj << group_member[i].GetAddress()->GetHouse() << "," << group_member[i].GetAddress()->GetStreet() << "," << group_member[i].GetAddress()->GetCity() << "," << group_member[i].GetAddress()->GetCountry() << endl;
	}
	obj.close();
}