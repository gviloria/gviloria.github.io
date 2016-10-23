/**************************************************************************************************
 *
 * NAME:            Gabriel Viloria
 *
 * DATE:            March 4, 2016
 *
 * DESCRIPTION:     This file contains the driver and necessary functions for Project 2. The
 *                  program is a user-interface for a bank database application which allows
 *                  the user to: add a new record in the database, modify a record in the database,
 *                  print information about a record using the account as a key, print all
 *                  information in the database, delete an existing record from the database
 *                  using the account no as a key, and the ability to quit the program.
 *
 *************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "database.h"

extern int debugmode;

int addRecord(struct record **,int, char[],char[],int);
int printRecord(struct record *, int);
int modifyRecord(struct record *, int, char[]);
void printAllRecords(struct record *);
int deleteRecord(struct record **,int);

/************************************************************************************************
 *
 * FUNCTION NAME:   addRecord
 *
 * DESCRIPTION:     Adds a record into the bank database and sorts the records in ascending
 *                  order using their accountno. This function copies the information
 *                  entered by the user and copies it into their respective data types and then
 *                  into the singly linked list. If start is NULL, then it will set the 
 *                  record as the first linked list. If start isn't  NULL, and the account
 *                  number entered by the user is less than any of the records on the linked list,
 *                  they will switch positions. The final while loop makes sure that if it is larger,
 *                  then it will go through the list to find a spot where it isnt greater than the
 *                  next record in the list.
 *
 * PARAMETERS:      start(struct **record): A pointer of a pointer to the structure of type record.
 *                  uaccountno(int): The user's account number.
 *                  uname(char*): The user's name.
 *                  uaddr(char*): The user's address.
 *                  uyob(int): The user's year of birth.
 *
 * RETURN VALUES:   0: Success
 *
 *************************************************************************************************/
