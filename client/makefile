CC=gcc -std=c++11
LINK=-lstdc++ \

SRC=src
OBJ=obj
HDR=-I./hdr \

install : synomilia_cli.exe
	
main : core packet
	$(CC) -g -o $(OBJ)/main $(SRC)/main.cpp $(OBJ)/core.o $(LINK) -lpthread $(HDR)

core : 
	$(CC) -c -o $(OBJ)/core.o $(SRC)/core.cpp $(LINK) $(HDR)
packet : 
	$(CC) -c -o $(OBJ)/packet.o $(SRC)/packet.cpp $(LINK) $(HDR)

synomilia_cli.exe : 
	$(CC) -I$(HDR) -c $(SRC)/synomilia_cli.cpp -o $(OBJ)/synomilia_cli
