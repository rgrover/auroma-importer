CXX = g++

all: auromaLexer auromaParser

auromaParser: parser.auroma.o                   \
              lex.auroma.o                      \
              auromaParserMain.o
	g++ $^ -o $@

auromaLexer: lex.auroma.o                       \
             auromaLexerMain.o                  \
             auromaParserbase.h
	$(CXX) $^ -o $@

lex.auroma.cc: auroma.lex auromaParserbase.h
	flex -o $@ $^

parser.auroma.cc auromaParserbase.h: auroma.y
	bisonc++ $^

parser.auroma.o: auromaParser.h auromaParser.ih

clean:
	rm -f *~ lex.*.cc *.o			\
            parser.auroma.cc auromaParserbase.h	\
            auromaLexer auromaParser
