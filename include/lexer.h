#ifndef LEXER_H
#define LEXER_H

typedef enum {
  TOKEN_INT,
  TOKEN_MAIN,
  TOKEN_LET,
  TOKEN_PRINT,
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_SEMICOLON,
  TOKEN_EQUAL,
  TOKEN_EOF
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

typedef struct {
  const char *source;
  int position;
} Lexer;

void init_lexer(Lexer *lexer, const char *source);
Token *get_next_token(Lexer *lexer);
void free_token(Token *token);

#endif
