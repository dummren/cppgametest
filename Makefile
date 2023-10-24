all: clean struct data lin64 win32

lin64:
	g++ -o bin/game \
		$(shell find src/ -type f -name '*.cpp') \
		$(shell find lib/lin64/ -type f -name '*.a') \
		-I./src/ -I./include/all -I./include/lin64/ \
		-lGL -lGLEW -lglfw -lopenal -lfreetype \
		-std=c++23 -s

lin64-debug:
	g++ -g -o bin/game \
		$(shell find src/ -type f -name '*.cpp') \
		$(shell find lib/lin64/ -type f -name '*.a') \
		-I./src/ -I./include/all -I./include/lin64/ \
		-lGL -lGLEW -lglfw -lopenal -lfreetype \
		-std=c++23

win32:
	i686-w64-mingw32-g++ -o bin/game.exe \
		$(shell find src/ -type f -name '*.cpp') \
		$(shell find lib/win32/ -type f -name '*.a') \
		-I./src/ -I./include/all -I./include/win32/ \
		-lopengl32 -lgdi32 -lglu32 \
		-static-libgcc -static-libstdc++ \
		-Wl,-Bstatic -lstdc++ -lwinpthread -Wl,-Bdynamic\
		-std=c++23 -s -Wno-volatile

win32-debug:
	i686-w64-mingw32-g++ -g -o bin/game.exe \
		$(shell find src/ -type f -name '*.cpp') \
		$(shell find lib/win32/ -type f -name '*.a') \
		-I./src/ -I./include/all -I./include/win32/ \
		-lopengl32 -lgdi32 -lglu32 \
		-static-libgcc -static-libstdc++ \
		-Wl,-Bstatic -lstdc++ -lwinpthread -Wl,-Bdynamic\
		-std=c++23 -Wno-volatile

.PHONY: data
data:
	cp -r data/ bin/

struct:
	mkdir -p bin/

clean:
	rm -rf bin/*
