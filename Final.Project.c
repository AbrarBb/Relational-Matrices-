#include <stdio.h>        // Include standard input/output library
#include <stdlib.h>      // Include standard library
#include <time.h>       // Include time library for randomization
#define MAX_N 100      // Define a constant MAX_N with a value of 100

int n;               // Declare an integer variable 'n' to store the number of relation matrices

int main()         // Main function
{
    clock_t start_time, end_time;                // Declare variables to measure time
    start_time = clock();                       // Record the start time
    double generation_time, verification_time; // Declare variables to store time durations
    double total_time;                        // Declare a variable to store the total time

    printf("Enter the number of relation matrices (n): "); // Prompt the user for input
    scanf("%d", &n);                                      // Read the user's input and store it in 'n'

    FILE* relationsFile = fopen("Relations.txt", "w");        // Open a file for writing relation matrices
    FILE* fp_results = fopen("Computational Time.txt", "w"); // Open a file for writing computational time results

        srand(time(NULL));        // Seed the random number generator with the current time

    for (int a = 0; a < n; a++) // Loop to generate 'n' relation matrices
    {
        int size = rand() % 10 + 1;        // Generate a random size for the matrix
        int relationMatrix[MAX_N][MAX_N]; // Declare a matrix to store the relation

        generateRelationMatrix(relationMatrix, size); // Generate a relation matrix

        fprintf(relationsFile, "Matrix %d (Size: %dx%d):\n", a + 1, size, size); // Write matrix information to the relations file
        printMatrixToFile(relationMatrix, size, relationsFile);                 // Write the matrix to the relations file
        fprintf(relationsFile, "\n");

        generation_time = ((double)clock() / CLOCKS_PER_SEC) * 1000; // Calculate generation time

        // Check if the matrix properties and write the results to the relations file
        if (isSymmetric(relationMatrix, size)) {
            fprintf(relationsFile, "Symmetric: Yes\n");
        } else {
            fprintf(relationsFile, "Symmetric: No\n");
        }

        if (isAntisymmetric(relationMatrix, size)) {
            fprintf(relationsFile, "Antisymmetric: Yes\n");
        } else {
            fprintf(relationsFile, "Antisymmetric: No\n");
        }

        if (isTransitive(relationMatrix, size)) {
            fprintf(relationsFile, "Transitive: Yes\n");
        } else {
            fprintf(relationsFile, "Transitive: No\n");
        }

        if (isEquivalence(relationMatrix, size)) {
            fprintf(relationsFile, "Equivalence Relation: Yes\n");
        } else {
            fprintf(relationsFile, "Equivalence Relation: No\n");
        }

        if (isFunction(relationMatrix, size)) {
            fprintf(relationsFile, "Function: Yes\n");
        } else {
            fprintf(relationsFile, "Function: No\n");
        }

        fprintf(fp_results, "  Matrix %d:\n", a + 1); // Write matrix information to the time results file
        fprintf(fp_results, "Generation Time: %lf milliseconds\n\n", generation_time); // Write generation time to the time results file
        fprintf(relationsFile, "\n");
    }

    end_time = clock(); // Record the end time
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calculate total time duration
    fprintf(fp_results, "\n\t\tVerification Time: %lf milliseconds\n\n", total_time * 1000); // Write total verification time to the time results file

    fclose(relationsFile); // Close the relations file
    fclose(fp_results);   // Close the time results file
    return 0;
}

// Function to generate a relation matrix
void generateRelationMatrix(int matrix[MAX_N][MAX_N], int n)
{
    for (int a = 0; a < n; a++)
    {
        for (int b = 0; b < n; b++)
        {
            matrix[a][b] = rand() % 2; // Fill the matrix with random values (0 or 1)
        }
    }
}

// Functions to check various properties of the relation matrix
// (isSymmetric, isAntisymmetric, isTransitive, isEquivalence, isFunction)

int isSymmetric(int matrix[MAX_N][MAX_N], int n)
{
    for (int a = 0; a < n; a++)           // Check if it's antisymmetric
    {
        for (int b = a + 1; b < n; b++) // Loop from a+1 to n-1
        {
            if (matrix[a][b] != matrix[b][a]) // Check if the matrix is not symmetric
            {
                return 0; // Return 0 to indicate not symmetric
            }
        }
    }
    return 1; // Return 1 to indicate symmetric
}

int isAntisymmetric(int matrix[MAX_N][MAX_N], int n)
{
    for (int a = 0; a < n; a++) // Loop n times
    {
        for (int b = 0; b < n; b++)
        {
            if (a != b && matrix[a][b] && matrix[b][a]) // Check if it's antisymmetric
            {
                return 0; // Return 0 to indicate not antisymmetric
            }
        }
    }
    return 1; // Return 1 to indicate antisymmetric
}

int isTransitive(int matrix[MAX_N][MAX_N], int n)
{
    for (int a = 0; a < n; a++)
     {
        for (int b = 0; b < n; b++)
            {
            for (int c = 0; c < n; c++)
                 {
                if (matrix[a][b] && matrix[b][c] && !matrix[a][c]) { // Check if it's transitive
                    return 0; // Return 0 to indicate not transitive
                }
            }
        }
    }
    return 1; // Return 1 to indicate transitive
}



int isEquivalence(int matrix[MAX_N][MAX_N], int n)
{
    if (isSymmetric(matrix, n) && isTransitive(matrix, n)) // Check if it's an equivalence relation
    {
        return 1; // Return 1 to indicate an equivalence relation
    }
    return 0;   // Return 0 to indicate not an equivalence relation
}

int isFunction(int matrix[MAX_N][MAX_N], int n)
{
    int used[n];         // Declare an array to keep track of how many times each element appears in rows
    for (int a = 0; a < n; a++) // Loop n times
    {
        used[a] = 0;          // Initialize used array
    }

    for (int a = 0; a < n; a++) // Loop n times
    {
        for (int b = 0; b < n; b++) // Loop n times
        {
            if (matrix[a][b])        // Check if there is a value in the matrix
            {
                used[b]++;         // Increment the count for the element
                if (used[b] > 1)  // Check if an element appears more than once
                {
                    return 0; // Return 0 to indicate not a function
                }
            }
        }
    }
    return 1; // Return 1 to indicate a function
}



// Function to print a matrix to a file
void printMatrixToFile(int matrix[MAX_N][MAX_N], int n, FILE* file)
{
    for (int a = 0; a < n; a++)       // Loop n times
    {
        for (int b = 0; b < n; b++) // Loop n times
        {
            fprintf(file, "%d ", matrix[a][b]); // Write the matrix elements to the file
        }
        fprintf(file, "\n");                   // Write a newline to the file after each row
    }
}







