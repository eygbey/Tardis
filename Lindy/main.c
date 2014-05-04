#include "competition.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    struct Event* ptr;

    readEvents(&ptr);

    menu(ptr);

    writeFile(ptr);

    return 0;
}
