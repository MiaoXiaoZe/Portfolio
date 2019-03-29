CFLAGS = -std=c11 -Wall -Wpedantic -Wextra -Werror $(DEBUG)
LDFLAGS = -O3 -Os

main: main.o boggle.o game.o player.o dict.o common.o
	$(CC) -o main main.o boggle.o game.o player.o dict.o common.o $(LDFLAGS)

main.o: main.c 
	$(CC) -c main.c $(CFLAGS)

game.o: game.c game.h
	$(CC) -c game.c $(CFLAGS)

player.o: player.c player.h
	$(CC) -c player.c $(CFLAGS)

boggle.o: boggle.c boggle.h
	$(CC) -c boggle.c $(CFLAGS)	

dict.o: dict.c dict.h
	$(CC) -c dict.c $(CFLAGS)	

common.o: common.c common.h
	$(CC) -c common.c $(CFLAGS)

.PHONY:clean

clean:
	rm *.o main