//
//  knowledgebase.cpp
//  

#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

// Static length record structure
class DirectionMatrix {
    public:
    int*** direction;//a 3D array
    //or using the pylib numlib for matrices
    // or eigen in C++
    char descr[20];
};

// Binary serialization of directionMatrix 
int main () {

    DirectionMatrix dirM;
    
    // Open the knowledge base to append to the file, and to read binary data
    fstream file ("knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app);

    if (file.is_open())
    {
        // Loop to build inputs of matrix
        while (1) {
            // TODO minimal fields for now
            printf("\nDescr: ");
            scanf ("%s", dirM.descr);
            // Check for exit command
            if (strcmp(dirM.descr, "exit") == 0)
                break;
            
            // Allocate memory for the 3D array
            dirM.direction = new int**[1];
            for (int i = 0; i < 1; ++i) {
                dirM.direction[i] = new int*[1];
                
                for (int j = 0; j < 1; ++j)
                    dirM.direction[i][j] = new int[1];
            }
            
            dirM.direction[0][0][0] = 1;
            
            //Save using the constant size
            file.write(dirM.descr, 20);
            // Convert int to character array using the pointer value
            file.write((char*) &dirM.direction, 3*sizeof(int));
        }
        
    } else {
        fprintf(stderr, "\nError opening knowledgebase.bin\n\n");
        exit (1);
    }
            
    while (file.read(dirM.descr, 20))
        printf("Descr = %10s\n", dirM.descr);
    
    file.close();
    
    //Delete pointers
    delete dirM.direction;
    
    return 0;
}

