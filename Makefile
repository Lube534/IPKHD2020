TARGET = nvirus
LIBS = -lncurses
CC = g++
CFLAGS = -g -Wall -std=c++11

.PHONY: default all clean run $(TARGET)

default: $(TARGET)
all: default

SOURCES = Virusdefense_final/Cleaner.cpp Virusdefense_final/Game.cpp Virusdefense_final/Lane.cpp Virusdefense_final/main.cpp Virusdefense_final/Safespace.cpp Virusdefense_final/Sprayer.cpp Virusdefense_final/Terminal.cpp  Virusdefense_final/Virus.cpp Virusdefense_final/Projectile.cpp
HEADERS =  Virusdefense_final/Cleaner.h Virusdefense_final/Color.h  Virusdefense_final/Game.h  Virusdefense_final/Lane.h  Virusdefense_final/Safespace.h Virusdefense_final/Terminal.h Virusdefense_final/Vec2D.h Virusdefense_final/Virus.h Virusdefense_final/Projectile.h

$(TARGET):
	$(CC) $(SOURCES) $(CFLAGS) $(LIBS) -o $@

run:
	./$(TARGET)
	
clean:
	-rm -f $(TARGET)
	
