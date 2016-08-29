/**************************************************************************************************
 *
 * NAME:            Gabriel Viloria
 *
 * HOMEWORK:        Project 2
 *
 * CLASS:           ICS 212
 *
 * INSTRUCTOR:      Ravi Narayan
 *
 * DATE:            April 24, 2016
 *
 * FILE:            llist.cpp
 *
 * DESCRIPTION:     This file contains all member class function definitions for the llist class 
 *                  for Project 2. DEBUG is turned off by default. To turn it on, change them to:
 *               
 *                  #ifndef DEBUG 
 *                  #define DEBUG 1
 *                  #endif
 *
 *                  DO THE SAME FOR 'llist.cpp'.
 *
 *************************************************************************************************/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include "record.h"
#include "llist.h"

#define DEBUG 0
#ifndef DEBUG
#endif


using namespace std;

/************************************************************************************************
 *
 * FUNCTION NAME:   llist
 *
 * DESCRIPTION:     Class constructor
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
llist::llist(){
    
    strcpy(filename,"project.txt");
    start = NULL;
    readfile();
    
    if (DEBUG ==1) {
        cout << "\n[DEBUG]\n****llist::llist() called****" << endl;
        cout << "Constructor has been called" << endl;
        cout << "*******************" << endl;
    }
}

/************************************************************************************************
 *
 * FUNCTION NAME:   llist
 *
 * DESCRIPTION:     Class constructor.
 *
 * PARAMETERS:      *m(char) : The filename to be processed.
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
llist::llist(char m[]){
    
    start = NULL;
    readfile();
    
    if (DEBUG ==1) {
        cout << "\n[DEBUG]\n****llist::llist(char[]) called****" << endl;
        cout << "Parameter = filename: " << m << endl;
        cout << "Constructor has been called" << endl;
        cout << "*******************" << endl;
    }
}

/************************************************************************************************
 *
 * FUNCTION NAME:   llist
 *
 * DESCRIPTION:     Class destructor.
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
llist::~llist(){
    
    writefile();
    cleanup();
    
    if (DEBUG ==1) {
        
        cout << "\n[DEBUG]\n****llist::~llist() called****" << endl;
        cout << "[DEBUG] Destructor has been called" << endl;
    }
}

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
 * PARAMETERS:      uaccountno(int): The user's account number.
 *                  uname(char[]): The user's name.
 *                  uaddr(char[]): The user's address.
 *                  uyob(int): The user's year of birth.
 *
 * RETURN VALUES:   0: Success
 *
 *************************************************************************************************/
