#include <iostream>
#include <string>

using namespace std;

static void encrypt(string &phrase, string key_code) {
	int length = phrase.length();
	int key_length = key_code.length();
	for (int i = 0, j = 0; i < length; i++, j++) {
		if (j >= key_length) {
			j = 0;
		}
		phrase[i] = phrase[i] + key_code[j] - '0' - '0';
	}
}

static void decrypt(string &phrase, string key_code) {
	int length = phrase.length();
	int key_length = key_code.length();
	for (int i = 0, j = 0; i < length; i++, j++) {
		if (j >= key_length) {
			j = 0;
		}
		phrase[i] = phrase[i] - key_code[j] + '0' + '0';
	}
}

/*
int main() {
	string phrase, key_code;

	cout << "Phrase to be encrypted: ";
	getline(cin, phrase);
	cout << "Key code: ";
	getline(cin, key_code);

	cout << "Encrypting..." << endl;
	encrypt(phrase, key_code);
	cout << phrase << endl;
	cout << "Decrypting..." << endl;
	decrypt(phrase, key_code);
	cout << phrase << endl;

	return 0;
}
*/