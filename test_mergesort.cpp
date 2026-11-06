#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "DataLoader.h"
#include "Mergesort.h"

using namespace std;

int failures = 0;

// mergeSort is correct if (1) the values are in order and (2) no song was lost or duplicated.
void check(const string& name, vector<Song> songs, const string& feature, bool descending) {
    SongField field = featureField(feature);
    vector<Song> original = songs;
    mergeSort(songs, feature, descending);

    bool inOrder = true;
    for (size_t i = 1; i < songs.size(); i++) {
        double prev = songs[i - 1].*field;
        double cur = songs[i].*field;
        if (descending ? prev < cur : prev > cur) { inOrder = false; break; }
    }

    auto ids = [](const vector<Song>& v) {
        vector<string> out;
        for (const Song& s : v) out.push_back(s.trackId);
        sort(out.begin(), out.end());
        return out;
    };
    bool sameSongs = ids(songs) == ids(original);

    bool pass = inOrder && sameSongs;
    if (!pass) failures++;
    cout << (pass ? "[PASS] " : "[FAIL] ") << name << " (" << feature
         << (descending ? ", desc" : ", asc") << ", n=" << songs.size() << ")\n";
}

vector<Song> makeSongs(const vector<double>& energies) {
    vector<Song> songs;
    for (size_t i = 0; i < energies.size(); i++) {
        Song s;
        s.trackId = "id" + to_string(i);
        s.energy = energies[i];
        songs.push_back(s);
    }
    return songs;
}

int main(int argc, char* argv[]) {
    // Edge cases
    check("empty", makeSongs({}), "energy", true);
    check("one song", makeSongs({0.5}), "energy", true);
    check("two songs", makeSongs({0.1, 0.9}), "energy", true);
    check("all equal", makeSongs(vector<double>(50000, 0.7)), "energy", true);

    vector<double> sorted(50000);
    for (int i = 0; i < 50000; i++) sorted[i] = i;
    check("already sorted", makeSongs(sorted), "energy", false);
    check("reverse sorted", makeSongs(sorted), "energy", true);

    mt19937 rng(42);
    uniform_int_distribution<int> fewValues(0, 11);
    vector<double> dupes(50000);
    for (double& d : dupes) d = fewValues(rng);
    check("only 12 distinct values", makeSongs(dupes), "energy", true);

    // Real data: every feature, both directions, plus timing vs std::sort
    if (argc > 1) {
        vector<Song> all = loadSongs(argv[1]);
        cout << "\nLoaded " << all.size() << " songs from " << argv[1] << "\n";

        vector<string> features = {"popularity", "danceability", "energy", "key", "loudness",
                                   "speechiness", "acousticness", "liveness", "valence",
                                   "tempo", "instrumentalness"};
        for (const string& f : features) {
            check("full dataset", all, f, true);
            check("full dataset", all, f, false);
        }

        vector<Song> pop = filterByGenre(all, "pop");
        check("pop genre only", pop, "danceability", true);

        cout << "\nTiming on all " << all.size() << " songs (average of 5 runs):\n";
        for (const string& f : {string("popularity"), string("danceability"), string("key")}) {
            SongField field = featureField(f);
            double ours = 0, stl = 0;
            for (int run = 0; run < 5; run++) {
                vector<Song> a = all, b = all;
                auto t0 = chrono::high_resolution_clock::now();
                mergeSort(a, f, true);
                auto t1 = chrono::high_resolution_clock::now();
                sort(b.begin(), b.end(), [field](const Song& x, const Song& y) { return x.*field > y.*field; });
                auto t2 = chrono::high_resolution_clock::now();
                ours += chrono::duration<double, milli>(t1 - t0).count();
                stl += chrono::duration<double, milli>(t2 - t1).count();
            }
            cout << "  " << f << ": mergeSort " << ours / 5 << " ms, std::sort " << stl / 5 << " ms\n";
        }
    } else {
        cout << "\nTip: Pass the path to 'spotify_dataset.csv' as a command-line argument to test full dataset parsing and sorting.\n";
    }

    cout << "\n" << (failures == 0 ? "All tests passed." : to_string(failures) + " test(s) failed.") << "\n";
    return failures == 0 ? 0 : 1;
}