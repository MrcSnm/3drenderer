GCC := mingw32-gcc
GCC_FLAGS := -Wall -std=c99 -Winline -g
RELEASE_FLAGS := -O3 -ffast-math

INCLUDE_PATHS := -I"C:/SDL2/i686-w64-mingw32/include"
LIB_PATHS := -L"C:/SDL2/i686-w64-mingw32/lib"

LIBS :=  -lmingw32 -lSDL2main -lSDL2 -lm
SRC := ./src/*.c ./src/**/*.c

OUTPUT := renderer.exe

build:
	$(GCC) $(GCC_FLAGS) $(SRC) $(INCLUDE_PATHS) $(LIB_PATHS) $(LIBS) -o $(OUTPUT)

run:
	./renderer

all:
	mingw32-make build && mingw32-make run

fast:
	$(GCC) $(GCC_FLAGS) $(SRC) $(INCLUDE_PATHS) $(LIB_PATHS) $(LIBS) $(RELEASE_FLAGS) -o $(OUTPUT)

fast-all:
	mingw32-make fast && mingw32-make run

clean:
	rm renderers