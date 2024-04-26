#include "header.h"
#include <unistd.h> /*getopt(3)*/

/*interpreter options :

    ./brainfuck [OPTIONS] <filename.bf>

    (-d OR --debug) : debug
    (-s OR --size) <size> : custom array size [0 - UINT_MAX]
    (-h OR --help)

*/

/*default values*/
bool _debug = false;
int _size = 65536; /*default length (should be at least 30k)*/

int parse_input(int argc, char **argv, char** filename){

    int opt;

    if(argc == 1){

        return 0; /*empty args*/
    }

    int ret = parse_filename(argc, argv);

    if(ret == -1){

        printf("Unrecognized file format. Filename should end in .b or .bf \n");
        return -1;/*error code*/
    }

    *filename = *(argv + ret);/*once i have the filename i save it. The function getopt modifies argv values*/

    while((opt = getopt(argc, argv, "dhns:")) != -1){
            
        switch(opt){

            case 'd' :

                _debug = true;
                break;

            case 'h' : /*overrides any other option and ptrint the help page, then quit*/

                help();
                break;

            case 's' :

                _size = atoi(optarg);
                if(_size <= 0){

                    puts("Invalid input in '-s <size>'. size length must be greater than 0");
                    help();
                    exit(EXIT_FAILURE);
                }
                    
                break;

            default :
                    
                puts("Unrecognized option");
                return -1; /*error*/
        }
    }

    return ret;/*return the argv index where the filename is*/
}

int parse_filename(int argc, char** argv){

    /*check whether the extension is right or not
    allowed extension : .b, .bf*/

    char* ptr;
    for(int i = 1; i < argc; i++){ /*cycle through every arguments to find the filename. (skip the first iteration since that is the executed program name, hence "brainfuck")*/

        ptr = *(argv + i);

        while(*ptr){ptr++;}
        if(strcmp(".b", (ptr - 2)) == 0 || strcmp(".bf", (ptr - 3)) == 0){return i;}/*return the argv index where the filename is*/
    }
    
    return -1;
}
