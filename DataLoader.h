#pragma once
#include <string>
#include <vector>
#include "Song.h"

// Reads the Kaggle Spotify Tracks CSV (dataset.csv) into a vector of Songs.
// Handles quoted fields that contain commas, e.g. "Hello, Goodbye".
// Rows that can't be parsed are skipped. Throws std::runtime_error if the file can't be opened.
std::vector<Song> loadSongs(const std::string& path);

// Returns only the songs whose genre matches exactly (e.g. "pop", "hip-hop").
std::vector<Song> filterByGenre(const std::vector<Song>& songs, const std::string& genre);
