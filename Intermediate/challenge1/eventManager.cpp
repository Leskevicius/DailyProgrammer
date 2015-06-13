/*
Rokas Leskevicius
5/27/15
Challenge 1 [INTERMEDIATE] event manager - from reddit.com/r/dailyprogrammer
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "encrypt.h"

using namespace std;

class event {
	friend class eventManager;
private:
	string name, description;
	int hour;
public:
	event(string name, string description, int hour);
	event(string name);
	friend bool operator< (const event &a, const event &b) {
		return a.hour < b.hour;
	}
	friend bool operator== (const event &a, const event &b) {
		return a.name == b.name;
	}
	friend ostream &operator<< (ostream &out, const event &e) {
		out << "\nName: " << e.name;
		out << "\nDescription: " << e.description;
		out << "\nHour: " << e.hour;
		return out;
	}
};

class eventManager {
private:
	int size;
	vector<event> eventList;
	void save();
	void load();
public:
	eventManager();
	void addEvent();
	void deleteEvent();
	void printEvents();
	void editEvent();
	void editMenu(vector<event>::iterator it);
	void menu();
};

eventManager::eventManager() {
	load();

}

void eventManager::addEvent() {
	string n, d;
	int h;
	
	cout << "\nWhat is the name of the event?" << endl;
	cin.ignore();
	getline(cin, n);
	cout << "\nWhat is the description of event '" << n << "'?" << endl;
	getline(cin, d);
	cout << "\nAt what hour will this event take place? (use military time)" << endl;
	cin >> h;
	event e(n,d,h);
	eventList.push_back(e);
	size++;
	sort(eventList.begin(), eventList.end());
}

void eventManager::deleteEvent() {
	string name;
	cout << "\nPlease enter the name of event to be deleted: " << endl;
	cin.ignore();
	getline(cin, name);
	
	event temp(name);
	vector<event>::iterator it = find(eventList.begin(),eventList.end(),temp);
	if (it == eventList.end()) {
		cout << "\nCould not find the event." << endl;
	} else {
		eventList.erase(it);
		size--;
		cout << "\nEvent has been deleted" << endl;
	}
}

void eventManager::printEvents() {
	if (size == 0) {
		cout << "\nThere are no entries." << endl;
	} else {
		for (int i = 0; i < size; i++) {
			cout << eventList[i] << endl;
		}
	}
}

void eventManager::editEvent() {
	string name;
	cout << "\nPlease enter the name of event to be edited: " << endl;
	cin.ignore();
	getline(cin, name);
	
	event temp(name);
	vector<event>::iterator it = find(eventList.begin(),eventList.end(),temp);
	if (it == eventList.end()) {
		cout << "\nCould not find the event." << endl;
	} else {
		editMenu(it);
	}

}

void eventManager::editMenu(vector<event>::iterator it) {
	int choice;
	
	while (true) {
		cout << "\nEditor Menu:\n1. Edit name\n2. Edit description\n3. Edit hour\n4. Done" << endl;
		cin >> choice;
		while (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nPlease choose from options 1 through 4." << endl;
			cin >> choice;
		}

		string name,desc;
		int hour;

	
		switch(choice) {
			case 1 : {
				cout << "\nEnter the new name: " << endl;
				cin.ignore();
				getline(cin, name);
				it->name = name;
				break;
			}
			case 2 : {
				cout << "\nEnter the new description: " << endl;
				cin.ignore();
				getline(cin, desc);
				it->description = desc;
				break;
			}
			case 3 : {
				cout << "\nEnter the new hour: " << endl;
				cin.ignore();
				cin >> hour;
				while (!cin) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nPlease enter time in military format." << endl;
					cin >> hour;
				}
				it->hour = hour;
				break;
			}
			case 4 : {
				return;
			}
			default : {
				cout << "\nPlease choose from options 1 through 4." << endl;
			}
		}
	}
}

void eventManager::menu() {
	int choice;
	cout << "\nMain Menu:\n1. Add an event\n2. Delete an event\n3. Edit events\n4. Print events\n5. Exit" << endl;
	cin >> choice;

	while (!cin) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nPlease choose from options 1 through 5." << endl;
		cin >> choice;
	}

	switch(choice) {
		case 1 : {
			addEvent();
			menu();
			return;
		}
		case 2 : {
			deleteEvent();
			menu();
			return;
		}
		case 3 : {
			editEvent();
			menu();
			return;
		}
		case 4 : {
			printEvents();
			menu();
			return;
		}
		case 5 : {
			save();
			return;
		}
		default : {
			cout << "\nInvalid choice: Please choose between 1-5." << endl;
			menu();
			return;
		}
	}
}

void eventManager::save() {
	ofstream datafile ("data.txt");
	datafile << size << '\n';
	for (int i = 0; i < size; i++) {
		datafile << eventList[i].name << '\n';
		datafile << eventList[i].description << '\n';
		datafile << eventList[i].hour << '\n';
	}
	datafile.close();
}

void eventManager::load() {
	ifstream datafile ("data.txt");

	if (datafile.peek() == ifstream::traits_type::eof()) {
		cout << "This is the first time running this program." << endl;
		size = 0;
		return;
	}

	string name, desc;
	int hour;

	if (size == 0) {
		cout << "Nothing to load." << endl;
		return;
	}

	for (int i = 0; i < size; i++) {
		datafile >> name;
		datafile >>  desc;
		datafile >> hour;
		event temp(name,desc,hour);
		eventList.push_back(temp);
	}
	datafile.close();
}

//***********************************************************************************************

event::event(string name, string description, int hour) {
	this->name = name;
	this->description = description;
	this->hour = hour;
}

event::event(string name) {
	this->name = name;
	this->description = "";
	this->hour = 0;
}

//***********************************************************************************************

int main() {
	eventManager e1;
	e1.menu();
	return 0;
}