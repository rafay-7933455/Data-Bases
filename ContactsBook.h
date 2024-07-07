#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Group.h"
#include <Windows.h>
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
class ContactsBook {
private:
	Contact* contacts_list; // array of contacts
	int size_of_contacts;   // storage limit
	int contacts_count;     // total contacts currently stored, next contact will be 
	// stored at this count plus 1 index
	Group* group_list;// = new Group[100];
	int size_of_groups;
	int groups_count;
	// history
	string* history;
	int history_size;
	int history_count;
public:
	ContactsBook();
	ContactsBook(int size_of_list1);

	~ContactsBook();

	int FindContactIndex(string id);
	int FindGroupIndex(string name);

	void ViewHistory();
	void AddToHistory(string str);
	void SaveHistory();
	void LoadHistory();
	void ClearHistory();

	void FrequentlyViewed();

	void SaveGroups();
	void LoadGroups();

	void DisplayGroupNames();

	Group* GetGroupList();
	Contact* GetContactList();

	void SetSizeOfList(int size);

	bool AddContact(Contact& contact);
	void DeleteContact();
	int TotalContacts();

	void CreateGroup(string name);
	void DeleteGroup(string name);
	void DisplayMembersOFaGroup();
	int TotalGroups();

	void SearchContact(string str);

	void PrintContactsSorted(string choice); // Only two choices first_name or last_name
	void PrintContactsUnsorted();
	void MergeDuplicates(); // Implement this function that finds and merges all the duplicates
	// Duplicate means exact equal, this means if

/*
*  This function loads contacts from the given file (see details in ContactsBook.cpp)
*/
	void LoadFromFile(string file_name);
	void SaveToFile(string file_name);

private:
	bool Full();
	void ResizeList();
	void SortContactsSorted(Contact* contacts_list, string choice);
};
