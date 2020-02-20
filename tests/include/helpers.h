#pragma once

#include <matcher/matcher.h>
#include <stdbool.h>
#include <stdlib.h>

static inline void
expect_match(
    char const str[],
    char const pattern[]
) {
    if (!c_matches_pattern(str, pattern)) {
        exit(1);
    }
}

static inline void
expect_mismatch(
    char const str[],
    char const pattern[]
) {
    if (c_matches_pattern(str, pattern)) {
        exit(1);
    }
}
