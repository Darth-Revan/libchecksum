cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# The project version number.
set(VERSION_MAJOR   1   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
add_definitions(-DCHECKSUM_VERSION="${VERSION}")

project(checksum LANGUAGES CXX VERSION ${VERSION})

# Enforce C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# check for useful compiler flags
INCLUDE(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-Wall" HAVE_WALL)
check_cxx_compiler_flag("-pedantic" HAVE_PEDANTIC)
check_cxx_compiler_flag("-Werror" HAVE_WERROR)
check_cxx_compiler_flag("-Weverything" HAVE_WEVERYTHING)
check_cxx_compiler_flag("-Wno-padded" HAVE_NOPADDED)
check_cxx_compiler_flag("-Wno-c++98-compat" HAVE_NO98COMPAT)
check_cxx_compiler_flag("-Wno-c++98-compat-pedantic" HAVE_NO98COMPAT_PED)
check_cxx_compiler_flag("-Wno-exit-time-destructors" HAVE_NOEXITTIME)
check_cxx_compiler_flag("-Wno-global-constructors" HAVE_GLOBCONST)
check_cxx_compiler_flag("-Wno-documentation-unknown-command" HAVE_NODOCWARN)
check_cxx_compiler_flag("-fno-rtti" HAVE_NORTTI)

# Set only available flags on current compiler
if (HAVE_WALL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
if (HAVE_PEDANTIC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif()
if (HAVE_WEVERYTHING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
endif()
if (HAVE_WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()
if (HAVE_NOPADDED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded")
endif()
if (HAVE_NO98COMPAT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat")
endif()
if (HAVE_NO98COMPAT_PED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic")
endif()
if (HAVE_NOEXITTIME)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-exit-time-destructors")
endif()
if (HAVE_GLOBCONST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors")
endif()
if (HAVE_NODOCWARN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation-unknown-command")
endif()
if (HAVE_NORTTI)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()
message("-- Compiling with flags '${CMAKE_CXX_FLAGS}' on '${CMAKE_CXX_COMPILER_ID}' ${CMAKE_CXX_COMPILER_VERSION}")

#configure target "doc" for building documentation with Doxygen
option(BUILD_DOCUMENTATION "Create HTML documentation of API with Doxygen" ON)
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed for building documentation")
    endif()
    message(STATUS "Building documentation with Doxygen")
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generate documentation with Doxygen"
            VERBATIM)
endif()

# include 3rd-party headers as SYSTEM-headers to quiet compiler on this files
include_directories(SYSTEM libs)
include_directories(include)
include_directories(src)

# Compile library
file(GLOB SOURCES include/libchecksum/*.h src/*.cpp src/*.h)
add_library(checksum SHARED ${SOURCES})
set_target_properties(checksum PROPERTIES LINKER_LANGUAGE CXX)

#configure target "LOCAL_tests" for building unit tests
option(BUILD_TESTS "Build unit tests with Catch2" OFF)
if(BUILD_TESTS)
    message(STATUS "Generating build target for unit tests.")
    set(TEST_SOURCES test/main.cpp test/checksums.cpp)
    add_executable(checksum_tests ${TEST_SOURCES})
    target_link_libraries(checksum_tests checksum)
    configure_file(test/testfile.txt testfile.txt COPYONLY)
endif()