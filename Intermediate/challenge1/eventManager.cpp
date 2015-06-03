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

using namespace std;

class event {
private:
	string name, description;
	int hour;
public:
	event(string name, string description, int hour);
	bool operator< (const event &b) const;
	friend bool operator== (const event &a, const event &b) {
		return a.hour == b.hour;
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
	vector<event> eventList;
	void save();
	void load();
public:
	eventManager();
	void addEvent();
	void deleteEvent();
	void printEvents();
	void editEvent();
	void menu();
};

eventManager::eventManager() {

}

void eventManager::addEvent() {
	string n, d;
	int h;
	
	cout << "\nWhat is the name of the event?" << endl;
	//cin.ignore();
	getline(cin, n);
	cout << "\nWhat is the description of event '" << n << "'?" << endl;
	//cin.ignore();
	getline(cin, d);
	cout << "\nAt what hour will this event take place? (use military time)" << endl;
	cin >> h;

	event e(n,d,h);
	eventList.push_back(e);

	sort(eventList.begin(), eventList.end());
}

void eventManager::deleteEvent() {
	int choice;
	string name;

	cout << "\nPrint events? (yes: 1, no: 0)" << endl;
	cin >> choice;
	if (choice) {
		printEvents();
	}

	cout << "\nPlease enter the name of event to be deleted: " << endl;
	cin.ignore();
	getline(cin, name);
	vector<event>::iterator it = find(eventList.begin(),eventList.end(),name);
	if (it == eventList.end()) {
		cout << "\nCould not find the event." << endl;
	} else {
		//eventList.erase(it);
		cout << "\nEvent has been deleted" << endl;
	}
}

void eventManager::printEvents() {
	int size = eventList.size();
	for (int i = 0; i < size; i++) {
		cout << eventList[i] << endl;
	}
}

void eventManager::editEvent() {

}

void eventManager::menu() {
	int choice;
	cout << "\nMain Menu:\n1. Add an event\n2. Delete an event\n3. Edit events\n4. Print events\n5. Exit" << endl;
	cin >> choice;

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

}

void eventManager::load() {

}

//***********************************************************************************************

event::event(string name, string description, int hour) {
	this->name = name;
	this->description = description;
	this->hour = hour;
}

bool event::operator< (const event &b) const{
	return hour < b.hour;
}

//***********************************************************************************************

int main() {
	eventManager e1;
	e1.menu();
	return 0;
}