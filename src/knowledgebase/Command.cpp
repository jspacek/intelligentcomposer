//
//  Control matrix functionality through command line codes, mostly for testing and initial setup.
//
// (1) Create object: g++ -std=c++11 -Wall -c -o command.o Command.cpp
// (2) Link: g++ -o bin/command oscpack_1_1_0/osc/OscTypes.o command.o oscpack_1_1_0/osc/OscOutboundPacketStream.o oscpack_1_1_0/ip/posix/UdpSocket.o
//  oscpack_1_1_0/ip/IpEndpointName.o oscpack_1_1_0/ip/posix/NetworkingUtils.o oscpack_1_1_0/osc/OscReceivedElements.o
//
//

#include <string.h>
#include <iostream>
#include <fstream>
#include "Matrix.cpp"
#include "Path.cpp"
#include "Listener.cpp"


#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/osc/OscReceivedElements.h>
#include <oscpack/ip/UdpSocket.h>


#define ADDRESS "127.0.0.1"
#define SEND_PORT 7000
#define RECV_PORT 7001
#define OUTPUT_BUFFER_SIZE 1024
#define DEBUG 1


using namespace std;

class Command {
    
public:
    
    Matrix* matrix;
    Path* path;
    IO* io;
    
    void listen() {
        
        Listener listener;
        UdpListeningReceiveSocket s(IpEndpointName( IpEndpointName::ANY_ADDRESS, RECV_PORT ),
                                    &listener );
        
        std::cout << "press ctrl-c to end\n";
        
        s.RunUntilSigInt();
    }
    
    // Handle user commands
    void command() {
        // Expect a command of max size 7
        char* command = (char*) malloc(7*sizeof(char));
        // Loop user prompt until exit
        while (1) {
            printf("\nEnter command (x = exit / c = compose / r = read / w = write / l = listen) ");
            scanf ("%s", command);
            // Check for exit command
            if (strcmp(command, "x") == 0)
                break;
            
            if (strcmp(command, "c") == 0) {
                // Create a variation of intervals
                path->compose(8, matrix);
            } else if (strcmp(command, "r") == 0) {
                // Retrieve a variation based on parameters
                //io->read(finality, interest, span, max, min, direction);
                io->read(8, 8, 8, 99, 99, 99, 99);
            } else if (strcmp(command, "w") == 0) {
                // Store a variation based on parameters
                //io->write(len, intervals, finality, interest);
                int intervals [8] = {2,3,-1,-1,0, 1, 1, -1};
                io->write(8, intervals, 8, 8);
            } else if (strcmp(command, "l") == 0) {
                // Listen for a rating
                listen();
            } else {
                cout << "Command not recognized";
            }
        }
        delete command;
    }
};

// Read, write, and send a test compressed motive
int main () {
    Command* c = new Command();
    c->matrix = new Matrix();
    c->path = new Path();
    c->io = new IO();
    
    // Generate options to the user
    c->command();
    
    delete c;
    
    return 0;
}

