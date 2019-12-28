#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "wordscape_dict/dict"

int main(int argc, char **argv) {
	if (argc == 1)
		return 0;
	std::vector<std::string> rming;
	std::vector<std::string> rmed, skipped;
	std::vector<std::string> words;
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
		if (find(rming.begin(), rming.end(), argv[i]) == rming.end() && add) {
			rming.push_back(argv[i]);
		}
	}
	//std::sort(rming.begin(), rming.end());
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
		if (find(rming.begin(), rming.end(), line) != rming.end()) {
			rmed.push_back(line);
		} else {
			words.push_back(line);
		}
	}
	fclose(file);
	for (std::string s : rming)
		if (find(rmed.begin(), rmed.end(), s) == rmed.end())
			skipped.push_back(s);
	//
	if (!rmed.empty()) {
		file = fopen(FILE_NAME, "w");
		if (file == NULL) {
			perror(FILE_NAME);
			return 1;
		}
		for (std::string s : words) {
			fprintf(file, "%s\n", s.c_str());
		}
		fclose(file);
	}
	if (!rmed.empty()) {
		printf("words removed:\n");
		for (std::string s : rmed)
			printf("%s\n", s.c_str());
	}
	if (!skipped.empty()) {
		printf("words skipped:\n");
		for (std::string s : skipped)
			printf("%s\n", s.c_str());
	}
	return 0;
}
