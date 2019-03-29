#ifndef BOGGLE_H_
#define BOGGLE_H_

typedef struct boggle boggle;
boggle *create_boggle(int size);
void free_boggle(boggle *);
int boggle_contains(boggle *, const char *word);
void shuffle_boggle(boggle *b);
void print_boggle(boggle *b);
#endif

