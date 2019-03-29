#ifndef PLAYER_H_
#define PLAYER_H_
#include <stdio.h>
#include "boggle.h"
typedef struct player player;
void player_set_name(player *p, const char *s);
void player_set_is_computer(player *p, int val);
void player_input(player *, boggle *b);
void player_print(player *);
void player_get_result(player *, boggle *);
void player_free(player *);
player *player_create();
int player_get_score(player *);
const char *player_get_name(player *);
#endif

