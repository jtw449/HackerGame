#include <iostream>
#include <list>
#include <ctime>

using std::string;
using std::list;

// Directories will hold files and other directories (subdirectories)
// NOTE will our class' namespace conflict with std libraries?
// TODO add parameter validation
class Directory {
  private:
    string name;
    // list of files contained in current directory
    list<File> files;
    list<Directory> sub_dirs;
    Directory parent_dir;
    Permissions permissions;
    User owner;
    time_t access_time;
    time_t modify_time;

  public:
    // constructor
    Directory(string d_name, Directory parent, Permissions perm_flags, User d_owner) {
      this->name = d_name;
      // don't init the files or sub_dirs, use a method later on
      // FIXME is this correct?
      this->files = new list<File>;
      this->sub_dirs = new list<Directory>;
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

    bool add_file(File new_file) {
      // add a file to the directory
      this->files.push_back(file);
      // update modify_time
      this->modify_time = time(nullptr);
      return true;
    }

    bool delete_file(string filename) {
      for (File file : this->files) {
       if (filename == file.name) {
         this->files.remove(file);
         delete file;
         return true;
       }
      }
      return false;
    }

    File get_file(string filename) {
      // searches the directory for the specified file, returns the file if exists
      for (File file : this->files) {
  	   if (filename == file.name) {
         // update access_time
         file.access_time = time(nullptr);
         return file;
       }
      }
      return nullptr;
    }

    bool add_dir(Directory new_sub) {
      // add a file to the directory
      this->sub_dirs.push_back(new_sub);
      // update modify_time
      this->modify_time = time(nullptr);
      return true;
    }

    bool delete_dir(string dir_name) {
      for (Directory dir : this->sub_dirs) {
       if (dir_name == dir.name) {
         this->sub_dirs.remove(dir);
         delete dir;
         return true;
       }
      }
      return false;
    }

    Directory get_dir(string dir_name) {
      // searches the directory for the specified file, returns the file if exists
      for (Directory dir : this->sub_dirs) {
       if (dir_name == dir.name) {
         // update access_time
         dir.access_time = time(nullptr);
         return dir;
       }
      }
      return nullptr;
    }

} dir;
