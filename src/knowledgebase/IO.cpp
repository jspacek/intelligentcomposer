/*
 
 Extract/Write data to/from the knowledgebase.bin
 data file, format and send it using OSC protocol.
 
 */

#include <iostream>
#include <cstring>
#include <fstream>

#define BLOCK_FIELD_SIZE 7
#define RECORD_DELIM 99
#define MAX_RECORD_SIZE 26
#define NO_SEARCH 99
#define DEBUG 1

using namespace std;

class IO {
    
public:
    
    int len;
    int* intervals;
    // User-generated attributes
    int finality, interest;
    // Calculated attributes
    int span, max, min, direction;
    
    // SERIALIZE: Write the compressed array as a binary little endian record
    void write(int len, int* melody, int finality, int interest) {
        // Open the knowledge base to append to the file (never overwrite!)
        fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app);
        int beg = RECORD_DELIM;
        // Computed values
        int max = -99;
        int min = 99;
        for (int i = 0;i<len;i++) {
            if (melody[i] > max) {
                max = melody[i];
            }
            if (melody[i] < min) {
                min = melody[i];
            }
        }
        if (DEBUG) cout << "\n finality = " << finality;
        if (DEBUG) cout << "\n interest = " << interest;
        if (DEBUG) cout << "\n max = " << max;
        if (DEBUG) cout << "\n min = " << min;
        int span = (max-min < 0)?(max-min)*-1:(max-min);
        if (DEBUG) cout << "\n span = " << span;
        // if max greater than min, direction is upwards
        int direction = (max > min)?1:0;
        if (DEBUG) cout << "\n direction = " << direction;
        
        if (file.is_open())
        {
            file.write((char*) &beg, sizeof(int));
            file.write((char*) &len, sizeof(int));
            file.write((char*) &finality, sizeof(int));
            file.write((char*) &interest, sizeof(int));
            file.write((char*) &span, sizeof(int));
            file.write((char*) &max, sizeof(int));
            file.write((char*) &min, sizeof(int));
            file.write((char*) &direction, sizeof(int));
            
            if (DEBUG) cout << "\nWRITE rated melody...";
            
            // Ignore default arguments sent, only write valid intervals
            for (int i = 0;i<len;i++) {
                if (DEBUG) cout << " " << melody[i] << " ";
                file.write((char*) &melody[i], sizeof(int));
            }
            
            file.close();
        } else {
            fprintf(stderr, "\nWrite: Error opening knowledgebase.bin\n\n");
            exit (1);
        }
    }
    
    
    // DESERIALIZE: Read the compressed motive array from the binary file
    // Retrieve a motive based on a finality value
    void read(int finality, int interest, int span, int max, int min, int direction) {
        
        // Open the knowledge base to append to the file, and to read binary data
        fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app | ios::beg);
        int beg, l, f, i, s, mx, mn, d;
        
        if (file.is_open())
        {
            
            // Find size of file
            file.seekg (0, file.end);
            int fileSize = file.tellg();
            // Store current position
            int start = rand() % fileSize/sizeof(int);
            if (DEBUG) cout << "\n File size is " << fileSize << " random start is " << start;
            int pos = start;
            if (start*sizeof(int) > fileSize-MAX_RECORD_SIZE) {
                // search last 10 elements
                pos = (fileSize/4) - 10;
            } else if (fileSize < MAX_RECORD_SIZE) {
                // file is too small
                pos = 0;
            }
            if (DEBUG) cout << "\n Search position is " << pos;
            // Navigate to a random block in the file starting from the beginning
            file.seekg(pos*sizeof(int), ios::beg);
            
            // Make sure we're at the begning of a variable-sized record
            file.read((char *) &beg, sizeof(int));
            while (beg != RECORD_DELIM && pos < fileSize) {
                pos++;
                file.read((char *) &beg, sizeof(int));
                if (DEBUG)
                    cout << "\n Seeking beginning of record, found " << beg << "\n";
            }
            int found = 0;
            
            // Perform search for a melody with the passed in attributes
            while (pos < fileSize) {
                // Read in the header fields
                file.read((char *) &l, sizeof(int));
                file.read((char *) &f, sizeof(int));
                file.read((char *) &i, sizeof(int));
                file.read((char *) &s, sizeof(int));
                file.read((char *) &mx, sizeof(int));
                file.read((char *) &mn, sizeof(int));
                file.read((char *) &d, sizeof(int));
                
                if (DEBUG)
                    std::cout << "\nRetrieved : "
                    << " finality= " << f << " interest= " << i << " span= " << s
                    << " max= " << mx << " min= " << mn << " direction= " << d;
                // Holder for the melodic intervals
                intervals = new int[l];
                int values[l];
                len = l;
                // Read in the interval values
                file.read((char*)values, l*sizeof(int));
                // Read next beginning delim
                file.read((char *) &beg, sizeof(int));
                
                if (DEBUG)
                    std::cout << "\nAttempt match for : "
                    << " finality= " << finality << " interest= " << interest << " span= " << span
                    << " max= " << max << " min= " << min << " direction= " << direction;
                
                // Retrieve the matching melody intervals
                if ((finality==NO_SEARCH || f==finality) && (interest==NO_SEARCH || i==interest)
                    && (span==NO_SEARCH || s==span) && (max==NO_SEARCH || mx==max)
                    && (min==NO_SEARCH || mn==min) && (direction==NO_SEARCH || d==direction)){
                    // If attributes match, read the melody data in as an array of size 18
                    for (int i=0;i<l;i++){
                        if (DEBUG) cout << "  Element [" << i << "] = " << values[i];
                        intervals[i] = values[i];
                    }
                    
                    if (DEBUG) cout << "\n FOUND MATCH, exit";
                    found = 1;
                    pos = fileSize++;
                }
                // Skip ahead by len, finality, and interest fields, + the length of the array fields
                pos = pos + sizeof(int)*(len + BLOCK_FIELD_SIZE);
                
            }
            
            // TODO if nothing found, how to recover from this?
            if (DEBUG) cout << "\n MATCH = " << found;
        } else {
            fprintf(stderr, "\nRead: Error opening knowledgebase.bin\n\n");
            exit (1);
        }
        
        file.close();
    }
};

