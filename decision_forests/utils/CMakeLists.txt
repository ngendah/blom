add_library(
        utils
        STATIC
        adaptive_work.cc
        logging_default.cc
)

target_include_directories(utils PUBLIC ${abseil_INCLUDE_DIRS})