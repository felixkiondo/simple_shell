The Project will mandate creating a UNIX Simple Shell Program
 A README.md file should be created at the root of the folder of the project.
 an AUTHORS file should be created at the root of your repository, listing all individuals having contributed content to the repository.
Here are the List of allowed functions and system calls!
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)
The Code Compilation will be done as follows:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

What to Do?
 Write a beautiful code that passes the Betty checks.

 Write a UNIX command line interpreter.

 Simple shell 0.1 +

Handle command lines with arguments
 Simple shell 0.2 +

Handle the PATH
fork must not be called if the command doesn’t exist
 Simple shell 0.3 +

Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit
 Simple shell 0.4 +

Implement the env built-in, that prints the current environment.
 Simple shell 0.1 +

Write your own getline function

Use a buffer to read many chars at once and call the least possible the read system call

You will need to use static variables

You are not allowed to use getline

You don’t have to:

be able to move the cursor.

 Simple shell 0.2 +

You are not allowed to use strtok.
 Simple shell 0.4 +

handle arguments for the built-in exit
Usage: exit status, where status is an integer used to exit the shell.
 Simple shell 1.0 +

Implement the setenv and unsetenv builtin commands

setenv * Initialize a new environment variable, or modify an existing one * Command syntax: setenv VARIABLE VALUE * Should print something on stderr on failure

unsetenv * Remove an environment variable * Command syntax: unsetenv VARIABLE * Should print something on stderr on failure.

 Simple shell 1.0 +

Implement the builtin command cd:
Changes the current directory of the process.
Command syntax: cd [DIRECTORY]
If no argument is given to cd the command must be interpreted like cd $HOME
You have to handle the command cd -
You have to update the environment variable PWD when you change directory
man chdir, man getcwd.
 Simple shell 1.0 +

Handle the commands separator ;
 Simple shell 1.0 +

Handle the && and || shell logical operators.
 Simple shell 1.0 +

Implement the alias builtin command
Usage: alias [name[='value'] ...]
alias: Prints a list of all aliases, one per line, in the form name='value'
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line in the form name='value' alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value.
 Simple shell 1.0 +

Handle variables replacement
Handle the $? variable
Handle the $$ variable.
 Simple shell 1.0 +

Handle comments (#).
 Simple shell 1.0 +

Usage: simple_shell [filename]
Your shell can take a file as a command line argument
The file contains all the commands that your shell should run before exiting
The file should contain one command per line
In this mode, the shell should not print a prompt and should not read from stdin.
