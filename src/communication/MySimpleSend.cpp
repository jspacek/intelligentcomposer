/* 
    Simple example of sending an OSC message using oscpack.
 
    Compile with g++ -Wall -Wextra -c -o MySimpleSend.o MySimpleSend.cpp
 
    Link:
     g++ -o bin/MySimpleSend oscpack_1_1_0/osc/OscTypes.o MySimpleSend.o oscpack_1_1_0/osc/OscOutboundPacketStream.o oscpack_1_1_0/ip/posix/UdpSocket.o oscpack_1_1_0/ip/IpEndpointName.o oscpack_1_1_0/ip/posix/NetworkingUtils.o

*/

#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/ip/UdpSocket.h>


#define ADDRESS "127.0.0.1"
#define PORT 7000

#define OUTPUT_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings

    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    // Send two messages - one is a direction matrix with note values
    // the second one is a "stop" message with value true
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/dirMatrixFive" )
            << 13 << 14 << 15 << 16 << 17 << osc::EndMessage
        << osc::BeginMessage( "/stop" )
            << true << osc::EndMessage
        << osc::EndBundle;
    
    transmitSocket.Send( p.Data(), p.Size() );
}

