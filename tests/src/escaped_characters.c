#include "helpers.h"

int
main(
    void
) {
    expect_mismatch("unicorn", "uni\\*");
    // expect_match("unicorn*", "unicorn\\*");

    return 0;
}
