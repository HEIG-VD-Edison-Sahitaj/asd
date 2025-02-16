/* ---------------------------
Labo        |   ASD2022_L1_COMPLEXITE
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   21.02.2024
Deadline    |   05.03.2024 (2359)
Goal        |   Main file for the generation of csv files that contain the operation counts of different sorting algorithms
Note        |   -
Source      |   -
--------------------------- */

#include <iostream>
#include <fstream>
#include "OpCounter.h"
#include "customSorts.h"
#include "generateVector.h"
#include <vector>
#include <algorithm>
#include <span>
#include <functional>

using namespace std;
// Represents a sorting algorithm function
using SortFunction = function<void(vector<OpCounter>&)>;
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
    return basePath + "/operation_count_" + sortTypes.first + ".csv";
}

/* ---------------------------
Name        | exportCSV
Parameter(s)| const string &fileName, const vector<vector<double>> &operationCounts
Return      | -
Goal        | Export the operation counts to a csv file
--------------------------- */
void exportCSV(const string &fileName, const vector<vector<double>> &operationCounts) {
    fstream file(fileName, ios::out);
    if (!file.is_open()) {
        cerr << "Could not open file for writing" << endl;
        return;
    }
    file << "size,bubbleSort_comparisons,bubbleSort_copy,insertionSort_comparisons,insertionSort_copy,selectionSort_comparisons,selectionSort_copy,sort_comparisons,sort_copy,stableSort_comparisons,stableSort_copy" << endl;
    for (size_t i = 0; i < sizes.size(); ++i) {
        file << sizes[i] << ",";
        for (size_t j = 0; j < TOTAL_ALGORITHMS*2; ++j) {
            file << operationCounts[i][j] << (j == TOTAL_ALGORITHMS*2 - 1 ? "\n" : ",");
        }
    }
}

/* ---------------------------
Name        | runSorts
Parameter(s)| const array<pair<string, Type>, TOTAL_TYPES_VECTOR> &vectorTypes, const array<SortFunction, TOTAL_ALGORITHMS> &functionAlgorithms
Return      | -
Goal        | Run the sorting algorithms and export the operation counts to csv files
--------------------------- */
void runSorts(const array<pair<string, Type>, TOTAL_TYPES_VECTOR> &vectorTypes, const array<SortFunction, TOTAL_ALGORITHMS> &functionAlgorithms) {
    for(size_t i = 0; i < vectorTypes.size(); ++i) {
        vector<vector<double>> allOperationCounts;
        for (size_t size : sizes) {
            vector<double> operationCountsLineCSV;
            for(auto func : functionAlgorithms) {
                vector<OpCounter> generatedVector = generateVector<OpCounter>(size, SEED, vectorTypes[i].second);
                OpCounter::resetPertinentOperations();
                func(generatedVector);
                operationCountsLineCSV.push_back(OpCounter::getPertinentComparaisons());
                operationCountsLineCSV.push_back(OpCounter::getPertinentCopy());
                OpCounter::resetPertinentOperations();
            }
            allOperationCounts.push_back(operationCountsLineCSV);
        }
        exportCSV(getFileName("../../rapport/csv", vectorTypes[i]), allOperationCounts);
    }
}


int main() {
    array<SortFunction, TOTAL_ALGORITHMS> functionAlgorithms =  {
            [](vector<OpCounter> &vec) { bubbleSort<OpCounter>(vec);},
            [](vector<OpCounter> &vec) { selectionSort<OpCounter>(vec); },
            [](vector<OpCounter> &vec) { insertionSort<OpCounter>(vec); },
            [](vector<OpCounter> &vec) { sort(vec.begin(),vec.end()); },
            [](vector<OpCounter> &vec) { stable_sort(vec.begin(),vec.end()); }
    };
    runSorts(typesVector, functionAlgorithms);
}