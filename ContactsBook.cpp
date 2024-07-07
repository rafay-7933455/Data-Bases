#include"ContactsBook.h"

ContactsBook::ContactsBook() {
	contacts_list = 0;
	size_of_contacts = contacts_count = 0;
	group_list = 0;
	size_of_groups = groups_count = 0;
	history = nullptr;
	history_size = history_count =  0;
}

ContactsBook::ContactsBook(int size_of_list1) {
	/*
	*	Initialize the contacts_list array, also initialize the size and count members accordingly
	*/
	size_of_contacts = size_of_list1;
	contacts_list = new Contact[size_of_contacts];
	contacts_count = 0;
	group_list = 0;
	size_of_groups = groups_count = 0;
	history = nullptr;
	history_size = history_count = 0;
}

ContactsBook::~ContactsBook() {
	delete[] contacts_list;
	delete[] group_list;
}

void ContactsBook::SetSizeOfList(int size) {
	size_of_contacts = size;
	contacts_list = new Contact[size_of_contacts];
}

bool ContactsBook::AddContact(Contact& C)
{
	/*
		- Check if the list is Full, if it is Full call the resize function
		- If list is not Full add the contact to the end of the array
		- (end means the place where last contact was inserted)
		- At start it will be 0th index as no contact has been inserted before so
		- count is zero (contacts_count member)
		- Increment the count
		- As inserted successFully, return 1
	*/
	//check
	if (Full()) ResizeList();
	//adding to contacts_list
	contacts_list[contacts_count] = C.CopyContact();
	//inserted successFully
	contacts_count++;
	return 1;
}

void ContactsBook::DeleteContact() {
	string id = "";
	cout << "Enter ID of the Contact: ";
	cin >> id;
	//find index
	int index = -1;
	for (int i = 0; i < contacts_count; i++) {
		if (id == contacts_list[i].GetID()) {
			index = i;
			break;
		}
	}
	//deleting
	if (index != -1) {
		for (int i = index; i < (contacts_count - 1); i++) {
			contacts_list[i] = contacts_list[i + 1].CopyContact();
		}
		contacts_count--;
		cout << "Deleted from Contacts Book\n";
		//delete from all groups
		for (int i = 0; i < groups_count; i++) {
			group_list[i].RemoveContact(id);
		}
	}
	else cout << "Contact not found...\n";
}

int ContactsBook::FindContactIndex(string id) {
	int index = -1;
	for (int i = 0; i < contacts_count; i++) {
		if (id == contacts_list[i].GetID()) {
			index = i;
			break;
		}
	}
	return index;
}

void ContactsBook::FrequentlyViewed() {
	Contact* my_list = new Contact[contacts_count];
	for (int i = 0; i < contacts_count; i++) {
		my_list[i] = contacts_list[i];
	}
	//Bubble sort
	for (int i = 0; i < contacts_count - 1; i++) {
		for (int j = 0; j < contacts_count - i - 1; j++) {
			if (my_list[j].GetSearchCount() < my_list[j + 1].GetSearchCount()) {
				Contact temp = my_list[j];
				my_list[j] = my_list[j + 1];
				my_list[j + 1] = temp;
			}
		}
	}
	int num = (contacts_count < 5) ? contacts_count : 5;
	// Printing the most viewed 5 contacts
	cout << BLUE;
	cout << "Most Viewed Contacts:\n";
	cout<<YELLOW;
	for (int i = (num-1); i >=0;i--){
		my_list[i].PrintContact();
	}

	delete[] my_list;
}


int ContactsBook::FindGroupIndex(string name) {
	int index = -1;
	for (int i = 0; i < groups_count; i++) {
		if (name == group_list[i].GetGroupName()) {
			index = i;
			break;
		}
	}
	return index;
}

void ContactsBook::CreateGroup(string name) {
	if (group_list == nullptr) {
		group_list = new Group;
		group_list->SetGroupName(name);
	}
	else if(groups_count>=size_of_groups) {
		size_of_groups = (size_of_groups > 0) ? (size_of_groups * 4) : 4;
		Group* new_list = new Group[size_of_groups];
		if (groups_count > 0) {
			for (int i = 0; i < groups_count; i++) {
				new_list[i] = group_list[i];
			}
			new_list[groups_count].SetGroupName(name);
			delete[] group_list;
			group_list = new_list;
		}
	}
	else if (groups_count < size_of_groups) {
		group_list[groups_count].SetGroupName(name);
	}
	groups_count++;
}

