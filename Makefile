CXX = g++
CXXFLAGS = -Wall -g
CMP = -c

strategyevaluator: obj/playerevaluator.o strategyevaluator.cpp
	$(CXX) $(CXXFLAGS) obj/playerevaluator.o obj/game.o obj/computerplayer.o obj/player.o obj/grid.o obj/ocean.o obj/boat.o obj/position.o strategyevaluator.cpp -o strategyevaluator

playertester: obj/game.o playertester.cpp
	$(CXX) $(CXXFLAGS) obj/game.o obj/player.o obj/grid.o obj/ocean.o obj/boat.o obj/position.o playertester.cpp -o playertester

obj/playerevaluator.o: obj/game.o playerevaluator.hpp playerevaluator.cpp
	$(CXX) $(CXXFLAGS) $(CMP) playerevaluator.cpp -o obj/playerevaluator.o

obj/game.o: obj/computerplayer.o game.hpp game.cpp
	$(CXX) $(CXXFLAGS) $(CMP) game.cpp -o obj/game.o

obj/computerplayer.o: obj/player.o computerplayer.hpp computerplayer.cpp
	$(CXX) $(CXXFLAGS) $(CMP) computerplayer.cpp -o obj/computerplayer.o

obj/player.o: obj/grid.o player.hpp player.cpp
	$(CXX) $(CXXFLAGS) $(CMP) player.cpp -o obj/player.o

obj/grid.o: obj/ocean.o grid.hpp grid.cpp
	$(CXX) $(CXXFLAGS) $(CMP) grid.cpp -o obj/grid.o

obj/ocean.o: obj/boat.o ocean.hpp ocean.cpp
	$(CXX) $(CXXFLAGS) $(CMP) ocean.cpp -o obj/ocean.o

obj/boat.o: obj/position.o boat.hpp boat.cpp
	$(CXX) $(CXXFLAGS) $(CMP) boat.cpp -o obj/boat.o

obj/position.o: position.hpp position.cpp
	$(CXX) $(CXXFLAGS) $(CMP) position.cpp -o obj/position.o

clean:
	rm obj/position.o obj/boat.o obj/ocean.o obj/grid.o obj/player.o obj/computerplayer.o obj/game.o obj/playerevaluator.o strategyevaluator

.PHONY: clean