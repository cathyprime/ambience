FLAGS := -l:libraylib.a -lm -pthread
INCLUDES := -L./external/raylib-5.0_linux_amd64/lib/ -I./external/raylib-5.0_linux_amd64/include/

debug: bin
	clang++ -O0 -ggdb main.cc data.cc -o bin/main $(FLAGS) $(INCLUDES)

build: bin
	clang++ -O3 main.cc data.cc -o bin/main $(FLAGS) $(INCLUDES)

bin:
	mkdir -p bin
