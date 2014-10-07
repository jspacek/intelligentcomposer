//
//  Created by jodi spacek on 2014-09-22.
//
//  Issues: May need to memory map knowledgebase.bin
//
// (1) Compile: g++ -std=c++11 -Wall -c -o send.o knowledgebase.cpp
// (2) Link: g++ -o bin/send oscpack_1_1_0/osc/OscTypes.o send.o oscpack_1_1_0/osc/OscOutboundPacketStream.o oscpack_1_1_0/ip/posix/UdpSocket.o
//  oscpack_1_1_0/ip/IpEndpointName.o oscpack_1_1_0/ip/posix/NetworkingUtils.o
//
//

#include <string.h>
#include <iostream>
#include <fstream>
#include "MotiveMatrix2D.cpp"
#include "ConstructMM.cpp"
#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/ip/UdpSocket.h>

#define ADDRESS "127.0.0.1"
#define PORT 7000
#define OUTPUT_BUFFER_SIZE 1024

using namespace std;

// SERIALIZE: Write the compressed array as a binary little endian record
void write(int* cm, int len) {
    
    // Open the knowledge base to append to the file (never overwrite!)
    fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app);

    if (file.is_open())
    {
        // Expect a command of size 4
        char* command = (char*) malloc(4*sizeof(char));
        
        // **** WRITE ****
        while (1) {
            printf("\nEnter command: ");
            scanf ("%s", command);
            // Check for exit command
            if (strcmp(command, "exit") == 0)
                break;
            
            if (strcmp(command, "save") == 0) {
                file.write((char*) &len, sizeof(int));
                for (int i = 0;i<len;i++) {
                    file.write((char*) &cm[i], sizeof(int));
                }
            }
        }
        file.close();
    } else {
        fprintf(stderr, "\nWrite: Error opening knowledgebase.bin\n\n");
        exit (1);
    }
    
}

// DESERIALIZE: Read the compressed motive array from the binary file

// TODO: Scan through different positions in fixed format records (use variable pos)
int* read(int pos) {
    
    // Open the knowledge base to append to the file, and to read binary data
    // Construct MM object
    fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app | ios::beg);
    int* cm;

    if (file.is_open())
    {
        cout << " file is open ";
        // Navigate to the first position in the file TODO use pos or search
        file.seekg (0, file.beg);
        
        int N = 0;
        file.read((char *) &N, sizeof(N));
        cm = new int[N];
        cout << " Size of array written was " << N << "\n";
        
        // Read the data in as an array of size N
        int values[N];
        cout << " read";
        
        file.read((char*)values, N*sizeof(int));
        for (int i=0;i<N;i++){
            cout << "  Element [" << i << "] = " << values[i];
            cm[i] = values[i];
        }
    } else {
        fprintf(stderr, "\nRead: Error opening knowledgebase.bin\n\n");
        exit (1);
    }
    file.close();
    
    return cm;
}

// Send the motive array to Max MSP
bool send(int* cm, int N) {
    
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE );
    
    // TODO LOOP
    
    p << osc::BeginBundleImmediate
    << osc::BeginMessage( "/dirTest3653" )
    << cm[0] << cm[1] << cm[2] << cm[3] << osc::EndMessage
    << osc::EndBundle;
    
    transmitSocket.Send(p.Data(), p.Size());
    
    return true;
}

// Read, write, and send a test compressed motive
int main () {
    ConstructMM* construct = new ConstructMM();
    MotiveMatrix2D* m3653775 = construct->motive3653775();
    CompressVariation* cm = m3653775->compress();
    
    write(cm->melody, m3653775->N);
    
    cm->melody = read(0);
    // TODO SEnd the entire object to iterate
    bool success = send(cm->melody, m3653775->N);
    delete construct;
    delete m3653775;
}

