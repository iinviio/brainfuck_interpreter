#include "header.h"

void help(){

    puts("\n\nUsage : brainfuck [OPTIONS] <file>\n");
    puts("Options : \n");
    puts(" -d \t\t Enable debug mode");
    puts(" -h \t\t Display (this) help page");
    puts(" -s <size> \t Set a custom size for the char array (default is 65536)\n");

    exit(EXIT_SUCCESS);
}
