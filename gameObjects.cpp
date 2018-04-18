/*
  Hacker Game - 2018
  Contains the definitions of the base classes required for the game
*/

// Files will be manipulated by the player
class File {
  int id;
  void* data;
} file;


// Servers contain unique filesystems and ip addresses
class Server {
  int ip;
  dir* root;
} serv;

// User is the player of the game. Will need to keep track of their current state
class User {
	private:
		string username;
		string password;
		Directory* workingDir;
		list <string> history;
		bool superUser = false;

	public:
		User() {

		}

		User(string username, string password) {
			this->username = username;
			this->password = password;
		}

		User(string username, string password, Directory* workingDir) {
			this->username = username;
			this->password = password;
			this->workingDir = workingDir;
		}

		string getUsername() {
			return username;
		}

		void setDirectory(Directory* workingDir) {
			this->workingDir = workingDir;
		}

		Directory* getDirectory() {
			return workingDir;
		}

		void addHistory(string command) {
			history.push_back(command);
		}

		list<string> getHistory() {
			return history;
		}

		void setSuperUser(bool superUser) {
			this->superUser = superUser;
		}

		bool getSuperUser() {
			return superUser;
		}

} user;

class Player {
	private:
		list <User*> userList;
		list <User*>::iterator userListIter;

		list <Server*> serverList;
		list <Server*>::iterator serverListIter;

		void addUser(User* newUser) {
			userList.push_back(newUser);
		}

		bool removeUser() {
			if (userList.size() > 1) {
				userListIter = userList.end();
				userList.erase(userListIter);

				return true;
			}
			else {
				return false;
			}
		}

		void addServer(Server* newServer) {
			serverList.push_back(newServer);
		}

		bool removeServer() {
			if (serverList.size() > 1) {
				serverListIter = serverList.end();
				serverList.erase(serverListIter);

				return true;
			}
			else {
				return false;
			}
		}


	public:
		Player() {

		}

		Player(string username, string password, Directory* workingDir, Server* newServer) {
			User* player = new User(username, password, workingDir);
			addUser(player);
			addServer(newServer);
		}

		void serverLogin(User* newUser, Server* newServer) {
			addUser(newUser);
			addServer(newServer);
		}

		bool serverLogout() {
			if (removeServer() && removeUser())
				return true;
			else
				return false;
		}

		bool userLogin(User* newUser) {
			if (userList.size() == 1) {
				addUser(newUser);
				return true;
			}
			else {
				if (removeUser()) {
					addUser(newUser);
					return true;
				}
				else {
					return false;
				}
			}
		}

		User* getCurrentUser() {
			if (!userList.empty()) {
				return userList.back();
			}
		}

		Server* getCurrentServer() {
			if (!serverList.empty()) {
				return serverList.back();
			}
		}

		string getCurrentUsername() {
			User temp = *userList.back();
			return temp.getUsername();
		}

		string getCurrentServerName() {
			Server temp = *serverList.back();
			return temp.getServerName();
		}
} player;

class Permissions {
	private:
		bool worldRead;
		bool worldWrite;
		bool worldExecute;
		bool userRead;
		bool userWrite;
		bool userExecute;

	public:
		void setWorldRead(bool worldRead) { this->worldRead = worldRead; }
		bool getWorldRead() { return worldRead; }

		void setWorldWrite(bool worldWrite) { this->worldWrite = worldWrite; }
		bool getWorldWrite() { return worldWrite; }

		void setWorldExecute(bool worldExecute) { this->worldExecute = worldExecute; }
		bool getWorldExecute() { return worldExecute; }

		void setUserRead(bool userRead) { this->userRead = userRead; }
		bool getUserRead() { return userRead; }

		void setUserWrite(bool userWrite) { this->userWrite = userWrite; }
		bool getUserWrite() { return userWrite; }

		void setUserExecute(bool userExecute) { this->userExecute = userExecute; }
		bool getUserExecute() { return userExecute; }
} permissions;
