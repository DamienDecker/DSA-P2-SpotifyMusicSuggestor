#ifndef DSA_P2_SPOTIFYMUSICSUGGESTOR_SORT_TIMERS_H
#define DSA_P2_SPOTIFYMUSICSUGGESTOR_SORT_TIMERS_H

#include <vector>
#include <string>
#include "Dataloader.h"

using namespace std;

// Holds everything the display needs after the sorts are done
struct SortResult {
    double mergeTime;
    double quickTime;
    vector<Song> sortedSongs;
};

// Filters allSongs by genre, sorts them by the feature with both merge sort
// and quick sort, and times each one
SortResult runSorts(vector<Song>& allSongs, string genre, string feature);


#endif //DSA_P2_SPOTIFYMUSICSUGGESTOR_SORT_TIMERS_H