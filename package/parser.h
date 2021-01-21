#include<string.h>

#include<unistd.h>

const int MAXARGS = 128;

int parseLine(char *input, char ***parsed);
int parsePipeline(char *input, char **output);
void parseSpace(char *input, char **output);

int parseLine(char *input, char ***parsed) {
  char* separated[2];
  int isPiped = parsePipeline(input, separated);
  if (isPiped) {
    for (int i = 0; i < 2; i++) {
      parseSpace(separated[i], parsed[i]);
    }
  } else {
    parseSpace(input, parsed[0]);
  }
  return isPiped;
}

int parsePipeline(char *input, char **separated) {
  for (int i = 0; i < 2; i++)
  {
    separated[i] = strsep(&input, "|");
    if (separated[i] == NULL) break;
  }
  if (separated[1] != NULL) return 1;
  return 0;
}

void parseSpace(char *input, char **parsed) {
  for (int i = 0; i < MAXARGS; i++)
  {
    parsed[i] = strsep(&input, " ");
    if (parsed[i] == NULL) break;
    if (!strlen(parsed[i])) i--;
  }
}