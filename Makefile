TARGET	= gol

CC			=	gcc
CFLAGS	= -Wall

SRC			=	src
BIN			=	bin
OBJ			=	obj

LIB			=	-lncurses

all: $(BIN)/$(TARGET)

$(BIN)/$(TARGET): $(OBJ)/gol.o
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $< -o $@ $(LIB)

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ)
	$(CC) -c $(CFLAGS) $< -o $@ $(LIB)

clean:
	rm -rf $(OBJ) $(BIN)
