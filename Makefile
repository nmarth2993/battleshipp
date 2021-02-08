CC = g++
CFLAGS = -Wall -g

battleship: boat.cpp boat.hpp position.cpp position.hpp
	$(CC) $(CFLAGS) boat.cpp boat.hpp position.cpp position.hpp -o battleship

oceantest: ocean.hpp ocean.cpp boat.cpp boat.hpp position.cpp position.hpp oceandriver.cpp
	$(CC) $(CFLAGS) boat.cpp boat.hpp position.cpp position.hpp ocean.hpp ocean.cpp oceandriver.cpp -o oceandriver

clean:
	rm battleship
	rm oceandriver