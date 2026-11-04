#pragma once
#include <string>

// One row of the Kaggle Spotify Tracks dataset.
// Every sortable feature is stored as a double so one sort function can handle all of them.
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

// A "pointer to a member" of Song, like &Song::energy.
// Given a Song s and a SongField f, s.*f reads that field.
// This lets the sorts look up the feature name once instead of comparing strings millions of times.
using SongField = double Song::*;

// Turns a feature name from the dropdown ("energy", "tempo", ...) into the matching field.
// Throws std::invalid_argument for an unknown name.
SongField featureField(const std::string& feature);
