CXX = g++
CXXFLAGS = -Wall -g
CMP = -c

bin/strategyevaluator: obj/playerevaluator.o source/strategyevaluator.cpp
	$(CXX) $(CXXFLAGS) obj/playerevaluator.o obj/game.o obj/computerplayer.o obj/player.o obj/grid.o obj/ocean.o obj/boat.o obj/position.o source/strategyevaluator.cpp -o bin/strategyevaluator

playertester: obj/game.o source/playertester.cpp
	$(CXX) $(CXXFLAGS) obj/game.o obj/player.o obj/grid.o obj/ocean.o obj/boat.o obj/position.o source/playertester.cpp -o bin/playertester

obj/playerevaluator.o: obj/game.o include/playerevaluator.hpp source/playerevaluator.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/playerevaluator.cpp -o obj/playerevaluator.o

obj/game.o: obj/computerplayer.o include/game.hpp source/game.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/game.cpp -o obj/game.o

obj/computerplayer.o: obj/player.o include/computerplayer.hpp source/computerplayer.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/computerplayer.cpp -o obj/computerplayer.o

obj/player.o: obj/grid.o include/player.hpp source/player.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/player.cpp -o obj/player.o

obj/grid.o: obj/ocean.o include/grid.hpp source/grid.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/grid.cpp -o obj/grid.o

obj/ocean.o: obj/boat.o include/ocean.hpp source/ocean.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/ocean.cpp -o obj/ocean.o

obj/boat.o: obj/position.o include/boat.hpp source/boat.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/boat.cpp -o obj/boat.o

obj/position.o: include/position.hpp source/position.cpp
	$(CXX) $(CXXFLAGS) $(CMP) source/position.cpp -o obj/position.o

clean:
	rm obj/* bin/*

.PHONY: clean