#include <vector>

using namespace std;

/*
 Directional matrix that is traversed to create variations of the original motivePath
 Defines the accompaniment for an entire piece. Range is NxM, N=7, M=21 where n is the
 x coordinate width and M is the y coordinate height.
 We have a 1 octave range across, and 3 octaves in height.
 */
class MotiveMatrix {
public:
    
    int N;
    int M;
    int ** matrix;
    vector<pair<int,int>> path;
    
    MotiveMatrix () {
        
        N = 7;
        M = 21;
        
        // Allocate space for the outer pointers
        // (Casting to its actual type afterwards)
        matrix = (int**) (malloc(N*sizeof(int*)));
        
        // Allocate space for each individual cell
        for (int i=0;i<N;i++){
            matrix[i] = (int*) malloc(M*(sizeof(int*)));
        }
        
        // Define a starting path for the motive
        path = {
            {0, 0},
            {1, 1},
            {2, 2},
            {2, 4},
            {2, 6},
            {3, 3},
            {3, 5},
            {4, 0},
            {4, 4},
            {5, 0},
            {5, 5},
            {5, 6}
        };
        
        matrix[0][0] = 1;// Note 1
        matrix[0][1] = 1;
        matrix[0][2] = 1;
        matrix[0][3] = 0;
        matrix[0][4] = 0;
        matrix[0][5] = 0;
        matrix[0][6] = 0;
        matrix[0][7] = 0;
        matrix[0][8] = 1;
        matrix[0][9] = 1;
        matrix[0][10] = 1;
        matrix[0][11] = 1;
        matrix[0][12] = 1;
        matrix[0][13] = 1;
        matrix[0][14] = 1;
        matrix[0][15] = 1;
        matrix[0][16] = 1;
        matrix[0][17] = 1;
        matrix[0][18] = 1;
        matrix[0][19] = 1;
        matrix[0][20] = 1;
        
        matrix[1][0] = 1;
        matrix[1][1] = 2;// Note 2
        matrix[1][2] = 2;
        matrix[1][3] = 2;
        matrix[1][4] = 2;
        matrix[1][5] = 2;
        matrix[1][6] = 2;
        matrix[1][7] = 3;
        matrix[1][8] = 3;
        matrix[1][9] = 3;
        matrix[1][10] = 3;
        matrix[1][11] = 3;
        matrix[1][12] = 3;
        matrix[1][13] = 3;
        matrix[1][14] = 3;
        matrix[1][15] = 3;
        matrix[1][16] = 3;
        matrix[1][17] = 3;
        matrix[1][18] = 3;
        matrix[1][19] = 3;
        matrix[1][20] = 3;
        
        matrix[2][0] = 2;
        matrix[2][1] = 1;
        matrix[2][2] = 5;// Note 3
        matrix[2][3] = 5;
        matrix[2][4] = 5;
        matrix[2][5] = 5;
        matrix[2][6] = 5;
        matrix[2][7] = 4;
        matrix[2][8] = 4;
        matrix[2][9] = 4;
        matrix[2][10] = 4;
        matrix[2][11] = 4;
        matrix[2][12] = 4;
        matrix[2][13] = 4;
        matrix[2][14] = 4;
        matrix[2][15] = 4;
        matrix[2][16] = 4;
        matrix[2][17] = 4;
        matrix[2][18] = 4;
        matrix[2][19] = 4;
        matrix[2][20] = 4;
        
        matrix[3][0] = 4;
        matrix[3][1] = 4;
        matrix[3][2] = 2;
        matrix[3][3] = 3;// Note 4
        matrix[3][4] = 3;
        matrix[3][5] = 3;
        matrix[3][6] = 2;
        matrix[3][7] = 2;
        matrix[3][8] = 2;
        matrix[3][9] = 2;
        matrix[3][10] = 2;
        matrix[3][11] = 2;
        matrix[3][12] = 2;
        matrix[3][13] = 2;
        matrix[3][14] = 2;
        matrix[3][15] = 2;
        matrix[3][16] = 2;
        matrix[3][17] = 2;
        matrix[3][18] = 2;
        matrix[3][19] = 2;
        matrix[3][20] = 2;
        
        matrix[4][0] = 5;// Note 5
        matrix[4][1] = 5;
        matrix[4][2] = 5;
        matrix[4][3] = 5;
        matrix[4][4] = 6;// Note 6
        matrix[4][5] = 6;
        matrix[4][6] = 6;
        matrix[4][7] = 5;
        matrix[4][8] = 5;
        matrix[4][9] = 5;
        matrix[4][10] = 5;
        matrix[4][11] = 5;
        matrix[4][12] = 5;
        matrix[4][13] = 5;
        matrix[4][14] = 5;
        matrix[4][15] = 5;
        matrix[4][16] = 5;
        matrix[4][17] = 5;
        matrix[4][18] = 5;
        matrix[4][19] = 5;
        matrix[4][20] = 5;
        
        matrix[5][0] = 2;// Note 7
        matrix[5][1] = 2;
        matrix[5][2] = 2;
        matrix[5][3] = 2;
        matrix[5][4] = 2;
        matrix[5][5] = 1;// Note 8
        matrix[5][6] = 0;
        matrix[5][7] = 1;
        matrix[5][8] = 2;
        matrix[5][9] = 3;
        matrix[5][10] = 3;
        matrix[5][11] = 1;
        matrix[5][12] = 1;
        matrix[5][13] = 1;
        matrix[5][14] = 1;
        matrix[5][15] = 1;
        matrix[5][16] = 1;
        matrix[5][17] = 0;
        matrix[5][18] = 0;
        matrix[5][19] = 0;
        matrix[5][20] = 0;
        
        matrix[6][0] = 2;// Note 7
        matrix[6][1] = 2;
        matrix[6][2] = 2;
        matrix[6][3] = 2;
        matrix[6][4] = 2;
        matrix[6][5] = 1;// Note 8
        matrix[6][6] = 0;
        matrix[6][7] = 1;
        matrix[6][8] = 2;
        matrix[6][9] = 3;
        matrix[6][10] = 3;
        matrix[6][11] = 1;
        matrix[6][12] = 1;
        matrix[6][13] = 1;
        matrix[6][14] = 1;
        matrix[6][15] = 1;
        matrix[6][16] = 1;
        matrix[6][17] = 0;
        matrix[6][18] = 0;
        matrix[6][19] = 0;
        matrix[6][20] = 0;
    }
};