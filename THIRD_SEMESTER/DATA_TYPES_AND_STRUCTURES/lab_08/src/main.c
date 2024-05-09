#include <stdio.h>
#include <stdlib.h>

#include "../inc/print.h"
#include "../inc/graph.h"

// Function to get a command number from the user
void get_cmd(short int *cmd)
{
    // Prompt the user to enter the command number
    printf("%s", "\nEnter the command number: ");
    // Read the command number from standard input and store it in cmd
    int rc = fscanf(stdin, "%hd", cmd);
    // Check if the reading was unsuccessful
    if (rc != 1)
    {
        // Flush the standard input to clear any remaining characters
        fflush(stdin);
        // Reprompt the user to enter the command number
        printf("%s", "\nEnter the command number: ");
        // Retry reading the command number from standard input
        rc = fscanf(stdin, "%hd", cmd);
    }
    // Flush the standard input to clear any remaining characters
    fflush(stdin);
}

int main(void)
{
    // Disable buffering for standard output
    setbuf(stdout, NULL);
    
    print_info();
    print_menu();
    
    // Initialize variables for the command, return code, and graph creation status
    short int cmd = 1, rc = 0;
    int graph_created = 0;
    
    // Create a graph structure and initialize it
    graph_t graph;
    init_graph(&graph);
    
    // Main program loop, continues until the user enters command 0
    while (cmd)
    {
        // Get the command from the user
        get_cmd(&cmd);
        // Switch statement to handle different commands
        switch(cmd)
        {
            // Command 0: End the program
            case(0):
                // Check if a graph is created, free it if necessary
                if (graph_created)
                    free_graph(&graph);
                // Print a message indicating the program is completed
                printf("\nThe program is completed.\n");
                break;
            // Command 1: Create a graph
            case(1):
                // Check if a graph is created, free it if necessary
                if (graph_created)
                    free_graph(&graph);
                // Call the function to create a graph and store the return code
                rc = create_graph(&graph);
                // Check the return code from create_graph
                if (rc == OK)
                {
                    // Set the graph_created flag to 1 and print a success message
                    graph_created = 1;
                    printf("\nThe graph is created\n");
                }
                else
                {
                    // Print an error message with the return code
                    printf("\nThe graph has not been created. Error code: %d\n", rc);
                }
                break;
            // Command 2: Print the graph and open the graph image
            case(2):
                // Check if a graph is not created, print a message
                if (!graph_created)
                    printf("\nThe graph has not been created.\n");
                else
                {
                    // Print the graph and generate an image using system commands
                    print_graph(&graph);
                    system("dot -Tpng graph.gv > graph.png");
                    system("xdg-open graph.png");
                }
                break;
            // Command 3: Determine the connectivity of the graph using DFS
            case(3):
                // Check if a graph is not created, print a message
                if (!graph_created)
                    printf("\nThe graph has not been created.\n");
                else
                {
                    // Prompt the user to enter the starting vertex for DFS
                    int start_vertex;
                    printf("\nEnter the number of the vertex from which to start DFS: ");
                    // Read the user input for the starting vertex and validate it
                    if (scanf("%d", &start_vertex) != 1 || start_vertex < 0 || start_vertex >= graph.size)
                    {
                        // If invalid input, flush standard input and print an error message
                        fflush(stdin);
                        printf("\nInvalid value for the vertex number.\n");
                    }
                    else
                    {
                        // Call the function to determine graph connectivity using DFS
                        is_connected(&graph, start_vertex);
                    }
                }
                break;
            // Default case: Invalid command number
            default:
                printf("\nInvalid command number.\n\n");
        }
    }
    // Return the final return code of the program
    return rc;
}
