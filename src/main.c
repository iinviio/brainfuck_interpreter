#include "header.h"

/* 
brainfuck instructions :

let 'char* data_array'. data_array points to the data array (the first cells at the beginning). All cells are sets to 0

> : increment data_array by one
< : decrement data_array by one
+ : increment *data_array by one. If *data_array == 255, increment will set *data_array = 0
- : decrement *data_array by one. If *data_array == 0, decrement will set *data_array = 255
. : print *data_array
, : take one byte in input and store it into *data_array
[ : if *data_array is 0 jump forward to the corresponding ']'. Else read the next instruction
] : if *data_array is nonzero jump back to the corresponding '['. Else read the next instruction



interpreter options :

    ./brainfuck <filename.bf> [OPTIONS]
    ./brainfuck (leave blank) to write a string to parse

    (-d OR --_debug) : _debug
    (-s OR --size) <size> : custom array size [0 - UINT_MAX]
    (-S OR --string) = "<String>" : parse the string <String> instead of a file
    (-h OR --help)    
*/

extern bool _debug;
extern int _size;

int main(int argc, char** argv){

    char* filename;
    int ret = parse_input(argc, argv, &filename);

    if(ret == -1){

        exit(EXIT_FAILURE);
    }

    if(!ret){/*ret == 0. no file provided, print help page*/

        help();/*print help page and exit the program*/
    }
    else{/*ret > 0*/

        FILE *fp;

        fp = fopen(filename, "r");
        if(fp == NULL){perror("Unable to properly open the file "); exit(EXIT_FAILURE);}

        fseek(fp, 0L, SEEK_END);
        long file_length = ftell(fp);
        rewind(fp);

        char instruction_pointer[file_length]; /*points to the current instruction of the bf program*/
        char tmp[1024];

        long bytes_read = 0;
        long acc = 0;

        /*load the program into the memory*/
        while ((bytes_read = fread(tmp, 1, sizeof(tmp), fp)) > 0){

            for (long i = 0; i < bytes_read; i++){
            
                instruction_pointer[acc++] = tmp[i];
            }

        }

        instruction_pointer[acc] = '\0'; /*fread do not add the terminating character*/

        if(fclose(fp) == EOF){perror("Unable to properly close the file. "); exit(EXIT_FAILURE);}

        int parenthesis_array[file_length];
        if(generate_prediction_array(instruction_pointer, file_length, parenthesis_array) == -1){/*generate the array used to store parenthesis position*/

            puts("Invalid program.");
            exit(EXIT_FAILURE);
        }
        
        execute(instruction_pointer, parenthesis_array);/*execute the bf program*/
    }


    if(_debug){puts("PARSING SUCCESSFULLY ENDED");}
    return 0;
}