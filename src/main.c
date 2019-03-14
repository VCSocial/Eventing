#include <stdio.h>
#include "event.h"

int main () 
{
    unsigned int id = create_event("Test Description 0", "08:00", "08:05");
    print_event(id);
    delete_event(id);
    print_event(id);

    return 0;
}
