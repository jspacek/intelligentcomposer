#include <vector>

using namespace std;
//
// Constructed static (TODO) motives in their original form, before they
// are reconstructed and modified as flat array variations

// TODO investigate const or namespace as static is not used in C/C++
//
class ConstructMM {
public:
    // Set the motive and motive path

    MotiveMatrix2D* motive1() {
        
        vector<pair<int,int>> motivePath = {
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
        MotiveMatrix2D* m = new MotiveMatrix2D(6, 10, motivePath);
        
        m->matrix[0][0] = -1;// Note 1
        m->matrix[0][1] = -1;
        m->matrix[0][2] = -1;
        m->matrix[0][3] = 0;
        m->matrix[0][4] = 0;
        m->matrix[0][5] = 0;
        m->matrix[0][6] = 0;
        m->matrix[0][7] = 0;
        m->matrix[0][8] = 1;
        m->matrix[0][9] = 1;
        m->matrix[1][0] = 1;
        m->matrix[1][1] = 2;// Note 2
        m->matrix[1][2] = 2;
        m->matrix[1][3] = 2;
        m->matrix[1][4] = 2;
        m->matrix[1][5] = 2;
        m->matrix[1][6] = 2;
        m->matrix[1][7] = 3;
        m->matrix[1][8] = 3;
        m->matrix[1][9] = 3;
        m->matrix[2][0] = 2;
        m->matrix[2][1] = 1;
        m->matrix[2][2] = 5;// Note 3
        m->matrix[2][3] = 5;
        m->matrix[2][4] = 5;
        m->matrix[2][5] = 5;
        m->matrix[2][6] = 5;
        m->matrix[2][7] = 4;
        m->matrix[2][8] = 4;
        m->matrix[2][9] = 4;
        m->matrix[3][0] = 4;
        m->matrix[3][1] = 4;
        m->matrix[3][2] = 2;
        m->matrix[3][3] = 3;// Note 4
        m->matrix[3][4] = 3;
        m->matrix[3][5] = 3;
        m->matrix[3][6] = 2;
        m->matrix[3][7] = 2;
        m->matrix[3][8] = 2;
        m->matrix[3][9] = 2;
        m->matrix[4][0] = 7;// Note 5
        m->matrix[4][1] = 7;
        m->matrix[4][2] = 7;
        m->matrix[4][3] = 7;
        m->matrix[4][4] = 6;// Note 6
        m->matrix[4][5] = 6;
        m->matrix[4][6] = 6;
        m->matrix[4][7] = 5;
        m->matrix[4][8] = 5;
        m->matrix[4][9] = 5;
        m->matrix[5][0] = 2;// Note 7
        m->matrix[5][1] = 2;
        m->matrix[5][2] = 2;
        m->matrix[5][3] = 2;
        m->matrix[5][4] = 2;
        m->matrix[5][5] = 1;// Note 8
        m->matrix[5][6] = 0;
        m->matrix[5][7] = -1;
        m->matrix[5][8] = -2;
        m->matrix[5][9] = -3;
        
        return m;
    }
};