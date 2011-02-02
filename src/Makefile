CXX = g++

all: auromaParser auromaLexer

auromaParser: parser.auroma.o
	g++ $^ -o $@

auromaLexer: lex.auroma.cc
	$(CXX) $^ -o $@

lex.auroma.cc: auroma.lex
	flex -o $@ $^

parser.auroma.cc auromaParserbase.h auromaParser.h auromaParser.ih : auroma.y
	bisonc++ $^

clean:
	rm -f lex.*.cc *.o auromaLexer \
            parser.auroma.cc auromaParserbase.h auromaParser.h auromaParser.ih