/* ---------------------------
Labo        |   ASD2022_L1_COMPLEXITE
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   21.02.2024
Deadline    |   05.03.2024 (2359)
Goal        |   Header file for the custom sorts
Note        |   -
Source      |   -
--------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_CUSTOMSORTS_H
#define ASD2022_L1_COMPLEXITE_CUSTOMSORTS_H

#include <vector>
#include <algorithm>
#include <span>

/* ---------------------------
Name        | bubbleSort
Parameter(s)| std::span<T> vec
Return      | -
Goal        | Sorts the vector using the bubble sort algorithm
--------------------------- */
template<typename T>
void bubbleSort(std::span<T> vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

/* ---------------------------
Name        | insertionSort
Parameter(s)| std::span<T> vec
Return      | -
Goal        | Sorts the vector using the insertion sort algorithm
--------------------------- */
template <typename T>
void insertionSort(std::span<T> vec) {
  for(auto i = vec.begin() + 1; i != vec.end(); ++i) {
    auto key = *i;
    auto j = i - 1;
    while(j >= vec.begin() && *j > key) {
      *(j + 1) = *j;
      --j;
    }
    *(j + 1) = key;
  }
}

/* ---------------------------
Name        | selectionSort
Parameter(s)| std::span<T> vec
Return      | -
Goal        | Sorts the vector using the selection sort algorithm
--------------------------- */
template<typename T>
void selectionSort(std::span<T> vec) {
  for(auto i = vec.begin(); i != vec.end(); ++i) {
    std::swap(*i, *min_element(i, vec.end()));
  }
}

#endif //ASD2022_L1_COMPLEXITE_CUSTOMSORTS_H
