CXX = g++

all: auromaParser auromaLexer

auromaParser: parser.auroma.o                   \
              lex.auroma.o                      \
              auromaParserMain.o
	g++ $^ -o $@

auromaLexer: lex.auroma.o                       \
             auromaLexerMain.o                  \
             auromaParserbase.h
	$(CXX) $^ -o $@

lex.auroma.cc: auroma.lex
	flex -o $@ $^

parser.auroma.cc auromaParserbase.h auromaParser.h auromaParser.ih : auroma.y
	bisonc++ $^

parser.auroma.o: auromaParser.h auromaParser.ih

clean:
	rm -f *~ lex.*.cc *.o			\
            parser.auroma.cc auromaParserbase.h	\
            auromaLexer auromaParser
