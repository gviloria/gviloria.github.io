/**************************************************************************************************
 *
 * NAME:            Gabriel Viloria
 *
 * DESCRIPTION:     
 *                  The
 *                  program is a user-interface for a bank database application which allows
 *                  the user to: add a new record in the database, modify a record in the database,
 *                  print information about a record using the account as a key, print all
 *                  information in the database, delete an existing record from the database
 *                  using the account no as a key, and the ability to quit the program.
 *
 *************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "record.h"
#include "database.h"
#include "iofunctions.h"

int debugmode;

void run_menu(char*,int,int,struct record**);
void check_arg(int, char **);
void get_input(char *, int *,int);
void display_menu();
void getField(char*, int);
void clear_line();
int isInteger(char *, int);

int main(int argc,char *argv[]){

    struct record* start = NULL;
    int choice;
    int input_size = 9;
    char decision[10];
    char filename[]= "data.txt";

    if(readfile(&start,filename) == 1){
        printf("\n\nFile '%s' could not be read. . .\n\n",filename);
    } else {
        printf("\n\nFile '%s' has been read successfully. . .\n\n",filename);
    }
    
    check_arg(argc,argv);
    display_menu();
    get_input(decision,&choice,input_size);

    while (!isInteger(decision,input_size) || choice < 1 || choice > 6){
        display_menu();
        printf("That is not a valid integer or your choice is not within the choices 1-6.\n");
        get_input(decision, &choice,input_size);
    }
    
    run_menu(decision,choice,input_size,&start);
}

/**************************************************************************************************
 *
 * FUNCTION NAME:   run_menu
 *
 * DESCRIPTION:     Runs the menu and it's functions within a while loop. If the choice is 1
 *                  it adds a record, 2: modifies a record and allow the user to change the NAME,
 *                  3: prints a record and prints all duplicates with same account number
 *                  4: prints all records, 5: deletes a record, and 6: exits the loop and thus
 *                  ending the program. Afterwards, the program will write all records to file
 *                  and will clear all of the allocated memory (if any).
 *                  If debug mode is invoked, it will display the function name,
 *                  it's parameters, and what it received. The clear() function has been called
 *                  after user inputs, most notably the scanf to remove the newline characters,
 *                  that cause the next user input to be skipped and before caused the menu to
 *                  display two times.
 *                  If debug mode is invoked, the functions information will be printed.
 *                  There is a bad input check for year of birth and accountno.
 *
 * PARAMETERS:      decision(char*):  Contains the user's input which will be processed to
 *                                    be the user's choice.
 *                  choice(int):      The user's choice for the menu whose range is 1-6.
 *                  input_size(int):  The preferred size for input
 *                  start(struct *record): The struct containing information from the bank.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void run_menu(char *decision,int choice,int input_size,struct record ** start){

    int accountno;
    char name[25];
    char address[80];
    int addresscap = 79;
    int yearofbirth;
    char yearinput[10];
    char info[100];
    char filename[] = "data.txt";

    while (choice != 6){

        while (!isInteger(decision,input_size) || choice < 1 || choice > 6){
            
            printf("Invalid choice. It is not within the choices 1-6.\n");
            display_menu();
            get_input(decision, &choice,input_size);
            
        }

        if (choice == 1){
            
            printf("Please create your own account number: ");
            scanf("%s",info);

            while(!isInteger(info,99)){
                printf("\nThat is not a valid account number. Only integers are allowed.\n");
                printf("Please create your own account number:");
                scanf("%s",info);
            }
            
            accountno = atoi(info);

            clear_line();

            printf("\nPlease enter your name: ");
            fgets(name, 24, stdin);

            printf("\nPlease enter your address:\n");
            printf("To finish your input, make a new line after your input and enter 'quit':\n");
            getField(address,addresscap);

            printf("\nPlease enter your year of birth: ");
            scanf("%s",yearinput);

            while(strlen(yearinput) != 4 || !isInteger(yearinput,10)){
                printf("\nNot a valid year of birth. Please try again: \n");
                scanf("%s",yearinput);
            }
            
            yearofbirth = atoi(yearinput);

            addRecord(start,accountno,name,address,yearofbirth);

            printf("\n");
        }

        else if (choice == 2){

            if (start == NULL) {

                printf("There are no records in the database to modify.\n");

            } else {

                printf("\nPlease enter the account number you want to modify: ");
                scanf("%d", &accountno);

                clear_line();

                printf("\nPlease enter your new name: ");
                fgets(name, 24, stdin);

                if(modifyRecord(*start, accountno, name) == 1){

                    printf("No matching record for account number: %d",accountno);
                    
                }
            }
            

            printf("\nPress ENTER to continue...\n");
        
        } else if (choice == 3){

            if (start == NULL){

                printf("The is no record in the database to print.\n");

            } else {

                printf("\nPlease enter your account number you want to view: ");
                scanf("%d", &accountno);

                clear_line();

                if (printRecord(*start, accountno) == 1) {
                    
                printf("\nNo records have been found for the account number: %d\n", accountno);
                    
                }
            }

            printf("\nPress ENTER to continue...\n");
        }

        else if (choice == 4){

            if (start == NULL){

                printf("There are no records in the database to display.\n");

            } else {

                printf("\n---------------ALL RECORDS---------------");
                printAllRecords(*start);
                
            }
            
            printf("\nPress ENTER to continue...\n");
            
        }

        else if (choice == 5){

            if(start == NULL){

                printf("There are no records in the database to delete.\n");
                
            } else {

                printf("\nPlease enter the account number you wish to delete: ");
                scanf("%d",&accountno);
                
                (deleteRecord(start,accountno));
            }
            
            printf("\nPress ENTER to continue...\n");
        }
        
        strncpy(name,"",sizeof(name)-1);
	    strncpy(address,"",sizeof(address)-1);
	    strncpy(info,"",sizeof(info)-1);
        
        clear_line();
        display_menu();
        get_input(decision,&choice,input_size);
        
        printf("\n");
    }

    printf("Program now closing. . .\n");
    writefile(*start,filename);
    
    if(debugmode == 1) {
        printf("\n[DEBUG]\n***Parameter Name: [run_menu]***\n-----Parameters-----\n");
        printf("char *decision:%s\nint choice:%d\nint input_size:%d\n",decision,choice,input_size);
        printf("********************************\n\n");
    }
}

/**************************************************************************************************
 *
 * FUNCTION NAME:   check_arg
 *
 * DESCRIPTION:     This function checks the command line argument to determine what mode
 *                  the program should be run in. If the argc is just 1, (./(program)) then
 *                  the program will run like normal, if the argc is equal to 2, and the string
 *                  of the second argument is equal to 'debug' then it will run debug mode by
 *                  setting the int for debug mode to 1, which will in turn trigger all the
 *                  debug if statements for all of the functions in the program. If the argc
 *                  count is larger than than what is needed, an error will display and end the
 *                  program.
 *                  If debug mode is invoked, the functions information will be printed.
 *
 * PARAMETERS:      argc(int):       The amount of arguments in the command line.
 *                  argv(char**):    The string arguments inputed into the command line.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void check_arg(int argc,char *argv[]) {

    if (argc == 1) {
        
        printf("\n\nThis program is a user-interface for a bank database application.\n");
        printf("*************************[NORMAL MODE]**************************\n");
        printf("\n\n");
        
        debugmode = 0;
    
    } else if (argc == 2 && (strcmp(argv[1], "debug") == 0) && argv[2] == NULL) {
        
        printf("\nThis program is a user-interface for a bank database application.");
        printf("\n*********************[DEBUG MODE ENABLED]***********************\n");
        printf("\n\n");
        
        debugmode = 1;

    } else {
        
        printf("\nInsufficient or invalid arguments: (%d)\n", argc);
        printf("You only have two choices: './gvhw3' [NORMAL] or './gvhw3 debug' for [DEBUG MODE]");
        exit(1);
        
    }

    if (debugmode == 1) {
        
        printf("\n[DEBUG]\n***Parameter Name: [check_arg]***\n-----Parameters-----\nargc:%d\n", argc);
        printf("*********************************\n\n");
        
    }
}

/**************************************************************************************************
 *
 * FUNCTION NAME:   get_input
 *
 * DESCRIPTION:     First prompts the user for an input choice for the menu, stores the
 *                  user's input(string) into the 'input' char array, checks whether the input
 *                  is a valid integer or not through the function call 'isInteger' and if it
 *                  returns 'true' or '1' then it uses the function 'atoi' to convert
 *                  the string argument to an integer and finally stores value within
 *                  the variable 'choice'.
 *                  If debug mode is invoked, the functions information will be printed.
 *
 * PARAMETERS:      *input(char):   Contains the user's input which will be processed.
 *                  *choice(int):   The choice of the user after bring processed.
 *                  input_size(int): The preferred size of input.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void get_input(char *input, int *choice, int input_size){

    printf("\nPlease enter the number of an option: ");
    fgets(input,input_size,stdin);

    printf("\n\n");
    
    if(isInteger(input,input_size)){
        *choice = atoi(input);
    }

    if(debugmode == 1){
        
        printf("\n[DEBUG]\n***Parameter Name: [get_input]***\n-----Parameters-----\n");
        printf("char input:%c\nint choice:%d\nint input_size:%d\n", *input,*choice,input_size);
        printf("*********************************\n\n");
        
    }
}

/**************************************************************************************************
 *
 * FUNCTION NAME:   isInteger
 *
 * DESCRIPTION:     Loops through each and every char of the user's input(string) and determines
 *                  whether or not that particular char its on is a valid integer through
 *                  the function 'isdigit'. If it finds that one of the char's is not an integer2
 *                  it returns '0', however if all of the char's are valid then the program returns
 *                  '1'. The first for loop replaces the newline character with a null character
 *                  to fix problems with the user input in menu.
 *                  If debug mode is invoked, the functions information will be printed.
 *
 * PARAMETERS:      input(char*):    Contains the user's input which will be processed.
 *                  input_size(int): The preferred size of input.
 *
 * RETURN VALUES:   1: The user's input is valid
 *                  0: The user's input is not valid
 *
 *************************************************************************************************/
