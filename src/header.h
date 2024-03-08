#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

void execute(char* instruction_pointer, int* prediction_array);/*execute the actual bf program*/
int parse_filename(int argc, char** argv);/*return the argv index where the filename is if no errors occured, -1 in case an error occurred*/
int parse_input(int argc, char** argv, char** filename);/*parse options. return -1 on error, 0 in case of empty arguments and the argv index where the filename is in case of success. (note that argv[0] is the name of the executed program, in this case "brainfuck". so in case of success the returned value will be grater than 0)*/
void help();/*print hel page, then quit*/
int generate_prediction_array(char* s, long len, int* prediction_array);/*generate the array used to store parenthesis position. Returns 0 on success, -1 on error*/
void cleanup(void* ptr);/*free the allocated memory for ptr*/