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

Where ever calloc is used before a strncpy, it is done so because strncpy isn't
actually guaranteed to null terminate the written string; it does not terminate
when the incoming string has been truncated. By having a buffer that is already
previously full of zero bytes, and calling strncpy with one less than the size
of the buffer, this subtle problem is avoided.

Please note that due to the requirement of the GUI library to specify a maximum
text input length, and preallocate a fixed buffer in advance for the result of
text inputs, any events' names or locations being added or edited are limited
to 255 bytes each (an arbitrary choice on my part). Nevertheless, values for
these fields read directly from a file or being saved to a file without any GUI
interaction are unlimited by this constraint.

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