int isInteger(char *input, int input_size) {

    int valid = 1;
    int i, x;

    for (x = 0; x < input_size; x++){

        if (input[x] == '\n'){

            input[x] = '\0';
            break;
        }

    }

    for (i = 0; i < strlen(input); i++)
    {

        if (!isdigit(input[i]))
        {
            valid = 0;
            break;
        }
    }

    if (debugmode == 1){
        printf("\n[DEBUG]\n***Parameter Name: [isInteger]***\n-----Parameters-----\n");
        printf("char *input:%s\nint input_size:%d\n",input,input_size);
        printf("*********************************\n\n");
    }

    return valid;
}

/**************************************************************************************************
 *
 * FUNCTION NAME:   display_menu
 *
 * DESCRIPTION:     Displays the menu's choices. If debug mode is invoked, the function's
 *                  information will be printed.
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void display_menu(){

    printf("-------Menu-------\n");
    printf("1. Add a new record\n");
    printf("2. Modify a record\n");
    printf("3. Print a record\n");
    printf("4. Print all records\n");
    printf("5. Delete a record\n");
    printf("6. Quit\n");

    if (debugmode == 1){
        printf("\n[DEBUG]\n***Parameter Name: [display_menu]***\n-----Parameters-----\nNo Parameters\n");
        printf("************************************\n\n");
    }

}

/**************************************************************************************************
 *
 * FUNCTION NAME:   getField
 *
 * DESCRIPTION:     Allows the user to press enter and keep entering information until they type
 *                  in 'quit' in a new line. The information per line gets appended using strncat.
 *                  If debug mode is invoked, the functions information will be printed.
 *
 * PARAMETERS:      address(char):   Contains the user's string for their address.
 *                  x(int):          The maximum amount of chars to allocate.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void getField(char address[],int x){

    char line[x];

    while (fgets(line, x, stdin)) {

        if (strcmp(line, "quit\n") == 0) {
            break;
        }
        strncat(address, line, x - 1 - strlen(address));

    }

    if (debugmode == 1){
        printf("\n[DEBUG]\n***Parameter Name: [getField]***\n-----Parameters-----\n");
        printf("Address: %s\nAddress Size Cap:%d\n",address,x);
        printf("********************************\n\n");
    }
}

/**************************************************************************************************
 *
 * FUNCTION NAME:   clear
 *
 * DESCRIPTION:     Loops until the newline character grabbed. Which deals with input
 *                  errors for following user input.
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   None
 *************************************************************************************************/
void clear_line(){
    while (getchar() != '\n');
}
