#include "../src/event.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>

Test(simple, create_event_valid) {
  cr_log_info("Create new event, and assert that id is greater than 0");
  unsigned int id = create_event("TEST", "09:42", "10:33");

  cr_log_info("Generated id is %d", id);
  cr_assert_neq(id, (unsigned int) 0);
}

Test(simple, delete_event_valid) {
  cr_log_info("Delete event, and assert that status returned is 0");
  unsigned int id = create_event("TEST", "09:42", "10:33");

  unsigned int status = delete_event(id);
  cr_assert_eq(status, (unsigned int) 0);
}

Test(simple, delete_event_invalid) {
  cr_log_info("Delete non-existent event, and assert that status returned is 1");

  unsigned int status = delete_event(0);
  cr_assert_eq(status, (unsigned int) 1);
}
