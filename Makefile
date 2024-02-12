INCLUDE = -Iraylib/include
LIBS = -Lraylib/libs

.PHONY: all main

main :
	gcc main.c -o main $(INCLUDE) $(LIBS) -lraylib

all : main
