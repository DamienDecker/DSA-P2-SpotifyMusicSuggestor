#pragma once
#include <string>

struct Song {
    std::string trackId;
    std::string artists;
    std::string albumName;
    std::string trackName;
    std::string genre;

    double popularity = 0;
    double durationMs = 0;
    bool isExplicit = false;
    double danceability = 0;
    double energy = 0;
    double key = 0;
    double loudness = 0;
    double mode = 0;
    double speechiness = 0;
    double acousticness = 0;
    double instrumentalness = 0;
    double liveness = 0;
    double valence = 0;
    double tempo = 0;
    int timeSignature = 0;
};

using SongField = double Song::*;

SongField featureField(const std::string& feature);
