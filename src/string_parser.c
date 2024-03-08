#include "header.h"

extern bool _debug;
extern int _size; /*size of data_array.*/

void execute(char* instruction_pointer, int* prediction_array){

    char data_array[_size]; /*points to the current memory location of the bf character array. */
    for(int i = 0; i < _size; i++){data_array[i] = (int) 0;}/*every memory location should be set to 0 according to bf ruleset*/

    int pos = 0; /*keeps track of data_array position.*/
    long i = 0; /*keeps track of where instruction_pointer and prediction_array are at.*/

    while(true){

        switch(instruction_pointer[i]){
            
            case '>' :

                if(_debug){printf("read : '>' %d times\n", prediction_array[i]);}

                if(pos + prediction_array[i] < _size){pos += prediction_array[i];}
                else{pos = (pos + prediction_array[i]) - _size;}

                i += prediction_array[i];
                break;
            
            case '<' :

                if(_debug){printf("read : '<' %d times\n", prediction_array[i]);}

                if(pos - prediction_array[i] >= 0){pos -= prediction_array[i];}
                else{pos = _size - 1 - (prediction_array[i] - pos);}

                i += prediction_array[i];
                break;

            case '+' :

                if(_debug){printf("read : '+' %d times\n", prediction_array[i]);}
                
                data_array[pos] += prediction_array[i];              
                i += prediction_array[i];
                break;

            case '-' :

                if(_debug){printf("read : '-' %d times\n", prediction_array[i]);}

                data_array[pos] -= prediction_array[i];
                i += prediction_array[i];
                break;

            case '.' :

                if(_debug){puts("read : '.'");}
                putchar(data_array[pos]);
                if(_debug){puts("");}

                i++;
                break;

            case ',' :

                if(_debug){puts("read : ',' (Waiting for an input) : ");}

                data_array[pos] = (char) getchar();
                if(data_array[pos] == EOF){puts("INPUT ERROR. QUIT."); exit(EXIT_FAILURE);}
                
                i++;
                break;

            case '[' : /*if *data_array is 0 iump forward to the corresponding ']'. Else read the next instruction*/

                if(_debug){puts("read : '['");}

                if(!(data_array[pos])){

                    i = prediction_array[i];
                    break;
                }

                i++;
                break;


            case ']' : /*if *data_array is nonzero iump back to the corresponding '['. Else read the next instruction*/

                if(_debug){puts("read : ']'");} 

                if(data_array[pos]){

                    i = prediction_array[i];
                    break;
                }

                i++;
                break;

            case '\0' :

                if(_debug){puts("\nEND OF STRING REACHED");}
                return;

            default :

                if(_debug){puts("\ncharacter read as comment");}
                i++;

        }
    }
}
