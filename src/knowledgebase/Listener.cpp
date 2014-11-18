/*
 
 Listen for commands from Max MSP train and play patch. Extract/Write data to/from the knowledgebase.bin
 data file, format and send it using osc protocol.
  
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
#include <oscpack/osc/OscOutboundPacketStream.h>
#include "IO.cpp"


#define ADDRESS "127.0.0.1"
#define SEND_PORT 7000
#define RECV_PORT 7001
#define OUTPUT_BUFFER_SIZE 1024
#define DEBUG 1

class Listener : public osc::OscPacketListener {
    
public:
    
    Matrix* matrix;
    Path* path;
    IO* io;
    
//protected:
    
    virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint) {
        (void) remoteEndpoint; // suppress unused parameter warning
        
        try {
            matrix = new Matrix();
            path = new Path();
            io = new IO();
            
            // Check for the type of message passed
            if ( std::strcmp( m.AddressPattern(), "/rate" ) == 0 ){
                // Receive rating from MaxMSP
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                // User defined variables
                osc::int32 len;
                osc::int32 finality;
                osc::int32 interest;
                // Melodic intervals to rate
                osc::int32 a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18;
                
                args >> len >> finality >> interest >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8 >> a9
                >> a10 >> a11 >> a12 >> a13 >> a14 >> a15 >> a16 >> a17 >> a18 >> osc::EndMessage;
                
                // Max MSP can send a maximum of 18 interval values
                int* intervals = new int[18];
                intervals[0] = a1;
                intervals[1] = a2;
                intervals[2] = a3;
                intervals[3] = a4;
                intervals[4] = a5;
                intervals[5] = a6;
                intervals[6] = a7;
                intervals[7] = a8;
                intervals[8] = a9;
                intervals[9] = a10;
                intervals[10] = a11;
                intervals[11] = a12;
                intervals[12] = a13;
                intervals[13] = a14;
                intervals[14] = a15;
                intervals[15] = a16;
                intervals[16] = a17;
                intervals[17] = a18;
                
                if (DEBUG)
                    std::cout << "Received '/rate' message with length " << len << " finality = " << finality << " interest = " << interest
                    << " and a1 = " << a1 << " a18 = " << a18 << "\n";
                
                // Write the details of this melody into the file
                io->write(len, intervals, finality, interest);
                
                cout << " \n wrote to file";
                
                
            } else if( std::strcmp( m.AddressPattern(), "/read" ) == 0 ){
                
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                
                // Request parameters from Max MSP
                osc::int32 finality;
                osc::int32 interest;
                osc::int32 span;
                osc::int32 max;
                osc::int32 min;
                osc::int32 direction;
                
                // Parse arguments from the message
                args >> finality >> interest >> span >> max >> min >> direction >> osc::EndMessage;
                
                if (DEBUG)
                    std::cout << "Received '/read' message with arguments: "
                    << " finality= " << finality << " interest= " << interest << " span= " << span
                    << " max= " << max << " min= " << min << " direction= " << direction << "\n";
                
                // Retrieve a melody based on the parameters
                io->read(finality, interest, span, max, min, direction);
                
                if (DEBUG)
                    cout << "\n SENDING intervals of length = " << io->len;
                
                // Send the melody with its length to Max MSP for playback
                send(io->len, io->intervals);
                
            } else if( std::strcmp( m.AddressPattern(), "/compose" ) == 0 ){
                
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                
                osc::int32 len;
                args >> len >> osc::EndMessage;
                
                std::cout << "received '/compose' message with argument: "
                << len << "\n";
                
                path->compose(len, matrix);
                send(path->len, path->intervals);
                
                
            } else if( std::strcmp( m.AddressPattern(), "/stop" ) == 0 ){
                
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bool a1 = (arg++)->AsBool();
                
                if( arg != m.ArgumentsEnd() )
                    throw osc::ExcessArgumentException();
                
                std::cout << "received '/stop' message with arguments: "
                << a1 << "\n";
            }
        } catch( osc::Exception& e ){
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: "
            << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }
    
    // Send the motive array to Max MSP
    void send(int len, int* melody) {
        
        UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, SEND_PORT ) );
        
        char buffer[OUTPUT_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE );
        cout << "  --> ";
        
        p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/send" ) << len;
        
        for (int i = 0;i<len;i++) {
            p << melody[i];
        }
        p << osc::EndMessage << osc::EndBundle;
        
        transmitSocket.Send(p.Data(), p.Size());
    }
  /*  int main () {
        matrix = new Matrix();
        path = new Path();
        io = new IO();
        
        return 0;
    }*/
};



