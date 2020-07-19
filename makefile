all : main.o AutoMalloc.o Internal_Array.o Guards.o AutoMalloc_String.o
	gcc build/main.o build/AutoMalloc.o build/Internal_Array.o build/Guards.o build/AutoMalloc_String.o  -o main -lm
	mv main ./build

main.o : src/main.c directories
	gcc -c -I include/ src/main.c
	mv main.o ./build/

AutoMalloc.o : src/AutoMalloc.c directories
	gcc -c -I include/ src/AutoMalloc.c
	mv AutoMalloc.o ./build/

Internal_Array.o : src/Internal_Array.c directories
	gcc -c -I include/ src/Internal_Array.c
	mv Internal_Array.o ./build/

AutoMalloc_String.o : src/AutoMalloc_String.c directories
	gcc -c -I include/ src/AutoMalloc_String.c
	mv AutoMalloc_String.o ./build/

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
