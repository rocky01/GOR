project("${CMAKE_PROJECT_NAME}-test")


file(GLOB_RECURSE LIB_HEADERS "${LIB_DIR}/*.hpp")
file(GLOB_RECURSE T_HEADERS "${TST_DIR}/*.hpp")
file(GLOB_RECURSE T_SRCS "${TST_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${LIB_HEADERS} ${T_HEADERS} ${T_SRCS})

include(gtest.cmake)

include_directories("${GTEST_SOURCE_DIR}/googletest/include"
                    "${GTEST_SOURCE_DIR}/googlemock/include"
                    "${TST_DIR}"
                    "${LIB_DIR}")

target_link_libraries(${PROJECT_NAME}
    libgtest
    libgmock
)

add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME})
