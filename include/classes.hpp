#ifndef CLASS_H
#define CLASS_H

// include package requirements here
#include <iostream>
#include <list>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::list;
using std::vector;

class Permissions;
class User;
class Player;
class File;
class Directory;
class Server;


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
};


class User {
  private:
    string username;
    string password;
    // Directory* workingDir;
    list<string> history;
    bool superUser = false;

  public:
    User() {

    }

    User(string username, string password) {
      this->username = username;
      this->password = password;
    }

    // User(string username, string password, Directory* workingDir) {
    // 	this->username = username;
    // 	this->password = password;
    // 	this->workingDir = workingDir;
    // }

    string getUsername() {
      return username;
    }

    // void setDirectory(Directory* workingDir) {
    // 	this->workingDir = workingDir;
    // }

    // Directory* getDirectory() {
    // 	return workingDir;
    // }

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
};


class File {
  private:
    string name;
    string data;
    time_t access_time;
    time_t modify_time;
    time_t change_time;
    Permissions permissions;
    User owner;

  public:
    // constructor
    File(string file_name, string data, Permissions perm_flags, User file_owner) {
      this->name = file_name;
      this->data = data;
      this->access_time = time(nullptr);
      this->modify_time = this->access_time;
      this->change_time = this->access_time;
      this->permissions = perm_flags;
      this->owner = file_owner;
    }

    bool set_name(string file_name) {
      this->name = file_name;
      this->change_time = time(nullptr);
      return true;
    }

    bool write_data(string data) {
      this->data = data;
      this->modify_time = time(nullptr);
      this->access_time = this->modify_time;
      this->change_time = this->modify_time;
      return true;
    }

    bool append_data(string data) {
      this->data = this->data.append(data);
      this->modify_time = time(nullptr);
      this->access_time = this->modify_time;
      this->change_time = this->modify_time;
      return true;
    }

    bool change_ownership(User new_owner) {
      this->owner = new_owner;
      this->change_time = time(nullptr);
      return true;
    }

    bool change_permissions(Permissions perm_flags) {
      this->permissions = perm_flags;
      this->change_time = time(nullptr);
      return true;
    }
};


class Player {
private:

	list < pair<User*, Server*> > connectionList;

	pair<User*, Server*> connectionPair;

	string suffix;

	void addConnection(User* user, Server* server) {
		connectionList.push_back(make_pair(user, server));
	}

	bool removeConnection() {
		if (connectionList.size() > 1) {
			connectionList.erase(connectionList.end());
			return true;
		}
		else {
			return false;
		}
	}

	pair<User*, Server*> getCurrentConnection() {
		connectionPair = connectionList.back();
		return connectionPair;
	}

public:
	Player() {

	}

	Player(string username, string password, Directory* workingDir, Server* newServer) {
		User* player = new User(username, password, workingDir);
		addConnection(player, newServer);
	}

	void serverLogin(User* newUser, Server* newServer) {
		addConnection(newUser, newServer);
	}

	bool serverLogout() {
		if (removeConnection())
			return true;
		else
			return false;
	}

	User* getCurrentUser() {
		if (!connectionList.empty()) {
			return get<0>(getCurrentConnection());
	 	}
	 }

	Server* getCurrentServer() {
		if (!connectionList.empty()) {
			return get<1>(getCurrentConnection());
		}
	}

	string getCurrentUsername() {
		User temp = *get<0>(getCurrentConnection());
		return temp.getUsername();
	}

	string getCurrentServerName() {
		Server temp = *get<1>(getCurrentConnection());
		return temp.getServerName();
	}

	string getCurrentDirectoryName() {
		User temp = *get<0>(getCurrentConnection());
		Directory tempdir = *temp.getDirectory();
		return tempdir.getDirectoryName();
	}

	bool getCurrentUserRoot() {
		User temp = *get<0>(getCurrentConnection());
		return temp.getSuperUser();
	}

	string getSuffix() {
		if (getCurrentUserRoot()) { suffix = "#"; }
		else if (!getCurrentUserRoot()) { suffix = "$"; }

		return suffix;
	}
};


class Directory {
  private:
    string name;
    // list of files contained in current directory
    list<File*> files;
    list<Directory*> sub_dirs;
    Directory* parent_dir;
    Permissions* permissions;
    User owner;
    time_t access_time;
    time_t modify_time;

  public:
    // constructor
    Directory(string d_name, Directory* parent, Permissions* perm_flags, User d_owner) {
      this->name = d_name;
      // don't init the files or sub_dirs, use a method later on
      this->parent_dir = parent;
      this->permissions = perm_flags;
      this->owner = d_owner;
      this->access_time = time(nullptr);
      this->modify_time = access_time;
    }

