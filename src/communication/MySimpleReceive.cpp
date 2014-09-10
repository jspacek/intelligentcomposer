/* 
    Example of two different ways to process received OSC messages using oscpack.
    Receives the messages from the SimpleSend.cpp example.
 
 
 Link with: 
 
 g++ -o bin/MySimpleReceive oscpack_1_1_0/osc/OscTypes.o MySimpleReceive.o oscpack_1_1_0/osc/OscReceivedElements.o oscpack_1_1_0/osc/OscPrintReceivedElements.o oscpack_1_1_0/ip/posix/UdpSocket.o oscpack_1_1_0/ip/IpEndpointName.o oscpack_1_1_0/ip/posix/NetworkingUtils.o
 
*/

#include <iostream>
#include <cstring>

#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif

#include <oscpack/osc/OscReceivedElements.h>
#include <oscpack/osc/OscPacketListener.h>
#include <oscpack/ip/UdpSocket.h>

#define PORT 7000

class ExamplePacketListener : public osc::OscPacketListener {
protected:

    virtual void ProcessMessage( const osc::ReceivedMessage& m, 
				const IpEndpointName& remoteEndpoint )
    {
        (void) remoteEndpoint; // suppress unused parameter warning

        try{
            // Check for the type of message
            if( std::strcmp( m.AddressPattern(), "/dirMatrix4" ) == 0 ){
                // We received a direction Matrix with width = 4
                // TODO adapt this to accept any sized argument
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                osc::int32 a1;
                osc::int32 a2;
                osc::int32 a3;
                osc::int32 a4;
                args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;
                
                std::cout << "received '/dirMatrix4' message with arguments: "
                    << a1 << " " << a2 << " " << a3 << " " << a4 << "\n";
                
            }else if( std::strcmp( m.AddressPattern(), "/stop" ) == 0 ){
                // example #2 -- argument iterator interface, supports
                // reflection for overloaded messages (eg you can call 
                // (*arg)->IsBool() to check if a bool was passed etc).
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bool a1 = (arg++)->AsBool();
               
                if( arg != m.ArgumentsEnd() )
                    throw osc::ExcessArgumentException();
                
                std::cout << "received '/stop' message with arguments: "
                    << a1 << "\n";
            }
        }catch( osc::Exception& e ){
            // any parsing errors such as unexpected argument types, or 
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: "
                << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }
};

int main(int argc, char* argv[])
{
    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings

    ExamplePacketListener listener;
    UdpListeningReceiveSocket s(
            IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
            &listener );

    std::cout << "press ctrl-c to end\n";

    s.RunUntilSigInt();

    return 0;
}