void ContactsBook::DeleteGroup(string name) {
	int index = -1;
	for (int i = 0; i < contacts_count; i++) {
		if (name == group_list[i].GetGroupName()) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		for (int i = index; i < (groups_count - 1); i++) {
			group_list[i] = group_list[i + 1];
		}
		groups_count--;
		cout << MAGENTA << "Successfully deleted the Group \"" << name << "\"\n";
	}
	else cout << RED << "Group not found...\nReturning Back to Main Menu\n";
}

void ContactsBook::DisplayMembersOFaGroup() {
	string group_name = "";
	cout << "Enter the Name of the Group you want to see members of: ";
	cin >> group_name;
	int index = FindGroupIndex(group_name);
	if (index != -1) group_list[index].DisplayAllMembers();
	else cout << RED << "No such group exists...\n";
}
//19
void ContactsBook::SaveGroups() {
	ofstream Cout("Groups.txt");
	Cout << groups_count << endl;
	for (int i = 0; i < groups_count; i++) {
		Cout << group_list[i].GetGroupName() << " " << group_list[i].GetNoOfMembers() << endl;
		for (int j = 0; j < group_list[i].GetNoOfMembers(); j++) {
			//Cout << group_list[i].GetMemberListCopy()[i];
			//line 1
			Cout << group_list[i].GetMemberListCopy()[j].GetID() << " " << group_list[i].GetMemberListCopy()[j].GetFirstName() << " " << group_list[i].GetMemberListCopy()[j].GetLastName() << " " << group_list[i].GetMemberListCopy()[j].GetMobileNumber() << " " << group_list[i].GetMemberListCopy()[j].GetEmail() << " " << group_list[i].GetMemberListCopy()[j].GetAddress()->GetHouse() << " " << group_list[i].GetMemberListCopy()[j].GetAddress()->GetStreet() << " " << group_list[i].GetMemberListCopy()[j].GetAddress()->GetCity() << " " << group_list[i].GetMemberListCopy()[j].GetAddress()->GetCountry() << endl;
		}
	}
	Cout.close();
}
//19
void ContactsBook::LoadGroups() {
	ifstream Cin("Groups.txt");
	Cin >> groups_count;
	group_list = new Group[100];
	for (int i = 0; i < groups_count; i++) {
		string g_name;
		int noOfMembers;
		Cin >> g_name >> noOfMembers;
		string id, f_name, l_name, mobile, email, h, s, ci, co;
		Date d;
		for (int j = 0; j < noOfMembers; j++) {
			//line 1
			Cin >> id >> f_name >> l_name >> mobile >> email >> h >> s >> ci >> co >> d.day >> d.month >> d.year;
		}
		Address* A = new Address(h,s,ci,co);
		Contact* C = new Contact(f_name, l_name, mobile, email, A, id, d);
		group_list[i].AddContact(C);
		group_list[i].SetGroupName(g_name);
	}
	Cin.close();
}

void ContactsBook::DisplayGroupNames() {
	if (group_list != nullptr) {
		cout << "Group Names: \n";
		cout << YELLOW;
		for (int i = 0; i < groups_count; i++) {
			cout << group_list[i].GetGroupName() << endl;
		}
	}
	else cout << MAGENTA << "There are no groups present in the ContactsBook\n";
}

int ContactsBook::TotalContacts()
{
	/*
	*	Return the total contacts currently stored
	*/
	return contacts_count;
	/*
	*	Remove this return -1; before writing your code
	*/
	//return -1;
}

bool ContactsBook::Full()
{
	return (contacts_count >= size_of_contacts);
}

void ContactsBook::ResizeList()
{
	/*
	*	Here you will resize the contact list, see example code given in lab manual to see how to resize arrays
	*	You will allocate a temporary new array of double the current size and copy the contacts from
	*       previous array to this array one by one, get the copy of each contact using CopyContact
	*       function of Contact class
	*	Delete the previous array
	*	Assign the new temporary array to the contacts_list pointer
	*	Updated the this->size_of_contacts with new size
	*/
	size_of_contacts = (size_of_contacts < 1) ? 4 : (size_of_contacts * 2);
	Contact* temp = new Contact[size_of_contacts];
	if (contacts_list != nullptr) {
		for (int i = 0; i < (contacts_count); i++) {
			temp[i] = contacts_list[i].CopyContact();//assigning deep copy of contacts_list array
		}
	}
	delete[] contacts_list;
	contacts_list = temp;
}

