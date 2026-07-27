#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//textmite...
int main()
{
    int i = 0;
    char input[500];
    char line[256];
    char *arr_of_input[500];
    char selectfile[60];
    int del_or_add_line = 1;
    printf("\noh yeah oh yeah put file in oh yeah : ");
    scanf("%s", selectfile);
    while (getchar() != '\n');
    FILE *file = fopen(selectfile, "r+"); //waa waa waa! my variables arent infront of me!! darn code.
    while (0 == 0) {
        if (del_or_add_line  == 0){
            FILE *file = fopen(selectfile, "r+"); //opens it 
        }
        if (file == NULL)
        {
            printf("this file is a lie\n");
            printf("you see its funny because the last three letters of file is ile\n");
            printf("you can re-arrange that to spell lie\n");
            printf("ha.. heh.. man..\n"); //comedy aint my strong suit
            return 0;
        }
        rewind(file); //snap back to the start of file oh there goes the pointer
        if (file != NULL) { //checks if file is real
            while (fgets(line, sizeof(line), file)) {
                printf("%s", line);
            }
        }
        else {
            printf("this file is a lie\n"); //shot...
            printf("wait i made this joke already");
            return 0;
        }
        printf("\n>");
        fflush(stdout); // doesn't wait for no buffer... he don't need em (sunglasses and explosion)
        //read input using fgets

        if (fgets(input, sizeof(input), stdin) == NULL) {
            //break on EOF
            break; 
        }

        size_t len = strlen(input); 
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        char *token = strtok(input, " "); // Sthis??
        while (token != NULL && i < 499) {
            arr_of_input[i++] = token; //actually genius line
            token = strtok(NULL, " \t\n"); //turns it into array
        }
        if (arr_of_input[0] == NULL){
            del_or_add_line = 1;
            printf("you input nothing am i a mind reader or something\n");
        }
        if (strcmp(arr_of_input[0], "test") == 0){
            del_or_add_line = 1;
            printf("test... done\n");
        } else if (strcmp(arr_of_input[0], "newline") == 0){
            del_or_add_line = 1;
            fprintf(file,"\n");

        } else if (strcmp(arr_of_input[0], "exit") == 0){
            del_or_add_line = 1;
            fclose(file);
            return 0;
        }else if (strcmp(arr_of_input[0], "deline") == 0) {
            //if (fgets(arr_of_input[1], sizeof(arr_of_input[1]), file) == NULL){
            //    printf("so that line doesn't actually exist\n");
            //    return 0;
            //}
            del_or_add_line = 0;
            if (file) fclose(file);
            if (arr_of_input[1] == NULL){
                printf("what line dude what line!! i cant read your mind \n");
                return 0;
            }
            int line_to_del = atoi(arr_of_input[1]); // therapist for argument, turns it into integer
            FILE *newfile = fopen(selectfile, "r"); //reading file
            if (newfile == NULL) { //checks if file exists
                printf("Error opening file for reading.\n");
                return 0;
            }
            FILE *temp = fopen("temp.txt", "w"); //makes the temp file
            if (temp == NULL) { //checks if temp file exists
                printf("Error creating temporary file.\n");
                fclose(newfile);
                return 0;
            }
            //this is so convoluted
            char buffer[256]; //where strings go when their file leaves them
            int current_line = 1;
            while (fgets(buffer, sizeof(buffer), newfile) != NULL) {
                // If it's NOT the line we want to delete, write it to the temp file
                if (current_line != line_to_del) {
                    fputs(buffer, temp);
                }
                current_line++;
            }
        
            fclose(newfile);
            fclose(temp);
        
            // Replace the old file with the updated temporary file
            remove(selectfile);
            rename("temp.txt", selectfile);
            printf("Successfully deleted line %d.\n", line_to_del);
            file = fopen(selectfile, "r+"); //remember!!! RE OPEN!!!!

        }else if (strcmp(arr_of_input[0], "insline") == 0){
            //if (fgets(arr_of_input[1], sizeof(arr_of_input[1]), file) == NULL){
            //    printf("so that line doesn't actually exist\n");
            //    return 0;
            //} no worky
            del_or_add_line = 0;
            if (file) fclose(file);
            if (arr_of_input[1] == NULL){
                printf("what line!! i cant read minds! \n");
                return 0;
            } else if (arr_of_input[2] == NULL){
                printf("cmon now you cant expect me to actually write nothing just use newline\n");
                return 0; //necessary?
            }
            FILE *newfile = fopen(selectfile, "r"); //opens file for reading
            int line_to_insert_locat = atoi(arr_of_input[1]); // Convert argument to integer
             if (newfile == NULL) { //checks if you can even read file
                 printf("Error opening file for reading.\n"); //we've gone over this.. you know the drill
                 return 0;
             }
             FILE *temp = fopen("temp.txt", "w"); //opens even better temp file
             if (temp == NULL) {
                 printf("Error creating temporary file.\n");
                 fclose(newfile);
                 return 0;
             }
             //this is so convoluted
             char buffer[256];
             int current_line = 1;
             while (fgets(buffer, sizeof(buffer), newfile) != NULL) {
                 if (current_line == line_to_insert_locat) {
                    int wordindex = 2; //remember! arr_of_input 0 and 1 are the command and text!
                    int finished = 1; //o is a standin for i so its practically a token
                    //fin is shorthand for finish
                    while (finished == 1){ //repeats printing until it detects fin
                        if (arr_of_input[wordindex] == NULL){
                            //printf("done!\n");
                            fprintf(temp, "\n");
                            finished = 0;
                        } else {
                            fprintf(temp,"%s ", arr_of_input[wordindex]);
                            wordindex++;
                        }
                    }
                 }
                    fputs(buffer, temp);
                 current_line++;
             }
         
             fclose(newfile);
             fclose(temp);
         
             // Replace the old file with the updated temporary file
             remove(selectfile);
             rename("temp.txt", selectfile);
             file = fopen(selectfile, "r+");

             printf("Successfully created line %d.\n", line_to_insert_locat);
        } else {
            del_or_add_line = 1;
            printf("this isn't a command!!!\n"); //failsafe
        }
        if (file) fclose(file); //remember remember it updates
        memset(arr_of_input, 0, sizeof(arr_of_input)); //failsafe 2.0
        i = 0;
    }
}
