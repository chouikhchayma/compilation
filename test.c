#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include <stdio.h>
#include <assert.h>

// Test function for lexical analyzer
void testLexer() {
    printf("Running Lexer Tests...\n");

    // Create a test input file
    FILE *source = fopen("test_input.txt", "w");
    fprintf(source, "program test; var x, y: int; begin x := 10; end.");
    fclose(source);

    source = fopen("test_input.txt", "r");
    Token token;

    // Test tokens
    token = getNextToken(source);
    assert(token.code == TOKEN_PROGRAM);
    assert(strcmp(token.lexeme, "program") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "test") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_VAR);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "x") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_COMMA);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "y") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_COLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_INT);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_BEGIN);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "x") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_ASSIGN);

    token = getNextToken(source);
    assert(token.code == TOKEN_NB);
    assert(strcmp(token.lexeme, "10") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_END);

    token = getNextToken(source);
    assert(token.code == TOKEN_DOT);

    token = getNextToken(source);
    assert(token.code == TOKEN_EOF);

    fclose(source);
    printf("Lexer Tests Passed!\n");
}

// Test function for syntax analyzer
void testParser() {
    printf("Running Parser Tests...\n");

    // Create a test input file
    FILE *source = fopen("test_input.txt", "w");
    fprintf(source, "program test; var x, y: int; begin x := 10; end.");
    fclose(source);

    source = fopen("test_input.txt", "r");
    lookahead = getNextToken(source);

    // Test parsing
    parseProgram(source);

    // Ensure the entire input is consumed
    assert(lookahead.code == TOKEN_EOF);

    fclose(source);
    printf("Parser Tests Passed!\n");
}

// Test function for semantic analyzer
void testSemantic() {
    printf("Running Semantic Tests...\n");

    // Create a test input file
    FILE *source = fopen("test_input.txt", "w");
    fprintf(source, "program test; var x, y: int; begin x := 10; y := x + 5; end.");
    fclose(source);

    source = fopen("test_input.txt", "r");
    lookahead = getNextToken(source);

    // Test parsing and semantic checks
    parseProgram(source);

    // Ensure the entire input is consumed
    assert(lookahead.code == TOKEN_EOF);

    fclose(source);
    printf("Semantic Tests Passed!\n");
}

int main() {
    testLexer();
    testParser();
    testSemantic();
    printf("All tests passed!\n");
    return 0;
}
