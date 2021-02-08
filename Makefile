CC = g++
CFLAGS = -Wall -g

battleship: boat.cpp boat.hpp position.cpp position.hpp
	$(CC) $(CFLAGS) boat.cpp boat.hpp position.cpp position.hpp -o battleship

clean:
	rm battleship