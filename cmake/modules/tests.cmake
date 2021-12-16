enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/BoundaryConditions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Checkpoints/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/GeometricObjects/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/InputReader/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/OutputWriter/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ParticleContainers/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SimulationLogic/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Visitors/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Tests/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/XML_Parser/*.cpp"
        )

add_executable(Tests ${TEST_SRC})

target_include_directories(Tests
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/libxsd
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        PRIVATE
        src
        )

target_link_libraries(Tests
        PUBLIC
        xerces-c
        gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests)
