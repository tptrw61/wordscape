all: wordscape addwords rmwords

WORDS=wordscape_dict
INC=here
INC_INST=inst

INST_LOC=/usr/local

CXXFLAGS:=-Wall

wordscape: wordscape.cpp $(WORDS)/dict $(INC)/filename.hpp
	g++ -I $(INC) wordscape.cpp -o $@ $(CXXFLAGS)

addwords: addwords.cpp $(WORDS)/dict $(INC)/filename.hpp
	g++ -I $(INC) addwords.cpp -o $@ $(CXXFLAGS)

rmwords: rmwords.cpp $(WORDS)/dict $(INC)/filename.hpp
	g++ -I $(INC) rmwords.cpp -o $@ $(CXXFLAGS)

clean:
	rm -f wordscape addwords rmwords

install: wordscape.cpp addwords.cpp rmwords.cpp $(INC_INST)/filename.hpp $(WORDS)
	-sudo mkdir $(INST_LOC)/etc/$(WORDS)
	sudo cp $(WORDS)/dict $(INST_LOC)/etc/$(WORDS)/dict
	sudo g++ -I $(INC_INST) wordscape.cpp -o $(INST_LOC)/bin/wordscape $(CXXFLAGS) -Werror
	sudo g++ -I $(INC_INST) addwords.cpp -o $(INST_LOC)/bin/addwords $(CXXFLAGS) -Werror
	sudo g++ -I $(INC_INST) rmwords.cpp -o $(INST_LOC)/bin/rmwords $(CXXFLAGS) -Werror

uninstall:
	sudo rm -f $(INST_LOC)/bin/wordscape $(INST_LOC)/bin/addwords $(INST_LOC)/bin/rmwords
	sudo rm -rf $(INST_LOC)/etc/$(WORDS)
