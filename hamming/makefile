
all: compile

compile: obj/hamming.o
	gcc -lm -o hamming obj/hamming.o

obj/hamming.o: obj/ src/hamming.c
	gcc -o obj/hamming.o -c src/hamming.c -Wall

obj/:
	mkdir obj

clean:
	rm -rf obj/

mrproper:
	rm -rf hamming

test_pass: compile
	# Testing with parameters
	#   - alphabet size = 256
	#   - word_length = 9
	#   - min hamming distance = 2
	./hamming 256 9 2

test_fail: compile
	# Testing with parameters
	#   - alphabet size = 256
	#   - word_length = 8
	#   - min hamming distance = 2
	./hamming 256 8 2
