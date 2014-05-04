#ifndef COMPETITION_H
#define COMPETITION_H

struct Event {
    char name[75];
    int numOfComps;
    //Competition Linked list to first Competition     
    struct Competition* firstComp;
    struct Competition* lastComp;
    struct Event* nextEvent;
};

struct Competition {       
    char format[15];
    char dance[10];
    char division[15];
    int numOfContestants;
    
    //Linked List to first competitor and next competition
    struct Contestant* firstContestant;
    struct Contestant* lastContestant;
    struct Competition* nextComp;
};

struct Contestant {
    char role[7];
    int number;
    char firstName[30];
    char lastName[30];

    struct Contestant* nextContestant;
};

#endif
