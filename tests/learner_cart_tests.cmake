# testing executable
enable_testing()
add_executable(learner_cart_tests)
target_link_directories(
        learner_cart_tests
        PUBLIC
        ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
        learner_cart_tests
        PRIVATE
        learner_cart_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
    include(GoogleTest)
    gtest_discover_tests(utils_tests)
endif()

