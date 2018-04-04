# Planned Object Implementations

[Home](../README.md)

## User

The user records the player's current game state.
```
class User {
  int connected_ip,
  Directory* current_dir
}
```
## Servers

The game will consist of various servers, each with a unique ip. Progression
through the game will be required to access certain servers. Each server contains
its own unique filesystem.
```
class Server {
  int ip,
  Directory* root_dir
}
```
## Filesystems

Filesystem will consist of directories and files. The root directory will be the start
of the filesystem. Permissions will be assigned to each file/folder.
```
class Directory {
  File* files,
  Directory* subdirectories,
  Directory* parent
}
```
Directories will hold files. Files will be manipulated throughout the game.
Directories may also contain other directories, subdirectories
```
class File {
  int id,
  void* data
}
```
Files will contain data that will be manipulated throughout the hacking game.

## Enumerations for game flow
```
enum Permissions {
  ... todo ...
}
```
Files and directories will have different permission levels.
```
enum Commands {
  ls,
  rm,
  mv,
  touch,
  cp,
  ssh,
  cd,
  cat,
  su,
  logout,
  clear
}
```
Commands will vary between servers.

Commands can be virtually executed via stdin. This should mimic the actual
execution of command line tools, such as ls, mkdir, etc...
* Will discuss more commands in detail later
* This is more of a 'table' than an object

### More to come...
