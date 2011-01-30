CXX = g++

lex: lex.auroma.cc
	$(CXX) $^ -o $@

lex.auroma.cc: auroma.lex
	flex -o $@ $^

clean:
	rm -f *.yy.c *.o *.cc lex