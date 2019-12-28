all: wordscape addwords rmwords

WORDS=wordscape_dict

wordscape: wordscape.cpp $(WORDS)
	g++ wordscape.cpp -o $@ -Wall

addwords: addwords.cpp $(WORDS)
	g++ addwords.cpp -o $@ -Wall

rmwords: rmwords.cpp $(WORDS)
	g++ rmwords.cpp -o $@ -Wall

clean:
	rm -f wordscape addwords rmwords

#install: wordscape
#	cp wordscape /usr/local/bin/wordscape

#uninstall: /usr/local/bin/wordscape
#	rm -f $<
