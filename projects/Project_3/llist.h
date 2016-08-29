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
 * FILE:            llist.h
 *
 * DESCRIPTION:     This file contains all member class function prototypes for the llist class for 
 *                  Project 2.
 *
 *************************************************************************************************/
#ifndef llist_h
#define llist_h

#include "record.h"

using namespace std;

class llist
{
    
private:
    
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    record *    reverse(record * );
    void        cleanup();
    
public:
    
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int, char[], char[], int);
    int printRecord(int);
    int modifyRecord(int, char[]);
    void printAll();
    int deleteRecord(int);
    void reverse();
    int isEmpty();
    
    friend ostream& operator<<(ostream& os, const llist& v);
    
    llist(const llist&);
    llist& operator=(const llist&);
    
};

#endif
