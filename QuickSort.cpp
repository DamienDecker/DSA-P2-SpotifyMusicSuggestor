#include "QuickSort.h"
#include <utility>

namespace {

// True if a should come before b in the final order.
bool comesBefore(double a, double b, bool descending) {
    return descending ? a > b : a < b;
}

// Looks at the first, middle and last songs and returns the middle value of the three.
// Using this as the pivot means sorted or reverse-sorted input still splits evenly.
double medianOfThree(const std::vector<Song>& songs, int low, int high, SongField field) {
    int mid = low + (high - low) / 2;
    double a = songs[low].*field;
    double b = songs[mid].*field;
    double c = songs[high].*field;

    if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
    return c;
}

// Sorts songs[low..high] (both ends included).
void quickSortRange(std::vector<Song>& songs, int low, int high, SongField field, bool descending) {
    while (low < high) {
        double pivot = medianOfThree(songs, low, high, field);

        // 3-way partition (Dutch national flag). After this loop:
        //   songs[low  .. lt-1]  come before the pivot
        //   songs[lt   .. gt]    equal the pivot (already in their final spot)
        //   songs[gt+1 .. high]  come after the pivot
        int lt = low;
        int i = low;
        int gt = high;
        while (i <= gt) {
            double value = songs[i].*field;
            if (comesBefore(value, pivot, descending)) {
                std::swap(songs[lt], songs[i]);
                lt++;
                i++;
            } else if (comesBefore(pivot, value, descending)) {
                std::swap(songs[i], songs[gt]);
                gt--; // don't move i: the swapped-in song hasn't been checked yet
            } else {
                i++;
            }
        }

        // Recurse on the smaller side and keep looping on the bigger one,
        // so the recursion never goes deeper than about log2(n) calls.
        if (lt - low < high - gt) {
            quickSortRange(songs, low, lt - 1, field, descending);
            low = gt + 1;
        } else {
            quickSortRange(songs, gt + 1, high, field, descending);
            high = lt - 1;
        }
    }
}

}

void quickSort(std::vector<Song>& songs, const std::string& feature, bool descending) {
    if (songs.size() < 2) {
        return;
    }
    SongField field = featureField(feature);
    quickSortRange(songs, 0, static_cast<int>(songs.size()) - 1, field, descending);
}
