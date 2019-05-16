all: UNO

main.o: main.c baraja.h conf.h game.h CLIplayer.h
	gcc -c main.c


baraja.o: baraja.c baraja.h
	gcc -c baraja.c


conf.o: conf.h conf.c players.h confplayers.h
    gcc -c conf.c

game.o: game.c game.h baraja.h players.h hands.h
    gcc -c game.c

confplayers.o: confplayers.c confplayers.h players.h hands.h
    gcc -c confplayers.c


UNO: main.o baraja.o conf.o confplayers.o game.o
	gcc main.o baraja.o conf.o confplayers.o game.o -o UNO.exe