# argHandler

### Overview
This is a simple addon which can help simplize works on shell interaction, with simple --help option and optional prefix.

### Structure
class arg : describe a single argument from shell.
class handler : describe a set of reaction to certain argument.

### Usage
First, you will need to create a handler object and decide whether you want to have prefix or not. Note that the strict mode is still under development and it will block any arguments that you do not define.
Second, use the append method to define a reaction to certain argument through defining a arg object and a certain kind of function that receive an iterator from the arguments array pointing to the current argument that match the arg object.
Third, call exec method and pass it with argc and argv to make it start.

### Install
This addon assume it in the lib directory and using the following project structure:
./root_dir/
           lib/
		   include/
		   .../
That is, the lib dir and include dir where the head file is, are on the same level.
The libaray file generated is placed just outside the dir, and the head file is copied into the right dir.

Further introduce is on the way.

### Other
This is a simple program made for self usage and may contain problems. Any advice is welcome.
