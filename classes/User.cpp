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
