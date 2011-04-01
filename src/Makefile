CXX = g++
CXXFLAGS += -g

PARSER_SRCS =                                   \
       parser.auroma.cc                         \
       lex.auroma.cc                            \
       auromaParserExt.cc                       \
       auromaParserMain.cc                      \
       paraElement.cc                           \
       paraElementContainer.cc                  \
       containerDirective.cc                    \
       para.cc                                  \
       block.cc                                 \
       variousParaElements.cc			\
       variousContainerDirectives.cc		\
       utils.cc

PARSER_OBJS = $(patsubst %.cc,%.o,$(PARSER_SRCS))

LEXER_SRCS =                                    \
       lex.auroma.cc                            \
       auromaLexerMain.cc

LEXER_OBJS = $(patsubst %.cc,%.o,$(LEXER_SRCS))

all: .dep auromaLexer auromaParser

auromaParser: $(PARSER_OBJS)
	$(CXX) $(CXXFLAGS) $(PARSER_OBJS) -o $@

auromaLexer: auromaParserbase.h $(LEXER_OBJS)
	$(CXX) $(CXXFLAGS) $(LEXER_OBJS) -o $@

lex.auroma.cc: auroma.lex auromaParserbase.h
	flex --batch -o $@ auroma.lex

parser.auroma.cc auromaParserbase.h: auroma.y
	bisonc++ $^

%.o : .dep


.dep : $(sort $(PARSER_SRCS) $(LEXER_SRCS)) *.h
	g++ -MM $^ > .dep

include .dep

clean:
	rm -f *~ lex.*.cc *.o .dep              \
            parser.auroma.cc auromaParserbase.h \
            auromaLexer auromaParser
