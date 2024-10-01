cmake_minimum_required(VERSION 3.5)

# Definitions
set(PROJECT_NAME scbl)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Set project name
project(${PROJECT_NAME})

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check for compiler and set optimization flags accordingly
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # For GCC or Clang compilers
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
elseif(MSVC)
    # For Microsoft Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
endif()

# Include paths
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

# Assign the include directories
include_directories(${INCLUDE_DIRS})

# Find library sources
file(GLOB_RECURSE LIB_SRC_FILES ${PROJECT_SOURCE_DIR}/include/*.cpp)

# Build static/shared library
add_library(${PROJECT_NAME}_LIB STATIC ${LIB_SRC_FILES})

# Install library
install(TARGETS ${PROJECT_NAME}_LIB DESTINATION lib)

# Install library headers
file(GLOB_RECURSE LIB_INC_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
install(FILES ${LIB_INC_FILES} DESTINATION include)

# Define the source files
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link the executable with the library
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_LIB)