#include "header.h"

/*  For parenthesis prediction the following code uses a stack and an array.
    when a '[' is encountered, its position is pushed into the stack, when the
    a ']' is encountered, the last position (which is relative to the last open parenthesis)
    is popped from the stack. So, at this point, we know the position of the two matching
    parenthesis. We now store the position of the ']' into 'prediction_array' at
    the index corresponding to the position of the '[' and vice versa.

    For the symbols +, -, <, >, we basically count how many times in a row a symbol repeat itself and
    we store that information into 'prediction_array' in the index corresponding to the first occurence
    of the symbol so that during the execution, when the symbol is encountered, we know exactly how many
    times repeat a certain instruction.
*/

extern bool _debug;
int generate_prediction_array(char* s, long len, int* prediction_array){/*return 0 on success, -1 otherwise*/

    if(!s || !prediction_array){return -1;}
    
    int stack[len];
    long stack_index = 0;
    long i = 0, j;/*i is the general inxex, j an auxiliary one.*/

    while(s[i]){

        switch(s[i]){

            case '[' : 

                /*add '[' position*/
                stack[stack_index++] = i;/*push i pos into the stack*/

                i++;
                break;

            case ']' :

                /*add ']' position*/
                stack_index--;
                if(stack_index < 0){puts("ERROR. PARENTHESIS MISSMATCH."); exit(EXIT_FAILURE);}
                
                int pos = stack[stack_index];/*pop the last entry of the stack*/

                /*put the matching closed parenthesis position into the position relative to the open one and vice versa*/
                prediction_array[pos] = i;
                prediction_array[i] = pos; 

                if(_debug){printf("[ : %d, ] : %ld\n", pos, i);}

                i++;
                break;

            case '+' :

                j = i;
                prediction_array[j] = 0; /*prediction array is not initialized at first*/
                while(s[i] == '+'){

                    prediction_array[j]++;
                    i++;
                }

                if(_debug){printf("+ : %d, j : %ld\n", prediction_array[j], j);}
                break;

            case '-' :

                j = i;
                prediction_array[j] = 0; /*prediction array is not initialized at first*/
                while(s[i] == '-'){

                    prediction_array[j]++;
                    i++;
                }

                if(_debug){printf("- : %d, j : %ld\n", prediction_array[j], j);}
                break;

            case '>' : 


                j = i;
                prediction_array[j] = 0; /*prediction array is not initialized at first*/
                while(s[i] == '>'){

                    prediction_array[j]++;
                    i++;
                }

                if(_debug){printf("> : %d, j : %ld\n", prediction_array[j], j);}
                break;

            case '<' : 

                j = i;
                prediction_array[j] = 0; /*prediction array is not initialized at first*/
                while(s[i] == '<'){

                    prediction_array[j]++;
                    i++;
                }
                
                if(_debug){printf("< : %d, j : %ld\n", prediction_array[j], j);}
                break;

            default :

                if(_debug){printf("ignored character : %c\n", s[i]);}
                i++;
                break;
        }

    }
    
    if(stack_index > 0){puts("ERROR. PARENTHESIS MISSMATCH."); exit(EXIT_FAILURE);}
    if(_debug){puts("JUMP PREDICTION SUCCESSFULLY FINISHED");}
    return 0;
}