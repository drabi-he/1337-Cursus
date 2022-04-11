<h1 align="center">
	💾 get_next_line
</h1>

<h2 align="center">
	<b><i>A C function that reads any valid file line by line until the end</i></b><br>
</h2>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/drabi-he/1337-Cursus?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/drabi-he/1337-Cursus?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/drabi-he/1337-Cursus?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/drabi-he/1337-Cursus?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/drabi-he/1337-Cursus?color=green" />
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-testing">Testing</a>
</h3>

---

## 💡 About the project

> _The aim of this project is to make you code a function that returns a line, read from a file descriptor._

	You will understand how files are opened, read and closed in an OS,
	and how they are interpreted by a programming language for further analysis.
	This task is crucial to understand for a future programmer since much of the time is based
	on manipulating files for data management and persistence.
	This project consists of coding a function that returns one line at a time from a text file.

For more detailed information, look at the [**subject of this project**](https://github.com/drabi-he/1337-Cursus/en.subject.pdf).


## 🛠️ Usage

### Requirements

The function is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.
<p  align="center"> :warning: The project must be written in accordance with the <a href="https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf" target="_blank">Norm</a> </p>
The Norm  is a programming standard that defines a set of rules to follow when writing code at 42. It applies to all C projects within the Common Core by default, and
to any project where it's specified. These are some of them:

    Each function must be maximum 25 lines, not counting the function's own curly brackets.
    
    Each line must be at most 80 columns wide, comments included.
    
    A function can take 4 named parameters maximum.
    
    You can't declare more than 5 variables per function.
    
    You're not allowed to use: for , do...while , switch , case ,  goto  ,
    ternary operators such as `?' and VLAs - Variable Length Arrays.
  The norminette (as we call the norm at 42) is in python and open source.
  
  Its repository is available at https://github.com/42School/norminette.
  
  In addition to the Norm, the subject have other requirements, which are:
  
    It is forbidden to declare global variables.
   
    Your read must use the BUFFER_SIZE defined during compilation to read from
    a file or from stdin. This value will be modified during the evaluation for testing
    purposes.
    
    The program will be compiled in this way:
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c.
    
    libft is not allowed for this project. You must add a get_next_line_utils.c file
    which will contain the functions that are needed for your get_next_line to work
### Instructions

**1. Using it in your code**

To use the function in your code, simply include its header:

```C
#include "get_next_line.h"
```

and, when compiling your code, add the source files and the required flag:

```shell
get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>
```

## 📋 Testing

You only have to edit the get_next_line.c file and uncomment the main function and headers inside it.
You can edit test.txt files to put another text if you wish to test othe cases.
Then simply run this command (change "xx" with desired buffer size) :

```shell
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=xx get_next_line.c get_next_line_utils.c && ./a.out
```

Or you can also use this third party tester to fully test the project

* [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester)
