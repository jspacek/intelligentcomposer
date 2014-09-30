//
//  Created by jodi spacek on 2014-09-27.
//
//
//

#include <iostream>

using namespace std;

// Constructs a Test Square 2x2 Matrix containing a motive on the diagonal
class MotiveMatrix2D {
public:
    // N = number of rows and columns (a square matrix)
    int N;
    // Container for the motive consisting of directional values
    int* motive;
    
    // Empty object
    MotiveMatrix2D(int value){
        N = value;
        motive = new int[N*N];
    }
    
    MotiveMatrix2D(int dimension, int* dm){
        N = dimension;
        // For simplicity and speed, store the matrix into a 1-D array
        motive = dm;
    }
};

// Used for testing a matrix
class TestMM {
public:
    // Test matrix motive for melody 3 - 6 - 5 - 3
    MotiveMatrix2D* test3653 () {
        int N = 4;
        int* dm = new int[N*N];
        
        dm[0] = 3;//* Note 1
        dm[1] = 4;
        dm[2] = 4;
        dm[3] = 6;
        dm[4] = 1;
        dm[5] = 6;//* Note 2
        dm[6] = 6;
        dm[7] = 4;
        dm[8] = 2;
        dm[9] = 5;
        dm[10] = 5;//* Note 3
        dm[11] = 5;
        dm[12] = 7;
        dm[13] = 7;
        dm[14] = 7;
        dm[15] = 3;//* Note 4
        
        MotiveMatrix2D* MM = new MotiveMatrix2D(N, dm);
        
        return MM;
    }
};