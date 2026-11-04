#include "DataLoader.h"
#include <fstream>
#include <stdexcept>

namespace {

// Splits one CSV line into fields. A field wrapped in double quotes may contain commas,
// and "" inside quotes stands for a single " character.
std::vector<std::string> splitCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (inQuotes) {
            if (c == '"' && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"';   // escaped quote
                i++;
            } else if (c == '"') {
                inQuotes = false; // closing quote
            } else {
                current += c;
            }
        } else if (c == '"') {
            inQuotes = true;
        } else if (c == ',') {
            fields.push_back(current);
            current.clear();
        } else if (c != '\r') {
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}

}

std::vector<Song> loadSongs(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open " + path);
    }

    // Column order in dataset.csv (column 0 is an unnamed row index):
    // ,track_id,artists,album_name,track_name,popularity,duration_ms,explicit,danceability,
    // energy,key,loudness,mode,speechiness,acousticness,instrumentalness,liveness,valence,
    // tempo,time_signature,track_genre
    const size_t expectedColumns = 21;

    std::vector<Song> songs;
    songs.reserve(115000);

    std::string line;
    std::getline(file, line); // skip header row

    while (std::getline(file, line)) {
        std::vector<std::string> f = splitCsvLine(line);
        if (f.size() != expectedColumns) {
            continue; // malformed row
        }

        try {
            Song s;
            s.trackId = f[1];
            s.artists = f[2];
            s.albumName = f[3];
            s.trackName = f[4];
            s.popularity = std::stod(f[5]);
            s.durationMs = std::stod(f[6]);
            s.isExplicit = (f[7] == "True" || f[7] == "true");
            s.danceability = std::stod(f[8]);
            s.energy = std::stod(f[9]);
            s.key = std::stod(f[10]);
            s.loudness = std::stod(f[11]);
            s.mode = std::stod(f[12]);
            s.speechiness = std::stod(f[13]);
            s.acousticness = std::stod(f[14]);
            s.instrumentalness = std::stod(f[15]);
            s.liveness = std::stod(f[16]);
            s.valence = std::stod(f[17]);
            s.tempo = std::stod(f[18]);
            s.timeSignature = std::stoi(f[19]);
            s.genre = f[20];
            songs.push_back(s);
        } catch (const std::exception&) {
            continue; // a number column was blank or not a number
        }
    }
    return songs;
}

std::vector<Song> filterByGenre(const std::vector<Song>& songs, const std::string& genre) {
    std::vector<Song> result;
    for (const Song& s : songs) {
        if (s.genre == genre) {
            result.push_back(s);
        }
    }
    return result;
}
