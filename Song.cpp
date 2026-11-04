#include "Song.h"
#include <stdexcept>
#include <unordered_map>

SongField featureField(const std::string& feature) {
    static const std::unordered_map<std::string, SongField> fields = {
        {"popularity", &Song::popularity},
        {"duration_ms", &Song::durationMs},
        {"danceability", &Song::danceability},
        {"energy", &Song::energy},
        {"key", &Song::key},
        {"loudness", &Song::loudness},
        {"mode", &Song::mode},
        {"speechiness", &Song::speechiness},
        {"acousticness", &Song::acousticness},
        {"instrumentalness", &Song::instrumentalness},
        {"liveness", &Song::liveness},
        {"valence", &Song::valence},
        {"tempo", &Song::tempo},
    };

    auto it = fields.find(feature);
    if (it == fields.end()) {
        throw std::invalid_argument("Unknown feature: " + feature);
    }
    return it->second;
}
