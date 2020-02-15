#include <matcher/matcher.h>
#include <stdbool.h>

int
main(
    void
) {
    if (!c_matches_pattern("unicorn", "unicorn")) {
        return 1;
    }

    if (!c_matches_pattern("MOO", "MOO")) {
        return 1;
    }

    return 0;
}
