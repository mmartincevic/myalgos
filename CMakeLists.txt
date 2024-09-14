cmake_minimum_required(VERSION 3.10)
project(Playground VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable folder support for Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_VS_USE_SPACES ON)
set(CMAKE_VS_INDENT_SIZE 4)

# Set runtime library to MultiThreaded DLL
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Download and unpack googletest at configure time
configure_file(external/googletest/CMakeLists.txt googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")
# Find all .h files in the include/playground directory
file(GLOB_RECURSE HEADERS "include/playground/*.h")

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add the include directory to the include path
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create source groups for Visual Studio filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HEADERS})

# Set the startup project (optional, but helpful)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Generate Visual Studio filters
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "")

# Force Visual Studio to show header files in the project
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Add test executable if test files exist
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
if(TEST_SOURCES)
  add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest gtest_main)
  target_include_directories(${PROJECT_NAME}_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

  # Discover tests
  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME}_tests)
else()
  message(STATUS "No test sources found. Skipping test executable creation.")
endif()