#include <stdio.h>
#include <string.h>
#include "record.h"
#include "iofunctions.h"
#include "database.h"

int readfile(struct record **, char []);
void writefile(struct record *, char []);

/************************************************************************************************
 *
 * FUNCTION NAME:   readfile
 *
 * DESCRIPTION:     Reads a file. First we create a file pointer called fp. Afterwards, we set
 *                  that to fopen which opens the file. The first parameter of fopen is the
 *                  name of the file that is to be opened and the second parameter is the mode.
 *                  In this case, "r" means 'Open a file for reading', nothing else.
 *
 *                  The while loop runs on the condition of the first data we're reading in
 *                  which is accountno. If fscanf reads 0, that means that there is no other
 *                  'record' to read from the txt file.
 *
 *                  The information is gathered respectively and afterwards is sent to
 *                  addRecord to be put into a linked list.
 *
 *                  Finally, we close the file with fclose since we are done reading it.
 *
 * PARAMETERS:      new(struct *account): A pointer to the structure of type account.
 *                  numcust(int*): The max capacity of the struct array.
 *                  filename(char*): The name of the file to be opened.
 *
 * RETURN VALUES:   1: Failure
 *                  0: Success
 *
 *************************************************************************************************/
int readfile(struct record ** start, char filename[]){

    FILE *fp = NULL;
    fp = fopen(filename,"r");

    int accountno = 0;
    char name[25] = { 0 };
    char address[80] = { 0 };
    int yearofbirth = 0;
    char line[80] = { 0 };
    int opened = 1;

    if (fp == NULL){

        opened = 1;

    } else {

        opened = 0;

        while (fscanf(fp, "%d\n", &accountno) > 0) {

	    strncpy(name,"",sizeof(name)-1);            
        fgets(name, 25, fp);
            
            while (fgets(line, 80, fp)) {
                
                if (strcmp(line, "*\n") == 0) {
                    
                    strncpy(line,"",sizeof(line)-1);
                    break;
                    
                }
                
                strncat(address, line, 79 - strlen(address));
                strncpy(line,"",sizeof(line)-1);
            }

        fscanf(fp, "%d", &yearofbirth);

        addRecord(start, accountno, name, address, yearofbirth);

	    strncpy(line,"",sizeof(line)-1);
	    strncpy(address,"",sizeof(address)-1);
	    strncpy(name,"",sizeof(name)-1);
            
        }
    }

    if (opened != 1){
    fclose(fp);
    }

    return opened;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   writefile
 *
 * DESCRIPTION:     This function writes information inputted information from the user
 *                  into the .txt file (if any). It creates a file pointer like the readfile,
 *                  but this time instead of "r" as the second parameter for fopen, we use "w"
 *                  which creates an empty file for writing into.
 *
 *                  The loop goes through the linked list until all of the records have been
 *                  printed.
 *                  (accountno)
 *                  (name)
 *                  (address)
 *                  *
 *                  (yearofbirth)
 *
 *
 * PARAMETERS:      start(struct *account): A pointer to the structure of type record.
 *                  filename(char*): The name of the file to be opened.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void writefile(struct record * start, char filename[]) {

    FILE *fp = NULL;
    fp = fopen(filename, "w");

    if (fp == NULL){

        printf("\n\nFile '%s' unable to be opened.\n\n",filename);

    } else {

        while (start != NULL) {

            fprintf(fp, "%d\n", start->accountno);
            fprintf(fp, "%s", start->name);
            fprintf(fp, "%s*\n", start->address);
            fprintf(fp, "%d\n", start->yearofbirth);
            start = start->next;

        }
    }
    fclose(fp);
}

