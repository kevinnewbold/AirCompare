cmake_minimum_required(VERSION 3.16)
project(AirCompare LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES
    src/data.h
    src/data.cpp
    src/heapsort.h
    src/heapsort.cpp
    src/mergesort.h
    src/mergesort.cpp
    src/listing.h
    src/listing.cpp
    src/main.cpp
)

add_executable(aircompare ${SOURCES})
target_link_libraries(aircompare PRIVATE sfml-graphics)
target_compile_features(aircompare PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET aircompare
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:aircompare>
        VERBATIM)
endif()

install(TARGETS aircompare)
