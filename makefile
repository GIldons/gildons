# Project: FireFlight - ECE453
# Makefile created by Dev-C++ 4.9.9.2
# Xunxado by Raul!
#i586-mingw32msvc-g++
#i586-mingw32msvc-gcc

CPP  = g++
CC   = gcc 
RES  =
O_DIR = OBJ/
OBJ  = main.o screen.o basic.o game_logic.o screen_opt.o I_O.o $(RES)
LINKOBJ  = $(O_DIR)main.o $(O_DIR)screen.o $(O_DIR)basic.o $(O_DIR)game_logic.o $(O_DIR)screen_opt.o $(O_DIR)I_O.o $(RES)
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
	$(CPP) $(LINKOBJ) -o "main" $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o $(O_DIR)main.o $(CXXFLAGS)

screen.o: screen.cpp
	$(CPP) -c screen.cpp -o $(O_DIR)screen.o $(CXXFLAGS)

basic.o: basic.cpp
	$(CPP) -c basic.cpp -o $(O_DIR)basic.o $(CXXFLAGS)
	
game_logic.o: game_logic.cpp
	$(CPP) -c game_logic.cpp -o $(O_DIR)game_logic.o $(CXXFLAGS)
	
screen_opt.o: screen_opt.cpp
	$(CPP) -c screen_opt.cpp -o $(O_DIR)screen_opt.o $(CXXFLAGS)
	
I_O.o: I_O.cpp
	$(CPP) -c I_O.cpp -o $(O_DIR)I_O.o $(CXXFLAGS)

# DO NOT EDIT BELOW THIS LINE

main.o: ./headers/basic.h ./headers/screen.h

# DO NOT EDIT ABOVE THIS LINE











# 
# # Fire Fight - ECE 453 Project
# # 
# CC=g++
# #
# CFLAGS= -Wall -Wextra -lSDL -lSDL_image
# O_DIR= OBJ/
# all: fire_fight
# 
# fire_fight: main.o 
# 	$(CC) $(O_DIR)main.o -o fire_fight
# 
# main.o: main.cpp
# 	$(CC) $(CFLAGS) -c main.cpp -o $(O_DIR)main.o
# 
# clean:
# 	rm -rf $(O_DIR)*o fire_fight 