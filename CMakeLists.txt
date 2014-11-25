cmake_minimum_required (VERSION 2.8.0)
project ("LTP - Chinese Word Segmentation Component.")

# project attributes section
# -- config cmake modules path
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set (CMAKE_CXX_FLAGS "-g")

if (APPLE)
  set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libstdc++ -Wno-error=c++11-narrowing")
endif(APPLE)

if (MINGW)
  set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-narrowing -fpermissive")
endif (MINGW)

# -- config output directories
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set (INCLUDE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/include)

# -- config source directories
set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set (THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty)

# -- config resource directories
set (CONFIGURE_DIR ${PROJECT_SOURCE_DIR}/conf)

# compiling section
# -- compile shipped libraries
add_subdirectory (thirdparty)

# -- compile source code
add_subdirectory (src)

# compile testing
add_subdirectory (test)
