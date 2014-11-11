//
//  Created by jodi spacek on 2014-09-22.
//
//  Issues: May need to memory map knowledgebase.bin
//
// (1) Compile: g++ -std=c++11 -Wall -c -o send.o Control.cpp
// (2) Link: g++ -o bin/send oscpack_1_1_0/osc/OscTypes.o send.o oscpack_1_1_0/osc/OscOutboundPacketStream.o oscpack_1_1_0/ip/posix/UdpSocket.o
//  oscpack_1_1_0/ip/IpEndpointName.o oscpack_1_1_0/ip/posix/NetworkingUtils.o oscpack_1_1_0/osc/OscReceivedElements.o
//
//

#include <string.h>
#include <iostream>
#include <fstream>
#include "MotiveMatrix.cpp"
#include "MotiveVariation.cpp"
#include "RatingListener.cpp"

#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/osc/OscReceivedElements.h>
#include <oscpack/ip/UdpSocket.h>


#define ADDRESS "127.0.0.1"
#define SEND_PORT 7000
#define RECV_PORT 7001

#define OUTPUT_BUFFER_SIZE 1024

using namespace std;
static int id;

// User elects to write, read, receive, or compose and send a motive to MAX MSP

// Send the motive array to Max MSP
void send(int id, int* melody, int len) {
    
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, SEND_PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE );
    cout << "  --> ";
    p << osc::BeginBundleImmediate
    << osc::BeginMessage( "/compose" ) << len;
    for (int i = 0;i<len;i++) {
        p << melody[i];
    }
    p << osc::EndMessage << osc::EndBundle;
    
    transmitSocket.Send(p.Data(), p.Size());
}

void listen() {
    
    RatingListener listener;
    UdpListeningReceiveSocket s(IpEndpointName( IpEndpointName::ANY_ADDRESS, RECV_PORT ),
                                &listener );
    
    std::cout << "press ctrl-c to end\n";
    
    s.RunUntilSigInt();
    
    
}

// Compose a new motive and send it
void compose(MotiveMatrix* mm, MotiveVariation* mv) {
    // TODO path length
    int len = 8;
    
    vector<pair<int,int>> mp = mv->selectPath(len, mm);
    cout << " Path is ";
    
    for (auto it = begin (mp); it != end (mp); ++it) {
        cout << " (" << it->first << ", " << it->second << ") ";
    }
    
    int* melody = mv->selectMelody(len, mp, mm);
    
    send(id++, melody, len);
}


// Handle user commands
void control(MotiveMatrix* mm, MotiveVariation* mv) {
    // Expect a command of max size 7
    char* command = (char*) malloc(7*sizeof(char));
    // Loop user prompt until exit
    while (1) {
        printf("\nEnter command (x = exit / c = compose / l = listen) ");
        scanf ("%s", command);
        // Check for exit command
        if (strcmp(command, "x") == 0)
        break;
        
        if (strcmp(command, "c") == 0) {
            // Create a variation based on the last
            compose(mm, mv);
        } else if (strcmp(command, "l") == 0) {
            // Listen for a rating
            listen();
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

