#include "../inc/graph.h"

#include <stdio.h>
#include <stdlib.h>
#include "../inc/exceptions.h"
#include "../inc/queue.h"

// Allocate a two-dimensional array (matrix) with n rows and m columns
static int** allocate_matrix(size_t n, size_t m)
{
    // Allocate memory for the array of pointers to rows and the matrix data in a contiguous block
    int **data = malloc(n * sizeof(int*) + n * m * sizeof(int));
    
    if (!data)
        return NULL;

    // Iterate over each row in the matrix
    for (size_t i = 0; i < n; ++i)
    {
        // Set the pointer to the beginning of each row by calculating the offset
        data[i] = (int*)((char*) data + n * sizeof(int*) + i * m * sizeof(int));

        // Iterate over each column in the row and initialize values to 0
        for (size_t j = 0; j < m; ++j)
            data[i][j] = 0;
    }
    
    // Return the allocated matrix
    return data;
}

// Free the memory allocated for the graph's matrices
void free_graph(graph_t *graph)
{
    // Check if the adjacency matrix is allocated
    if (graph->matrix)
    {
        // Free the memory allocated for the adjacency matrix
        free(graph->matrix);
        // Set the pointer to NULL after freeing to avoid dangling pointers
        graph->matrix = NULL;
    }

    // Check if the transposition matrix is allocated
    if (graph->transpos_matrix)
    {
        // Free the memory allocated for the transposition matrix
        free(graph->transpos_matrix);
        // Set the pointer to NULL after freeing to avoid dangling pointers
        graph->transpos_matrix = NULL;
    }
}

// Initialize the graph structure by setting matrix and transposition matrix pointers to NULL and size to 0
void init_graph(graph_t *graph)
{
    // Set the adjacency matrix pointer to NULL
    graph->matrix = NULL;

    // Set the transposition matrix pointer to NULL
    graph->transpos_matrix = NULL;

    // Set the size of the graph to 0
    graph->size = 0;
}

// Function to create a graph by taking user input for vertices, paths, and their connections
int create_graph(graph_t *graph)
{
    // Prompt the user to enter the total number of vertices in the graph
    printf("Enter the total number of vertices in the graph: ");

    // Read the user input for the number of vertices and check for errors
    if (scanf("%d", &(graph->size)) != 1 || graph->size < 1)
    {
        // Print an error message for incorrect input
        printf("\nIncorrect value\n\n");
        // Flush the standard input to clear any remaining characters
        fflush(stdin);
        // Return an error code indicating an incorrect size input
        return ERR_SIZE;
    }

    // Flush the standard input to clear any remaining characters
    fflush(stdin);

    // Allocate memory for the adjacency matrix and transposition matrix
    graph->matrix = allocate_matrix(graph->size, graph->size);
    graph->transpos_matrix = allocate_matrix(graph->size, graph->size);

    // Check if memory allocation for matrices was successful
    if (!graph->matrix || !graph->transpos_matrix)
    {
        // Free the allocated memory for matrices
        free_graph(graph);
        // Return an error code indicating memory allocation failure
        return ERR_MEMORY;
    }

    // Loop to prompt the user for paths between vertices
    for (size_t i = 0; i < (size_t)graph->size; ++i)
    {
        // Print information about the current vertex
        printf("\n - Vertex %zu -\n", i);

        // Prompt for the number of paths for the current vertex
        int numPaths;
        printf("Enter the number of paths for vertex %zu: ", i);
        // Read the user input for the number of paths and check for errors
        if (scanf("%d", &numPaths) != 1 || numPaths < 0)
        {
            // Print an error message for incorrect input and decrement i to re-prompt for the same vertex
            fflush(stdin);
            printf("Incorrect value.\n");
            i--;
            continue;
        }
        // Flush the standard input to clear any remaining characters
        fflush(stdin);

        // Loop to prompt the user for destination vertices for each path
        for (int j = 0; j < numPaths; ++j)
        {
            int destinationVertex;
            
            // Prompt for the destination vertex for each path
            printf("\tWhich vertex do you want to point to for path %d? (Enter the vertex number): ", j);
            // Read the user input for the destination vertex and check for errors
            if (scanf("%d", &destinationVertex) != 1 || destinationVertex < 0 || destinationVertex >= graph->size)
            {
                // Print an error message for incorrect input and decrement j to re-prompt for the same path
                fflush(stdin);
                printf("Incorrect value for the vertex number.\n");
                j--;
                continue;
            }

            // Assign the path to the adjacency matrix and transposition matrix
            // Assuming presence of a path, adjust as needed
            (graph->matrix)[i][destinationVertex] = 1;
            (graph->transpos_matrix)[destinationVertex][i] = 1;
        }
    }

    // Flush the standard input to clear any remaining characters
    fflush(stdin);

    // Return OK code indicating successful graph creation
    return OK;
}

// Function to print the graph as a DOT file for visualization
void print_graph(graph_t *graph)
{
    // Open a file named "graph.gv" in write mode
    FILE *f = fopen("graph.gv", "w");

    // Write the initial lines for a DOT file with a directed graph
    fprintf(f, "digraph graph_pic {\n");

    // Loop through each vertex in the graph
    for (size_t i = 0; i < (size_t)graph->size; ++i)
        // Loop through each vertex again to check for edges
        for (size_t j = 0; j < (size_t)graph->size; ++j)
            // Check if there is a non-zero value in the adjacency matrix indicating an edge
            if (graph->matrix[i][j] != 0)
                // Write a line to the DOT file representing the edge
                fprintf(f, "%zu -> %zu [label=\"%.1d\"];\n", i, j, graph->matrix[i][j]);

    // Write the closing brace for the DOT file
    fprintf(f, "}\n");
    
    // Close the file
    fclose(f);
}

    
// Depth-First Search (DFS) function to check the connectivity of the graph
static void dfs_check_connected(graph_t *graph, int **matrix, int *visited, int index)
{
    // Mark the current vertex as visited
    visited[index] = 1;

    // Iterate through each vertex in the graph
    for (int i = 0; i < graph->size; ++i) 
    {
        // Check if the current vertex is not the starting vertex, there is an edge, and the neighbor is not visited
        if (i != index && matrix[index][i] && !visited[i])
            // Recursively call DFS for the unvisited neighbor
            dfs_check_connected(graph, matrix, visited, i);
    }
}

// Updated is_connected function with a start vertex parameter
// Function to check if the graph is connected starting from a specified vertex using DFS
int is_connected(graph_t *graph, int start_vertex)
{
    // Allocate an array to track visited vertices during DFS
    int *visited = calloc(graph->size, sizeof(int));

    // Check if memory allocation was successful
    if (!visited)
        return ERR_MEMORY;

    // Call DFS to mark visited vertices starting from the specified start_vertex
    dfs_check_connected(graph, graph->matrix, visited, start_vertex);

    // Assume the graph is initially connected
    int connected = 1;

    // Check if there are any unvisited vertices
    for (int i = 0; i < graph->size; ++i) {
        // If a vertex is not visited, set connected to 0 and break the loop
        if (visited[i] == 0) {
            connected = 0;
            break;
        }
    }

    // Free the memory allocated for the visited array
    free(visited);

    // Print a message indicating whether the graph is connected or not
    if (connected) {
        printf("\nGraph is connected.\n\n");
    } else {
        printf("\nGraph is not connected.\n\n");
    }

    // Return 1 if connected, 0 if not connected
    return connected;
}


