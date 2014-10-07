//
//  Initial input of a motive in 2D Matrix format
//  that is used to generate variations on the motive
//
#include <vector>
#include <iostream>

using namespace std;

//
// Compressed variation of a motive matrix, that is the motive path (melody)
//
class CompressVariation {
public:
    // length of the array
    int len;
    int* melody;
    
    CompressVariation (int** matrix, vector<pair<int,int>> mp) {
        len = 0;
        melody = new int[mp.size()];
        // Parse motivic elements from the matrix
        for (auto it = begin (mp); it != end (mp); ++it) {
            cout << " compress the variation " << it->first << " " << it->second;
            melody[len] = matrix[it->first][it->second];
            len++;
        }
        len++;
    }
};

class MotiveMatrix2D {
public:
    // N is the height
    int N;
    // M is the width
    int M;
    // Container for the motive consisting of directional values
    int** matrix;
    // Motive path to traverse through the matrix
    vector<pair<int,int>> motivePath;
    
    // Instantiates a matrix with an empty matrix array that has
    // been allocated memory in the order of N*M
    MotiveMatrix2D(int n, int m, vector<pair<int,int>> mp) {
        N = n;
        M = m;
        motivePath = mp;
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
    
    /*
     TODO
     */
    int* changePath() {
        
        int* anArray = new int[N];
        anArray[0] = 6;
        anArray[1] = 5;
        anArray[2] = 4;
        anArray[3] = 3;
        return anArray;
        
    }
    
    CompressVariation* compress() {
        CompressVariation* cv = new CompressVariation(matrix, motivePath);
        return cv;
    }
};