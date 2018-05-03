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
	mkdir,
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

	Player* player = new Player();

	User* playerUser = new User(username, password1);
	playerUser->setSuperUser(true);

	std::list<User*> server1UserList;
	server1UserList.push_back(playerUser);

	Server* server1 = new Server("127.0.0.1", server1UserList);

	player->serverLogin(server1UserList.front(), server1);

	player->getCurrentUser()->setWorkingDir(server1->getRootDir());

	//server1->mkdir(player->getCurrentUser(), "/etc");

	std::cin.ignore(INT_MAX, '\n');

	while (playing == true) {

		std::cout << "[" << player->getCurrentUsername() << "@" << player->getCurrentServer()->getIP() << " " << player->getCurrentDirectoryName() << "]" << player->getSuffix() << " ";
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
				if (tokens.size() >= 2) {
					server1->cd(player->getCurrentUser(), tokens[1]);
					break;
				}

			case ls:
				if (2 == tokens.size()) {
					std::cout << server1->ls(tokens[1]);
				}
				else {
					std::cout << "Error\n";
				}
				break;

			case mkdir:
				if (2 == tokens.size()) {
					std::cout << "Creating...\n";
					if (server1->mkdir(player->getCurrentUser(), tokens[1])) {
						std::cout << "Created\n";
					} else {
						std::cout << "Error creating directory\n";
					}
				}
				else {
					std::cout << "Error\n";
				}
				break;

			case rm:
				if (2 != tokens.size()) {
					std::cout << "Error\n";
					break;
				}
				if (server1->rm(tokens[1])) {
					std::cout << "File deleted.\n";
				}
				else {
					std::cout << "Failed to delete.\n";
				}
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
	if (inString == "mkdir") return mkdir;
	return error;
}
