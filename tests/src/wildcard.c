#include "helpers.h"

int
main(
    void
) {
    expect_match("unicorn", "uni*");
    expect_match("unicorn", "*corn");
    expect_match("unicorn", "un*rn");
    expect_match("foo unicorn bar", "*unicorn*");
    expect_match("unicorn", "*");

    return 0;
}
