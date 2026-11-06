#include <chrono>
#include "SortTimer.h"
#include "Mergesort.h"
#include "quicksort.h"

SortResult runSorts(vector<Song> &allSongs, string genre, string feature) {
    SortResult result;

    //Only keep the songs from the genre the user picked
    vector<Song> genreSongs = filterByGenre(allSongs, genre);
 
    //Make two copies so both sorts start with the same unsorted data
    vector<Song> mergeSongs = genreSongs;
    vector<Song> quickSongs = genreSongs;
 
    //Time merge sort (true = highest first)
    auto mergeStart = chrono::high_resolution_clock::now();
    mergeSort(mergeSongs, feature, true);
    auto mergeEnd = chrono::high_resolution_clock::now();
    result.mergeTime = chrono::duration<double, milli>(mergeEnd - mergeStart).count();
 
    //Time quick sort (true = highest first)
    auto quickStart = chrono::high_resolution_clock::now();
    quickSort(quickSongs, feature, true);
    auto quickEnd = chrono::high_resolution_clock::now();
    result.quickTime = chrono::duration<double, milli>(quickEnd - quickStart).count();

    //Save the sorted songs so the display can use them
    result.sortedSongs = mergeSongs;

    return result;
}
