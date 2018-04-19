// main file
// gcc -std=c++11 main.cpp classes.cpp -o prog

#include "include/classes.hpp"

Commands hashit(std::string const& inString);

enum Commands {
	cd,
	ls,
	rm,
	mv,
	cp,
	touch,
	cat,
	su,
	ssh,
	logout,
	clear,
	error
};

int main() {
	string username;
	string password1;
	string password2;
	string input;
	bool playing = true;

	cout << "Welcome to the game etc...";

	cout << "\n\nNew account setup" << "\nPlease enter username: ";
	cin >> username;

	do {
		cout << "\nPlease enter password: ";
		cin >> password1;

		cout << "Please verify password: ";
		cin >> password2;

		if (password1 != password2) {
			cout << "\nPasswords do not match!";
		}
	} while (password1 != password2);


	Server* homeServer = new Server("Home");

	Directory* thisIsAPlaceHolder = new Directory();

	Player* player = new Player(username, password1, thisIsAPlaceHolder, homeServer);

	cin.ignore(INT_MAX, '\n');

	while (playing == true) {

		cout << "[" << player->getCurrentUsername() << "@" << player->getCurrentServerName() << " " << player->getCurrentDirectoryName() << "]" << player->getSuffix() << " ";
		getline(cin, input);

		vector <string> tokens;

		stringstream check(input);

		string buffer;


		while (getline(check, buffer, ' '))
		{
			tokens.push_back(buffer);
		}

		if (tokens.size() >= 1) {
			switch (hashit(tokens[0])) {
			case cd:
				//cout << tokens[1];
				break;

			case ls:

				break;

			case rm:

				break;

			case mv:

				break;

			case cp:

				break;

			case touch:

				break;

			case cat:

				break;

			case su:

				break;

			case ssh:

				break;

			case logout:

				break;

			case clear:
				cout << string(100, '\n');
				break;

			case error:
				cout << "Command not found.\n";
				break;
			}
		}
	}

	return 0;
}

Commands hashit(std::string const& inString) {
	if (inString == "cd") return cd;
	if (inString == "ls") return ls;
	if (inString == "rm") return rm;
	if (inString == "mv") return mv;
	if (inString == "cp") return cp;
	if (inString == "touch") return touch;
	if (inString == "cat") return cat;
	if (inString == "su") return su;
	if (inString == "ssh") return ssh;
	if (inString == "logout") return logout;
	if (inString == "clear") return clear;
	return error;
}
