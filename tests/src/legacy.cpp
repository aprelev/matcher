#include <contest/utilities/matcher.h>
#include <gtest/gtest.h>

class MatcherTests
    : public ::testing::Test {
protected:
    bool doesMatch_;

public:
    MatcherTests()
        : doesMatch_()
    {};

    void
    ExpectMatch(
        char const *str,
        char const *filter
    ) {
        doesMatch_ = false;

        EXPECT_EQ(ct_statusOk, ct_matchAgainstFilter(str, filter, &doesMatch_));
        EXPECT_TRUE(doesMatch_);
    }

    void
    ExpectMismatch(
        char const *str,
        char const *filter
    ) {
        doesMatch_ = true;

        EXPECT_EQ(ct_statusOk, ct_matchAgainstFilter(str, filter, &doesMatch_));
        EXPECT_FALSE(doesMatch_);
    }
};

TEST_F(MatcherTests, NullReferenceCheck) {
    char const *sampleString = "Foo", *sampleFilter = "Bar";
    bool sampleOutput;

    EXPECT_EQ(ct_statusNullReference, ct_matchAgainstFilter(nullptr, sampleFilter, &sampleOutput));
    EXPECT_EQ(ct_statusNullReference, ct_matchAgainstFilter(sampleString, sampleFilter, nullptr));
}

TEST_F(MatcherTests, ExactMatchLowercase) {
    ExpectMatch("unicorn", "unicorn");
}

TEST_F(MatcherTests, ExactMatchUppercase) {
    ExpectMatch("MOO", "MOO");
}

TEST_F(MatcherTests, WildcardAtTheEnd) {
    ExpectMatch("unicorn", "uni*");
}

TEST_F(MatcherTests, WildcardInTheBeginning) {
    ExpectMatch("unicorn", "*corn");
}

TEST_F(MatcherTests, WildcardInTheMiddle) {
    ExpectMatch("unicorn", "un*rn");
}

TEST_F(MatcherTests, WildcardOnBothEnds) {
    ExpectMatch("foo unicorn bar", "*unicorn*");
}

TEST_F(MatcherTests, PlainWildcard) {
    ExpectMatch("unicorn", "*");
}

TEST_F(MatcherTests, EmptyPattern) {
    ExpectMatch("unicorn", "");
}

TEST_F(MatcherTests, NegatedExactMatch) {
    ExpectMismatch("unicorn", "!unicorn");
}

TEST_F(MatcherTests, NegatedWildcardAtTheEnd) {
    ExpectMismatch("unicorn", "!uni*");
}

TEST_F(MatcherTests, SpecialSymbol) {
    ExpectMismatch("unicorn", "uni\\*");
}

TEST_F(MatcherTests, SubstringAtTheEnd) {
    ExpectMatch("unicorn", "corn");
}

TEST_F(MatcherTests, SubstringInTheBeginning) {
    ExpectMatch("unicorn", "uni");
}

TEST_F(MatcherTests, SubstringInTheMiddle) {
    ExpectMatch("unicorn", "ico");
}

TEST_F(MatcherTests, Range) {
    ExpectMatch("unicorn", "foo:co:bar");
}