/* ---------------------------
Labo        |   ASD2022_L1_COMPLEXITE
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   21.02.2024
Deadline    |   05.03.2024 (2359)
Goal        |   Main file for the generation of csv files that contain the operation counts of different sorting algorithms
Note        |   -
Source      |   -
--------------------------- */

#include "generateVector.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <array>
#include <functional>
#include "customSorts.h"
#include "generateVector.h"

using namespace std;
// Represents a sorting algorithm function
using SortFunction = function<void(vector<int>&)>;
const unsigned SEED = 666;
const size_t TOTAL_ALGORITHMS = 5;
const size_t TOTAL_TYPES_VECTOR = 4;
// Represents the sizes of the vectors to be generated
const array<size_t, 10> sizes = { 10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 10000 };
// Represents the types of vectors to be generated
const array<pair<string, Type>, TOTAL_TYPES_VECTOR> typesVector = {
        make_pair("increasing", Type::INCREASING),
        make_pair("decreasing", Type::DECREASING),
        make_pair("random", Type::RANDOM),
        make_pair("almost", Type::ALMOST)
};

/* ---------------------------
Name        | getFileName
Parameter(s)| string basePath, const pair<string, Type> &sortTypes
Return      | string
Goal        | Generate the file name for the csv file
--------------------------- */
string getFileName(string basePath, const pair<string, Type> &sortTypes) {
    return basePath + "/time_measurement_" + sortTypes.first + ".csv";
}

/* ---------------------------
Name        | exportCSV
Parameter(s)| const string &fileName, const vector<vector<double>> &executionTimes
Return      | -
Goal        | Export the operation counts to a csv file
--------------------------- */
void exportCSV(const string &fileName, const vector<vector<double>> &executionTimes) {
    fstream file(fileName, ios::out);
    if (!file.is_open()) {
        cerr << "Could not open file for writing" << endl;
        return;
    }
    file << "size,bubble_sort,selection_sort,insertion_sort,sort,stable_sort" << endl;
    for (size_t i = 0; i < sizes.size(); ++i) {
        file << sizes[i] << ",";
        for (size_t j = 0; j < TOTAL_ALGORITHMS; ++j) {
            file << fixed << setprecision(6) << executionTimes[i][j] << (j == TOTAL_ALGORITHMS - 1 ? "\n" : ",");
        }
    }
}

/* ---------------------------
Name        | measureTime
Parameter(s)| SortFunction &sortFunction, vector<int> &vector
Return      | -
Goal        | Measure the time it takes to sort a vector per algorithm
--------------------------- */
double measureTime(SortFunction &sortFunction, vector<int> &vector) {
    auto start = chrono::high_resolution_clock::now();
    sortFunction(vector);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, milli>(end - start).count();
}

/* ---------------------------
Name        | runSorts
Parameter(s)| const array<pair<string, Type>, TOTAL_TYPES_VECTOR> &vectorTypes, const array<SortFunction, TOTAL_ALGORITHMS> &functionAlgorithms
Return      | -
Goal        | Run the sorting algorithms and export the duration to csv files
--------------------------- */
void runSorts(const array<pair<string, Type>, TOTAL_TYPES_VECTOR> &vectorTypes, const array<SortFunction, TOTAL_ALGORITHMS> &functionAlgorithms) {
    for(size_t i = 0; i < vectorTypes.size(); ++i) {
        vector<vector<double>> allExecutionTimes;
        for (size_t size : sizes) {
            vector<double> executionTimesLineCSV;
            for(auto func : functionAlgorithms) {
                vector<int> generatedVector = generateVector<int>(size, SEED, vectorTypes[i].second);
                executionTimesLineCSV.push_back(measureTime(func, generatedVector));
            }
            allExecutionTimes.push_back(executionTimesLineCSV);
        }
        exportCSV(getFileName("../../rapport/csv", vectorTypes[i]), allExecutionTimes);
    }
}

int main() {
    array<SortFunction, TOTAL_ALGORITHMS> functionAlgorithms =  {
            [](vector<int> &vec) { bubbleSort<int>(vec);},
            [](vector<int> &vec) { selectionSort<int>(vec); },
            [](vector<int> &vec) { insertionSort<int>(vec); },
            [](vector<int> &vec) { sort(vec.begin(),vec.end()); },
            [](vector<int> &vec) { stable_sort(vec.begin(),vec.end()); }
    };
    runSorts(typesVector, functionAlgorithms);
}