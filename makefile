all : main.o AutoMalloc.o Vec.o Guards.o
	gcc build/main.o build/AutoMalloc.o build/Vec.o build/Guards.o -o main -lm
	mv main ./build

main.o : src/main.c directories
	gcc -c -I include/ src/main.c
	mv main.o ./build/

AutoMalloc.o : src/AutoMalloc.c directories
	gcc -c -I include/ src/AutoMalloc.c
	mv AutoMalloc.o ./build/

Vec.o : src/Vec.c directories
	gcc -c -I include/ src/Vec.c
	mv Vec.o ./build/

Guards.o : src/Guards.c directories
	gcc -c -I include/ src/Guards.c
	mv Guards.o ./build/

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
