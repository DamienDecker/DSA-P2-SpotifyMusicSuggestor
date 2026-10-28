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
        main.cpp)

target_compile_features(DSA_P2_SpotifyMusicSuggestor PRIVATE cxx_std_17)
target_link_libraries(DSA_P2_SpotifyMusicSuggestor PRIVATE SFML::Graphics)