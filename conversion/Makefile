EPUBS :=					\
	TheLifeDivine.epub			\
	EssaysOnTheGita.epub			\
	TheSynthesisOfYoga.epub			\
	LettersOnYoga.epub			\
        TheHumanCycle.epub			\
        TheRenaissanceInIndia.epub		\
        EssaysInPhilosophyAndYoga.epub


all: $(addprefix epubs/,$(EPUBS))

epubs/%.epub: patchedXMLs/%.xml
	dbtoepub $^ -o $@

patchedXMLs/%.xml : xmlsFromAuromaParser/%.xml
	cp $^ $@
	if [ -e $(patsubst %.xml,%.patch,$@) ]; then patch $@ < $(patsubst %.xml,%.patch,$@);  fi

xmlsFromAuromaParser/%.xml : parseableTexts/%.txt
	../src/auromaParser $^ > $@
	./addUnicode.pl $@ > $@.tmp
	mv $@.tmp $@

.SECONDARY : patchedXMLs/$(patsubst %.epub,%.xml,$(EPUBS))