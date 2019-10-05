.DEFAULT_GOAL := dogma-editor

CFLAGS = -g -fno-stack-protector -Iinclude -fpermissive -Isrc -lGL -lglfw -lm

#PY_CFLAGS  := $(shell python2-config --cflags)
#PY_LDFLAGS := $(shell python2-config --ldflags)

LDFLAGS := -lpthread -ldl

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
	g++ $(CFLAGS) $(LDFLAGS) $^ -o$@
