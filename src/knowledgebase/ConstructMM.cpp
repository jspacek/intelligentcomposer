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

    MotiveMatrix2D* motive3653775() {
        
        // Matrix motive for melody 3 - 6 - 5 - 3 - 7 - 7 - 5
        vector<pair<int,int>> motivePath = {
            {0, 0},
            {1, 1},
            {2, 2},
            {3, 3},
            {4, 0},
            {4, 4},
            {5, 0},
            {5, 5}
        };
        MotiveMatrix2D* m3653775 = new MotiveMatrix2D(6, 10, motivePath);
        
        m3653775->matrix[0][0] = 3;// Note 1
        m3653775->matrix[0][1] = 3;
        m3653775->matrix[0][2] = 3;
        m3653775->matrix[0][3] = 4;
        m3653775->matrix[0][4] = 4;
        m3653775->matrix[0][5] = 4;
        m3653775->matrix[0][6] = 5;
        m3653775->matrix[0][7] = 5;
        m3653775->matrix[0][8] = 5;
        m3653775->matrix[0][9] = 6;
        m3653775->matrix[1][0] = 6;
        m3653775->matrix[1][1] = 6;// Note 2
        m3653775->matrix[1][2] = 6;
        m3653775->matrix[1][3] = 5;
        m3653775->matrix[1][4] = 5;
        m3653775->matrix[1][5] = 5;
        m3653775->matrix[1][6] = 5;
        m3653775->matrix[1][7] = 4;
        m3653775->matrix[1][8] = 4;
        m3653775->matrix[1][9] = 4;
        m3653775->matrix[2][0] = 2;
        m3653775->matrix[2][1] = 5;
        m3653775->matrix[2][2] = 5;// Note 3
        m3653775->matrix[2][3] = 5;
        m3653775->matrix[2][4] = 6;
        m3653775->matrix[2][5] = 6;
        m3653775->matrix[2][6] = 6;
        m3653775->matrix[2][7] = 5;
        m3653775->matrix[2][8] = 5;
        m3653775->matrix[2][9] = 5;
        m3653775->matrix[3][0] = 1;
        m3653775->matrix[3][1] = 1;
        m3653775->matrix[3][2] = 2;
        m3653775->matrix[3][3] = 3;// Note 4
        m3653775->matrix[3][4] = 2;
        m3653775->matrix[3][5] = 2;
        m3653775->matrix[3][6] = 2;
        m3653775->matrix[3][7] = 3;
        m3653775->matrix[3][8] = 3;
        m3653775->matrix[3][9] = 3;
        m3653775->matrix[4][0] = 7;// Note 5
        m3653775->matrix[4][1] = 7;
        m3653775->matrix[4][2] = 7;
        m3653775->matrix[4][3] = 6;
        m3653775->matrix[4][4] = 6;// Note 6
        m3653775->matrix[4][5] = 6;
        m3653775->matrix[4][6] = 6;
        m3653775->matrix[4][7] = 8;
        m3653775->matrix[4][8] = 8;
        m3653775->matrix[4][9] = 8;
        m3653775->matrix[5][0] = 2;// Note 7
        m3653775->matrix[5][1] = 2;
        m3653775->matrix[5][2] = 2;
        m3653775->matrix[5][3] = 2;
        m3653775->matrix[5][4] = 3;
        m3653775->matrix[5][5] = 5;// Note 8
        m3653775->matrix[5][6] = 5;
        m3653775->matrix[5][7] = 5;
        m3653775->matrix[5][8] = 5;
        m3653775->matrix[5][9] = 6;

        
        return m3653775;
    }
};