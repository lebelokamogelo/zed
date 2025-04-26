#include "lexer.c"
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Error: Could not open file %s\n", filename);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)malloc(size + 1);
  if (!buffer) {
    printf("Error: Memory allocation failed\n");
    fclose(file);
    exit(1);
  }

  size_t read = fread(buffer, 1, size, file);
  buffer[read] = '\0';
  fclose(file);
  return buffer;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  char *program = read_file(filename);

  Lexer lexer;
  init_lexer(&lexer, program);

  while (1) {
    Token *token = get_next_token(&lexer);
    switch (token->type) {
    case TOKEN_INT:
      printf("int\n");
      continue;
    case TOKEN_MAIN:
      printf("main\n");
      continue;
    case TOKEN_LET:
      printf("let\n");
      continue;
    case TOKEN_PRINT:
      printf("print\n");
      continue;
    case TOKEN_IDENTIFIER:
      printf("%s\n", token->value);
      continue;
    case TOKEN_NUMBER:
      printf("%s\n", token->value);
      continue;
    case TOKEN_LPAREN:
      printf("(\n");
      continue;
    case TOKEN_RPAREN:
      printf(")\n");
      continue;
    case TOKEN_LBRACE:
      printf("{\n");
      continue;
    case TOKEN_RBRACE:
      printf("}\n");
      continue;
    case TOKEN_SEMICOLON:
      printf(";\n");
      continue;
    case TOKEN_EQUAL:
      printf("=\n");
      continue;
    case TOKEN_EOF:
      printf("EOF\n");
      free_token(token);
      break;
    }

    free(program);
    return 0;
  }
}
