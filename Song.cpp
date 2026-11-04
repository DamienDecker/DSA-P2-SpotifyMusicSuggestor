#include "Song.h"
#include <string>
#include <stdexcept>

using namespace std;

// returns which Song field to sort by based on the feature name
SongField featureField(const string& feature) {
    if (feature == "popularity") {
        return &Song::popularity;
    }
    else if (feature == "duration_ms") {
        return &Song::durationMs;
    }
    else if (feature == "danceability") {
        return &Song::danceability;
    }
    else if (feature == "energy") {
        return &Song::energy;
    }
    else if (feature == "key") {
        return &Song::key;
    }
    else if (feature == "loudness") {
        return &Song::loudness;
    }
    else if (feature == "mode") {
        return &Song::mode;
    }
    else if (feature == "speechiness") {
        return &Song::speechiness;
    }
    else if (feature == "acousticness") {
        return &Song::acousticness;
    }
    else if (feature == "instrumentalness") {
        return &Song::instrumentalness;
    }
    else if (feature == "liveness") {
        return &Song::liveness;
    }
    else if (feature == "valence") {
        return &Song::valence;
    }
    else if (feature == "tempo") {
        return &Song::tempo;
    }
    // feature name not found
    else {
        throw invalid_argument("Unknown feature: " + feature);
    }
}