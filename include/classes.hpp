#ifndef CLASS_H
#define CLASS_H

// include package requirements here
#include <iostream>
#include <utility>
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
    Directory* workingDir;
    list<string> history;
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

    bool checkPassword(string pass) {
      return (pass == this->password);
    }

    void setWorkingDir(Directory* workingDir) {
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
};


class File {
  private:
    string name;
    string data;
    time_t access_time;
    time_t modify_time;
    time_t change_time;
    Permissions* permissions;
    User* owner;

  public:
    // constructor
    File(string file_name, string data, Permissions* perm_flags, User* file_owner) {
      this->name = file_name;
      this->data = data;
      this->access_time = time(nullptr);
      this->modify_time = this->access_time;
      this->change_time = this->access_time;
      this->permissions = perm_flags;
      this->owner = file_owner;
    }

    string getName() {
      return this->name;
    }

    string get_contents() {
      return this->data;
    }

    bool set_name(string file_name) {
      this->name = file_name;
      this->change_time = time(nullptr);
      return true;
    }

    bool set_access_time(time_t time) {
      this->access_time = time;
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

    bool change_ownership(User* new_owner) {
      this->owner = new_owner;
      this->change_time = time(nullptr);
      return true;
    }

    bool change_permissions(Permissions* perm_flags) {
      this->permissions = perm_flags;
      this->change_time = time(nullptr);
      return true;
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
    User* owner;
    time_t access_time;
    time_t modify_time;

  public:
    // constructor
    Directory(string d_name, Directory* parent, Permissions* perm_flags, User* d_owner) {
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
      for (File* file : this->files) {
        delete file;
      }
      for (Directory* dir : this->sub_dirs) {
        delete dir;
      }
    }

    string getName() {
      return this->name;
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
       if (filename == file->getName()) {
         this->files.remove(file);
         delete file;
         return true;
       }
      }
      return false;
    }

    File* get_file(string filename) {
      // searches the directory for the specified file, returns the file if exists
      for (File* file : this->files) {
        if (filename == file->getName()) {
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

    Directory* get_dir(string dir_name) {
      // searches the directory for the specified file, returns the file if exists
      for (Directory* dir : this->sub_dirs) {
        if (dir_name == dir->name) {
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
  std::list<User*> Accounts;
  bool SSH;

  vector<string>* parsePath(string absPath) {
    //check absPath for invalid chars
    if(absPath.find('\"') || absPath.find('\'') || absPath.find('\n') || absPath.find('\\')) {
      return nullptr;
    }

    //setup for absPath parsing
    vector<string>* nameList = new vector<string>();
    std::size_t base = 1, next = 0;
    next = absPath.find('/', base);

    //iterate through string and push folder names onto end of vector
    while(next != string::npos) {
      nameList->push_back( absPath.substr(base, next-base) );
      base = next+1;
      next = absPath.find('/', base);
    }

    return nameList;
  }

  //only send the path portion to this function, WITH a trailing '/' but without a trailing filename
  Directory* validatePath(string absPath) {
    if (absPath.empty()) return nullptr;
    if (absPath.at(0) != '/') return nullptr;
    if (absPath.back() != '/') return nullptr;

    vector<string>* folderList = parsePath(absPath);
    if (!folderList || folderList->empty()) return nullptr;

    Directory* curDir = this->rootDirectory;
    for (string folderName : *folderList) {
      curDir = curDir->get_dir(folderName);
      if (!curDir) return nullptr;
    }

    delete folderList;
    return curDir;
  }

  void separateNameFromPath(string absPath, string* nameCallback, string* pathCallback) {
    std::size_t base = absPath.rfind("/") + 1;
    *nameCallback = absPath.substr(base, absPath.length() - base);
    *pathCallback = absPath.substr(absPath.length()-nameCallback->length(), base-1);
  }

public:
  Server(string IP, std::list<User*> userList) {
    this->IP = IP;
    this->rootDirectory = new Directory("root", nullptr, nullptr, userList.front());
    this->Accounts = userList;
    this->SSH = true;
  }
  ~Server() {
    delete this->rootDirectory;
    for(User* user : this->Accounts) {
      delete user;
    }
  }

  User* connect(string username, string password) {
    for(User* user : this->Accounts) {
      if (user->getUsername() == username && user->checkPassword(password)) {
        return user;
      }
    }
  }

  string ls(string absPath) {
    Directory* folder = validatePath(absPath);
    if (!folder) return "";

    list<Directory*> dirs = folder->get_sub_dirs();
    list<File*> files = folder->get_files();

    string ls = "";
    for (Directory* dir : dirs) {
      ls.append(dir->getName());
      ls += "/\n";
    }
    for (File* file : files) {
      ls.append(file->getName());
      ls += '\n';
    }
  }

  bool cd(User* user, string absPath) {
    Directory* folder = validatePath(absPath);
    if (!folder) return false;

    user->setWorkingDir(folder);
  }

  bool touch(User* user, string absPath) {
    if (absPath.back() == '/') {
      return false;
    }
    string name, path;
    separateNameFromPath(absPath, &name, &path);

    Directory* folder = validatePath(path);
    if (!folder) return false;

    File* new_file = new File(name, "", nullptr, user);
    folder->add_file(new_file);
  }

  bool mkdir(User* user, string absPath) {
		if (absPath.back() == '/') {
			absPath.pop_back();
		}
		string name, path;
		separateNameFromPath(absPath, &name, &path);
    Directory* folder = validatePath(path);
    if (!folder) return false;
		Directory new_dir = new Directory(name, folder, nullptr, user->getUsername());
		folder.add_dir(new_dir);
		return true;
  }

  bool mv(string src, string dest) {
		// check if destination exists
		Directory* folder = validatePath(dest);
		if (!folder) return false;
		if (src.back() == '/') {
			src.pop_back();
		}
		Directory* new_folder;
		File* new_file;
		string name, path;
		separateNameFromPath(src, &name, &path);
		Directory* src_folder = validatePath(path);
		if (!src_folder) return false;
		if (src_folder->get_dir(name)) {
			// move the dir
			new_folder = src_folder->get_dir(name);
			folder->add_dir(new_folder);
			src_folder->delete_dir(new_folder);
		}
		else if (src_folder->get_file(name)) {
			// move the file
			new_file = src_folder->get_file(name);
			folder->add_file(new_file);
			src_folder->delete_file(new_file);
		}
		return true;
  }
  bool cp(string src, string dest) {
		// check if destination exists
		Directory* folder = validatePath(dest);
		if (!folder) return false;
		if (src.back() == '/') {
			src.pop_back();
		}
		Directory* new_folder;
		File* new_file;
		string name, path;
		separateNameFromPath(src, &name, &path);
		Directory* src_folder = validatePath(path);
		if (!src_folder) return false;
		if (src_folder->get_dir(name)) {
			// move the dir
			new_folder = src_folder->get_dir(name);
			folder->add_dir(new_folder);
		}
		else if (src_folder->get_file(name)) {
			// move the file
			new_file = src_folder->get_file(name);
			folder->add_file(new_file);
		}
		return true;
  }
  bool rm(string absPath) {
		// check if destination exists
		Directory* new_folder;
		File* new_file;
		string name, path;
		separateNameFromPath(absPath, &name, &path);
		Directory* folder = validatePath(path);
		if (!folder) return false;
		if (folder->get_dir(name)) {
			// remove the dir
			new_folder = folder->get_dir(name);
			folder->delete_dir(new_folder);
		}
		else if (folder->get_file(name)) {
			// move the file
			new_file = folder->get_file(name);
			folder->delete_file(new_file);
		}
		return true;
  }
  string cat(string absPath) {
		if (absPath.back() == '/') {
			absPath.pop_back();
		}
		string name, path, stringContents;
		separateNameFromPath(absPath, &name, &path);
		Directory* folder = validatePath(path);
		if (!folder) return stringContents;	//return an empty string on failure
		File* file = folder->get_file(name);
		stringContents = file->get_contents();
		return stringContents;
  }
  // void sudo(string cmd, string password) {
	//
  // }
  // void su(string password) {
	//
  // }
  // void clear() {
	//
  // }

};


class Player {
private:

  list < std::pair<User*, Server*> > connectionList;

  std::pair<User*, Server*> connectionPair;

  string suffix;

  void addConnection(User* user, Server* server) {
    connectionList.push_back(std::make_pair(user, server));
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

  std::pair<User*, Server*> getCurrentConnection() {
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
      return std::get<0>(getCurrentConnection());
    }
   }

  Server* getCurrentServer() {
    if (!connectionList.empty()) {
      return std::get<1>(getCurrentConnection());
    }
  }

  string getCurrentUsername() {
    User temp = *std::get<0>(getCurrentConnection());
    return temp.getUsername();
  }

  string getCurrentServerName() {
    Server temp = *std::get<1>(getCurrentConnection());
    return temp.getServerName();
  }

  string getCurrentDirectoryName() {
    User temp = *std::get<0>(getCurrentConnection());
    Directory tempdir = *temp.getDirectory();
    return tempdir.getDirectoryName();
  }

  bool getCurrentUserRoot() {
    User temp = *std::get<0>(getCurrentConnection());
    return temp.getSuperUser();
  }

  string getSuffix() {
    if (getCurrentUserRoot()) { suffix = "#"; }
    else if (!getCurrentUserRoot()) { suffix = "$"; }

    return suffix;
  }
};

#endif
