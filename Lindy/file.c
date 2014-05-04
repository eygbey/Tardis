#include "competition.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void fgrab(char* s, FILE* file){
    char buffer;
    int i = 0;

    do
    {
        buffer = fgetc(file);

	//Check leading whitespace
	if( isspace(buffer) == 0 ){
            s[i] = buffer;
  	    i++;
	    //printf("%c",buffer);
	}else{
	    //printf(".");
	}
    }while( isspace(buffer) == 0 );

    s[i] = '\0';
} 

void fcreateEvent (struct Event** e, FILE* file) {   
  
    (*e)->nextEvent = NULL;
    (*e)->firstComp = NULL;
    (*e)->lastComp = NULL;

    char buffer[75];
    char buf;
    int index = 0;

    (*e)->numOfComps = 0;

    do
    {
	buf = fgetc(file);
	
	if( !isspace(buf)){
	    buffer[index] = buf;
	    index++;
	}
    }while(buf != '\n');

    buffer[index] = '\0';  

    strcpy((*e)->name,buffer);             //Copy buffer into object member(name)
    printf("Event: %s",(*e)->name);

    //return e;
}

void fcreateComp (struct Competition** comp, FILE* file){
    char f[20];
    char d[20];
    char dv[20];

    //struct Competition* comp = malloc(sizeof(struct Competition));

    (*comp)->firstContestant = (*comp)->lastContestant = NULL;
    (*comp)->nextComp = NULL;

    (*comp)->numOfContestants = 0;

    fgrab(f,file);
    strcpy((*comp)->format, f);       //Read Comp Format
    printf("Format: %s\n", (*comp)->format);

    fgrab(d,file);
    strcpy((*comp)->dance, d);        //Read Dance Type
    printf("Dance: %s\n", (*comp)->dance);

    fgrab(dv,file);
    strcpy((*comp)->division, dv);     //Read Comp Division
    printf("Division: %s\n", (*comp)->division);

    //return comp;
}

void fcreateCon (struct Contestant** c, FILE* file){
    //struct Contestant* c = malloc(sizeof(struct Contestant));

    (*c)->nextContestant = NULL;

    char first[30];
    char last[30];
    char r[10];
    char num[30];

    fgrab(first,file);     
    strcpy((*c)->firstName, first);
    printf("First Name: %s\n",(*c)->firstName);
   
    fgrab(last,file);
    strcpy((*c)->lastName, last);
    printf("Last Name: %s\n",(*c)->lastName);

    fgrab(r,file);
    strcpy((*c)->role, r);
    printf("Role: %s\n",(*c)->role);

    fgrab(num,file);
    (*c)->number = atoi(num);
    printf("Number: %d\n",(*c)->number);

    //return c;
}

readEvents(struct Event** ptr){
    
    FILE * pFile;
    pFile = fopen ( "events.txt" , "r" );
    if (pFile==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }

    struct Event* current;

    //Main Loop
    do
    {
	char buffer = fgetc(pFile);

 	if( feof(pFile) == 0 )
	{
	    switch(buffer)
	    {
	    	case '#':
	    	{
		    struct Event* e = malloc(sizeof(struct Event)); 
		    fcreateEvent(&e, pFile);
		    current = e;
	 	    break;
	    	}
	    	case '@':
	    	{
		    struct Competition* c = malloc(sizeof(struct Competition)); 
		    fcreateComp(&c, pFile);
		    loadComp(&current, c);
		    break;
	    	}
	    	default:
	    	{
		    ungetc(buffer, pFile);
		    struct Contestant* co = malloc(sizeof(struct Contestant));
		    fcreateCon(&co, pFile);
		    loadCon(&current, co);
		    break;
	    	}
	    }
	}		
  
    }while( feof(pFile) == 0 );//End of Main Loop

    *ptr = current;

    // terminate
    fclose (pFile);
}

void writeFile(struct Event* ptr){

    FILE * pFile;
    pFile = fopen ( "event.txt" , "w" );
    if (pFile==NULL) {            
        fputs ("File error",stderr);
        exit (1);
    }

    struct Event* nextEvnt = ptr;

    //Event Layer
    do
    {
	fputc('#', pFile); fputs(nextEvnt->name,pFile); fputc('\n', pFile);

        struct Competition* comp = nextEvnt->firstComp;

        //Competition Layer    
        do
        {
	    fputc('@', pFile);
            fputs(comp->format, pFile); fputc(' ', pFile);
            fputs(comp->dance, pFile); fputc(' ', pFile);
            fputs(comp->division, pFile); fputc('\n', pFile);

            struct Contestant* contestant = comp->firstContestant;    

            //Contestant Layer
            do
            {
                fputs(contestant->firstName, pFile); fputc(' ', pFile);
            	fputs(contestant->lastName, pFile); fputc(' ', pFile);
            	fputs(contestant->role, pFile); fputc(' ', pFile);

		char buffer[10]; sprintf(buffer,"%d", contestant->number);

		fputs(buffer, pFile); fputc('\n', pFile); 

                contestant = contestant->nextContestant;

            }while( contestant != NULL );

            comp = comp->nextComp;

        }while( comp != NULL );

        nextEvnt = nextEvnt->nextEvent;

    }while( nextEvnt != NULL );

    fclose(pFile);
}
