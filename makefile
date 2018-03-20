prog: main.cpp Parser.cpp Parser.h Automaton.cpp Automaton.h DFA.cpp DFA.h Structs.h
	g++ -std=c++11 -o optionalProject main.cpp Parser.cpp Parser.h Automaton.cpp Automaton.h DFA.cpp DFA.h Structs.h
clean:
	rm -f optionalProject