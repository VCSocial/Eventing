#include <stdio.h>
#include "event.h"

int main () 
{
    printf("TEST\n");
    unsigned int id = create_event("Test Desc 0", "08:00", "08:05");

    print_event(id);

    return 0;
}
