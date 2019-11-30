.DEFAULT_GOAL := dogma-editor

CFLAGS = -g -fno-stack-protector -Iinclude -fpermissive -Isrc -lGL -lm -Wno-write-strings

#PY_CFLAGS  := $(shell python2-config --cflags)
#PY_LDFLAGS := $(shell python2-config --ldflags)

LDFLAGS := -lpthread -ldl
LDFLAGS += $(shell pkg-config --static --libs glfw3)

SRCFILES := $(wildcard src/*.cpp) 
C_SRCFILES := $(wildcard src/*.c) 

OBJFILES := $(patsubst src/%.cpp,obj/%.o,$(SRCFILES)) 
OBJFILES += $(patsubst src/%.c,obj/%.o,$(C_SRCFILES)) 

clean:
	rm obj/*
	rm dogma-editor

obj/%.o: src/%.cpp
	g++ -c $(CFLAGS) $< -o $@

obj/%.o: src/%.c
	gcc -c $(CFLAGS) $< -o $@

dogma-editor: $(OBJFILES)
	g++ $(CFLAGS) $(LDFLAGS) external/glfw/build/src/libglfw3.a $^ -o$@
