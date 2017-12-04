ELF=main
SRC=$(shell find -name '*.cpp')
OBJ=$(SRC:.cpp=.o)

CC=g++ -g -lpthread -lsqlite3
CXX=g++ -g
$(ELF):$(OBJ)
	$(CC) $(OBJ) -o $(ELF)
clean:
	rm -f $(OBJ) $(ELF)
all:
	make clean;make
