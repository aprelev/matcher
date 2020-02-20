#include "helpers.h"

int
main(
    void
) {
    expect_match("unicorn", "unicorn");
    expect_match("MOO", "MOO");

    return 0;
}
