//
//  Initial input of a motive in 2D Matrix format
//  that is used to generate variations on the motive
//

#include <iostream>

using namespace std;

class MotiveMatrix2D {
public:
    // N is the height
    int N;
    // M is the width
    int M;
    // Container for the motive consisting of directional values
    int** matrix;
    
    // Instantiates a matrix with an empty matrix array that has
    // been allocated memory in the order of N*M
    MotiveMatrix2D(int n, int m) {
        N = n;
        M = m;
        // Allocate space for the outer pointers
        // (Casting to its actual type afterwards)
        matrix = (int**) (malloc(N*sizeof(int*)));
        
        // Allocate space for each individual cell
        for (int i=0;i<N;i++){
            matrix[i] = (int*) malloc(M*(sizeof(int*)));
        }
    }
    
    /*
     Generates a 90deg rotation of this matrix and parses
     the diagonal motive, compressing into an array
     */
    int* rotate() {
        
        int* anArray = new int[N];
        anArray[0] = 6;
        anArray[1] = 5;
        anArray[2] = 4;
        anArray[3] = 3;
        return anArray;
        
    }
    
    int* compress() {
        // Construct a path along the diagonal
        int* anArray = new int[N];
        anArray[0] = 6;
        anArray[1] = 5;
        anArray[2] = 4;
        anArray[3] = 3;
        return anArray;

    }
};