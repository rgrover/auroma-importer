CXX = g++

lex: lex.auroma.cc
	$(CXX) $^ -o $@

lex.auroma.cc: auroma.lex
	flex -o $@ $^

clean:
	rm -f lex.*.cc *.o lex