
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define DEBUG 1

class Path {
public:
    int len;
    int* intervals;
    vector<pair<int,int>> path;
    
    /************ Motive Path Traversal *********************************
     
     A path can move L-R horizontally, or L-R diagonally.
     Using rand gen seed values in the bit vectors, the combinations are
     
     diagonalBV      leftRightBV
        0               0           Move Left
        0               1           Move Right
        1               0           Move Left Diagonal
        1               1           Move Right Diagonal
     
     ********************************************************************/

    void selectPath(int pathLength, Matrix* matrix) {
        
        // Set the path max value for the traversal bit vectors
        int bitLength = pow (2.0, pathLength);
        
        // Initialize seed values for path traversal
        unsigned int leftRightBV = rand() % bitLength;
        unsigned int diagonalBV = rand() % bitLength;
        // Start anywhere in the matrix
        int x = rand() % matrix->N;
        int y = rand() % matrix->M;
        
        // Bit manipulation to determine traversal steps
        for (int i=0;i<pathLength;i++) {
            // Determine x coordinate step
            if ((leftRightBV >> i) & 1) {
                // Move right if within boundary N
                if (x+1 < matrix->N) x++;
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
                if (y+1 < matrix->M) y++;
                // Otherwise, move down
                else y--;
            }
            // Add the next step coordinates to the vector
            path.push_back(make_pair(x, y));
        }
        
    }
    
    
    /************ Weighted Moving Average calculation ********************
     
     An interval can be either zero, positive or negative, and
     it can have a max size of 8.
     
     A weighted moving average is used to determine the likelihood of the
     next interval being positive or negative. If the interval value is 0,
     the note is repeated and is not part of the average calculation.
          
     *********************************************************************/
    void selectMelody(int pathLength, vector<pair<int,int>> mp, Matrix* matrix) {
        // Construct an array of interval values
        intervals = new int[pathLength];
        // Set balanced values for calculation
        intervals[0] = 1;
        intervals[1] = -1;
        intervals[2] = 0;
        intervals[3] = -1;
        intervals[4] = 1;
        // Store the probability of a positive or negative interval
        int history = 0;
        int i = 0;
        int j = 0;
        cout << "\n Melody Selection ";
        
        // Loop around the matrix to select interval values
        // then use weighted moving average to determine if
        // positive, negative or equal
        for (auto it = begin (mp); it != end (mp); ++it) {
            // Modify counter if within 5 elements of the beginning
            if (i < 5) j = 4;
            else j = i;
            history = 5*intervals[j-3] + 10*intervals[j-2] + 50*intervals[j-1];
            // if random is > prob
            int random = 50 + history*.15;
            if (random < 5 ) random = 5;
            else if (random > 99) random = 99;
            
            int r = rand() % 100;
            if (r > random) intervals[i] = matrix->matrix[it->first][it->second];
            else if (r <= random) intervals[i] = -1 * matrix->matrix[it->first][it->second];
            i++;
        }
        
    }
    
    // Compose a new motive and send it
    void compose(int l, Matrix* matrix) {
        len = l;

        selectPath(len, matrix);
        if (DEBUG) cout << "\n Path is ";
        
        for (auto it = begin (path); it != end (path); ++it) {
            if (DEBUG) cout << " (" << it->first << ", " << it->second << ") ";
        }
        
        selectMelody(len, path, matrix);
    }
};