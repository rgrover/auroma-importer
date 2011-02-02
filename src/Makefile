CXX = g++

lex: lex.auroma.cc
	$(CXX) $^ -o $@

lex.auroma.cc: auroma.lex
	flex -o $@ $^

parse.cc Parserbase.h Parser.h Parser.ih : auroma.y
	bisonc++ $^

clean:
	rm -f lex.*.cc *.o lex