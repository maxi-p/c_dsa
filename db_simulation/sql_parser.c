#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BUFFER_LEN 100

typedef struct {
    int id;
    char name[50];
    int age;
} Person;

Person person[] = {
    {1, "Max", 23},
    {2, "Gena", 23},
    {3, "Moore", 23},
    {4, "Jimmy", 23},
    {5, "Brandin", 23},
    {6, "Jonny", 23}
};

void str_tolower(char *query) {
    int len = strlen(query);

    for (int i = 0; i < len; i++) {
        *(query + i) = tolower(*(query + i));
    }
}

void left_strip(char* query) {
    int start = 0, end = strlen(query);

    while (start < end && (query[start] == ' ' || query[start] == '\t')) {
        start++;
    }
    while (start < end && (query[end-1] == ' ' || query[end-1] == '\t')) {
        end--;
    }

    for (int i = 0; i < end - start; i++) {
        query[i] = query[start + i];
    }

    query[end - start] = '\0';
}

void execute_query(char *select_content, char *from_content, char *where_content) {
    if (strcmp(select_content, "*") == 0) {
        printf("everything\n");
    } else {
        printf("something\n");
    }

    if (strcmp(from_content, "person") == 0) {
        printf("person table\n");
    } else {
        printf("other table");
    }

    if (strcmp(where_content, "") == 0) {
        printf("all values\n");
    } else {
        printf("specific values\n");
    }
}

void* parse_sql(char *query) {
    // lowercasing the query
    str_tolower(query);

    // searching for select keyword
    char *select_content = strstr(query, "select");
    if (select_content == NULL) {
        printf("Error: select not found\n");
        return NULL;
    } 

    // moving past select keyword
    select_content += strlen("select");
    left_strip(select_content);

    // searching the from keyword
    char *from_content = strstr(select_content, "from");
    if (from_content == NULL) {
        printf("Error: from not found\n");
        return NULL;
    }
    
    // trimming select content to not include "from ..."
    int len_select_content = from_content - select_content;
    select_content[len_select_content] = '\0';
    left_strip(select_content);
    printf("Select content: %s\n", select_content);

    // moving past from keyword
    from_content += strlen("from");
    left_strip(from_content);

    // searching the optional where keyword
    int where_present = 0;
    char *where_content = strstr(from_content, "where");
    if (where_content != NULL) {
        // trimming the from content to not include "where ..."
        int len_where_content = where_content - from_content;
        from_content[len_where_content] = '\0';
        left_strip(from_content);
        printf("From content: %s\n", from_content);

        where_content += strlen("where");
        left_strip(where_content);
        where_present = 1;
    } else {
        where_content = from_content;
    }

    char *semicolon = strstr(where_content, ";");
    if (semicolon == NULL) {
        printf("Error: query must end with semicolon\n");
        return NULL;
    } 

    // trimming the where (or from) content to not include ";"
    int len_semi_content = semicolon - where_content;
    where_content[len_semi_content] = '\0';
    left_strip(where_content);
    if (where_present) {
        printf("Where content: %s\n", where_content);
        execute_query(select_content, from_content, where_content);
    } else {
        printf("From content: %s\n", where_content);
        execute_query(select_content, from_content, "\0");
    }


    return NULL;
}

int main() {
    char buffer[MAX_BUFFER_LEN + 1];

    char *query;

    printf("Enter you SQL query: ");
    scanf("%100[^\n]", buffer);
    buffer[MAX_BUFFER_LEN] = '\0';
    int len = strlen(buffer);
    
    query = (char *) malloc(sizeof(char) * (len + 1));
    strcpy(query, buffer);
    query[len] = '\0';

    // printf("%s\n", query);
    
    parse_sql(query);
    
    free(query);
    return 0;
}
