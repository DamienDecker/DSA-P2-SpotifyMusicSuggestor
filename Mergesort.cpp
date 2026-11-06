#include "Mergesort.h"
#include "DataLoader.h"
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
        while (i <= mid) {
            temp[k++] = songs[i++];
        }
        while (j <= right) {
            temp[k++] = songs[j++];
        }

        for (int x = left; x <= right; x++) {
            songs[x] = temp[x];
        }
    }
    // sorts each half recursively, then merges them
    void mergeSortHelper(vector<Song>& songs, vector<Song>& temp, int left, int right,
                         SongField field, bool descending) {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSortHelper(songs, temp, left, mid, field, descending);
        mergeSortHelper(songs, temp, mid + 1, right, field, descending);
        mergeHalves(songs, temp, left, mid, right, field, descending);
    }
}

// sorts songs by the chosen feature
void mergeSort(vector<Song>& songs, const string& feature, bool descending) {
    if (songs.size() < 2) {
        return;
    }
    SongField field = featureField(feature);

    // one temp buffer shared by every merge
    vector<Song> temp(songs.size());
    mergeSortHelper(songs, temp, 0, static_cast<int>(songs.size()) - 1, field, descending);
}