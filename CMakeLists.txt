####################
#      Global      #
####################

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

#####################
#      Project      #
#####################

# Project variables
set(LOCAL_PROJECT_NAME "Color_Space_Transform")
set(LOCAL_PROJECT_VERSION "0.0.1")
set(LOCAL_PROJECT_DESCRIPTION "Image color space transformation without OpenCV")

# Project setup
project(${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES CXX)

# Source files (relative to "src" directory)
set(SOURCES
    src/main.cpp
)

# Include directories for headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs # For stb_image and stb_image_write
)

# Configure the target executable
add_executable(${LOCAL_PROJECT_NAME} ${SOURCES})

# Set output directory for the executable
set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# Compiler options (optional: add warnings or optimizations)
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE -Wall -Wextra -O2)

####################
#   Dependencies   #
####################

# stb_image and stb_image_write are header-only libraries, so no additional linking is required.
