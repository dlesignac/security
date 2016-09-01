all: compile

test: compile
	./stegano_code

compile: obj/main.o
	gcc -o stegano_code obj/main.o

obj/main.o: obj/
	gcc -o obj/main.o -c src/main.c

obj/:
	mkdir obj/

clean:
	rm -rf obj/

mrproper:
	rm -rf stegano_code
