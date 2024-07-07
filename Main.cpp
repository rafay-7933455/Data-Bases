/*
*   Include all the needed headers here to run the scenarios
*/
#include<iostream>
#include<string>
#include"ContactsBook.h"
#include<Windows.h>
//escape sequences for colors
#define RED         "\033[31m"     // Red text
#define GREEN       "\033[32m"     // Green text
#define YELLOW      "\033[33m"     // Yellow text
#define BLUE        "\033[34m"     // Blue text
#define MAGENTA     "\033[35m"     // Magenta text
#define CYAN        "\033[36m"     // Cyan text
#define WHITE		"\033[37m"     // White text
#define BOLDCYAN    "\033[1m\033[500m"
using namespace std;
//returns nameless temporary object of type Address
Address AddressReturner() {
	string house, street, city, country;
	cout << BLUE;
	cout << "Enter House No.: ";
	cin >> house;
	cout << "Enter Street No.: ";
	cin >> street;
	cout << "Enter City: ";
	cin >> city;
	cout << "Enter Country: ";
	cin >> country;

	return Address(house, street, city, country);
}

int main() {
	//--
	//--
	ContactsBook Book;
	int choice = -1;
	string choice_of_sorting = "";
	//pointers were creating ambiguity so initializing pointers to nullptr
	Contact* C = nullptr;  
	Address* A = nullptr;
	Address* A1 = nullptr;
	Contact* C1 = nullptr;
	int contactsNo = -1;
	//Loading Previously Saved Groups
	Book.LoadGroups();
	//Loading Previously Saved Contacts
	Book.LoadFromFile("Text.txt");
	//Loading Search History
	Book.LoadHistory();
	while (choice) {
		string line1 = "00. Exit\n01. Add New Contact\n02. Merge Duplicates\n03. Total Groups in the ContactsBook\n04. Print Contacts Sorted (input choice, (first or First) or (last or Last)\n05. Print Contacts\n06. Advance Search contacts\n07. Display Count of Contacts\n08. Add Contact To A Group\n09. Delete A Contact\n10. Remove Contact From A Group\n11. Search History\n12. 5 Most Frequently Viewed Contacts\n13. Create A Group\n14. Delete A Group\n15. View List Of Names of All Groups\n16. View Members of a Group\n17. Clear Search History\n18. Update a Contact\n19. View a Contact";
		cout << GREEN << line1 << endl;
		string line2 = "";
		cout << BLUE << "Enter choice here: " << WHITE;
		cin >> choice;
		//check for valid and invalid choices
		while ((choice < 0) || (choice > 19)) {
			cout << RED << "Invalid Choice!!! Error!!!\n";
			cout << RED << "Enter choice again: ";
			cin >> choice;
		}
		system("cls");
		switch (choice) {
		case 0: {
			cout << MAGENTA << "Exited from the Contacts Book\n" << WHITE;
			break;
		}
		case 1:
		{
			cout << BLUE;
			cout << "Enter the number of contacts that should be added in the Contacts Book: ";
			cin >> contactsNo;
			while (contactsNo < 1) {
				cout << "Invalid Value...Please try again!!!\nEnter the number of contacts that should be added in the Contacts Book (atleast 2): ";
				cin >> contactsNo;
			}
			A = new Address[contactsNo];
			C = new Contact[contactsNo];
			cout << GREEN;
			for (int i = 0; i < contactsNo; i++) {
				// Initialize each element of C and A here
				cout << "Enter details for contact " << i + 1 << ":" << endl;
				string f, l, m, e, id;
				cout << "Enter first name: ";
				cin >> f;
				cout << "Enter last name: ";
				cin >> l;
				cout << "Enter Email Address: ";
				cin >> e;
				cout << "Enter Mobile No.: ";
				cin >> m;
				cout << "Enter an id for the contact: ";
				cin >> id;
				Date d;
				string d1, m1, y1;
				cout << "Enter birth-day: ";
				cin >> d1;
				cout << "Enter birth-month: ";
				cin >> m1;
				cout << "Enter birth-year: ";
				cin >> y1;
				d.day = d1;
				d.month = m1;
				d.year = y1;
				cout << "Enter Address: \n";
				A[i] = AddressReturner();
				C[i].SetContact(f, l, m, e, &A[i], id, d);
			}
			// Add contacts to the ContactsBook after initializing them
			for (int i = 0; i < contactsNo; i++) {
				Book.AddContact(C[i]);
			}
			Book.SaveToFile("Text.txt");
			break;
		}
		case 2:
			//merge duplicate contacts
			Book.MergeDuplicates();
			cout << YELLOW;
			cout << "\nSuccessFully Merged the Duplicates...\n";
			Book.SaveToFile("Text.txt");
			break;
		case 3: {
			//display no of groups
			cout << BLUE;
			cout << "Total Groups Present in this contactsBook: " << WHITE << Book.TotalGroups() << endl;
			break;
		}
		case 4: {
			//displaying contacts order with respect to first name or last name depending upon the choice
			cout << YELLOW;
			cout << "Enter your choice: ";
			cout << WHITE;
			cin >> choice_of_sorting;
			if (choice_of_sorting == "0") {
				cout << RED << "Returning to the Main Menu\n";
				break;
			}
			cout << YELLOW;
			cout << "\nSorted: \n\n";
			Book.PrintContactsSorted(choice_of_sorting);
			break;
		}
		case 5: {
			//displaying contacts in the order they were added to contacts book
			cout << BLUE << "\nUnsorted: \n\n" << YELLOW;
			Book.PrintContactsUnsorted();
			break;
		}
		case 6:{
			//advance search
			cout << GREEN;
			line2 = "Enter the detail about the contact to be searched: ";
			string mystr = "";
			cout << line2 << WHITE;
			cin >> mystr;
			cout << BLUE;
			cout << "Details: \n";
			Book.SearchContact(mystr);
			break;
		}
		case 7: {
			//display count of contacts
			cout << BLUE;
			cout << "No. of Contacts in Contacts Book: " << Book.TotalContacts() << endl;
			break;
		}
		case 8: {
			//add contact to a group
			cout << GREEN;
			cout << "Enter the id of contact: ";
			string id = "";
			cin >> id;
			//find index
			int c_index = Book.FindContactIndex(id);
			if (c_index != -1) {
				cout << GREEN << "Enter Group Name: ";
				string g_name = "";
				cin >> g_name;
				int g_index = Book.FindGroupIndex(g_name);
				if (g_index != -1) {
					Book.GetGroupList()[g_index].AddContact(&Book.GetContactList()[c_index]);
					cout << YELLOW << "Successfully Added the Contact to the Group " << Book.GetGroupList()[g_index].GetGroupName() << endl;
					Book.SaveGroups();
				}
				else cout << RED << "Group not found...\n";
			}
			else cout << RED << "Contact Not found...\n";
			break;
		}
		case 9: {
			//delete a contact
			Book.DeleteContact();
			Book.SaveToFile("Text.txt");
			Book.SaveGroups();
			break;
		}
		case 10: {
			//remove contact from a group
			string g_name = "";
			cout << GREEN << "Enter the name of a the Group from which you want to delete a contact: ";
			cin >> g_name;
			int index = Book.FindGroupIndex(g_name);
			if (index == -1) {
				cout << RED << "No such group exists...\nReturning Back to Main Menu\n";
			}
			else {
				string id = "";
				cout << RED << "Enter the ID of the contact to be removed from the group: ";
				cin >> id;
				Book.GetGroupList()[index].RemoveContact(id);
				Book.SaveGroups();
			}
			break;
		}
		case 11: {
			// View Search History
			Book.ViewHistory();
			break;
		}
		case 12: {
			// 5 Most Frequently Viewed Contacts
			Book.FrequentlyViewed();
			break;
		}
		case 13: {
			//create a group
			string group_name = "";
			cout << GREEN << "Enter Group Name: ";
			cin >> group_name;
			if (group_name == "0") {
				cout << RED << "Returning to the Main Menu\n";
				break;
			}
			Book.CreateGroup(group_name);
			cout << MAGENTA << "Successfully Created the Group \"" << group_name << "\"\n";
			Book.SaveGroups();
			break;
		}
		case 14: {
			//delete a group
			string g_name = "";
			cout << GREEN << "Enter the name of the group you want to delete: ";
			cin >> g_name;
			if (g_name == "0") {
				cout << RED << "Returning to the Main Menu\n";
				break;
			}
			Book.DeleteGroup(g_name);
			Book.SaveGroups();
			break;
		}
		case 15: {
			//display names of all present groups
			cout << BLUE;
			Book.DisplayGroupNames();
			break;
		}
		case 16: {
			//display members of a specific group
			cout << BLUE;
			Book.DisplayMembersOFaGroup();
			break;
		}
		case 17: {
			Book.ClearHistory();
			break;
		}
		case 18: {
			//update a contact
			string id = "";
			cout << BLUE;
			cout << "Enter the ID of the contact You want to update the details of which: ";
			cin >> id;
			int index = Book.FindContactIndex(id);
			if (index != -1) {
				cout << GREEN;
				cout << "Enter details for contact: " << endl;
				string f, l, m, e, new_id;
				cout << "Enter first name: ";
				cin >> f;
				cout << "Enter last name: ";
				cin >> l;
				cout << "Enter Email Address: ";
				cin >> e;
				cout << "Enter Mobile No.: ";
				cin >> m;
				cout << "Enter an id for the contact: ";
				cin >> new_id;
				Date d;
				string d1, m1, y1;
				cout << "Enter birth-day: ";
				cin >> d1;
				cout << "Enter birth-month: ";
				cin >> m1;
				cout << "Enter birth-year: ";
				cin >> y1;
				d.day = d1;
				d.month = m1;
				d.year = y1;
				cout << "Enter Address: \n";
				Address B = AddressReturner();
				Book.GetContactList()[index].SetContact(f, l, m, e, &B, new_id,d);
				Book.SaveToFile("Text.txt");
			}
			else {
				cout << RED << "Contact Not Found.\n";
			}
			break;
		}
		case 19: {
			//View a contact
			string id = "";
			cout << BLUE;
			cout << "Enter the id of the contact you want to view: ";
			cin >> id;
			int index = Book.FindContactIndex(id);
			if (index != -1) {
				Book.GetContactList()[index].PrintContact();
				Book.GetContactList()[index].IncreaseSearchCount();
			}
			else {
				cout << RED << "Contact Not Found.\n";
			}
			break;
		}
		default: {
			//give error for invalid choixe
			cout << RED << "\nError: Invalid Choice!!!\nReturning Back to Main Menu\n";
			break;
		}
		}
		if (choice == 0) {
			break;
		}
		cout << WHITE;
		system("pause");
		system("cls");
	}



	// Clean up dynamically allocated memory
	delete[] C;
	delete[] A;
	delete[] A1;
	delete[] C1;

	return 0;
}





