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
    
    CompressVariation (int l, int* m) {
        len = l;
        melody = m;
    }
};

class MotiveVariation {
public:
    
    /************ Rules for motive path traversal **************
     
        3 Bit vectors store previous direction choices.
        A direction can be either positive or negative (or 0, oh no!).
        A path can move L-R horizontally, or L-R diagonally.
        The default move is a straight move forward along y-coor.
     
     ***********************************************************/
    
    // Bit vector stores previous neg/pos interval values
    unsigned int signBV;
    // Bit vector stores previous left/right diagonal direction choices
    unsigned int diagonalBV;
    // Bit vector stores previous left/right across direction choices
    unsigned int sidewaysBV;
    
    /*
     Selects a motive path through the matrix based on historic choices
     */
    vector<pair<int,int>> selectPath(int lengthPath, MotiveMatrix* mm) {
        
        // Assign a random starting seed value for both note selection
        // TODO and matrix path directions
        vector<pair<int,int>> mp;
        
        // TODO check bounds with the matrix
        
        if (signBV == 0) {
            signBV = 2;
        }
        signBV = 6;

        // Check the last choice made, give it weighting 5
        if (signBV & 1) {
            // the last choice made was positive
            cout << " last choice positive ";
            
        }
        if ((signBV >> 1) & 1 ){
            // the second-to-last choice made was positive
            cout << " second to last choice positive ";

        }
        if ((signBV >> 2) & 1 ){
            // third-to-last choice made was positive
            cout << " third to last choice positive ";
            
        }
        // TODO return a dummy version for now
        mp =  {
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
            {6, 10},
            {6, 15}
        };
        return mp;
    }
    
    /*
     Compress without variation
     */
    CompressVariation* compress(vector<pair<int,int>> mp, MotiveMatrix* mm) {
        int len = 0;
        int* melody = new int[mp.size()];
        cout << "  { ";
        // Parse motivic elements from the matrix
        for (auto it = begin (mp); it != end (mp); ++it) {
            cout << " (" << it->first << ", " << it->second << ") ";
            melody[len] = mm->matrix[it->first][it->second];
            len++;
        }
        len++;
        cout << " }";
        CompressVariation* cv = new CompressVariation(len, melody);
        
        return cv;
    }
    
    /*
     Return a compressed melody that is a variation of the original
     */
    CompressVariation* variation(MotiveMatrix* mm) {
        //default path to 12 for now
        vector<pair<int,int>> mp = selectPath(12, mm);
        CompressVariation* cv = compress(mp, mm);
        return cv;
    }
};