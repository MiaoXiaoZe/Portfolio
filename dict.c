#include "./dict.h"
#include "./common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


static char **words;
static int count = 0;
static int capacity = 0;

void dict_init(void) {
    words = calloc(5, sizeof(char *));
    capacity = 5;
}

void dict_free(void) {
    if (words) {
        for (int i = 0; i < count; ++i) {
            if (words[i]) {
                free(words[i]);
            }
        }
        free(words);
        words = 0;
    }
}

static void dict_insert_word(const char *word) {
    if (count >= capacity) {
        capacity *= 2;
        words = realloc(words, sizeof(char *) * capacity);
    }
    if (word) {
        words[count++] = strdup(word);
    } else {
        words[count++] = NULL;
    }
}

static int dict_compare(const void *a, const void *b) {
    char **str1 = (char **)a;
    char **str2 = (char **)b;
    return strcmp(*str1, *str2);
}

void dict_loadwords(const char *filename) {
    FILE *fp = fopen(filename, "r");
    static char s[BUFSIZ];
    while (fgets(s, sizeof(s), fp)) {
        char *end = strchr(s, '\n');
        if (end) {
            *end = '\0';
        } else {
            s[BUFSIZ - 1] = '\0';
        }
        if (strlen(s) < 3) {  // only words that have length > 3 count
            continue;
        }
        upcase(s);
        dict_insert_word(s);
    }
    fclose(fp);
    dict_insert_word(NULL);
    --count;
    qsort(words, count, sizeof(char *), dict_compare);
}

int dict_findword(const char *name) {
    return bsearch(&name, words, count, sizeof(char *), dict_compare) != 0;
}

char **dict_begin() {
    return &words[0];
}

char **dict_end() {
    return &words[count];
}

int word_point(const char *word) {
    if (!dict_findword(word)) {
        return -1;
    }
    int n = strlen(word);
    switch (n) {
    case 3:
    case 4:
        return 1;
    case 5:
        return 2;
    case 6:
        return 3;
    case 7:
        return 5;
    default:
        if (n >= 8) {
            return 11;
        }
        return -1;
    }
}

