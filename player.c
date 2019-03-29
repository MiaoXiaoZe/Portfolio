#include "./player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "dict.h"
struct player {
    char name[BUFSIZ];
    int score;
    char **input;
    int is_computer;
};

void player_set_name(player *p, const char *s) {
    strncpy(p->name, s, sizeof(p->name));
}

void player_set_is_computer(player *p, int val) {
    p->is_computer = val;
}

void player_input(player *p, boggle *b) {
    printf("It's %s's turn\n", p->name);
    if (!p->is_computer) {
        p->input = readstrlist("Please enter your words, you have only 03:00 left", 3 * 60, b);
    } else {
        char s[10];
        puts("Press any key to continue");
        fgets(s, 10, stdin);
        p->input = dict_begin();
    }
}

void player_print(player *p) {
    printf("%s: Score %d\n", p->name, p->score);
}

void player_get_result(player *p, boggle *b) {
    int sum = 0;
    for (int i = 0; p->input[i]; ++i) {
        if (boggle_contains(b, p->input[i])) {
            int c = word_point(p->input[i]);
            if (c > 0) {
                sum += c;
                printf("%s(%d)\n", p->input[i], c);
            }
        }
    }
    printf("Total score for %s this round: %d\n", p->name, sum);
    p->score += sum;
    if (!p->is_computer) {
        freestrlist(p->input);
        p->input = 0;
    }
}

void player_free(player *p) {
    if (!p->is_computer) {
        if (p->input) {
            freestrlist(p->input);
            p->input = 0;
        }
    }
    free(p);
}

player *player_create() {
    player* p =  calloc(1, sizeof(player));
    p->score = 0;
    return p;
}

int player_get_score(player *p) {
    return p->score;
}

const char *player_get_name(player *p) {
    return p->name;
}

