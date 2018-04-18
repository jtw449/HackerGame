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
