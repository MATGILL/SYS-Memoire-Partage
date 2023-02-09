CFLAGS = -Wall -g

all : bin/tp3 bin/nettoie


bin/tp3: obj/tp3.o
		gcc -o bin/tp3 obj/tp3.o

bin/nettoie: obj/nettoie.o
		gcc -o bin/nettoie obj/nettoie.o

obj/tp3.o: src/tp3.c 
		gcc $(CFLAGS) -I./include -c src/tp3.c -o obj/tp3.o

obj/nettoie.o: src/nettoie.c
		gcc $(CFLAGS) -I./include -c src/nettoie.c -o obj/nettoie.o