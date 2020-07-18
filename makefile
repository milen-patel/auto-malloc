all : main.o AutoMalloc.o
	gcc build/main.o build/AutoMalloc.o -o main -lm
	mv main ./build

main.o : src/main.c directories
	gcc -c -I include/ src/main.c
	mv main.o ./build/

AutoMalloc.o : src/AutoMalloc.c directories
	gcc -c -I include/ src/AutoMalloc.c
	mv AutoMalloc.o ./build/

.PHONY: clean
clean:
	rm -rf ./build/
	mkdir build

.PHONY: run
run:
	./build/main

.PHONY: leak-test
leak-test:
	valgrind --leak-check=full --track-origins=yes ./build/main

.PHONY: directories
directories: 
	mkdir -p build