int llist::addRecord(int uaccountno,char uname[],char uaddr[],int uyob){
    
    struct record * toAdd = new record;
    toAdd->accountno = uaccountno;
    strcpy(toAdd->name, uname);
    strcpy(toAdd->address, uaddr);
    toAdd->yearofbirth = uyob;
    toAdd->next = NULL;
    
    if (start == NULL) {
        
        start = toAdd;
        
    } else {
        
        if (uaccountno < (start)->accountno) {
            
            toAdd->next = start;
            start = toAdd;
            
        } else {
            
            struct record * curr = start;
            
            while (curr->next != NULL && curr->next->accountno < uaccountno) {
                
                curr = curr->next;
            }
            
            toAdd->next = curr->next;
            curr->next = toAdd;
        }
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [addRecord]***\n-----Parameters-----\n" << endl;
        cout << "Account No: " << uaccountno << endl;
        cout << "Name: " << uname << endl;
        cout << "Address: " << uaddr << endl;
        cout << "Account No: " << uyob << endl;
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
 * PARAMETERS:      uaccountno(int): The user's account number.
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int llist::printRecord(int uaccountno){
    
    int found = 1;
    
    struct record *printOne = start;
    
    while(printOne != NULL){
        
        if(uaccountno == (printOne)->accountno){
        
            cout << "\n\n------------INFORMATION------------\n";
            cout << "[Account Number]\n"<< (printOne)->accountno << "\n\n";
            cout << "[Name]\n" << (printOne)->name << "\n" << endl;
            cout << "[Address]\n" << (printOne)->address << "\n";
            cout << "[Year Of Birth]\n" << (printOne)->yearofbirth << "\n\n\n";
            
            found = 0;
        }
        
        printOne = (printOne)->next;
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [printRecord]***\n-----Parameters-----\n" << endl;
        cout << "Account No.: " << uaccountno << endl;
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
 * PARAMETERS:      uaccountno(int): The user's account number.
 *                  name(char*): The user's name.
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int llist::modifyRecord(int uaccountno,char name[]){
    
    int found = 1;
    struct record * modify = start;
    
    while (modify != NULL){
        
        if (uaccountno == (modify)->accountno) {
            
            strncpy((modify)->name,name,sizeof((modify)->name));
            
            found = 0;
            
        }
        
        modify = (modify)->next;
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [modifyRecord]***\n-----Parameters-----\n" << endl;
        cout << "Account No.: " << uaccountno << endl;
        cout << "Name: " << name << endl;
    }

    return found;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   printAll
 *
 * DESCRIPTION:     Prints all records in the database.
 *                  Loops through each record in the database and prints out their information
 *                  while start is not NULL. After printing the initial set (if applicable)
 *                  it will point to the next record.
 *                  If debug mode is invoked, then the function's name and parameters will be sent.
 *                  However, since this is a pointer we don't need to print it out.
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void llist::printAll(){
    
    struct record * printAll = start;
    
    while (printAll != NULL){
        
        cout << "\n\n------------INFORMATION------------\n";
        cout << "[Account Number]\n" << (printAll)->accountno << "\n\n";
        cout << "[Name]\n" << (printAll)->name << "\n" << endl;
        cout << "[Address]\n" << (printAll)->address << "\n";
        cout << "[Year Of Birth]\n" << (printAll)->yearofbirth << "\n\n";
        
        printAll = (printAll)->next;
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [printAll]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
        
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
 * PARAMETERS:      uaccountno(int): The account number of the user.
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int llist::deleteRecord(int uaccountno){
    
    int found = 1;
    
    while (start != NULL && (start)->accountno == uaccountno) {
        
        struct record *toDelete = start;
        start = (start)->next;
        free(toDelete);
        
        found = 0;

    }
    
    if (start != NULL) {
        
        struct record *curr = start;
        
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
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [deleteRecord]***\n-----Parameters-----\n" << endl;
        cout << "Account No.: " << uaccountno << endl;
    }

    return found;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   reverse
 *
 * DESCRIPTION:     Will reverse the linked list.
 *
 * PARAMETERS:      head(record *): the record to be processed.
 *
 * RETURN VALUES:   A record or NULL.
 *
 *************************************************************************************************/
record * llist::reverse(record * head){
    
    if (head == NULL){
        return NULL;
        
    } else if (head->next == NULL){
        return head;
        
    } else {
        
        struct record * tail = head->next;
        head->next = NULL;
        
        struct record * reversed = reverse(tail);
        tail->next = head;
        return reversed;
        
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [record * reverse]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
        
    }
    
}

/************************************************************************************************
 *
 * FUNCTION NAME:   reverse
 *
 * DESCRIPTION:     Initializes start as the reversed version of start.
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void llist::reverse(){
    
    start = reverse(start);
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [reverse]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
    }
    
}

/************************************************************************************************
 *
 * FUNCTION NAME:   cleanup
 *
 * DESCRIPTION:     Will clean up allocated space.
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
void llist::cleanup(){
    
    struct record * toFree = start;
    
    while(toFree != NULL){
        
        toFree = (start)->next;
        delete start;
        start = toFree;
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [cleanup]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
    }
}

/************************************************************************************************
 *
 * FUNCTION NAME:   readfile
 *
 * DESCRIPTION:     Will read the input file (if it exists) and store the appropriate information
 *                  into the appropriate variables within the struct and add the record until there
 *                  is nothing else to read in the file. Address is read up until "***ENDADDRESS***"
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int llist::readfile() {
    
    ifstream fin(filename);
    string line;
    
    if (fin.is_open()){
        
        while (getline(fin, line)) {
        
            int accountno = atoi(line.c_str());
            getline(fin, line);
            int yob = atoi(line.c_str());
            getline(fin, line);
            string name = line;
            string address = "";
        
            while (getline(fin, line) && line != "***ENDADDRESS***") {
                address += line;
                address += "\n";
            }
        
            addRecord(accountno, (char*) name.c_str(), (char*) address.c_str(), yob);
        }
    
    }
    
    fin.close();
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [readfile]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
        
    }
    
    return 0;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   writefile
 *
 * DESCRIPTION:     Will write every record to file. Address is written till "***ENDADDRESS***".
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   0: Success
 *                  1: Failure
 *
 *************************************************************************************************/
int llist::writefile() {
    
    
    ofstream fout(filename,ios::out);
    
    struct record * current = start;
    
    if (fout.is_open()){
        
        while (current != NULL) {
        
            fout << current->accountno << endl;
            fout << current->yearofbirth << endl;
            fout << current->name << endl;
            fout << current->address;
            fout << "***ENDADDRESS***" << endl;

            current = current->next;
            
        }
    
    fout.close();
        
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [writefile]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
        
    }
    
    return 0;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   ostream& operator<<
 *
 * DESCRIPTION:     Overloaded << operator function which is used in place of printAll.
 *
 * PARAMETERS:      os(ostream&): A reference to an object of type std::ostream
 *                  v(const llist&): A reference to an const object of type llist
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
ostream& operator<<(ostream& os, const llist& v){
    
    struct record * overload = v.start;
    
    while(overload != NULL){
        
        os << "\n\n------------INFORMATION------------\n";
        os << "[Account Number]\n" << overload->accountno << "\n\n";
        os << "[Name]\n" << overload->name << "\n\n";
        os << "[Address]\n" << overload->address << "\n";
        os << "[Year Of Birth]\n" << overload->yearofbirth << "\n\n\n";
        
        overload = overload->next;
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [ostream& operator<<]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
        
    }
    
    return os;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   llist
 *
 * DESCRIPTION:     Copy constructor. Creates a llist object 'head' by initializing it with an object
 *                  of the same class 'start', which has been created previously.
 *
 * PARAMETERS:      copy(const llist&): A reference to an const object of type llist
 *
 * RETURN VALUES:   None
 *
 *************************************************************************************************/
llist::llist(const llist& copy){
    
    start = NULL;
    struct record * head = copy.start;
    
    while (head != NULL){
        
        addRecord(head->accountno, head->name, head->address, head->yearofbirth);
        head = head->next;
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [llist (copy constructor)]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
        
    }
}

/************************************************************************************************
 *
 * FUNCTION NAME:   llist& llist::operator=
 *
 * DESCRIPTION:     Overloaded assignment operator. All values of start are copied to the new 
 *                  object head.
 *
 * PARAMETERS:      asgn(const llist&): A reference to an const object of type llist
 *
 * RETURN VALUES:   Copy constructor
 *
 *************************************************************************************************/
llist& llist::operator=(const llist& asgn){
    
    cleanup();
    
    start = NULL;
    struct record * head = asgn.start;
    
    while (head != NULL){
        
        addRecord(head->accountno, head->name, head->address, head->yearofbirth);
        head = head->next;
    }
    
    if (DEBUG == 1){
        
        cout << "\n[DEBUG]\n***Parameter Name: [llist (overloaded asssignment constructor)]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
        
    }
    
    return *this;
}

/************************************************************************************************
 *
 * FUNCTION NAME:   isEmpty
 *
 * DESCRIPTION:     Checks if there are records.
 *
 * PARAMETERS:      None
 *
 * RETURN VALUES:   0: Not empty
 *                  1: Empty
 *
 *************************************************************************************************/
int llist::isEmpty(){
    
    if (start == NULL){
        return 1;
    }
    
    
    if (DEBUG ==1){
        cout << "\n[DEBUG]\n***Parameter Name: [isEmpty]***\n-----Parameters-----\n" << endl;
        cout << "No Parameters" << endl;
    }
    
    return 0;
    
}
