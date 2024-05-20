#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int encode(int , int , char** , FILE* , FILE*);
int encoder(int argc, char **argv) {
  FILE * input = stdin;
  FILE * output = stdout;
  int plus; 
  int debugMode = 1; //true
  for (int i = 1; i < argc; i++) {
    if(strcmp(argv[i] , "-D") == 0)
    {
        debugMode = 0; //false
        fprintf(stderr, "%s\n", argv[i]);
    }
    else if(strcmp(argv[i] , "+D") == 0)
    {
        debugMode = 1; //true
    }
    else if (strncmp(argv[i], "-I", 2) == 0) 
    {
            input = fopen(argv[i] + 2, "r");
            if (input == NULL) {
                fprintf(stderr, "Error opening input file: %s\n", argv[i] + 2);
                return 1;
            }
    }
    else if (strncmp(argv[i], "-O", 2) == 0) 
    {
            output = fopen(argv[i] + 2, "w");
            if (output == NULL) 
            {
                fprintf(stderr, "Error opening output file: %s\n", argv[i] + 2);
                return 1;
            }
    }
    else if(strncmp(argv[i] , "+e" , 2) == 0)
    {
        plus = 1;
        encode(plus , argc , argv , input , output);
    }
    else if(strncmp(argv[i] , "-e" , 2) == 0)
    {
        plus = 0;
        encode(plus , argc , argv , input , output);
    }
    if(debugMode)
    {
          if(strcmp(argv[i] , "+D") == 1)
          {
            fprintf(stderr, "%s\n", argv[i]);
          }      
    }
  }
  


  return 0;

}



int encode(int plus, int argc, char ** argv , FILE * input , FILE * output)
{
    int *encoding_key= NULL;
    int key_length = 0;
    int currentindex = 0;

    for (int i = 1; i < argc; i++) {
        if (plus == 0 || plus == 1) {
            char *key_str = argv[i] + 2; // Skip "+e" or "-e"
            key_length = strlen(key_str);
            encoding_key = (int *)malloc(key_length * sizeof(int));

            // Convert encoding key digits to integers
            for (int j = 0; j < key_length; j++) {
                encoding_key[j] = key_str[j] - '0';
            }
        }
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        if (isalpha(c) && islower(c)) {
            int encoding_offset = encoding_key[currentindex];
            if (plus == 0) { 
                c -= encoding_offset;
                if (c < 'a') { 
                    c += 26;
                }
            } else { 
                c += encoding_offset;
                if (c > 'z') { 
                    c -= 26;
                }
            }
            currentindex = (currentindex + 1) % key_length; 
        }
        else if (isdigit(c)) {
            int encoding_offset = encoding_key[currentindex];
            if (plus == 0) { 
                c -= encoding_offset;
                if (c < '0') { 
                    c += 10;
                }
            } else {
                c += encoding_offset;
                if (c > '9') { 
                    c -= 10;
                }
            }
            currentindex = (currentindex + 1) % key_length; 
        }
        fputc(c, output); 
    }
    free(encoding_key);
    return 0;
}

    

