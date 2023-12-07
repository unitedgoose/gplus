// headers
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// constants
const char* version = "0.1.0";
const short year = 2023;

typedef unsigned int byte;

// functions
#define clear() printf("\e[1;1H\e[2J")

void error(char* text) {
    printf("\033[38;5;202m%s\033[0m", text);
    exit(1);
}

// run code
void runCode(char* code) {
    printf("Actual thing that runs the code is coming soon, so here's the code:\n%s", code);
}

// main
int main(int argc, char** argv) {

    char code[1024] = "";
    char line[256] = "";

    if(argc == 1) {

        // terminal
        clear();
        printf("\033[1mG+ Terminal - Version %s\033[0m\n(c) %d Pique & AP\nPress enter twice to run code, type \"exit\" to exit\n", version, year);
        
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

    } else if(argc == 2) {

        if(argv[2] == "-r") {

            printf("run the project?");

        }

        // run from file
        FILE *file;
        file = fopen(argv[1], "r");

        while(fgets(line, 1024, file)) {
            strcat(code, line);
        }
        fclose(file);
        
        if(code[0] == '\0') {
            error("File is empty or doesn't exist.");
        }
        runCode(code);

    } else {
        error("More than 2 arguments provided.");
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