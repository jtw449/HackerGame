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
class Directory {
  file* files;
  dir* sub;
  dir* parent;
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
