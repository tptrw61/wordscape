all: wordscape addwords rmwords

wordscape: wordscape.cpp words
	g++ wordscape.cpp -o $@ -Wall

addwords: addwords.cpp words
	g++ addwords.cpp -o $@ -Wall

rmwords: rmwords.cpp words
	g++ rmwords.cpp -o $@ -Wall

clean:
	rm -f wordscape addwords rmwords

#install: wordscape
#	cp wordscape /usr/local/bin/wordscape

#uninstall: /usr/local/bin/wordscape
#	rm -f $<
