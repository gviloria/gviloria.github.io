/**************************************************************************************************
 *
 * NAME:            Gabriel Viloria
 *
 * HOMEWORK:        Project 1
 *
 * CLASS:           ICS 212
 *
 * INSTRUCTOR:      Ravi Narayan
 *
 * DATE:            March 4, 2016
 *
 * FILE:            record.h
 *
 * DESCRIPTION:     This file contains the record structure which contains information about
 *                  a users account number, name, address, year of birth, and a pointer to the
 *                  next record.
 *
 *************************************************************************************************/
extern int debugmode;

struct record
{
    int accountno;
    char name[25];
    char address[80];
    int yearofbirth;
    struct record* next;
};

