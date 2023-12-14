
// headers
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <ctype.h>

#include <string.h>
#include <math.h>
#include <time.h>

// constants
const char* version = "0.1.0";
const short year = 2023;

// macros and typedefs
int ri;
#define repeat(n) for (ri = 0; ri < n; ++ri)

typedef unsigned char byte;

#define clear() printf("\e[1;1H\e[2J")

// general functions
void error(char* text) {
    printf("\033[38;5;202m%s\033[0m\n", text);
}

// runner utils
char code[4096];

char thisChar;
int i, codeLength, charNumber;
char cache[256];

void goUntil(char until) {
    i = 0;
    cache[0] = '\0';
    while(code[charNumber] != until) {
        cache[i] = code[charNumber];
        cache[i + 1] = '\0';
        ++i;
        ++charNumber;
    }
}
void goUntilAny(char* until) {
    i = 0;
    cache[0] = '\0';
    while(strchr(until, code[charNumber])) {
        cache[i] = code[charNumber];
        cache[i + 1] = '\0';
        ++i;
        ++charNumber;
    }
}

// run code
void runCode() {
    
    codeLength = strlen(code);
    charNumber = 0;

    while(charNumber < codeLength) {
        thisChar = code[charNumber];

        if(thisChar == ' ') {

            // its a space, do nothing

        } else if(thisChar == '#') {

            // the rest of this line is a comment, so go to next line
            goUntil('\n');

        } else if(isdigit(thisChar) || thisChar == '.') {

            // its a number literal
            goUntilAny("0123456789.");

        } else if(thisChar == '"') {

            // its an unformatted string literal
            ++charNumber;
            goUntil('"');

        } else {
            printf("Found unsupported char %c\n", code[charNumber]);
        }

        ++charNumber;
    }
}

// compile code to c
void compileCode() {
    error("Compile to C coming soon!");
    exit(1);
}

// cli
int main(int argc, char** argv) {

    srand(time(NULL));

    // variables
    char givenCode[1024] = "";
    char line[256] = "";
    char confirm[1];

    if(argc == 1) {

        // no action argument
        error("You need to provide an action argument.");
        puts(
            "-i   Enter the interpreter console\n"
            "-t   Lets you type code then runs it\n"
            "-r   Run code from a file\n"
            "-c   Compile code from a file into C code\n"
            "-q   quack"
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
                    strcpy(code, givenCode);
                    runCode();
                    givenCode[0] = '\0';
                } else if(strcmp(line, "exit\n") == 0) {
                    error("Exited terminal.");
                    return 0;
                } else {
                    strcat(givenCode, line);
                }
            }
            
            // lets user type code then run
            case 't':

            clear();
            puts("\033[1mType your G+ code:\033[0m");

            while(true) {
                printf("  ");
                fgets(line, 256, stdin);
                if(line[1] == '\0') {
                    strcpy(code, givenCode);
                    runCode();
                    return 0;
                } else {
                    strcat(givenCode, line);
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
                    strcat(givenCode, line);
                }
                fclose(file);
                
                if(givenCode[0] == '\0') {
                    error("File is empty or doesn't exist.");
                    return 1;
                }
                strcpy(code, givenCode);
                runCode();
            } else {
                puts("Cancelled.");
            }

            // compile code from file to c
            case 'c':

            printf("Compile the code in %s to C? y/n", argv[2]);
            fgets(confirm, 1, stdin);

            if(confirm[0] == 'y') {
                FILE *file;
                file = fopen(argv[1], "r");

                while(fgets(line, 1024, file)) {
                    strcat(givenCode, line);
                }
                fclose(file);
                
                if(givenCode[0] == '\0') {
                    error("File is empty or doesn't exist.");
                    return 1;
                }
                strcpy(code, givenCode);
                compileCode();
            } else {
                puts("Cancelled.");
            }
        
            // quack easter egg
            case 'q':

            double quacks = (double)((double)rand() / (double)(RAND_MAX / 0.35)) + 0.3;
            int totalQuacks = 0;
        
            while(totalQuacks < 1000000) {

                repeat(ceil(quacks)) {
                    printf("quack ");
                }

                quacks = quacks * (((double)rand() / (double)(RAND_MAX / 0.7)) + 1.25);
                totalQuacks = totalQuacks + (int)ceil(quacks);
                if(quacks > 10000) {
                    printf("[%d]", totalQuacks);
                }

                getchar();

            }

            puts("");
            error(
                "Congratulations! You've reached over a million quacks in one keypress.\n"
                "So, please stop now or your computer's gonna turn into the Hiroshima bomb."
            );
            return 0;

            // unknown action argument
            default:
            error("Unknown action argument.");
            return 1;

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
  - You can't use = and == with strings! Use strcpy() and strcmp()!
*/
