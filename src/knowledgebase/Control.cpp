//
//  Created by jodi spacek on 2014-09-22.
//
//  Issues: May need to memory map knowledgebase.bin
//
// (1) Compile: g++ -std=c++11 -Wall -c -o send.o Control.cpp
// (2) Link: g++ -o bin/send oscpack_1_1_0/osc/OscTypes.o send.o oscpack_1_1_0/osc/OscOutboundPacketStream.o oscpack_1_1_0/ip/posix/UdpSocket.o
//  oscpack_1_1_0/ip/IpEndpointName.o oscpack_1_1_0/ip/posix/NetworkingUtils.o
//
//

#include <string.h>
#include <iostream>
#include <fstream>
#include "MotiveMatrix.cpp"
#include "MotiveVariation.cpp"
#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/ip/UdpSocket.h>

#define ADDRESS "127.0.0.1"
#define SEND_PORT 7000
#define RECV_PORT 7001

#define OUTPUT_BUFFER_SIZE 1024

using namespace std;

// User elects to write, read, receive, or compose and send a motive to MAX MSP

// Send the motive array to Max MSP
void send(int* cm, int len) {
    
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, SEND_PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE );
    cout << "--> ";
    // TODO iterate through elements using len not hard coded
    p << osc::BeginBundleImmediate
    << osc::BeginMessage( "/dirTest3653775" )
    << cm[0] << cm[1] << cm[2] << cm[3] << cm[4] << cm[5] << cm[6] << cm[7] << cm[8] << cm[9] << cm[10] << cm[11]
    << osc::EndMessage
    << osc::EndBundle;
    
    transmitSocket.Send(p.Data(), p.Size());
}

// Compose a new motive and send it
void compose(MotiveMatrix* mm, MotiveVariation* mv) {
    
    vector<pair<int,int>> mp = mv->selectPath(12, mm);
    cout << " Path is ";
    
    for (auto it = begin (mp); it != end (mp); ++it) {
       cout << " (" << it->first << ", " << it->second << ") ";
    }

    // TODO send(cm->melody, cm->len);    
}

// SERIALIZE: Write the compressed array as a binary little endian record
void write(int* cm, int len) {
    
    // Open the knowledge base to append to the file (never overwrite!)
    fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app);
    
    if (file.is_open())
    {
        file.write((char*) &len, sizeof(int));
        for (int i = 0;i<len;i++) {
            file.write((char*) &cm[i], sizeof(int));
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
        // Navigate to the first position in the file TODO use pos or search
        file.seekg (0, file.beg);
        
        int N = 0;
        file.read((char *) &N, sizeof(N));
        cm = new int[N];
        cout << " Size of array written was " << N << "\n";
        
        // Read the data in as an array of size N
        int values[N];
        
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

// Handle user commands
void control(MotiveMatrix* mm, MotiveVariation* mv) {
    // Expect a command of max size 7
    char* command = (char*) malloc(7*sizeof(char));
    // Loop user prompt until exit
    while (1) {
        printf("\nEnter command (exit / compose) ");
        scanf ("%s", command);
        // Check for exit command
        if (strcmp(command, "exit") == 0)
            break;
        
        if (strcmp(command, "cmp") == 0) {
            // Create a variation based on the last 
            compose(mm, mv);
        } else {
            cout << "Command not recognized";
        }
    }
    delete command;
}

// Read, write, and send a test compressed motive
int main () {
    MotiveMatrix* mm = new MotiveMatrix();
    MotiveVariation* mv = new MotiveVariation();

    // Generate options to the user
    control(mm, mv);
    
    delete mm;
    delete mv;
}

