#ifndef DICT_H_
#define DICT_H_


void dict_init(void);
void dict_free(void);
void dict_loadwords(const char *filename);
int dict_findword(const char *name);
char **dict_begin();
char **dict_end();

int word_point(const char *word);
#endif

