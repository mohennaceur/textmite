
#include "textmite.h"
//textmite...

int main(int argc, char *argv[]) //I do not understand why argc comes with argv, but it is how it is.
{
    char input[500]; //originally, i thought i'd have to worry about the variables location for optimization's sake, but turns out, it doesn't matter!
    char *arr_of_input[500];
    int iteration;
    error_handler(argv[1], 1); 
    FILE *file = open_file(argv[1], 1); //this is the new fopen.
    while (1){
        iteration = 0;
        memset(arr_of_input, 0, sizeof(arr_of_input)); //resets the memory so it can run again
        printfile(file);
        printf("\n>"); //this runs
        fflush(stdout);
        //read input using fgets
        if (fgets(input, sizeof(input), stdin) == NULL) {
            //break on EOF
            break; 
        }
        if (input[0] == '\n') {
            printf("No input provided!\n");
            exit(EXIT_FAILURE);
        }
        size_t len = strlen(input); 
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        char *token = strtok(input, " "); // Sthis??
        while (token != NULL && iteration < 499) {
            arr_of_input[iteration++] = token; //actually genius line
            token = strtok(NULL, " \t\n"); //turns it into array
        }
        if (arr_of_input[0] == NULL){
            perror("No input\n");
        } else if(strcmp(arr_of_input[0], "exit") == 0) {
            printf("Ending process... \n");
            exit(EXIT_SUCCESS);
        } else if (strcmp(arr_of_input[0], "help") == 0) {
            help_panel();
        } else if (strcmp(arr_of_input[0], "insline") == 0) { 
            error_handler(arr_of_input[1], 1);
            error_handler(arr_of_input[2], 1);
            if (file) fclose(file); //useful
            ins_line(argv[1], arr_of_input);
            file = open_file(argv[1], 1);
        } else if (strcmp(arr_of_input[0], "deline") == 0){
            if (file) fclose(file);
            del_line(argv[1], arr_of_input); //function !!! yay
            file = open_file(argv[1], 1);
        } else if (strcmp(arr_of_input[0], "newline") == 0){
            fprintf(file, "\n"); //a proffesional functionchud would turn this into a function for 'compacticity dudeee'
            //however, i am not a cannibalistic humanoid underground dweller
        } else {
            perror("Input invalid (run help for help.)\n");
        }
        
    }
}
