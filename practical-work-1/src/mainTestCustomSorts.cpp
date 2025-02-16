/* ---------------------------
Labo        |   ASD2022_L1_COMPLEXITE
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   21.02.2024
Deadline    |   05.03.2024 (2359)
Goal        |   Main file for the custom sorts
Note        |   -
Source      |   -
--------------------------- */

#include <iostream>
#include "customSorts.h"

using namespace std;

int main() {
    vector<int> vec = {3, 2, 1, 5, 4, 43};
    vector<int> vec2 = {2, 1, 4, 6, 10, 3};
    vector<int> vec3 = {2, 10, 3, 910, 1, 20};
    bubbleSort<int>(vec);
    cout << "Bubble sort : ";
    for(auto i : vec) {
        cout << i << " ";
    }
    cout << endl;
    insertionSort<int>(vec2);
    cout << "Insertion sort : ";
    for(auto i : vec2) {
        cout << i << " ";
    }
    cout << endl;
    selectionSort<int>(vec3);
    cout << "Selection sort : ";
    for(auto i : vec3) {
        cout << i << " ";
    }
    cout << endl;
}