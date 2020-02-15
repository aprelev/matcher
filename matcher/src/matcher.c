#include <matcher/matcher.h>
#include <string.h>

/* Returns true iff string matches pattern
 * anchored to the beginning of the string.
 */
static bool
matchesHere(
    char const *str,
    char const *pattern
) {
    switch (*pattern) {

    /* Both '\0' and pattern delimiter characters denominate end of pattern.
     * If we got this far, we've got a match.
     */
    case '\0':
    case ':':
        return true;

    /* '$' anchors pattern to the end of string.
     * If we got this far, and string end here, we've got a match.
     */
    case '$':
        return (*str == '\0');

    /* '?' matches any single character in string but '\0'.
     * Skips current string character and proceeds.
     */
    case '?':
        return (*str && matchesHere(str + 1, pattern + 1));

    /* '*' matches any substring (including empty substring).
     * Tries matching here next pattern token (in case substring is indeed empty),
     * as well as matching the same pattern while skipping current character.
     */
    case '*':
        return (*str && matchesHere(str + 1, pattern)) || matchesHere(str, pattern + 1);

    /* Regular character.
     * Matches itself, and proceeds.
     */
    default:
        return (*str == *pattern) && matchesHere(str + 1, pattern + 1);
    }
}

/* Returns true iff string matches pattern
 * with arbitrary offset.
 */
static bool
matchesAnywhere(
    char const *str,
    char const *pattern
) {
    /* Processes first character of the pattern,
     * it may have special meaning.
     */
    switch (*pattern) {

    /* '^' anchors pattern to the beginning of the string.
     * Either we have a match here, or we don't have a match.
     */
    case '^':
        return matchesHere(str, pattern);

    /* '!' negates pattern.
     * Skips this token and inverts result of match.
     */
    case '!':
        return !matchesAnywhere(str, pattern + 1);

    /* First pattern token is not special.
     * Tries matching with increasing offset.
     */
    default:
        while (*str) {
            if (matchesHere(str, pattern))
                return true;

            ++str;
        }

        /* Reached end of string, and not a single match was found. */
        return false;
    }
}

/* Returns true iff string matches any pattern in list;
 * where patterns are separated by colons.
 */
static bool
matchesAny(
    char const *str,
    char const *patterns
) {
    char const *current = patterns;
    while (current) {

        /* Tries matching against current pattern. */
        if (matchesAnywhere(str, current))
            return true;

        /* Proceeds to next pattern. */
        current = strchr(current, ':');

        /* Skips colon character. */
        if (current)
            ++current;
    }

    return false;
}

#include <nolibc/extensions/check.h>

bool
c_matches_pattern(
    char const str[],
    char const pattern[] /* optional */
) {
    _Check_not_null(str);

    static const char
        match_everything_pattern[] = "*";

    /* Replaces filter with matches-everything pattern
     * when it is NULL or empty.
     */
    if (!pattern || *pattern == 0) {
        pattern = match_everything_pattern;
    }

    return matchesAny(str, pattern);
}
