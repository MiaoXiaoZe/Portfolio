#include "./boggle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct boggle {
    int size;
    char **board;

//  for search
    int *visited;
};



boggle *create_boggle(int size) {
    boggle* b = calloc(1, sizeof(boggle));
    b->size = size;
    char **board = calloc(size, sizeof(char *));
    for (int i = 0; i < size; ++i) {
        board[i] = calloc(size, sizeof(char));
    }

    b->board   = board;
    b->visited = calloc(b->size * b->size, sizeof(int));
    return b;
}

void free_boggle(boggle *b) {
    if (b && b->board) {
        for (int i = 0; i < b->size; ++i) {
            if (b->board[i]) {
                free(b->board[i]);
            }
        }
        free(b->board);
    }
    if (b->visited) {
        free(b->visited);
    }
    free(b);
}

void shuffle_boggle(boggle *b) {
    for (int i = 0; i < b->size; ++i) {
        for (int j = 0; j < b->size; ++j) {
            b->board[i][j] = rand() % 26 + 'A';
        }
    }
}

void print_boggle(boggle *b) {
    for (int i = 0; i < b->size; ++i) {
        for (int j = 0; j < b->size; ++j) {
            printf(" %c ", b->board[i][j]);
        }
        puts("");
    }
}

static int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
static int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};


// Deep first search
int boggle_find(boggle *b, int i, int j, const char *word) {
    if (*word == '\0') {
        return 1;
    }
    if (b->board[i][j] != *word) {
        return 0;
    }
    if (word[1] == '\0') {
        return 1;
    }
    int ok = 0;
    b->visited[i * b->size + j] = 1;
    for (int k = 0; k < 8; ++k) {
        int ci = i + dx[k], cj = j + dy[k];
        if (ci < 0 || ci >= b->size || cj < 0 || cj >= b->size) {
            continue;
        }
        if (b->visited[ci * b->size + cj]) {
            continue;
        }
        if (boggle_find(b, ci, cj, word + 1)) {
            ok = 1;
            break;
        }
    }
    b->visited[i * b->size + j] = 0;
    return ok;
}

int boggle_contains(boggle *b, const char *word) {
    if (!b || !word) {
        return 0;
    }



    for (int i = 0; i < b->size; ++i) {
        for (int j = 0; j < b->size; ++j) {
            if (boggle_find(b, i, j, word)) {
                return 1;
            }
        }
    }
    return 0;
}
