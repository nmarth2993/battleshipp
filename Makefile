CC = g++
CFLAGS = -Wall -g

gridtest: griddriver.cpp grid.hpp grid.cpp ocean.hpp ocean.cpp boat.cpp boat.hpp position.cpp position.hpp
	$(CC) $(CFLAGS) griddriver.cpp grid.hpp grid.cpp ocean.hpp ocean.cpp boat.cpp boat.hpp position.cpp position.hpp -o gridtest

oceantest: ocean.hpp ocean.cpp boat.cpp boat.hpp position.cpp position.hpp oceandriver.cpp
	$(CC) $(CFLAGS) boat.cpp boat.hpp position.cpp position.hpp ocean.hpp ocean.cpp oceandriver.cpp -o oceandriver

battleship: boat.cpp boat.hpp position.cpp position.hpp
	$(CC) $(CFLAGS) boat.cpp boat.hpp position.cpp position.hpp -o battleship

clean:
	rm battleship
	rm oceandriver