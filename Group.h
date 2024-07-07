#pragma once
#include"Contact.h"
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

class Group {
	string group_name;
	Contact* group_member;
	int no_of_members;
public:
	Group();
	void SetGroupName(string n);
	Contact* GetMemberListCopy();
	string GetGroupName();
	Group operator = (Group* g);
	void AddContact(Contact* obj);
	int GetNoOfMembers();
	void DisplayAllMembers();
	//Delete Contact
	void RemoveContact(string id);
	//Load from File Function
	void LoadFromFile();

	void SaveToFile(string file_name);
};