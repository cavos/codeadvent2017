cmake_minimum_required (VERSION 3.9)
project (codeadvent2017)

# BOOST_INCLUDEDIR    (d:\_prj\cpp\boost_1_65_1\)
# BOOST_LIBRARYDIR    d:\_prj\cpp\boost_1_65_1\stage\lib\
# BOOST_ROOT          d:\_prj\cpp\boost_1_65_1\boost

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.65.1)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET (CMAKE_C_FLAGS_INIT                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

SET (CMAKE_CXX_FLAGS_INIT                "-Wall -fcolor-diagnostics")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

include_directories(${Boost_INCLUDE_DIRS}) 
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

add_executable(codeadvent17 codeadvent17.cpp
day01_InverseCaptcha.cpp
day02_CorruptionChecksum.cpp
day03_SpiralMemory.cpp
day04_HighEntropyPassphrases.cpp
day05_TwistyTrampolines.cpp
day06_MemoryReallocation.cpp
day07_RecursiveCircus.cpp
day08_RegisterProcessor.cpp
day09_StreamProcessing.cpp
day10_KnotHash.cpp
day11_HexEd.cpp
day12_DigitalPlumber.cpp
day13_PacketScanners.cpp
day14_DiskDefragmentation.cpp
day15_DuelingGenerators.cpp
day16_PermutationPromenade.cpp
day17_Spinlock.cpp
# stdafx.cpp
)

target_link_libraries(codeadvent17 ${Boost_LIBRARIES})
