#include "competition.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void reallocateMemory(struct Event*);
void freeMemory(struct Event*,int);
struct Competition createComp();
void createContestant(struct Contestant**);
void displayEvents(struct Event*);
void fgrab(char*, FILE*);
void readEvents(struct Event**);
void writeFile();
void menu(struct Event*);

//Memory Management Functions
void loadCon(struct Event**, struct Contestant*);
void loadComp(struct Event**, struct Competition*);

void menu(struct Event* ptr){

    char choice;

    do
    {
        printf("A. Create a New Event\n");
        printf("B. Create a New Competition\n");
        printf("C. Add a Contestant\n");
        printf("D. Display Events\n");
        printf("E. \n");
        printf("F. Exit the Program\n");
        printf("Enter A Choice: ");

        choice = fgetc(stdin);fgetc(stdin);

        switch(choice)
        {
            case 'A': case 'a':
                break;
            case 'B': case 'b':
                break;
            case 'C': case 'c':
	    {
		struct Contestant* c = malloc(sizeof(struct Contestant));
		createContestant(&c);
		loadCon(&ptr, c);
                break;
	    }
            case 'D': case 'd':
                displayEvents(ptr);
                break;
        }
    }while(choice != 'F' && choice != 'f');
}

//Creates a competition
struct Competition createComp() {
    char choice;
    //Create a new object
    struct Competition comp;
    //Menu
    printf("A. Lindy Hop");
    printf("B. Charleston");
    printf("C. Blues");
    printf("D. Balboa");
    
    choice = fgetc(stdin);fgetc(stdin);
  
    switch(choice)
    {
        case 'A': case 'a':
            strcpy(comp.dance,"Lindy");
            break;
        case 'B': case 'b':
            strcpy(comp.dance,"Charleston");
            break;
        case 'C': case 'c':
            strcpy(comp.dance,"Blues");
            break;
        case 'D': case 'd':
            strcpy(comp.dance,"Balboa");
            break;
    	default:
            printf("INVALID CHOICE: PLEASE CHOOSE AGAIN\n\n");
            break;              
    }

    printf("A. Strict");
    printf("B. Open");
    printf("C. Jack and Jill");
    
    choice = fgetc(stdin);fgetc(stdin);
    while(choice < 5 || choice > 0)
    {
        switch(choice)
        {
            case 'A': case 'a':
                strcpy(comp.format,"Strictly");
                break;
            case 'B': case 'b':
                strcpy(comp.format,"Open");
                break;
            case 'C': case 'c':
                strcpy(comp.format,"JJ");
                break;
            default:
                printf("INVALID CHOICE: PLEASE CHOOSE AGAIN: ");
                break;              
        }
    }
    
    printf("A. Beginner");
    printf("B. Intermediate");
    printf("C. Advanced");
    printf("D. All Star");
    printf("E. Invitational");
    
    choice = fgetc(stdin);fgetc(stdin);//Eats newline char
    while(choice < 5 || choice > 0)
    {
        switch(choice)
        {
            case 'A': case 'a':
                strcpy(comp.division,"Beginner");
                break;
            case 'B': case 'b':
                strcpy(comp.division,"Intermediate");
                break;
            case 'C': case 'c':
                strcpy(comp.division,"Advanced");
                break;
            case 'D': case 'd':
                strcpy(comp.division,"Allstar");
                break;
            case 'E': case 'e':
                strcpy(comp.division,"Invitational");
                break;
            default:
                printf("INVALID CHOICE! PLEASE CHOOSE AGAIN: ");
                choice = fgetc(stdin);fgetc(stdin);//Eats newline char
                break;              
        }
    }
    
    return comp;
}

void createContestant(struct Contestant** contestant) {
    
    printf("First Name: ");
    gets( (*contestant)->firstName );

    printf("Last Name: ");
    gets( (*contestant)->lastName );    

    char buffer[10];

    printf("Competitor's Number: ");
    gets( buffer );
    (*contestant)->number = atoi(buffer);

    printf("Competitor's Role: "); 
    gets( (*contestant)->role );   
}

void displayEvents(struct Event* ptr){
    struct Event* nextEvnt = ptr;

    //Event Layer
    do
    {
	printf("Event Name: %s", nextEvnt->name);
	printf("Number of Competitions: %d\n", nextEvnt->numOfComps);
	printf("================================================\n");

	struct Competition* comp = nextEvnt->firstComp;

	//Competition Layer
	do
	{
	    printf("  Division: %s\n", comp->division);
	    printf("  Dance: %s\n", comp->dance);
	    printf("  Format: %s\n", comp->format);
	    printf("  Number of Contestants: %d\n", comp->numOfContestants);
	    printf("------------------------------------------------\n");
 
	    struct Contestant* contestant = comp->firstContestant;

	    //Contestant Layer
	    do
	    {
            	printf("    First Name: %s\n", contestant->firstName);
            	printf("    Last Name: %s\n", contestant->lastName);
            	printf("    Role: %s\n", contestant->role);
            	printf("    Number: %d\n\n", contestant->number);

		contestant = contestant->nextContestant;

	    }while( contestant != NULL );

	    comp = comp->nextComp;

	}while( comp != NULL );

	printf("\n\n");

	nextEvnt = nextEvnt->nextEvent;
    }while( nextEvnt != NULL );
}



