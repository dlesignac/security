
all: check

check: reference
	python3 src/main.py ./test/ obj/check
	diff obj/ref obj/check

reference: obj/
	python3 src/main.py ./test/ obj/ref

obj/:
	mkdir obj

clean:
	rm -rf obj/
