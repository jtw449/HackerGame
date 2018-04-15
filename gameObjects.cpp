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
  int connected_ip;
  dir* curr;
} user;
