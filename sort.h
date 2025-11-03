#ifndef SORT
#define SORT

#include "stringProcessor.h"

// Функція обміну двох рядків (покажчиків на char)
void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

// Допоміжна функція для розділення масиву (partition)
size_t partition(char** arr, size_t low, size_t high) {
    char* pivot = arr[high];  // Останній елемент як опорний
    size_t i = low;

    for (size_t j = low; j < high; j++) {
        // Порівнюємо рядки за алфавітом
        if (strcmp(arr[j], pivot) < 0) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

// Допоміжна рекурсивна функція для швидкого сортування
void quick_sort_recursive(char** arr, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(arr, low, high);

        if (pi > 0)  // Запобігаємо переповненню для size_t
            quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

// Основна функція швидкого сортування
void quick_sort(char** arr, size_t length) {
    if (arr == nullptr || length <= 1) return;
    quick_sort_recursive(arr, 0, length - 1);
}

#endif // !SORT