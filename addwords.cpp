#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include "filename.hpp"

int main(int argc, char **argv) {
	if (argc == 1)
		return 0;
	std::vector<std::string> adding;
	std::vector<std::string> uniq;
	std::vector<std::string> dupl;
	std::vector<std::string> words;
	std::vector<std::string> wnew;
	for (int i = 1; i < argc; i++) {
		bool add = 1;
		for (char *c = argv[i]; *c != '\0'; c++) {
			if (*c >= 'a' && *c <= 'z')
				continue;
			if (*c >= 'A' && *c <= 'Z')
				*c += 'a' - 'A';
			else {
				add = 0;
				break;
			}
		}
		if (find(adding.begin(), adding.end(), argv[i]) == adding.end() && add)
			adding.push_back(argv[i]);
	}
	std::sort(adding.begin(), adding.end());
	//
	FILE *file = fopen(FILE_NAME, "r");
	if (file == NULL) {
		perror(FILE_NAME);
		return 1;
	}
	size_t n = 0;
	char *line = NULL;
	while (getline(&line, &n, file) != -1) {
		for (char *c = line; *c != '\0'; c++) {
			if (*c == '\n') {
				*c = '\0';
				break;
			}
		}
		words.push_back(line);
	}
	fclose(file);
	//
	for (std::string s : adding) {
		if (find(words.begin(), words.end(), s) == words.end())
			uniq.push_back(s);
		else
			dupl.push_back(s);
	}
	sort(uniq.begin(), uniq.end());
	//
	wnew.resize(uniq.size() + words.size());
	merge(uniq.begin(), uniq.end(), words.begin(), words.end(), wnew.begin());
	//
	if (!uniq.empty()) {
		file = fopen(FILE_NAME, "w");
		if (file == NULL) {
			perror(FILE_NAME);
			return 1;
		}
		for (std::string s : wnew) {
			fprintf(file, "%s\n", s.c_str());
		}
		fclose(file);
	}
	if (!uniq.empty()) {
		printf("words added:\n");
		for (std::string s : uniq)
			printf("%s\n", s.c_str());
	}
	if (!dupl.empty()) {
		printf("words skipped:\n");
		for (std::string s : dupl)
			printf("%s\n", s.c_str());
	}
	return 0;
}
