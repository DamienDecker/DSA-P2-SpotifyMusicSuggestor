<H1> COP3530 - Project 2 </h1>
This repository contains the source code for **Team DSV's Spotify Song Suggestor,** developed in C++ using CLion, CMake, and SFML

<h2> Table of Contents </h2>

- [Project Overview](#project-overview)
- [Prerequisites & Dependencies](#prerequisites--dependencies)
- [Project Structure](#project-structure)
- [How to Build and Run](#how-to-build-and-run)
  - [1. Running the Frontend Application](#1-running-the-frontend-application)
  - [2. Running the Standalone Sorting Tests & Benchmarks](#2-running-the-standalone-sorting-tests--benchmarks)

## Project Overview
This project implements and compares Merge Sort and Quick Sort using the Spotify song dataset. It features an interactive graphical frontend built with SFML.

## Project Structure

- `main.cpp` / `Button.cpp/.h` – SFML graphical user interface components.
- `Song.cpp/.h` - Song Struct
- `Mergesort.cpp/.h` – Custom Merge Sort implementation.
- `QuickSort.cpp/.h` – Custom Quick Sort implementation.
- `SortTimer.cpp/.h` - Merge Sort and Quick Sort Timer
- `DataLoader.cpp/.h` – CSV parser for loading dataset entries.
- `test_mergesort.cpp` – Standalone test suite and performance benchmark runner.
- `resources/dataset.csv` – Spotify song dataset (~114k rows).
- `resources/arial.ttf` – Font file required for the UI.

## How to Build and Run

### 1. Running the Frontend Application

1. Open the project folder in **CLion**.
2. Go to **Run > Edit Configurations...** and select the **`DSA_P2_SpotifyMusicSuggestor`** target.
3. Ensure the **Working directory** is set to your project root folder (the top-level folder containing `CMakeLists.txt` and `resources/`).
4. Click the green **Run** button to launch the graphical app.

### 2. Running the Standalone Sorting Tests & Benchmarks

The standalone test suite validates edge cases (empty lists, duplicates, sorted order) and benchmarks performance against `std::sort` using the full dataset.

1. In CLion, select the **`test_mergesort`** or **`quicksort_test`** run configuration.
2. Ensure the **Working directory** is set to your project root folder.
3. In the **Program arguments** field, specify the path to the dataset:
   ```text
   resources/dataset.csv
   ```
  
