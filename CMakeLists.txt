CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

project(Bayan)

option(WITH_GTEST "Whether to build Gtest test" ON)

find_package(Boost COMPONENTS program_options system REQUIRED)

add_executable(BayanPro
    main.cpp
    cmd_line_parser.h
    cmd_line_parser.cpp
    utility.h
    utility.cpp
    bayan/bayan.cpp
    bayan/bayan.h
    bayan/factory.h
    bayan/file.h
    bayan/hash.h
    bayan/hash_crc32.cpp
    bayan/hash_crc32.h
    bayan/hash_md5.cpp
    bayan/hash_md5.h
    )

set_property(TARGET BayanPro PROPERTY CXX_STANDARD 17)

target_link_libraries(BayanPro ${Boost_LIBRARIES})

if(WITH_GTEST)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_executable(tests 
                    tests.cpp
                    cmd_line_parser.h
                    cmd_line_parser.cpp
                    utility.h
                    utility.cpp
                    bayan/bayan.cpp
                    bayan/bayan.h
                    bayan/factory.h
                    bayan/file.h
                    bayan/hash.h
                    bayan/hash_crc32.cpp
                    bayan/hash_crc32.h
                    bayan/hash_md5.cpp
                    bayan/hash_md5.h)

    set_target_properties(tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
    target_link_libraries(tests
        ${Boost_LIBRARIES}
        gtest_main
    )
endif()
