// headers
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// constants
const char* version = "0.1.0";
const short year = 2023;

typedef unsigned char byte;

// functions
#define clear() printf("\e[1;1H\e[2J")

void error(char* text) {
    printf("\033[38;5;202m%s\033[0m\n", text);
}

// run code
void runCode(char* code) {

}

// main
int main(int argc, char** argv) {

    // variables
    char code[1024] = "";
    char line[256] = "";
    char confirm[1];

    if(argc == 1) {

        // no action argument
        error("You need to provide an action argument.");
        puts(
            "-i   Enter the interpreter console\n"
            "-t   Lets you type code then runs it\n"
            "-r   Run code from a file\n"
            "-c   Compile code from a file into C code"
        );
        return 1;

    } else if(argc == 2) {
        switch(argv[1][1]) {

            // interpreter console
            case 'i':

            clear();
            printf(
                "\033[1mG+ Terminal - Version %s\033[0m\n"
                "(c) %d Pique & AP\n"
                "Press enter twice to run code, type \"exit\" to exit\n"
                ,version, year
            );
                
            while(true) {
                printf(">> ");
                fgets(line, 256, stdin);
                if(line[1] == '\0') {
                    runCode(code);
                    code[0] = '\0';
                } else if(strcmp(line, "exit\n") == 0) {
                    error("Exited terminal.");
                } else {
                    strcat(code, line);
                }
            }
            
            // lets user type code then run
            case 't':

            clear();
            puts("Type your G+ code:");

            while(true) {
                printf("  ");
                fgets(line, 256, stdin);
                if(line[1] == '\0') {
                    runCode(code);
                    return 0;
                } else {
                    strcat(code, line);
                }
            }

            // run code from file
            case 'r':

            printf("Run the code in %s? y/n", argv[2]);
            fgets(confirm, 1, stdin);

            if(confirm[0] == 'y') {
                FILE *file;
                file = fopen(argv[1], "r");

                while(fgets(line, 1024, file)) {
                    strcat(code, line);
                }
                fclose(file);
                
                if(code[0] == '\0') {
                    error("File is empty or doesn't exist.");
                    return 1;
                }
                runCode(code);
            } else {
                puts("Cancelled.");
            }

            // compile code from file to c
            case 'c':

            printf("Compile the code in %s to C? y/n", argv[2]);
            fgets(confirm, 1, stdin);

            if(confirm[0] == 'y') {
                puts("Coming soon.");
                return 1;
            } else {
                puts("Cancelled.");
            }
        
        }
    }

    return 0;
}

/*
Things to know:
  - Only use puts() and printf() to print
  - Numeric types are byte, short, and int (8, 16, and 32 bit)
  - Only allocate enough for what's needed
  - Always initialize strings as empty strings
*/