    // destructor
    ~Directory() {
      for (File file : this->files) {
        delete file;
      }
      for (Directory dir : this->sub_dirs) {
        delete dir;
      }
      delete this->files;
      delete this->sub_dirs;
    }

    bool add_file(File* new_file) {
      // add a file to the directory
      this->files.push_back(new_file);
      // update modify_time
      this->modify_time = time(nullptr);
      return true;
    }

    bool delete_file(string filename) {
      for (File* file : this->files) {
       if (filename == file->name) {
         this->files.remove(file);
         delete file;
         return true;
       }
      }
      return false;
    }

    File get_file(string filename) {
      // searches the directory for the specified file, returns the file if exists
      for (File* file : this->files) {
       if (filename == file->name) {
         // update access_time
         file->access_time = time(nullptr);
         return file;
       }
      }
      return nullptr;
    }

    bool add_dir(Directory* new_sub) {
      // add a file to the directory
      this->sub_dirs.push_back(new_sub);
      // update modify_time
      this->modify_time = time(nullptr);
      return true;
    }

    bool delete_dir(string dir_name) {
      for (Directory* dir : this->sub_dirs) {
       if (dir_name == dir->name) {
         this->sub_dirs.remove(dir);
         delete dir;
         return true;
       }
      }
      return false;
    }

    Directory get_dir(string dir_name) {
      // searches the directory for the specified file, returns the file if exists
      for (Directory* dir : this->sub_dirs) {
       if (dir_name == dir->name) {
         // update access_time
         dir->access_time = time(nullptr);  //probably don't want to update access time here. Should be done in the command functions in Server
         return dir;
       }
      }
      return nullptr;
    }

		string get_name() {
			return this->name;
		}

		list<File*> get_files() {
			return this->files;
		}

		list<Directory*> get_sub_dirs() {
			return this->sub_dirs;
		}
};


class Server {

private:
  string IP;
  Directory* rootDirectory;
  std::list<User> Accounts;
  bool SSH;

  vector<string>* parsePath(string absPath) {
    //check absPath for invalid chars
    if(str.find('\"') || str.find('\'') || str.find('\n') || str.find('\\')) {
      return nullptr;
    }

    //setup for absPath parsing
    vector<string>* nameList = new vector<string>();
    std::size_t base = 1, next = 0;
    next = absPath.find('/', base);

    //iterate through string and push folder names onto end of vector
    while(next != string::npos) {
      nameList.push_back( absPath.substr(base, next-base) );
      base = next+1;
      next = absPath.find('/', base);
    }

    return nameList;
  }

  //only send the path portion to this function, WITH a trailing '/' but without a trailing filename
  Directory* validatePath(string absPath) {
    if (!absPath) return nullptr;
    if (absPath.at(0) != '/') return nullptr;
    if (absPath.back() != '/') return nullptr;

    vector<string>* folderList = parsePath(absPath);
    if (!folderList || folderList->empty()) return nullptr;

    Directory* curDir = this->rootDirectory;
    for (Directory folderName : *folderList) {
      curDir = curDir.get_dir(folderName);
      if (!curDir) return nullptr;
    }

    delete *folderList;
    return curDir;
  }

public:
  Server(string IP, std::list<User> userList) {
    this->IP = IP;
    this->rootDirectory = new Directory();
    this->accounts = userList;
    this->SSH = true;
  }
  ~Server() {
    delete this.rootDirectory;
    for(User user : this.Accounts) {
      delete user;
    }
  }

  string getIP() {
    return this->IP;
  }

  User* connect(string username, string password) {
    for(User user : this.Accounts) {
      if (user.username == username && user.password == password) {
        return true;
      }
    }
  }

  string ls(string absPath) {
    Directory* folder = validatePath(absPath);
    if (!folder) return "";


  }

  bool cd(User* user, string absPath) {
    Directory* folder = validatePath(absPath);
    if (!folder) return false;

    user.setWorkingDir(folder);
  }

  void touch(string absPath) {
    Directory* folder = validatePath(absPath);
    if (!folder) return false;
  }

  void mkdir(string absPath) {
		if (absPath.back() == '/') {
			absPath.pop_back();
		}
		std::size_t found = absPath.rfind("/");
		string filename;
		strcpy(filename, (absPath+filename))
    Directory* folder = validatePath(absPath);
    if (!folder) return false;

  }

  void mv(string src, string dest) {

  }
  void cp(string src, string dest) {

  }
  void rm(string absPath) {

  }
  string cat(string absPath) {

  }
  // void sudo(string cmd, string password) {

  // }
  // void su(string password) {

  // }
  // void clear() {

  // }

};

#endif
