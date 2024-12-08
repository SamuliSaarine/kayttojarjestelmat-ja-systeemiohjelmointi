#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node for linked list
typedef struct Node
{
    char *line;
    struct Node *next;
} Node;

// Function prototype
void reverse_lines(Node *head, FILE *output);

int main(int argc, char *argv[])
{
    // Initializing variable
    FILE *input = NULL, *output = NULL;
    Node *head = NULL;

    // Argument validation (There should not be more than 3 arguments)
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Open files based on arguments
    if (argc == 1)
    {
        // If input and output files are not specified, we take input from standard input and write output to standard output
        input = stdin;
        output = stdout;
        printf("Enter lines to reverse (Ctrl+D to end):\n");
    }
    else if (argc == 2)
    {
        // If output file is not specified, we take input from file and write output to standard output
        if ((input = fopen(argv[1], "r")) == NULL)
        {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        output = stdout;
    }
    else
    {
        // If both files are specified in arguments, we take input from first file and write output to second file

        // Checking that input file is different from output file
        if (strcmp(argv[1], argv[2]) == 0)
        {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }

        // Checking that input file argument is valid
        if ((input = fopen(argv[1], "r")) == NULL)
        {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        // Checking that ouput file argument is valid
        if ((output = fopen(argv[2], "w")) == NULL)
        {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            fclose(input);
            exit(1);
        }
    }

    // Read lines into linked list
    char *line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, input)) != -1)
    {
        Node *new_node = malloc(sizeof(Node));
        // Checking if malloc failed when allocating memory
        if (!new_node)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        new_node->line = strdup(line);
        new_node->next = head;
        head = new_node;
    }
    free(line);

    // Reverse and output lines
    reverse_lines(head, output);

    // Clean up
    fclose(input);
    if (output != stdout)
        fclose(output);
    while (head)
    {
        Node *temp = head;
        head = head->next;
        free(temp->line);
        free(temp);
    }
    return 0;
}

// Print lines in reverse order
void reverse_lines(Node *head, FILE *output)
{
    for (Node *curr = head; curr; curr = curr->next)
    {
        fprintf(output, "%s", curr->line);
    }
}