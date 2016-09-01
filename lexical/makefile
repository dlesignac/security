all: compile

test: compile
	touch obj/tmp
	hexdump -v -e '/1 "%02x"' test/test.txt > obj/tmp
	./analyzer < obj/tmp

compile: obj/
	flex -o obj/yy.lex.c src/analyzer.lex
	gcc obj/yy.lex.c -o analyzer

obj/:
	mkdir obj

clean:
	rm -rf obj/

mrproper:
	rm -rf analyzer
