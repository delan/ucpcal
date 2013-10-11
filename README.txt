Unix and C Programming 120
Calendar assignment

The program being submitted is fairly complex, so I hope that I have made it as
clear to understand as possible. In addition to comments in the code, all
function prototypes in header files are prefixed with Doxygen-compatible
formatted comments which include a formal description of the purpose, actions,
parameters and return values of functions, or in the case of data structure
definitions, the purpose of the structure and/or its fields.

All global symbols declared by this program's source code, with the exception
of the externally supplied files gui.{c,h}, follow a consistent format of
ucpcal_*, as a primitive form of namespacing to avoid pollution.

All functions relating to data structures, named ucpcal_$tag, are named in the
manner of ucpcal_$tag_$action, where $action often includes "new" and "free".

While every reasonable effort has been made to make this program safe and free
of memory errors and leaks, some leaks may occur in the GUI side of the
application. Also, more importantly, this program is probably not resistant to
a malicious user. This is mainly due to the fact that many safer variants of
common functions, such as snprintf(), are only available in ISO C99, a standard
not within the scope of this unit.

This submission includes the following source files:

* date.{c,h}: data structures and algorithms for handling dates and times
* event.{c,h}: data structures and algorithms for handling calendar events
* gui.{c,h}: supplied wrapper around GTK+ by David Cooper
* list.{c,h}: data structures and algorithms for linked lists of events
* ucpcal.{c,h}: the main source files for the application's UI/business logic

Also included are the remaining non-source files and directories:

* Makefile: POSIX make recipes for building the program
* Doxyfile: configuration file for the Doxygen documentation generator
* README.txt: this README file
* test.txt: a valid calendar file input for testing purposes, from the spec
* .git*: metadata for the Git DVCS (you can view my development progress!)

The Makefile mentioned above has the following rules:

* ucpcal: the default rule, which builds the program
* docs: builds HTML and LaTeX documentation with Doxygen
* clean: deletes all generated files
* submission: archives all files for the final submission

Delan Azabani
#17065012
