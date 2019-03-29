#ifndef COMMON_H_
#define COMMON_H_
#include "./boggle.h"
extern char *strdup(const char *);
int readline(char *s);
void upcase(char *s);
void randomize(void);
int readint(const char *prompt);
int readintrange(const char *prompt, int x, int y);
int readyn(const char *prompt);
char** readstrlist(const char *prompt, int time, boggle *b);
void freestrlist(char **);
#endif

