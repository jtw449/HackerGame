/*
  Hacker Game - 2018
  Contains the definitions of the base classes required for the game
*/

// Files will be manipulated by the player
class File {
  int id;
  void* data;
} file;

// Directories will hold files and other directories (subdirectories)
// NOTE will our class' namespace conflict with std libraries?
// TODO add parameter validation
class Directory {
  public:
    // constructor
    Directory(string d_name, dir curr_dir, list <perm> perm_flags, user d_owner) {
      this.name = d_name;
      // don't init the files or sub_dirs, use a method later on
      // FIXME is this correct?
      this.files = files();
      this.sub_dirs = sub_dirs();
      this.parent_dir = curr_dir;
      this.permissions = perm_flags;
      this.owner = d_owner;
      this.access_time = time(nullptr);
      this.modify_time = access_time;
    }

  bool add_file(file new_file) {
    // NOTE what constraints on this function?
    // -- max num files/dir?
    // add a file to the directory
    this.files.push_back(file);
    // update modify_time
    this.modify_time = time(nullptr);
    return true;
  }

  file get_file(string filename) {
    // searches the directory for the specified file, returns the file if exists
    for (file::iterator iter = this.files.begin(); iter != this.files.end(); iter++) {
	   if (filename == iter.name) {
       // update access_time
       iter.access_time = time(nullptr);
       return iter;
     }
    }
    return nullptr;
  }

  bool add_dir(dir new_sub) {
    // NOTE what constraints on this function?
    // -- max num files/dir?
    // add a file to the directory
    this.sub_dirs.push_back(new_sub);
    // update modify_time
    this.modify_time = time(nullptr);
    return true;
  }

  dir get_dir(string dir_name) {
    // searches the directory for the specified file, returns the file if exists
    for (file::iterator iter = this.sub_dirs.begin(); iter != this.sub_dirs.end(); iter++) {
     if (filename == iter.name) {
       // update access_time
       iter.access_time = time(nullptr);
       return iter;
     }
    }
    return nullptr;
  }

  // TODO add more functionality through methods after implementation testing 

  private:
    string name;
    // list of files contained in current directory
    list <file> files;
    list <dir> sub_dirs;
    dir parent_dir;
    list <perm> permissions;
    user owner;
    time_t access_time;
    time_t modify_time;
} dir;

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
