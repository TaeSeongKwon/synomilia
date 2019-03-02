CC=gcc -std=c++11
LINK=-lstdc++ \

SRC=src
OBJ=obj
HDR=-I./hdr \

install : synomilia_cli.exe
	
main : core
	$(CC) -g -o $(OBJ)/main $(SRC)/main.cpp $(OBJ)/core.o $(LINK) -lpthread $(HDR)

core : 
	$(CC) -c -o $(OBJ)/core.o $(SRC)/core.cpp $(LINK) $(HDR)

synomilia_cli.exe : 
	$(CC) -I$(HDR) -c $(SRC)/synomilia_cli.cpp -o $(OBJ)/synomilia_cli