int addRecord(struct record ** start,int uaccountno, char uname[], char uaddr[],int uyob) {

    struct record *toAdd = malloc(sizeof(struct record));
    toAdd->accountno = uaccountno;
    strcat(toAdd->name, uname);
    strcat(toAdd->address, uaddr);
    toAdd->yearofbirth = uyob;

    if (*start == NULL) {

        *start = toAdd;

    } else {

        if (uaccountno < (*start)->accountno) {

            toAdd->next = *start;
            *start = toAdd;

        } else {

            struct record *curr = *start;

            while (curr->next != NULL && curr->next->accountno < uaccountno) {

                curr = curr->next;
            }

            toAdd->next = curr->next;
            curr->next = toAdd;
        }
    }

    if (debugmode == 1) {
        printf("\n[DEBUG]\n***Parameter Name: [addRecord]***\n-----Parameters-----\n");
        printf("Account No.:%d\nName:%s\nAddress:%s\nYear Of Birth:%d\n", uaccountno, uname, uaddr, uyob);
        printf("*********************************\n\n");
    }

    return 0;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   printRecord
 *
 * DESCRIPTION:     Prints a record when given the account number.
 *                  While start isn't null, it will loop through each record to see
 *                  if the account number enter from the user matches one with the database.
 *                  If it's a match it will print that record, and all records with the same
 *                  account number.
 *
 * PARAMETERS:      new(struct *record): A pointer to the structure of type record.
 *                  accountno(int): The user's account number.
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int printRecord(struct record * start, int uaccountno){

    int found = 1;

    while (start){

        if (uaccountno == (start)->accountno) {

            printf("\n\n------------INFORMATION------------\n");
            printf("[Account Number]\n%d\n\n",(start)->accountno);
            printf("[Name]\n%s\n",(start)->name);
            printf("[Address]\n%s\n",(start)->address);
            printf("[Year Of Birth]\n%d\n",(start)->yearofbirth);
            
            found = 0;
        }

        start = start->next;
    }

    if (debugmode == 1) {
        printf("\n[DEBUG]\n***Parameter Name: [printRecord]***\n-----Parameters-----\nAccount No.:%d\n", uaccountno);
        printf("***********************************\n\n");
    }

    return found;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   modifyRecord
 *
 * DESCRIPTION:     Modifies a record when given the account number, and allows the user
 *                  to change their name.
 *                  While start is not null, it will loop through each record and if it matches
 *                  it will change the current name in the record to the new name entered by the
 *                  user.
 *
 * PARAMETERS:      start(struct record): The structure of type record.
 *                  uaccountno(int): The user's account number.
 *                  name(char*): The user's name.
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int modifyRecord(struct record * start, int uaccountno, char name[]){

    int found = 1;

    while (start){

        if (uaccountno == (start)->accountno) {

            strncpy((start)->name,name,sizeof((start)->name));

            found = 0;
        }

        start = start->next;
    }
    if (debugmode == 1) {
        
        printf("\n[DEBUG]\n***Parameter Name: [modifyRecord]***\n");
        printf("-----Parameters-----\nAccount No.:%d\nName:%s\n",uaccountno,name);
        printf("**************************************\n\n");
    }

    return found;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   printAllRecords
 *
 * DESCRIPTION:     Prints all records in the database.
 *                  Loops through each record in the database and prints out their information
 *                  while start is not NULL. After printing the initial set (if applicable)
 *                  it will point to the next record.
 *                  If debug mode is invoked, then the function's name and parameters will be sent.
 *                  However, since this is a pointer we don't need to print it out.
 *
 * PARAMETERS:      start(struct *record): A pointer to the structore of type record.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void printAllRecords(struct record * start){

    while (start){

        printf("\n\n------------INFORMATION------------\n");
        printf("[Account Number]\n%d\n\n",(start)->accountno);
        printf("[Name]\n%s\n",(start)->name);
        printf("[Address]\n%s\n",(start)->address);
        printf("[Year Of Birth]\n%d\n",(start)->yearofbirth);

        start = start->next;
    }

    if (debugmode == 1) {
        
        printf("\n[DEBUG]\n***Parameter Name: [printAllRecords]***\n-----Parameters-----\nNone:(Only pointer)\n");
        printf("***************************************\n\n");
        
    }
}

/************************************************************************************************
 *
 * FUNCTION NAME:   deleteRecords
 *
 * DESCRIPTION:     Deletes a record in the database when given the account number.
 *                  The first while loop checks to see whether strat is null AND
 *                  if the account number entered by the user matches the current record's
 *                  account number; if TRUE then it deletes that record and point to the next
 *                  record in the linked list. If start isn't NULL and while the next record
 *                  isn't null, and if the next record's account number matches that of the
 *                  one entered by the user, we will delete that record and point to the record
 *                  after the next record, and free that record. If not then, it will point to 
 *                  the next record.
 *                  If debug mode is invoked, then it will display the account number entered
 *                  and the function's name.
 *
 * PARAMETERS:      start(struct *record): A pointer to the structure of type record.
 *                  uaccountno(int): The account number of the user.
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int deleteRecord(struct record ** start, int uaccountno){

    int found = 1;

    while (*start != NULL && (*start)->accountno == uaccountno) {

        struct record *toDelete = *start;
        *start = (*start)->next;
        free(toDelete);

        found = 0;
    }

    if (*start != NULL) {

        struct record *curr = *start;

        while (curr->next != NULL) {

            if (curr->next->accountno == uaccountno) {

                struct record *toDelete = curr->next;
                curr->next = curr->next->next;
                free(toDelete);

                found = 0;

            } else {

                curr = curr->next;
            }
        }
    }

    if (debugmode == 1) {
        
        printf("\n[DEBUG]\n***Parameter Name: [deleteRecord]***\n-----Parameters-----\nAccount No.:%d\n",uaccountno);
        printf("************************************\n\n");
        
    }

    return found;
}

