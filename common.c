#include "./common.h"
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void randomize() {
#ifdef SEED
    srand(SEED);
#else
    srand(time(0));
#endif
}

int readline(char *s) {
    char* ret = fgets(s, BUFSIZ, stdin);
    if (ret) {
        for (int i = 0; i < BUFSIZ; ++i) {
            if (s[i] == '\n') {
                s[i] = '\0';
            }
            if (s[i] == '\0') {
                return 1;
            }
        }
        s[BUFSIZ - 1] = '\0';
    }
    return ret != NULL;
}


void upcase(char *s) {
    for (int i = 0; s[i]; ++i) {
        s[i] = toupper(s[i]);
    }
}

int readint(const char *prompt) {
    static char s[BUFSIZ];
    while (1) {
        printf("%s> ", prompt);
        readline(s);
        char *end;
        int k = strtol(s, &end, 10);
        if (!end || end[0] != 0) {
            puts("Please input a number!");
            continue;
        } else {
            return k;
        }
    }
}

int readintrange(const char *prompt, int l, int r) {
    static char s[BUFSIZ];
    if (r == -1) {
        snprintf(s, sizeof(s), "%s(>=%d)", prompt, l);
        while (1) {
            int k = readint(s);
            if (k < l) {
                printf("Please input a number >= %d", l);
            } else {
                return k;
            }
        }
    } else {
        snprintf(s, sizeof(s), "%s(%d-%d)", prompt, l, r);
        while (1) {
            int k = readint(s);
            if (k < l || k > r) {
                printf("Please input a number in the range [%d, %d]", l, r);
            } else {
                return k;
            }
        }
    }
}

int readyn(const char *prompt) {
    static char s[BUFSIZ], t[BUFSIZ];
    snprintf(s, sizeof(s), "%s(y/Y/n/N)> ", prompt);
    puts(s);
    while (1) {
        readline(t);
        if (t[1] != '\0' || !strchr("YyNn", t[0])) {
            puts("Please answer using Y,y,n or N");
        } else {
            return t[0] == 'Y' || t[0] == 'y';
        }
    }
}


static int isalphabet(const char *s) {
    for (int i = 0; s[i]; ++i) {
        if (!isalpha(s[i])) {
            return 0;
        }
    }
    return 1;
}

char **readstrlist(const char *prompt, int rest, boggle *b) {
    static char s[BUFSIZ];
    char **list = NULL;
    int count = 0;

    puts(prompt);
    puts("Press enter to start timing");
    readline(s);
    print_boggle(b);
    puts("");
    int start = time(NULL);
    while (1) {
        int t = time(NULL);
        int k = rest - (t - start);
        printf("\033[1T");
        printf("                                                             \n");
        printf("\033[1T");
        printf("Time left - %02d:%02d> ", k / 60, k % 60);
        readline(s);
        t = time(NULL);
        k = rest - (t - start);
        if (k <= 0) {
            puts("Time over, press enter to continue");
            readline(s);
            list = realloc(list, sizeof(char *) * (count + 1));
            list[count] = NULL;
            return list;
        }
        if (!isalphabet(s)) {
            puts("Please enter only letters");
            continue;
        }
        int dup = 0;
        upcase(s);
        for (int i = 0; i < count; ++i) {
            if (!strcmp(list[i], s)) {
                dup = 1;
                break;
            }
        }
        if (!dup) {
            list = realloc(list, sizeof(char *) * (count + 1));
            list[count] = strdup(s);
            ++count;
        }
    }
}

void freestrlist(char **s) {
    for (int i = 0; s[i]; ++i) {
        free(s[i]);
    }
    free(s);
}

