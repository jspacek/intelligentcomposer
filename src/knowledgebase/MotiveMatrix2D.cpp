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
    // melody in an array
    int* melody;
    // set by the supervisor
    int rating;
    // historic modulation
    vector<pair<int,int>> modifiedMP;
    
    CompressVariation (int** matrix, int N, int M, vector<pair<int,int>> mp, bool compose) {
        len = 0;
        if (compose) {
            // create a new motive variation based on the motive path and MM bounds
            // TODO attributes to select the correct variation
            melody = new int[mp.size()];
            cout << " { ";
            // Parse motivic elements from the matrix
            for (auto it = begin (mp); it != end (mp); ++it) {
                // Vary the path, making sure it doesn't go outside the matrix bounds
                int n = it->first;
                if (n+1 <= N-1) n++; else n--;
                int m = it->second;
                if (m+2 <= M-1) m+=2; else m--;
                melody[len] = matrix[n][m];
                modifiedMP.push_back(std::make_pair(n,m));
                cout << " (" << n << ", " << m << ") ";
                len++;
            }
            len++;
            cout << " }";
        } else {
            // compress without modifying the motive path
            melody = new int[mp.size()];
            cout << "  { ";
            // Parse motivic elements from the matrix
            for (auto it = begin (mp); it != end (mp); ++it) {
                cout << " (" << it->first << ", " << it->second << ") ";
                melody[len] = matrix[it->first][it->second];
                len++;
            }
            len++;
            cout << " }";
        }
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
    vector<pair<int,int>> rotate(vector<pair<int,int>> mp) {
        // TODO
        return mp;
        
    }
    
    /*
     Modify the melody path and compress
     Return a compressed melody that is a variation of the original
     */
    CompressVariation* variation(vector<pair<int,int>> lastMP) {
        CompressVariation* cv;
        if (lastMP.size() == 0) {
            // First variation
            cv = new CompressVariation(matrix, N, M, motivePath, true);
        } else {
           cv = new CompressVariation(matrix, N, M, lastMP, true);
        }
        
        return cv;
    }
    /*
     Modify the melody path and compress the original
     Return a compressed melody without variation
     */
    CompressVariation* compress() {
        CompressVariation* cv = new CompressVariation(matrix, N, M, motivePath, false);
        return cv;
    }
};