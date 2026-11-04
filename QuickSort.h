#pragma once
#include <string>
#include <vector>
#include "Song.h"

// Sorts songs in place by the given feature ("energy", "tempo", ...), implemented from scratch.
// descending = true puts the highest values first (what the rankings screen wants).
//
// Design choices:
//  - Median-of-three pivot: avoids the O(n^2) worst case on already-sorted input.
//  - 3-way partition (< pivot | == pivot | > pivot): the dataset has many repeated values
//    (e.g. key is only 0-11, popularity has thousands of 0s), and this keeps those fast.
//  - Recurse into the smaller side, loop on the larger side: recursion depth stays O(log n),
//    so the program can't run out of stack.
//
// Time:  average O(n log n), worst case O(n^2) (very unlikely with median-of-three).
// Space: O(log n) extra for the recursion.
void quickSort(std::vector<Song>& songs, const std::string& feature, bool descending = true);
