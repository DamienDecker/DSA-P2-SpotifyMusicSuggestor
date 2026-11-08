#include "DataLoader.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_set>

using namespace std;

// splits a csv line into columns
vector<string> splitLine(const string& line) {
    vector<string> columns;
    string word = "";
    bool inQuotes = false;

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];

        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes) {
            columns.push_back(word);
            word = "";
        }
        else if (c != '\r') {
            word += c;
        }
    }
    columns.push_back(word);
    return columns;
}

// reads all songs from the csv
vector<Song> loadSongs(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Could not open " + path);
    }

    vector<Song> songs;
    string line;
    getline(file, line);

    while (getline(file, line)) {
        vector<string> col = splitLine(line);

        if (col.size() != 21) {
            continue;
        }

        try {
            Song song;
            song.trackId = col[1];
            song.artists = col[2];
            song.albumName = col[3];
            song.trackName = col[4];
            song.popularity = stod(col[5]);
            song.durationMs = stod(col[6]);
            song.isExplicit = (col[7] == "True");
            song.danceability = stod(col[8]);
            song.energy = stod(col[9]);
            song.key = stod(col[10]);
            song.loudness = stod(col[11]);
            song.mode = stod(col[12]);
            song.speechiness = stod(col[13]);
            song.acousticness = stod(col[14]);
            song.instrumentalness = stod(col[15]);
            song.liveness = stod(col[16]);
            song.valence = stod(col[17]);
            song.tempo = stod(col[18]);
            song.timeSignature = stoi(col[19]);
            song.genre = col[20];
            songs.push_back(song);
        }
        catch (...) {
            continue;
        }
    }

    return songs;
}

// keeps songs from the chosen genre and skips repeats of the same song
vector<Song> filterByGenre(const vector<Song>& songs, const string& genre) {
    vector<Song> result;
    unordered_set<string> seen;

    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].genre == genre) {
            string songKey = songs[i].trackName + "|" + songs[i].artists;
            if (seen.count(songKey) == 0) {
                seen.insert(songKey);
                result.push_back(songs[i]);
            }
        }
    }
    return result;
}
