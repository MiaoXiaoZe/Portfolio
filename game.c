#include "./game.h"
#include <stdlib.h>
static boggle *b = NULL;
int mode;
player *p[3];
player *p1, *p2, *com;
int playercount;
int nround = 0;
void init(void) {
    randomize();
    dict_init();
    dict_loadwords("dict.txt");
    p1 = player_create();
    p2 = player_create();
    com = player_create();
    player_set_name(p1, "Player 1");
    player_set_name(p2, "Player 2");
    player_set_name(com, "Computer");
    player_set_is_computer(p1, 0);
    player_set_is_computer(p2, 0);
    player_set_is_computer(com, 1);
    int size = readintrange("What size of board will you play?", 3, -1);
    b = create_boggle(size);
    mode = readintrange("What mode will you play?\n\t1. Single Player\n\t2. Double Player\n\t3. Vs Computer", 1, 3);
    p[0] = p1;

    switch (mode) {
    case 1:
        playercount = 1;
        break;
    case 2:
        playercount = 2;
        p[1] = p2;
        break;
    case 3:
        playercount = 2;
        p[1] = com;
        break;
    }
}

void initgame(void) {
    static char s[BUFSIZ];
    printf("\n");
    printf("\n");
    printf("Round %d\n", ++nround);
    for (int i = 0; i < playercount; ++i) {
        player_print(p[i]);
    }
    printf("\n");
    printf("\n");
    shuffle_boggle(b);
    puts("Press Enter to continue");
    fgets(s, sizeof(s), stdin);
}

void cleanup(void) {
    player_free(com);
    player_free(p2);
    player_free(p1);
    free_boggle(b);
    dict_free();
}
void game(void) {
    for (int i = 0; i < playercount; ++i) {
        printf("\033[2J");
        player_input(p[i], b);
        player_get_result(p[i], b);
        static char s[BUFSIZ];
        readline(s);
    }
}

void endgame(void) {
    if (playercount == 1) {
        printf("Well done, you played for %d round(s)\n", nround);
        printf("You final result is\n");
        player_print(p[0]);
    } else {
        int a = player_get_score(p[0]);
        int b = player_get_score(p[1]);
        if (a == b) {
            printf("%d vs %d. Tie.\n", a, b);
        } else if (a > b) {
            printf("%d vs %d. %s wins\n", a, b, player_get_name(p[0]));
        } else {
            printf("%d vs %d. %s wins\n", a, b, player_get_name(p[1]));
        }
    }
}
