#include "QuickSort.h"
#include <vector>
#include <string>

using namespace std;

bool goesBefore(double a, double b, bool descending) {
    if (descending) {
        return a > b;
    }
    return a < b;
}

int quickPartition(vector<Song>& songs, int low, int high, SongField field, bool descending) {
    int middle = (low + high) / 2;
    double pivot = songs[middle].*field;
    int left = low - 1;
    int right = high + 1;

    while (true) {
        left++;
        while (goesBefore(songs[left].*field, pivot, descending)) {
            left++;
        }
        right--;
        
        while (goesBefore(pivot, songs[right].*field, descending)) {
            right--;
        }

        if (left >= right) {
            return right;
        }

        Song temp = songs[left];
        songs[left] = songs[right];
        songs[right] = temp;
    }
}

void quickSortHelper(vector<Song>& songs, int low, int high, SongField field, bool descending) {
    if (low < high) {
        int split = quickPartition(songs, low, high, field, descending);
        quickSortHelper(songs, low, split, field, descending);
        quickSortHelper(songs, split + 1, high, field, descending);
    }
}

void quickSort(vector<Song>& songs, const string& feature, bool descending) {
    if (songs.size() < 2) {
        return;
    }
    SongField field = featureField(feature);
    quickSortHelper(songs, 0, songs.size() - 1, field, descending);
}