//Print Sorted Contacts Fun ()
void ContactsBook::PrintContactsSorted(string choice)
{
	//*	Create a copy of this->contacts_list array here (do it by creating a new function that returns copy)
	//*	Call the sort function SortContactsSorted to sort the newly created copy
	//*	This copy is created to avoid changing the original insertion order of contact list
	//*	Then print the contacts in following format:
	//*	[First Name] [Last Name] [Mobile] [Email]
	//*	Call the address print function to print address on next line
	if ((choice == "first") || (choice == "last") || (choice == "First") || (choice == "Last")) {
		Contact* sorted_list = new Contact[contacts_count];
		for (int i = 0; i < contacts_count; i++)
		{
			sorted_list[i] = contacts_list[i].CopyContact(); // Deep copy of the Contact object
		}
		SortContactsSorted(sorted_list, choice);
		for (int i = 0; i < contacts_count; i++)
		{
			sorted_list[i].PrintContact();
		}
		delete[] sorted_list;
	}
	else cout << "Invalid choice!! Returning to Main Menu\n";
}

void ContactsBook::PrintContactsUnsorted() {
	if (contacts_list != nullptr) {
		for (int i = 0; i < (contacts_count); i++) {
			contacts_list[i].PrintContact();
		}
	}
	else cout << "Contacts Book is empty...\nReturning back to Main Menu\n";
}

//fun() to sort a contacts list
void ContactsBook::SortContactsSorted(Contact* contacts_list, string choice)
{
	int n = contacts_count;
	for (int i = 0; i < n - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if ((choice == "first") || (choice == "First"))
			{
				if (contacts_list[j].GetFirstName() < contacts_list[minIndex].GetFirstName())
				{
					minIndex = j;
				}
			}
			else if ((choice == "last") || (choice == "Last"))
			{
				if (contacts_list[j].GetLastName() < contacts_list[minIndex].GetLastName())
				{
					minIndex = j;
				}
			}
		}
		if (minIndex != i)
		{
			// Swapping of Contacts
			Contact temp = contacts_list[i];
			contacts_list[i] = contacts_list[minIndex];
			contacts_list[minIndex] = temp;
		}
	}
}

void ContactsBook::MergeDuplicates() {
	// Implement this function that finds and merges all the duplicates
	// Duplicate means exact equal
	// If there are three copies of a Contact, then only one should remain
	// For example: If total contact are 10, and 2 contacts are same, after removing duplicates
	// 9 contacts will be left; and the this->contacts_count of list will 9
	// At the end display contacts merged, and count of merged contacts
	for (int x = 0; x < contacts_count; x++)
	{
		for (int y = x + 1; y < contacts_count; y++)
		{
			if (contacts_list[x] == contacts_list[y])
			{
				contacts_list[y] = contacts_list[contacts_count - 1];
				contacts_count--;
				y--;
			}
		}
	}
}

void ContactsBook::SaveHistory() {
	ofstream Writer("Ha.txt");
	Writer << history_count << endl;
	for (int i = 0; i < (history_count); i++) {
		Writer << history[i] << " ";
	}
	Writer.close();
}

void ContactsBook::ClearHistory() {
	delete[] history;
	history = nullptr;
	ofstream Eraser("Ha.txt", ios::trunc);
	Eraser.close();
	cout << YELLOW << "Successfully Cleared Your Search History\n";
}

void ContactsBook::LoadHistory() {
	ifstream Reader("Ha.txt");
	Reader >> history_count;
	for (int i = 0; i < (history_count); i++) {
		string str;
		Reader >> str;
		if (history_count >= history_size) {
			history_size = (history_size <= 0) ? (4) : (history_size * 4);
			string* new_list = new string[history_size];
			delete[] history;
			history = new_list;
		}
		history[i] = str;
	}
}

