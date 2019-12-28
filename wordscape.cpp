#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 8

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "%s: missing arg\n", argv[0]);
		return 1;
	}
	std::string letters = argv[1];
	if (letters.size() < MIN_WORD_LENGTH || letters.size() > MAX_WORD_LENGTH) {
		fprintf(stderr, "%s: invalid arg '%s'\n", argv[0], argv[1]);
		return 1;
	}
	int lc[26] = {0};
	for (int i = 0; i < (int)letters.size(); i++) {
		if (letters[i] >= 'a' && letters[i] <= 'z')
			lc[letters[i] - 'a']++;
		else if (letters[i] >= 'A' && letters[i] <= 'Z')
			lc[letters[i] - 'A']++;
		else {
			fprintf(stderr, "%s: invalid arg '%s'\n", argv[0], argv[1]);
			return 1;
		}
	}
	FILE *f = fopen("words", "r");
	if (f == NULL) {
		perror("words");
		return 1;
	}
	size_t n = 0;
	char *line = NULL;
	std::vector<std::string> w3;
	std::vector<std::string> w4;
	std::vector<std::string> w5;
	std::vector<std::string> w6;
	std::vector<std::string> ws[MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1];
	while (getline(&line, &n, f) != -1) {
		int sl = strlen(line);
		if (line[sl-1] == '\n')
			line[sl-1] = '\0';
		sl--;
		if (sl > (int)letters.size() || sl < MIN_WORD_LENGTH)
			continue;
		int c[26] = {0};
		for (int i = 0; i < sl; i++)
			c[line[i] - 'a']++;
		bool add = 1;
		for (int i = 0; i < 26; i++) {
			if (c[i] > lc[i]) {
				add = 0;
				break;
			}
		}
		if (add) {
			ws[sl-MIN_WORD_LENGTH].push_back(line);
		}
	}
	fclose(f);
	for (int i = 0; i < MAX_WORD_LENGTH-MIN_WORD_LENGTH+1; i++)
		for (std::string s : ws[i])
			printf("%s\n", s.c_str());
	return 0;
}
