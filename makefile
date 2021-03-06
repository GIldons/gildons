# Project: FireFlight - ECE453
# Write by Raul Matheus Martins
# Sponsored by Plexu and CAPES - Brazil

CPP  = g++
CC   = gcc 
RES  =
O_DIR = OBJ/
OBJ  = main.o screen.o basic.o game_logic.o screen_opt.o I_O.o neolib.o $(RES)
LINKOBJ  = $(O_DIR)main.o $(O_DIR)screen.o $(O_DIR)basic.o $(O_DIR)game_logic.o $(O_DIR)screen_opt.o $(O_DIR)I_O.o $(O_DIR)neolib.o $(RES)
LIBS =  -lSDL -lSDL_image -lSDL_ttf
INCS = 
CXXINCS = 
BIN  = main
CXXFLAGS =  -Wall -Wextra $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before main all-after


clean: clean-custom
	${RM} $(LINKOBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o "main" $(LIBS)

main.o: main.c
	$(CC) -c main.c -o $(O_DIR)main.o $(CXXFLAGS)

screen.o: screen.c
	$(CC) -c screen.c -o $(O_DIR)screen.o $(CXXFLAGS)

basic.o: basic.c
	$(CC) -c basic.c -o $(O_DIR)basic.o $(CXXFLAGS)
	
game_logic.o: game_logic.c
	$(CC) -c game_logic.c -o $(O_DIR)game_logic.o $(CXXFLAGS)
	
screen_opt.o: screen_opt.c
	$(CC) -c screen_opt.c -o $(O_DIR)screen_opt.o $(CXXFLAGS)
	
I_O.o: I_O.c
	$(CC) -c I_O.c -o $(O_DIR)I_O.o $(CXXFLAGS)
	
neolib.o: neolib.c
	$(CC) -c neolib.c -o $(O_DIR)neolib.o $(CXXFLAGS)

# DO NOT EDIT BELOW THIS LINE


# DO NOT EDIT ABOVE THIS LINE
