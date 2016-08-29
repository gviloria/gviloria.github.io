---
layout: project
type: project
image: images/bank.png
title: Bank Database
permalink: projects/micromouse
date: 2016
labels:
  - C
summary: A bank database application that allows the user to add/delete/edit bank accounts. 
---

[Project Link](https://github.com/gviloria/gviloria.github.io/tree/master/projects/Project_1)

   The program is able to run in (2) modes - DEBUG & NORMAL
   By default the program runs NORMAL MODE. In order to to run DEBUG mode: in the command line
   you need to append "debug" after the project name like so - "./gvproject1 debug".
   DEBUG allows the user to see what functions are being passed as well as the values.
   
   Upon opening the program, the user will have 6 choices:
   
* Add a new record
* Modify a record
* Print a record
* Print all records
* Delete a record
* Quit
   
   When the user adds a record [CHOICE (1)], they will be prompted to provide:
   - A customized account number
   - Name
   - Address
   - Birth year
   
   When the user modifies a record [CHOICE (2)], they will be prompted to provide:
   - The account number associated with the account
     * If this is successful and the program is able to find a match:
       - The user will be given the opportunity to change their name
   
   When the user prints a record [CHOICE (3)], they will be prompted to provide:
   - The account number associated with the account
     * If this is successful and the program is able to find a match:
       - The user will display all data stored such as their name, address, account number, and birth year
  
   When the user prints all records [CHOICE (4)],
   - All data stored will be displayed in ascending order according to their account number.
   
   When the user deletes a record [CHOICE (5)], they will be prompted to provide:
   - The account number associated with the account
     * If this is successful and the program is able to find a match:
       - The account will be deleted.
  
  And when [CHOICE (6)] is chosen, the program will write to file and quit the program.


