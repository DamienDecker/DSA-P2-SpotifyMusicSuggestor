#pragma once
#include <string>
#include <vector>
#include "Song.h"

// sorts songs by the chosen feature using merge sort
// descending = true puts the highest values first
void mergeSort(std::vector<Song>& songs, const std::string& feature, bool descending = true);