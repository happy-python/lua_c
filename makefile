build:
	gcc -std=c99 -Wall ./lib/lua/src/*.c ./*.c -o main -o main
run:
	./main