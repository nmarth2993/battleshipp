CXX = g++
INC = -I /home/dev/cmsc202/battleship/
CXXFLAGS = -Wall -g $(INC)
CMP = -c

S_INC = strategy/include
S_SRC = strategy/source

bin/CPUstrat: bin/strategyevaluator $(S_INC)/Brickboard.hpp $(S_INC)/computerstrategy.hpp $(S_INC)/Heatmap.hpp $(S_SRC)/Brickboard.cpp $(S_SRC)/computerstrategy.cpp $(S_SRC)/Heatmap.cpp source/CPUstrat.cpp
	$(CXX) $(CXXFLAGS) obj/playerevaluator.o obj/game.o obj/computerplayer.o obj/player.o obj/grid.o obj/ocean.o obj/boat.o obj/position.o $(S_INC)/Brickboard.hpp $(S_INC)/computerstrategy.hpp $(S_INC)/Heatmap.hpp $(S_SRC)/Brickboard.cpp $(S_SRC)/computerstrategy.cpp $(S_SRC)/Heatmap.cpp source/CPUstrat.cpp -o bin/CPUstrat

bin/strategyevaluator: obj/playerevaluator.o source/strategyevaluator.cpp
	$(CXX) $(CXXFLAGS) obj/playerevaluator.o obj/game.o obj/computerplayer.o obj/player.o obj/grid.o obj/ocean.o obj/boat.o obj/position.o source/strategyevaluator.cpp -o bin/strategyevaluator

bin/playertester: obj/game.o source/playertester.cpp
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