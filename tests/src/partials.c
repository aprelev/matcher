#include "helpers.h"

int
main(
    void
) {
    expect_match("unicorn", "corn");
    expect_match("unicorn", "uni");
    expect_match("unicorn", "ico");

    return 0;
}
