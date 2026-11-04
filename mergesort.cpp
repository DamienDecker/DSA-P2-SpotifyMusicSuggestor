#include "mergesort.h"
#include <vector>
#include <string>
using namespace std;

namespace {

    // checks which value comes first
    bool mergeGoesBefore(double a, double b, bool descending) {
        if (descending) {
            return a > b;
        }
        return a < b;
    }

    // merges the sorted ranged [left, mid] and [mid + 1, right]
    void mergeHalves(vector<Song>& songs, vector<Song>& temp, int left, int mid, int right,
    SongField field, bool descending) {
        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j <= right) {
            // only take from the right half if it strictly goes first,
            // so equal songs keep their original order
            if (mergeGoesBefore(songs[j].*field, songs[i].*field, descending)) {
                temp[k++] = songs[j++];
            } else {
                temp[k++] = songs[i++];
            }
        }
    }
}