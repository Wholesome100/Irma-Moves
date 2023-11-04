# Irma Moves
This was a university project for Data Structures, the specifics of which are detailed in IrmaMoves.pdf

Please, do not copy this code to complete assignments. Logical observation is welcome, but copying will not instill the necessary skills and confidence to succeed.

# Running the Code
Clone the repository into your preferred development environment. The code can be run from the command line, but I opted for Visual Studio 2022 (MSVC Compiler)

With Visual Studio, open the .sln file. In the source files, only IrmaMoves.c and testcase05.c are included.
A preprocessor directive _CRT_SECURE_NO_WARNINGS may be needed to execute the program, as the strncpy function is flagged as being unsafe (the function is fine in this case, but is susceptible to buffer overflow like scanf).
Run the Local Windows Debugger to execute the program for testcase05.

The other test cases will need to be included/excluded as desired due to the project requirements. (Every testcase has an indivdual main() function to facilitate fast grading)
The intended output for each test case can be checked against their respective output file.
