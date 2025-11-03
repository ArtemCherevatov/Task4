#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR

#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include "sort.h"

#define STRING_MAX 512ull

// Функція для отримання рядка від користувача
const int32_t get_str(const char const* msg, char* str, const int32_t limit) {
    printf("%s", msg);

    if (fgets(str, limit, stdin) != NULL) {
        // Видаляємо символ нового рядка
        size_t len = 0;
        while (str[len] != '\0') {
            if (str[len] == '\n') {
                str[len] = '\0';
                break;
            }
            len++;
        }
        return (int32_t)len;
    }
    return -1;
}

// Функція для обчислення довжини рядка
const size_t strlenn(const char* str) {
    if (str == NULL) return 0;

    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Функція для копіювання рядка
void strcopy(char* fStr, char* sStr, size_t until) {
    if (fStr == NULL || sStr == NULL) return;

    for (size_t i = 0; i < until && sStr[i] != '\0'; i++) {
        fStr[i] = sStr[i];
    }
    fStr[until] = '\0';
}

// Функція для порівняння рядків
int32_t strcmpp(const char* fStr, const char* sStr) {
    if (fStr == NULL && sStr == NULL) return 0;
    if (fStr == NULL) return -1;
    if (sStr == NULL) return 1;

    size_t i = 0;
    while (fStr[i] != '\0' && sStr[i] != '\0') {
        if (fStr[i] != sStr[i]) {
            return (int32_t)(fStr[i] - sStr[i]);
        }
        i++;
    }
    return (int32_t)(fStr[i] - sStr[i]);
}

// Функція конкатенації (вже реалізована)
char* strcatt(char* fStr, const char* sStr) {
    char* ptr = fStr + strlenn(fStr);
    while (*sStr != '\0') {
        *ptr++ = *sStr++;
    }
    *ptr = '\0';
    return fStr;
}

// Функція перевірки валідності рядка (вже реалізована)
bool is_string_valid(char* str) {
    bool isThereString = false;
    bool isThereColon = false;
    const size_t size = strlenn(str);
    for (size_t i = 0; i < size; i++) {
        if ((str[i] == ':' || str[i] == ';' || str[i] == ',') && i == 0ull) {
            return false;
        }
        if (str[i] == ':') {
            isThereColon = true;
        }
        else if (isThereColon) {
            if (str[i] == ',') {
                if (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' ') {
                    return false;
                }
                else {
                    isThereString = true;
                }
            }
            if (str[i] == ';') {
                if (!isThereString || (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' ')) {
                    return false;
                }
                else {
                    isThereColon = false;
                }
            }
            if (str[i] == ':') {
                return false;
            }
        }
        else {
            isThereString = false;
        }
    }
    return true;
}

// Функція обробки рядка (вже реалізована)
char* process_string(char* str) {
    const size_t length = strlenn(str);
    char* result = (char*)calloc(length, sizeof(char));
    for (size_t i = 0; i < length; i++) {
        if (str[i] != ':') {
            char temp[2] = { str[i], '\0' };
            strcatt(result, temp);
            continue;
        }
        if (str[i + 1] != ' ') {
            return NULL;
        }
        strcatt(result, ": ");
        const size_t strsPreCnt = 100;
        char** arr = (char**)calloc(strsPreCnt, sizeof(char*));
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++) {
            arr[strsCnt] = (char*)calloc(STRING_MAX, sizeof(char));
        }
        for (size_t j = i + 2ull, strRealCnt = 0ull; j < length; j++) {
            if (str[j] == ',') {
                ++strRealCnt;
                ++j;
            }
            else if (str[j] == ';') {
                quick_sort(arr, ++strRealCnt);
                for (size_t k = 0; k < strRealCnt; k++) {
                    strcatt(result, arr[k]);
                    if (k == strRealCnt - 1ull) {
                        strcatt(result, ";");
                    }
                    else {
                        strcatt(result, ", ");
                    }
                }
                i = j;
                break;
            }
            else {
                char temp[2] = { str[j], '\0' };
                strcatt(arr[strRealCnt], temp);
            }
        }
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++) {
            free(arr[strsCnt]);
        }
        free(arr);
    }
    return result;
}

#endif