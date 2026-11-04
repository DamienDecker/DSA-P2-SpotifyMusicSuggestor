#pragma once
#include <string>
#include <vector>
#include "Song.h"

std::vector<Song> loadSongs(const std::string& path);

// Returns only the songs whose genre matches
std::vector<Song> filterByGenre(const std::vector<Song>& songs, const std::string& genre);
