cmake_minimum_required(VERSION 4.1)
project(DSA_P2_SpotifyMusicSuggestor)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)


add_executable(DSA_P2_SpotifyMusicSuggestor
        main.cpp
        Button.h
        Button.cpp
        Song.h
        Song.cpp
        DataLoader.h
        DataLoader.cpp
        QuickSort.h
        QuickSort.cpp
)

target_compile_features(DSA_P2_SpotifyMusicSuggestor PRIVATE cxx_std_17)
target_link_libraries(DSA_P2_SpotifyMusicSuggestor PRIVATE SFML::Graphics)

# Standalone sort tests (no SFML). Run: ./quicksort_test resources/dataset.csv
add_executable(quicksort_test
        tests/quicksort_test.cpp
        Song.cpp
        DataLoader.cpp
        QuickSort.cpp
)
target_compile_features(quicksort_test PRIVATE cxx_std_17)