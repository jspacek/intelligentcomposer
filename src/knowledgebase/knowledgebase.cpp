//
//  Created by jodi spacek on 2014-09-22.
//
//  Issues: May need to memory map knowledgebase.bin
//
// (1) Compile: g++ -Wall -Wextra -c -o send.o knowledgebase.cpp
// (2) Link: g++ -o bin/send oscpack_1_1_0/osc/OscTypes.o send.o oscpack_1_1_0/osc/OscOutboundPacketStream.o oscpack_1_1_0/ip/posix/UdpSocket.o
//  oscpack_1_1_0/ip/IpEndpointName.o oscpack_1_1_0/ip/posix/NetworkingUtils.o
//
//

#include <string.h>
#include <iostream>
#include <fstream>
#include "MotiveMatrix2D.cpp"
#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/ip/UdpSocket.h>

#define ADDRESS "127.0.0.1"
#define PORT 7000
#define OUTPUT_BUFFER_SIZE 1024

using namespace std;

// SERIALIZE: Write the MM object as a binary little endian record
void write(MotiveMatrix2D* MM) {
    
    // Open the knowledge base to append to the file (never overwrite!)
    fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app);
    
    if (file.is_open())
    {
        // Loop to accept commands from the supervisor
        char* command = (char*) malloc(4*sizeof(char));
        
        // **** WRITE **** Save a MotiveMatrix2D object
        while (1) {
            printf("\nEnter command: ");
            scanf ("%s", command);
            // Check for exit command
            if (strcmp(command, "exit") == 0)
                break;
            
            if (strcmp(command, "save") == 0) {
                file.write((char*) &MM->N, sizeof(int));
                for (int i = 0;i<MM->N*MM->N;i++) {
                    file.write((char*) &MM->motive[i], sizeof(int));
                }
            }
        }
        file.close();
    } else {
        fprintf(stderr, "\nWrite: Error opening knowledgebase.bin\n\n");
        exit (1);
    }
}

// DESERIALIZE: Read and return the MM object form the binary file
// TODO: Scan through different positions in fixed format records (use variable pos)
MotiveMatrix2D* read(int pos) {
    
    // Open the knowledge base to append to the file, and to read binary data
    // Construct MM object
    MotiveMatrix2D* MM;
    fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app | ios::beg);
    
    if (file.is_open())
    {
        cout << " file is open ";
        // Navigate to the first position in the file TODO pos
        file.seekg (0, file.beg);
        
        int N = 0;
        file.read((char *) &N, sizeof(N));
        cout << " Size of matrix is " << N << "\n";
        MM = new MotiveMatrix2D(N);
        
        // Read the data in as an N*N int sized buffered block
        int values[N*N];
        cout << " read";
        
        file.read((char*)values, N*N*sizeof(int));
        for (int i=0;i<N*N;i++){
            cout << "  Element [" << "][" << i%4 << "] = " << values[i];
            MM->motive[i] = values[i];
        }
        
    } else {
        fprintf(stderr, "\nRead: Error opening knowledgebase.bin\n\n");
        exit (1);
    }
    
    file.close();
    
    return MM;
}

// Send the MM object to Max MSP
bool send(MotiveMatrix2D* MM) {
    
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE );
    
    // Send a motive matrix with note values
    
    p << osc::BeginBundleImmediate
    << osc::BeginMessage( "/dirTest3653" )
    << MM->motive[0] << MM->motive[1] << osc::EndMessage
    << osc::EndBundle;
    
    transmitSocket.Send( p.Data(), p.Size() );
    
    return true;
}

// Read and write a test MotiveMatrix2D object
int main () {
    
    TestMM* test = new TestMM();
    MotiveMatrix2D* MM = test->test3653();
    
    write(MM);
    
    MM = read(0);
    
    bool success = send(MM);
    
    delete test;
    delete MM;
}

