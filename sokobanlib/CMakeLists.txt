set(TARGET "sokobanlib")
project(${TARGET})

set(INCLUDEDIR "include")
set(LIBDIR "lib")

set(SRC_FILES
        src/sokobanlib.cpp) # add source files here

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${LIBDIR})

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})

add_subdirectory(tests)
