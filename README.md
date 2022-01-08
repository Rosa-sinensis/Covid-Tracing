# Covid Tracing Database - First Year UG Project
This is my first year UG project, which is to build a database for covid tracing app in C language.

### Goal
Set up a database for a covid tracing app using knowledge learned throughout the lecture.
Plus, the data structure need to be done using both linked list and binary tree, so comparison of the tradeoff can be made

### How it works?
1. Each user can check-in to place that is listed by the app (ICBD-1).
2. If the user is new, meaning his/her name is not in the database yet, he/she need to register to the app by simply inputting his/her name to the system.
3. The user then will be given an ID (ICBD-2). 
4. The data input by the user will be saved in database and can be accessed for analysis purposes.
5. Dev can see which person has been to a particular place or simply see all of the record in database.

### Implementation
Linked list and binary tree method is implemented for the data structure.
For the binary tree, dsw algorithm is used as the sorting algorithm

### Future Plan
- Clean the code; segregating function into different subsections and header file.
- Adding new features, especially the ones highlighted in the ICBD part.


### ICBD - Improvement Can Be Done
ICBD 1: If the place that a user want to set is not in the list, the user can just input it into the system and the database will create the target place. The target place then can be accessed by anyone in the future.

ICBD 2: The ID is quite useless, as far as I know. Initially, the ID is designed for differentiating between user that has two same name. However, implementing this features would affect significantly the other part of codes, meaning a considerable amount of effort and time need to be invested. To put it simply, grade-to-effort ratio for creating this feature is not enticing.


* Any feedback, suggestion or improvement that can be made is much welcome. :)
