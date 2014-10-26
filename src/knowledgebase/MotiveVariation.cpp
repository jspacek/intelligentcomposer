
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

/**
*   Compressed variation of a motive matrix, that is the motive path (melody)
**/
class CompressVariation {
public:
    
    // length of the array
    int len;
    // melody in an array
    int* melody;
    // set by the supervisor
    int rating;
    
    CompressVariation (int l, int* m) {
        len = l;
        melody = m;
    }
};

class MotiveVariation {
public:
    
    /************ Motive Path Traversal *********************************
     
     A path can move L-R horizontally, or L-R diagonally.
     Using rand gen seed values in the bit vectors, the combinations are
     
     diagonalBV      leftRightBV
        0               0           Move Left
        0               1           Move Right
        1               0           Move Left Diagonal
        1               1           Move Right Diagonal
     
     ********************************************************************/

    vector<pair<int,int>> selectPath(int pathLength, MotiveMatrix* mm) {
        
        vector<pair<int,int>> mp;
        // Set the path max value for the traversal bit vectors
        int bitLength = pow (2.0, pathLength);
        
        // Initialize seed values for path traversal
        unsigned int leftRightBV = rand() % bitLength;
        unsigned int diagonalBV = rand() % bitLength;
        // Start anywhere in the matrix
        int x = rand() % mm->N;
        int y = rand() % mm->M;
        
        // Bit manipulation to determine traversal steps
        for (int i=0;i<pathLength;i++) {
            // Determine x coordinate step
            if ((leftRightBV >> i) & 1) {
                // Move right if within boundary N
                if (x+1 < mm->N) x++;
                // Otherwise, move left
                else x--;
            } else {
                // Move left if x-1 >= 0
                if (x-1>0) x--;
                else x++;
            }
            // Determine diagonal move in y-coor
            if ((diagonalBV >> i) & 1) {
                // Move up if within boundary M
                if (y+1 < mm->M) y++;
                // Otherwise, move down
                else y--;
            }
            // Add the next step coordinates to the vector
            mp.push_back(make_pair(x, y));
        }
        
        return mp;
    }
    
    // TODO SELECT STRAIGHT PATH

    
    /************ Weighted Moving Average calculation ********************
     
     An interval can be either zero, positive or negative, and
     it can have a max size of 8.
     
     A weighted moving average is used to determine the likelihood of the
     next interval being positive or negative. If the interval value is 0,
     the note is repeated and is not part of the average calculation.
     
     *********************************************************************/
    
    int* selectMelody(int pathLength, vector<pair<int,int>> mp, int** mm) {
        // Construct an array of interval values
        int* melody = new int[pathLength];
        // Seed value for weighted average in percent
        int weightedMovingAverage = rand() % 100;
        
        // Loop around the matrix to select interval values
        // then use weighted moving average to determine if
        // positive, negative or equal
        
        for (int i=0;i<pathLength;i++) {
            
            
            
        }
        
        return melody;
    }
};