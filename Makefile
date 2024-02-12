INCLUDE = -Iraylib/include
LIBS = -Lraylib/libs

main :
	gcc main.c -o main $(INCLUDE) $(LIBS) -lraylib

all : main
