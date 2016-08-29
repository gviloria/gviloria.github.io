/**************************************************************************************************
 *
 * NAME:            Gabriel Viloria
 *
 * DESCRIPTION:     The
 *                  program is a user-interface for a bank database application which allows
 *                  the user to: add a new record in the database, modify a record in the database,
 *                  print information about a record using the account as a key, print all
 *                  information in the database, delete an existing record from the database
 *                  using the account no as a key, and the ability to quit the program.
 *
 *************************************************************************************************/
#include <iostream>
#include <cstring>
#include "llist.h"
#include "record.h"

#define DEBUG 0
#ifndef DEBUG
#endif

using namespace std;

void display_menu();
void run_menu(char[],int);
void get_input(char[],int&);
void getField(char[],int);
int isInteger(char[]);

int main(int argc, const char * argv[]) {
    
    char decision[10];
    int choice;
    
    if (DEBUG == 1){
        
        cout << "\n\n*****DEBUG MODE HAS BEEN ENABLED*****\n\n" << endl;
        
    } else {
        
        cout << "\n\n*****DEBUG MODE IS OFF*****\n\n" << endl;
    }
    
    display_menu();
    get_input(decision,choice);
    
    while (!isInteger(decision) || choice < 1 || choice > 7){
        
        display_menu();
        cout << "That is not a valid choice.\n" << endl;
        get_input(decision, choice);
        
    }
    
    run_menu(decision,choice);
    
    cout << "\n\nProgram now closing. . .\n" << endl;
    
    return 0;
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
 *                  &decision(int):   The choice of the user after bring processed.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void get_input(char decision[],int& choice){
    
    cout << "\nPlease enter the number of an option: " << endl;
    cin >> decision;
    cin.ignore();
    
    if (isInteger(decision))
    {
        choice = atoi(decision);
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [get_input]***\n-----Parameters-----" << endl;
        cout << "char *decision: " << decision;
        cout << "\nint& choice: " << choice;
        cout << "\n********************************\n\n";
    }
}

/**************************************************************************************************
 *
 * FUNCTION NAME:   run_menu
 *
 * DESCRIPTION:     Runs the menu and it's functions within a while loop. If the choice is 1
 *                  it adds a record, 2: modifies a record and allow the user to change the NAME,
 *                  3: prints a record and prints all duplicates with same account number
 *                  4: prints all records, 5: deletes a record, 6: reverses the list 
 *                  and 7: exits the loop and thus
 *                  ending the program. Afterwards, the program will write all records to file
 *                  and will clear all of the allocated memory (if any).
 *                  If debug mode is invoked, it will display the function name,
 *                  it's parameters, and what it received.
 *                  If debug mode is invoked, the functions information will be printed.
 *                  There is a bad input check for year of birth and accountno.
 *
 * PARAMETERS:      decision(char[]):  Contains the user's input which will be processed to
 *                                    be the user's choice.
 *                  choice(int):      The user's choice for the menu whose range is 1-6.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void run_menu(char decision[],int choice){
    
    llist mylist2("projectnon.txt");
    llist mylist;
    
    int accountno = 0;
    char name[25] = {0};
    char address[80] = {0};
    int yearofbirth = 0;
    char yearinput[10] = {0};
    char info[100] = {0};
    int x = 80;

    while (choice != 7){
        
        while (!isInteger(decision) || choice < 1 || choice > 7){
            
            display_menu();
            cout << "That is not a valid choice." << endl;
            get_input(decision, choice);
            
        }
        
        if (choice == 1){
            
            cout << "Please create your own account number: " << endl;
            cin.getline(info,100);
            
            while(!isInteger(info)){
                
                cout << "\nThat is not a valid account number.\n" << endl;
                cout << "Please create your own account number:" << endl;
                
                cin.getline(info,100);
            }
            
            accountno = atoi(info);
            
            cout << "Please enter your name: " << endl;
            cin.getline(name,25);
            
            cout << "Please enter your address:" << endl;
            cout << "(To finish your input, make a new line after your input and enter 'quit')" << endl;
            getField(address,x);
            
            cin.ignore();
            
            cout << "Please enter your year of birth: " << endl;
            cin.getline(yearinput,10);
            
            while(strlen(yearinput) != 4 || !isInteger(yearinput)){
                
                printf("Not a valid year of birth. Please try again:");
                cin.getline(yearinput,10);
                
            }
            
            yearofbirth = atoi(yearinput);
            
            mylist.addRecord(accountno,name,address,yearofbirth);
            
        }
        
        else if (choice == 2){
            
            if (mylist.isEmpty() == 1){
                cout << "\n\nThere is no record to modify at the moment.\n\n" << endl;
            
            } else {
                
                cout << "\nPlease enter the account number you want to modify: " << endl;
                cin.getline(info,100);
            
                while(!isInteger(info)){
                
                    cout << "\nThat is not a valid account number.\n" << endl;
                    cout << "Please create your own account number:" << endl;
                
                    cin.getline(info,100);
                }
            
                accountno = atoi(info);
            
                cout << "\nPlease enter your name: " << endl;
                cin.getline(name,25);
            
                if (mylist.modifyRecord(accountno,name) == 1){
                
                    cout << "\n\n\nThere were no matching records with the given account number\n\n\n" << endl;
                }
                
            }
            
        }
        
        else if (choice == 3){
            
            if (mylist.isEmpty() == 1){
                cout << "\n\nThere is no record to view at the moment.\n\n" << endl;
                
            } else {
                
                cout << "\nPlease enter your account number you want to view: " << endl;
                cin.getline(info,100);
            
                while(!isInteger(info)){
                
                    cout << "\nThat is not a valid account number.\n" << endl;
                    cout << "Please create your own account number:" << endl;
                
                    cin.getline(info,100);
                }
            
                accountno = atoi(info);
            
                if (mylist.printRecord(accountno) == 1){
                
                    cout << "\n\n\nThere were no matching records with the given account number\n\n\n" << endl;
                }
            }
            
        }
        
        else if (choice == 4){
            
            if (mylist.isEmpty() == 1){
                cout << "\n\nThere is no record to print at the moment.\n\n" << endl;
            
            } else {
    
                cout << "\n---------------ALL RECORDS---------------" << endl;
                cout << mylist;
            }
            
        }
        
        else if (choice == 5){
            
            if (mylist.isEmpty() == 1){
                
                cout << "\n\nThere is no record to delete at the moment.\n\n" << endl;
                
            } else {
            
                cout << "\nPlease enter the account number you wish to delete: " << endl;
                cin.getline(info,100);
            
                while(!isInteger(info)){
                
                    cout << "\nThat is not a valid account number.\n" << endl;
                    cout << "Please create your own account number:" << endl;
                
                    cin.getline(info,100);
                }
            
                accountno = atoi(info);
            
                if (mylist.deleteRecord(accountno) == 1){
                
                    cout << "\n\n\nThere were no matching records with the given account number\n\n\n" << endl;
                }
                
            }
            
        }
        
        else if (choice == 6){
            
            if (mylist.isEmpty() == 1){
                
                cout << "\n\nThere is no record to reverse at the moment.\n\n" << endl;
                
            } else {
                
                mylist.reverse();
                cout << "\nThe list has been reversed \n" << endl;
            }
            
        }
        
        display_menu();
        get_input(decision,choice);
    
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [run_menu]***\n-----Parameters-----" << endl;
        cout << "char *decision: " << decision;
        cout << "\nint& choice: " << choice;
        cout << "\n********************************\n\n";
        
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
 * PARAMETERS:      input(char[]):    Contains the user's input which will be processed.
 *
 * RETURN VALUES:   1: The user's input is valid
 *                  0: The user's input is not valid
 *
 *************************************************************************************************/
int isInteger(char input[]) {
    
    int valid = 1;
    int i;
    
    for (i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
        {
            valid = 0;
            break;
        }
    }
    
    return valid;
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [isInteger]***\n-----Parameters-----" << endl;
        cout << "char *input: " << input << endl;
        cout << "*********************************\n\n" << endl;
        
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
void getField(char address[], int x){
    
    char line[80] = {0};
    char append[10] = {'\n'};
    
    do {
        
        cin.get(line,x);
        
        if (strcmp(line, "quit") == 0) {
            break;
        }
        
        strncat(address, line, x - 1 - strlen(address));
        strncat(address, append, x - 1 - strlen(address));
        
    } while (getchar() != '*');
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [getField]***\n-----Parameters-----" << endl;
        cout << "Address: " << address << endl;
        cout << "Int: " << x << endl;
    }

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
    
    cout << "-------Menu-------" << endl;
    cout << "1. Add a new record" << endl;
    cout << "2. Modify a record" << endl;
    cout << "3. Print a record" << endl;
    cout << "4. Print all records" << endl;
    cout << "5. Delete a record" << endl;
    cout << "6. Reverse the list" << endl;
    cout << "7. Quit" << endl;
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [display_menu]***\n-----Parameters-----" << endl;
        cout << "No Parameters" << endl;
    }
    
}
