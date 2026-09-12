
#include "textmite.h"
/* im using these quotes now!!!
exit_fully() use if file is open
exit(EXIT_FAILURE) if no file opened*/
void printfile(FILE *file){
    rewind(file); //snap back to the start of file oh there goes the pointer
    int iteration = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
       iteration++;
       printf("%d : %s", iteration, line);
    }
}
/*void exit_fully(FILE *file){
    fclose(file);
    printf("Exiting file...\n");
    exit(EXIT_SUCCESS);
}*/ //turns out, this is useless! exit(exit_failure) always closes them for you
void double_check(int suspect){
    if (suspect < 1) { //if its less than 1 you probably messed something up
        perror("Suspect (usually argument 1) was invalid.\n");
        exit(EXIT_FAILURE); //nothing was opened yet so we don't need close_fully
    }
}
void error_handler(void *argument, int fatal){
    if (argument == NULL){ //checks whether a file was supplied
        if (fatal == 1){
            perror("fatal error!\n");
            exit(EXIT_FAILURE);
        } else {
            perror("No input provided! Not a fatal error.\n");
        }
    }
}
FILE *open_file(char *filename, int file_type){ //im really curious, what is const char? how is it useful in any way
    FILE *file;
    if (file_type == 1){
        file = fopen(filename, "r+");
    } else {
        file = fopen(filename, "w+");
    }
    error_handler(file, 1); //god i love this function
    return file;
}
void help_panel(void){
    printf("Thank you for using Textmite! Here are the commands.\n");
    printf("help: Shows a help panel! You just ran it /:\n");
    printf("exit: Self explanatory. exits the file\n");
    printf("insline: Inserts a line to a specific line [insline (line) (text_to_input)\n");
    printf("Flags for insline: -n (new line, eg; insline 4 terry the textmite -n is very cool)\n");
    printf("deline: Deletes a line (deline x)\n");
    printf("newline: Creates a new line");
}
void del_line(char *filename, char *arr_of_input[]){
    error_handler(arr_of_input[1], 1); //no need to check file because was checked previously
    int line_to_del = atoi(arr_of_input[1]); // therapist for argument, turns it into integer
    FILE *file = open_file(filename, 1);
    FILE *temp = open_file("temp", 0); //its so compact its enough to make a man cry
    //this is so convoluted
    char buffer[256]; //where strings go when their file leaves them
    int current_line = 1;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // If it's NOT the line we want to delete, write it to the temp file
        if (current_line != line_to_del) {
            fputs(buffer, temp);
        }
        current_line++;
    }
    fclose(file);
    fclose(temp);
    // Replace the old file with the updated temporary file
    remove(filename);
    rename("temp", filename);
    printf("Successfully deleted line %d.\n", line_to_del); 
}
void ins_line(char *filename, char *arr_of_input[]){
    int line_to_insert_locat = atoi(arr_of_input[1]); // Convert argument to integer            
    double_check(line_to_insert_locat);
    //the worst part of all of this is fixing the tabs
    //there were like 40 tabs
    FILE *file = open_file(filename, 1);
    FILE *temp = open_file("temp", 0); //its so compact its enough to make a man cry
    //this is so convoluted
    char buffer[256];
    int current_line = 1;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (current_line == line_to_insert_locat) {
            int wordindex = 2; //remember! arr_of_input 0 and 1 are the command and line!
            while (arr_of_input[wordindex] != NULL){ //repeats printing until it detects fin
                if (strcmp(arr_of_input[wordindex], "-n") == 0){
                    fprintf(temp, "\n");
                } else {
                    fprintf(temp,"%s ", arr_of_input[wordindex]);
                }
                wordindex++;
            }
            fprintf(temp, "\n"); //works???
        }
        fputs(buffer, temp);
        current_line++;
    }
    fclose(temp);
    fclose(file);
    // Replaces the old file with the updated temporary file
    if (remove(filename) != 0){
        perror("removing temp file failed\n");
        exit(EXIT_FAILURE);
    }
    if (rename("temp", filename) != 0){
        perror("renaming temp file failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Successfully created line %d.\n", line_to_insert_locat);
}
