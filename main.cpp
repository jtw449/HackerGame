// main file
// gcc -std=c++11 main.cpp classes.cpp -o prog

#include "include/classes.hpp"
#include <limits.h>

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

Commands hashit(const std::string &inString);

int main() {
	string username;
	string password1;
	string password2;
	string input;
	bool playing = true;

	std::cout << "Welcome to the game etc...";

	std::cout << "\n\nNew account setup" << "\nPlease enter username: ";
	std::cin >> username;

	do {
		std::cout << "\nPlease enter password: ";
		std::cin >> password1;

		std::cout << "Please verify password: ";
		std::cin >> password2;

		if (password1 != password2) {
			std::cout << "\nPasswords do not match!";
		}
	} while (password1 != password2);


	Server* homeServer = new Server("Home");

	Directory* thisIsAPlaceHolder = new Directory();

	Player* player = new Player(username, password1, thisIsAPlaceHolder, homeServer);

	std::cin.ignore(INT_MAX, '\n');

	while (playing == true) {

		std::cout << "[" << player->getCurrentUsername() << "@" << player->getCurrentServerName() << " " << player->getCurrentDirectoryName() << "]" << player->getSuffix() << " ";
		std::getline(std::cin, input);

		vector <string> tokens;

		std::stringstream check(input);

		string buffer;


		while (getline(check, buffer, ' '))
		{
			tokens.push_back(buffer);
		}

		if (tokens.size() >= 1) {
			switch (hashit(tokens[0])) {
			case cd:
				std::cout << tokens[1];
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
				std::cout << string(100, '\n');
				break;

			case error:
				std::cout << "Command not found.\n";
				break;
			}
		}
	}

	return 0;
}

Commands hashit(const std::string &inString) {
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
