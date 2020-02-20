function(add_tests suite)
  foreach(test IN LISTS ARGN)
    get_filename_component(test_name ${test} NAME_WE)

    add_executable(${test_name} ${test})
    target_include_directories(${test_name} PRIVATE include)
    target_link_libraries(${test_name} matcher)

    add_test(${suite}/${test_name} ${test_name})
  endforeach()
endfunction()

add_tests(matcher
  src/empty_pattern.c
  src/escaped_characters.c
  src/exact_match.c
  src/negated.c
  src/partials.c
  src/wildcard.c
)
