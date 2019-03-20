
#include <stdio.h>
#include "game.h"




int main(void) {
    init();
    while (1) {
        initgame();
        game();
        if (readyn("Continue Game?")) {
            continue;
        } else {
            break;
        }
    }
    endgame();
    cleanup();
    return 0;
}


