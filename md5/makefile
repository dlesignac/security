
all: compile

test: compile
	./md5 test/input

compile: obj/bithandling.o obj/io.o obj/md5.o
	gcc -o md5 obj/bithandling.o obj/io.o obj/md5.o -std=c99

obj/md5.o: obj/ src/md5.c src/bithandling.h src/io.h
	gcc -o obj/md5.o -c src/md5.c -Wall -std=c99

obj/bithandling.o: obj/ src/bithandling.c
	gcc -o obj/bithandling.o -c src/bithandling.c -Wall -std=c99

obj/io.o: obj/ src/io.c
	gcc -o obj/io.o -c src/io.c -Wall -std=c99

obj/:
	mkdir obj

clean:
	rm -rf obj/

mrproper:
	rm -rf md5
