#include "helpers.h"

int
main(
    void
) {
    expect_match("foo", "!bar");
    expect_mismatch("unicorn", "!unicorn");
    expect_mismatch("unicorn", "!uni*");

    return 0;
}