void ContactsBook::ViewHistory() {
	if (history != nullptr) {
		cout << BLUE << "Order ( Most Recent First )\n";
		for (int i = (history_count - 1); i >= 0; i--) {
			cout << YELLOW << "-> " << history[i] << endl;
		}
	}
	else {
		cout << RED << "Your History is Empty\n";
	}
}

void ContactsBook::AddToHistory(string str) {
	if (history_count >= history_size) {
		history_size = (history_size <= 0) ? (4) : (history_size * 4);
		string* new_list = new string[history_size];
		if (history != nullptr) {
			for (int i = 0; i < (history_count - 1); i++) {
				new_list[i] = history[i];
			}
		}
		delete[] history;
		history = new_list;
	}
	history[history_count] = str;
	history_count++;
}

void ContactsBook::SearchContact(string str)
{
	//Adding searched string to history array and resizing history list if needed
	AddToHistory(str);
	//Saving History for future use
	SaveHistory();
	//Final Advance search
	bool found = 0;//to check contact is found or not
	for (int i = 0; i < contacts_count; i++) {
		string contact = contacts_list[i].GetID() + contacts_list[i].GetFirstName() + contacts_list[i].GetFirstName() + contacts_list[i].GetMobileNumber() + contacts_list[i].GetEmail() + contacts_list[i].GetAddress()->GetHouse() + contacts_list[i].GetAddress()->GetStreet() + contacts_list[i].GetAddress()->GetCity() + contacts_list[i].GetAddress()->GetCountry();
		int index = 0;
		for (int j = 0; j < contact.length(); j++) {
			//loop to check whether every chrctr entered finds its match or not
			if (tolower(str[index]) == tolower(contact[j])) {
				index++;
			}
			if (index == str.length()) {
				cout << YELLOW;
				contacts_list[i].PrintContact();
				cout << endl;
				found = 1;
				break;//just to print one contact one time
			}
		}
		if((i==(contacts_count-1))&&(found==0)) cout << RED << "No Contact matches with the entered detail...\n";
	}
}
//Accessor for grouplist array
Group* ContactsBook::GetGroupList() {
	return group_list;
}
//Accessor for contactslist array
Contact* ContactsBook::GetContactList() {
	return contacts_list;
}
int ContactsBook::TotalGroups() {
	return groups_count;
}
//Load from File Function
void ContactsBook::LoadFromFile(string file_name)
{
	/*
	*	Read contacts back from file in the same format
	*	Read the contacts_count, and run a loop for this contacts_count and read the
	*	contacts in the same format as you stored
	*	Add them to contact book (this.AddContact function can be used)
	*	Finally, close the file
	*/
	ifstream obj(file_name);
	if (!obj)
	{
		cout << "Error opening file: " << file_name << endl;
		return;
	}
	int count;
	obj >> count;
	obj.ignore();
	for (int i = 0; i < count; i++)
	{
		string identity, first_name, last_name, mobile_number, email_address, day,month,year;
		getline(obj, identity, ',');
		getline(obj, first_name, ',');
		getline(obj, last_name, ',');
		getline(obj, mobile_number, ',');
		getline(obj, email_address);
		string house1, street1, city1, country1;
		getline(obj, house1, ',');
		getline(obj, street1, ',');
		getline(obj, city1, ',');
		getline(obj, country1);
		Date d;
		d.day = day;
		d.month = month;
		d.year = year;
		Address* address1 = new Address(house1, street1, city1, country1);
		Contact* C = new Contact(first_name, last_name, mobile_number, email_address, address1, identity, d);
		AddContact(*C);
	}
	obj.close();
}

void ContactsBook::SaveToFile(string file_name)
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
	obj << contacts_count << endl;
	for (int i = 0; i < contacts_count; i++) {
		//line 1
		obj << contacts_list[i].GetID() << "," << contacts_list[i].GetFirstName() << "," << contacts_list[i].GetLastName() << "," << contacts_list[i].GetMobileNumber() << "," << contacts_list[i].GetEmail() << endl;
		//line 2
		obj << contacts_list[i].GetAddress()->GetHouse() << "," << contacts_list[i].GetAddress()->GetStreet() << "," << contacts_list[i].GetAddress()->GetCity() << "," << contacts_list[i].GetAddress()->GetCountry() << endl;
	}
	obj.close();
}
/*
*   Include all the needed headers here to run the scenarios
*/
