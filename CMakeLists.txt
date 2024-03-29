cmake_minimum_required(VERSION 3.10)

# define project name, version
project(PSEMolDyn_GroupG VERSION 0.0.1)

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# set Release as the default build type if it is not yet set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# collect all cpp files
file(GLOB_RECURSE MY_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/2D/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/BoundaryConditions/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Checkpoints/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/GeometricObjects/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/InputReader/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/OutputWriter/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ParticleContainers/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SimulationLogic/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Visitors/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/XML_Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SimulationAnalysis/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/MolSim.cpp"


        # header don't need to be included but this might be necessary for some IDEs
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
# create make target
add_executable(MolSim ${MY_SRC} )

# set cxx standard. You may raise this if you want.
target_compile_features(MolSim
        PRIVATE
            cxx_std_14
)

target_include_directories(MolSim
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/libxsd
            ${CMAKE_CURRENT_SOURCE_DIR}/libs
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#target_compile_options(MolSim PUBLIC -pg)

target_link_libraries(MolSim
        # stuff that is used in headers and source files
        PUBLIC
        xerces-c
        #-pg
        )

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
include(tests)

# activate all compiler warnings. Clean up your code :P
# depending on the compiler different flags are used
target_compile_options(MolSim
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-Wall>
            # disable some spam warnings for icpc...
            $<$<CXX_COMPILER_ID:Intel>:-w3 -wd383,981,1418,1572,2259>
)

include(doxygen)
include(openmp)