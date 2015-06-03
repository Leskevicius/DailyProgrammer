/*
Rokas Leskevicius
5/27/2015
Challenge 1 [EASY] - from reddit.com/r/dailyprogrammer
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


//add an entry to file data.txt
void addEntry() { 
	//output stream that will save text to data.txt file
	//ios::app is used so the file is opened in append mode
	ofstream datafile ("data.txt", ios::app);

	string entry;
	cout << "\nPlease enter your first and last name, age, and reddit username: " << endl;
	
	//ignore so we get rid of '\n' from stream due to previous line
	cin.ignore();
	getline(cin, entry);
	datafile << entry << '\n';
	datafile.close();
}

//print all the data in data.txt file
void printData() {
	//input stream so we can read all the entries in data.txt file
	ifstream datafile ("data.txt");

	string name, lastname, age, username;
	while (datafile >> name >> lastname >> age >> username) {
		if (name == "0") {
			break;
		}
		else {
			cout << "\nName: " << name << "\nLast Name: " << lastname << "\nAge: " << age << "\nUser Name: " << username << endl;
		}
	}
	datafile.close();
}

void menu() {
	int choice;

	cout << "\nMain Menu\n1. Add an entry\n2. Print data\n3. Close" << endl;
	cin >> choice;
	switch(choice) {
		case 1: {
			addEntry();
			menu();
			break;
		}
		case 2: {
			printData();
			menu();
			break;
		}
		case 3: {
			break;
		}
		default: {
			cout << "Please choose options 1-3." << endl;
			menu();
		}
	}
}


int main() {
	menu();
	return 0;
}