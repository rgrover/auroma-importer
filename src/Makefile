CXX = g++

all: auromaLexer auromaParser

auromaParser: parser.auroma.o                   \
              lex.auroma.o                      \
              auromaParserMain.o		\
              para.o				\
              paraElement.o
	g++ $^ -o $@

auromaLexer: auromaParserbase.h

auromaLexer: lex.auroma.o auromaLexerMain.o
	$(CXX) lex.auroma.o auromaLexerMain.o -o $@

lex.auroma.cc: auroma.lex auromaParserbase.h
	flex --batch -o $@ $^

parser.auroma.cc auromaParserbase.h: auroma.y
	bisonc++ $^

parser.auroma.o: auromaParser.h auromaParser.ih

para.o: para.cc para.h paraElement.h
paraElement.o: paraElement.h
stringParaElement.o: stringParaElement.h

clean:
	rm -f *~ lex.*.cc *.o			\
            parser.auroma.cc auromaParserbase.h	\
            auromaLexer auromaParser
