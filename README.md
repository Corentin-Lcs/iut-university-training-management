<h1 align="center">University Management · IUT de Paris - Rives de Seine</h1>

The "University Training Management" GitHub project is a command-line interpreter that allows managing a university training. The commands enable defining the structure of the program as well as the enrolled students, assigning grades to these students, and performing end-of-semester and end-of-year tasks (such as editing grade reports and establishing jury decisions).

> [!IMPORTANT]  
> The project has been developed exclusively in a professional context, with the specific aim of promoting learning. It is carried out as a project for the University of Paris.

<p align="center">
  <img src="https://github.com/Corentin-Lcs/iut-university-training-management/blob/main/University.jpg" alt="University.jpg"/>
</p>

## Description

The application interprets 8 distinct commands with the `command_name <requested_arguments>` syntax. The commands can be entered either using the standard input (keyboard) or by redirecting a text file to the standard input. In any case, the program reads the commands from the standard input and produces results on the standard output (the screen). The commands are as follows : 

- Program exit : `exit`
- Definition of training : `formation <number_of_UE>`
- Adding an exam : `epreuve <semester_number> <subject_name> <exam_name> [<UE_coefficient>...]`
- Checking coefficients : `coefficients <semester_number>`
- Adding a grade : `note <semester_number> <student_name> <subject_name> <exam_name> <grade>`
- Checking grades : `notes <semester_number> <student_name>`
- Displaying a transcript : `releve <semester_number> <student_name>`
- Displaying a jury decision : `decision <student_name>`

> To understand the role and conditions of each command, please consult the manual for the subject by clicking [here](https://github.com/Corentin-Lcs/iut-university-training-management/blob/main/Sujet.pdf).

## Usage

To compile the `main.c` file from the command prompt, run the following command :

```
gcc [source_code_name].c -o [executable_name]
gcc main.c -o prog
```

> For more details about the concept of compilation and compilers, here are some useful links :
>
> Link 1 : <https://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/gcc.html> [FR]
> 
> Link 2 : <https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html> [EN]
>          
> Link 3 : <https://www.cyberciti.biz/faq/compiling-c-program-and-creating-executable-file/> [EN]
>
> Link 4 : <https://medium.com/@laura.derohan/compiling-c-files-with-gcc-step-by-step-8e78318052> [EN]
> 
> Link 5 : <https://gcc.gnu.org> [EN]

To launch the program from the command prompt, type the following command :

```
start prog.exe
```

> There are several other ways to run the executable.

Once the `prog.exe` executable is launched, run the available commands with the following syntax :

```
command_name <requested_arguments>
```

## Test Sets

Each `xxx` test set includes 2 files. The first, named `in-xxx.txt`, contains a sequence of commands to be accepted by the program. The second, named `out-xxx.txt`, contains the series of messages that the program must display when the commands contained in `in-xxx.txt` are entered on the keyboard.

You can copy the commands from `in-xxx.txt` one by one to paste them one by one when running the program. You can just as well copy multiple lines at once and submit them (by pasting them at once) into the program run window. This mode is particularly useful when you want to use the debugger and set breakpoints.

To avoid any copy / paste, it is possible to redirect the program input by executing the following command :

```
prog.exe < in-xxx.txt
```

> The `in-xxx.txt` and `out-xxx.txt` files must be in the directory containing the executable file.

The program runs and there is nothing to enter, the commands are taken from `in-xxx.txt`. Instead, the results are displayed on the screen. This mode is great when you want to debug your program displays.

To redirect program output, use the following command :

```
prog.exe < in-xxx.txt > result-xxx.txt
```

Again, nothing to enter but the results are no longer displayed on the screen. Everything the program should have printed is now saved in the `result-xxx.txt` file. This mode will make it possible to automatically compare that the program displays what is expected.

To do this, run the following command :

```
fc out-xxx.txt result-xxx.txt
``` 

This command displays "FC : no differences encountered" if the 2 files do not differ at any point and displays the differences found otherwise.

## Project's Structure

```
iut-university-training-management/
├─ README.md
├─ LICENSE
├─ Sujet.pdf
├─ Sujet.tex
├─ University.jpg
└─ src/
   ├─ main.c
   ├─ prog.exe
   ├─ Large Test Sets/
   │  ├─ Sprint 1/
   │  │  ├─ in-sp1.txt
   │  │  └─ out-sp1.txt
   │  ├─ Sprint 2/
   │  │  ├─ in-sp2.txt
   │  │  └─ out-sp2.txt
   │  ├─ Sprint 3/
   │  │  ├─ in-sp3.txt
   │  │  └─ out-sp3.txt
   │  ├─ Sprint 4/
   │  │  ├─ in-sp4.txt
   │  │  └─ out-sp4.txt
   │  └─ Sprint 5/
   │     ├─ in-sp5.txt
   │     └─ out-sp5.txt
   └─ Small Test Sets/
      ├─ Sprint 1/
      │  ├─ in-sp1-base.txt
      │  ├─ in-sp1-error.txt
      │  ├─ out-sp1-base.txt
      │  └─ out-sp1-error.txt
      ├─ Sprint 2/
      │  ├─ in-sp2-base.txt
      │  ├─ in-sp2-error.txt
      │  ├─ out-sp2-base.txt
      │  └─ out-sp2-error.txt
      ├─ Sprint 3/
      │  ├─ in-sp3-base.txt
      │  ├─ in-sp3-error.txt
      │  ├─ out-sp3-base.txt
      │  └─ out-sp3-error.txt
      └─ Sprint 4/
         ├─ in-sp4-base.txt
         ├─ in-sp4-error.txt
         ├─ out-sp4-base.txt
         └─ out-sp4-error.txt
```

Named `Sujet.pdf` (Subject.pdf), the file contains the subject of the project and is the compiled version of `Sujet.tex` (Subject.tex).

Named `in-xxx-base.txt` or `out-xxx-base.txt`, the file contains the normal usage of the commands.

Named `in-xxx-error.txt` or `out-xxx-error.txt`, the file contains the usage causing all the error messages of the commands.

## Meta

Created by [@Corentin-Lcs](https://github.com/Corentin-Lcs). Feel free to contact me !

Distributed under the GNU GPLv3 license. See [LICENSE](https://github.com/Corentin-Lcs/iut-university-training-management/blob/main/LICENSE) for more information.
