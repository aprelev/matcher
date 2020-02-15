#pragma once

#include <nolibc/extensions/unmangled.h>
#include <stdbool.h>

_Unmangled bool
c_matches_pattern(
    char const str[],
    char const pattern[] /* optional */
);
