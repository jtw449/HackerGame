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
    list <User*> userList;
    list <User*>::iterator userListIter;

    // list <Server*> serverList;
    // list <Server*>::iterator serverListIter;

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

    // void addServer(Server* newServer) {
    // 	serverList.push_back(newServer);
    // }

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

    // Player(string username, string password, Directory* workingDir, Server* newServer) {
    // 	User* player = new User(username, password, workingDir);
    // 	addUser(player);
    // 	addServer(newServer);
    // }

    // void serverLogin(User* newUser, Server* newServer) {
    // 	addUser(newUser);
    // 	addServer(newServer);
    // }

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

    // User* getCurrentUser() {
    // 	if (!userList.empty()) {
    // 		return userList.back();
    // 	}
    // }

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
	
    string getCurrentDirectoryName() {
	User temp = *userList.back();
	Directory tempdir = *temp.getDirectory();
	return tempdir.getDirectoryName();
    }

    bool getCurrentUserRoot() {
	User temp = *userList.back();
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
         dir->access_time = time(nullptr);
         return dir;
       }
      }
      return nullptr;
    }
};


class Server {

private:
  string IP;
  Directory* rootDirectory;
  std::list<User> Accounts;
  bool SSH;

  Directory* validatePath(string path) {
    if (!path) return nullptr;

    vector<string>* folderList = parsePath(path);
    if (!folderList) return nullptr;

    Directory* curDir = nullptr;
    for (Directory folder : *folderList) {
      curDir = curDir.get_dir(folder);
      if (!curDir) return nullptr;
    }

    delete folderList;
    return curDir;
  }

  vector<string>* parsePath(string path) {
    //check path for invalid chars
    if(str.find('\"') || str.find('\'') || str.find('\n') || str.find('\\')) {
      return nullptr;
    }

    vector<string>* nameList = new vector<string>();
    std::size_t base, next = 0;
    //iterate through string and push folder names onto end of vector
    while(next != string::npos) {
      nameList.push_back( path.substr(base+1, next-base) );
      base = next;
      next = path.find('/', base+1);
    }
    nameList.push_back( path.substr(base+1, path.length()) );
    return nameList;
  }

public:
  Server(string IP, std::list<User> userList) {
    this.IP = IP;
    this.rootDirectory = new Directory();
    this.accounts = userList;
    this.SSH = true;
  }
  ~Server() {
    delete this.rootDirectory;
    for(User user : this.Accounts) {
      delete user;
    }
  }

  User* connect(string username, string password) {
    for(User user : this.Accounts) {
      if (user.username == username && user.password == password) {
        return true;
      }
    }
  }
  string ls(string path) {

  }

  bool cd(User* user, string path) {
    Directory* startingDir;
    if(path.at(0) == '/') { // if path starts at root folder
      startingDir = this->rootDirectory;
    } else {
      startingDir = user.getDirectory();
    }

    Directory* folder = validatePath(path);
    Directory* folder = validatePath( parsePath(path), startingDir );

    if (!folder) return false;

    user.setWorkingDir(folder);
  }

  void touch(string path) {

  }
  void mv(string src, string dest) {

  }
  void cp(string src, string dest) {

  }
  void rm(string path) {

  }
  string cat(string path) {

  }
  void sudo(string cmd, string password) {

  }
  void su(string password) {

  }
  void clear() {

  }

};

#endif
