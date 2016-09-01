
all: compile

compile: sentry grantee intruder

sentry: obj/server.o obj/sentry.o
	gcc -o sentry obj/server.o obj/sentry.o

obj/sentry.o: obj/ src/sentry.c src/server.h
	gcc -o obj/sentry.o -c src/sentry.c -Wall

obj/server.o: obj/ src/server.c
	gcc -o obj/server.o -c src/server.c -Wall

grantee: obj/client.o obj/grantee.o
	gcc -o grantee obj/client.o obj/grantee.o

obj/grantee.o: obj/ src/grantee.c src/client.h
	gcc -o obj/grantee.o -c src/grantee.c -Wall

intruder: obj/client.o obj/intruder.o
	gcc -o intruder obj/client.o obj/intruder.o

obj/intruder.o: obj/ src/intruder.c src/client.h
	gcc -o obj/intruder.o -c src/intruder.c -Wall

obj/client.o: obj/ src/client.c
	gcc -o obj/client.o -c src/client.c -Wall

obj/:
	mkdir obj

clean:
	rm -rf obj/

mrproper:
	rm -rf sentry grantee intruder
