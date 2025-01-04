#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 100

typedef enum {
    CATEGORY_IDENTIFIER,
    CATEGORY_NUMBER,
    CATEGORY_OPERATOR,
    CATEGORY_KEYWORD,
    CATEGORY_UNKNOWN
} LexemeType;

const char *reserved[] = {"var", "begin", "end", "if", "then", "else", "programm"};
const int reserved_count = sizeof(reserved) / sizeof(reserved[0]);

int checkReserved(const char *word) {
    for (int i = 0; i < reserved_count; i++) {
        if (strcmp(word, reserved[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void showToken(LexemeType type, const char *value) {
    const char *type_names[] = {"Identifier", "Number", "Operator", "Keyword", "Unknown"};
    printf("[%s]: %s\n", type_names[type], value);
}

void analyzeSource(const char *input) {
    char buffer[MAX_LENGTH];
    int buffer_index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char current = input[i];

        if (isspace(current)) {
            continue;
        }

        if (isalpha(current)) {
            buffer_index = 0;
            while (isalnum(input[i])) {
                buffer[buffer_index++] = input[i++];
            }
            buffer[buffer_index] = '\0';
            i--;
            if (checkReserved(buffer)) {
                showToken(CATEGORY_KEYWORD, buffer);
            } else {
                showToken(CATEGORY_IDENTIFIER, buffer);
            }
            continue;
        }

        if (isdigit(current)) {
            buffer_index = 0;
            while (isdigit(input[i]) || input[i] == '.') {
                buffer[buffer_index++] = input[i++];
            }
            buffer[buffer_index] = '\0';
            i--;
            showToken(CATEGORY_NUMBER, buffer);
            continue;
        }

        if (strchr("<>=!", current)) {
            buffer_index = 0;
            buffer[buffer_index++] = current;
            if (input[i + 1] == '=') {
                buffer[buffer_index++] = input[++i];
            }
            buffer[buffer_index] = '\0';
            showToken(CATEGORY_OPERATOR, buffer);
            continue;
        }

        buffer[0] = current;
        buffer[1] = '\0';
        showToken(CATEGORY_UNKNOWN, buffer);
    }
}

int main() {
    const char *source_code = "begin var a = 100; if a > 50 then end;";
    printf("Processing source code...\n\n");
    analyzeSource(source_code);
    return 0;
}