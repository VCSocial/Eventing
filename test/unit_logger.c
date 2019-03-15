#include "../src/logger.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>

Test(simple, test2) {
  cr_log_info("STUB always successful");

  cr_assert_neq(0, 1); 
}
