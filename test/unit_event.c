#include "../src/event.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>

Test(simple, test) {
  cr_log_info("Create new event, and assert that id is greater than 0");
  unsigned int id = create_event("TEST", "09:42", "10:33");
  cr_log_info("Generated id is %d", id);
  cr_assert_neq(id, (unsigned int) 0); 
}
