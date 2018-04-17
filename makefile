prog: main.cpp Parser.cpp Parser.h Automaton.cpp Automaton.h DFA.cpp DFA.h Structs.h
	g++ -o optionalProject -std=c++11 main.cpp Automaton.h Automaton.cpp Parser.cpp Parser.h DFA.cpp DFA.h Structs.h
clean:
	rm -f optionalProject