add_library(matcher
    src/matcher.c
)

target_include_directories(
    matcher PUBLIC
    include
)

target_compile_features(
    matcher PUBLIC
    c_std_11
)

target_link_libraries(
    matcher PUBLIC
    nolibc
)
