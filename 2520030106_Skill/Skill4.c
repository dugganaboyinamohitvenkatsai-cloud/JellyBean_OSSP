#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1. Create Token Structures
typedef struct {
    char text[100];
} Token;

// 2. Produce Execution Structures (Parse Tree Node)
typedef struct ParseNode {
    char *command;
    char *arguments[64];
    int arg_count;
    struct ParseNode *leftChild;  // For future complex commands (like pipes |)
    struct ParseNode *rightChild;
} ParseNode;

int main() {
    char input[1024];
    Token tokens[64]; // Validate Token Streams via array tracking
    
    while(1) {
        printf("parser> ");
        if (!fgets(input, 1024, stdin)) break;
        
        // 3. Handle Whitespace & Handle Empty Commands
        int is_empty = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isspace(input[i])) { is_empty = 0; break; }
        }
        
        if (is_empty) {
            // Detect Errors
            printf("[Syntax Error] Empty command detected. Please enter a valid command.\n");
            continue;
        }

        // 4. Split Input into Tokens & Identify Delimiters (Space, Tab, Newline)
        int token_count = 0;
        char *token_str = strtok(input, " \n\t");
        
        while (token_str != NULL) {
            strcpy(tokens[token_count].text, token_str);
            token_count++;
            token_str = strtok(NULL, " \n\t");
        }

        // 5. Generate Parse Trees / Execution Structures
        ParseNode root;
        root.command = tokens[0].text;
        root.arg_count = 0;
        root.leftChild = NULL;
        root.rightChild = NULL;

        for (int i = 0; i < token_count; i++) {
            root.arguments[root.arg_count++] = tokens[i].text;
        }
        root.arguments[root.arg_count] = NULL; // Execution structures must be NULL terminated

        // 6. Debug Parsing Output
        printf("\n--- PARSE TREE DEBUG OUTPUT ---\n");
        printf("Root Node (Command): %s\n", root.command);
        for (int i = 0; i < root.arg_count; i++) {
            printf("  |-- Leaf Node (Argument %d): %s\n", i, root.arguments[i]);
        }
        printf("-------------------------------\n\n");
    }
    return 0;
}
