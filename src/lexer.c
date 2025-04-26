#include "../include/lexer.h"
#include <stdlib.h>
#include <string.h>

void init_lexer(Lexer *lexer, const char *source) {
  lexer->source = source;
  lexer->position = 0;
}

static char peek(Lexer *lexer) { return lexer->source[lexer->position]; }

static char advance(Lexer *lexer) { return lexer->source[lexer->position++]; }

static Token *create_token(TokenType type, char *value) {
  Token *token = (Token *)malloc(sizeof(Token));
  token->type = type;
  token->value = value;
  return token;
}

Token *get_next_token(Lexer *lexer) {
  while (peek(lexer) != '\0') {
    if (peek(lexer) == ' ' || peek(lexer) == '\n') {
      advance(lexer);
      continue;
    }

    if ((peek(lexer) >= 'a' && peek(lexer) <= 'z') ||
        (peek(lexer) >= 'A' && peek(lexer) <= 'Z')) {
      char word[50];
      int i = 0;
      while ((peek(lexer) >= 'a' && peek(lexer) <= 'z') ||
             (peek(lexer) >= 'A' && peek(lexer) <= 'Z') ||
             (peek(lexer) >= '0' && peek(lexer) <= '9')) {
        word[i++] = advance(lexer);
      }
      word[i] = '\0';

      char *value = (char *)malloc(i + 1);
      strcpy(value, word);

      if (strcmp(value, "int") == 0) {
        free(value);
        return create_token(TOKEN_INT, NULL);
      }
      if (strcmp(value, "main") == 0) {
        free(value);
        return create_token(TOKEN_MAIN, NULL);
      }
      if (strcmp(value, "let") == 0) {
        free(value);
        return create_token(TOKEN_LET, NULL);
      }
      if (strcmp(value, "print") == 0) {
        free(value);
        return create_token(TOKEN_PRINT, NULL);
      }
      return create_token(TOKEN_IDENTIFIER, value);
    }

    if (peek(lexer) >= '0' && peek(lexer) <= '9') {
      char number[50];
      int i = 0;
      while (peek(lexer) >= '0' && peek(lexer) <= '9') {
        number[i++] = advance(lexer);
      }
      number[i] = '\0';

      char *value = (char *)malloc(i + 1);
      strcpy(value, number);
      return create_token(TOKEN_NUMBER, value);
    }

    char c = advance(lexer);
    if (c == '(')
      return create_token(TOKEN_LPAREN, NULL);
    if (c == ')')
      return create_token(TOKEN_RPAREN, NULL);
    if (c == '{')
      return create_token(TOKEN_LBRACE, NULL);
    if (c == '}')
      return create_token(TOKEN_RBRACE, NULL);
    if (c == ';')
      return create_token(TOKEN_SEMICOLON, NULL);
    if (c == '=')
      return create_token(TOKEN_EQUAL, NULL);
  }
  return create_token(TOKEN_EOF, NULL);
}

void free_token(Token *token) {
  if (token->value)
    free(token->value);
  free(token);
}
