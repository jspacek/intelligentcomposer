/*
 Example of two different ways to process received OSC messages using oscpack.
 Receives the messages from the SimpleSend.cpp example.
 
 Compile: g++ -Wall -Wextra -c -o MySimpleReceive.o MySimpleReceive.cpp
 
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
#include <oscpack/osc/OscOutboundPacketStream.h>

#define ADDRESS "127.0.0.1"
#define SEND_PORT 7000
#define RECV_PORT 7001
#define OUTPUT_BUFFER_SIZE 1024

class RatingListener : public osc::OscPacketListener {
    
    public:
    
    int len;
    int rating;
    int* intervals;
    int finality;
    
    protected:
    
    virtual void ProcessMessage( const osc::ReceivedMessage& m,
                                const IpEndpointName& remoteEndpoint )
    {
        (void) remoteEndpoint; // suppress unused parameter warning
        MotiveMatrix* mm = new MotiveMatrix();
        MotiveVariation* mv = new MotiveVariation();
        try {
            // Check for the type of message
            if ( std::strcmp( m.AddressPattern(), "/rate" ) == 0 ){
                // Receive a rating
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                osc::int32 len;
                osc::int32 finality;
                osc::int32 rating;
                osc::int32 a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18;
                
                args >> len >> finality >> rating >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8 >> a9 >> a10 >> a11 >> a12 >> a13 >> a14 >> a15 >> a16 >> a17 >> a18 >> osc::EndMessage;
                
                intervals = new int[18];
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
                
                std::cout << "received '/rate' message with length " << len << " finality = " << finality << " rating = " << rating
                << " and a1 = " << a1 << " a18 = " << a18 << "\n";
                
                write(len, intervals, finality, rating);
                
                
            } else if( std::strcmp( m.AddressPattern(), "/read" ) == 0 ){
                
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                
                osc::int32 a1;
                osc::int32 a2;
                args >> a1 >> a2 >> osc::EndMessage;
                std::cout << "received '/read' message with arguments: "
                << " finality= " << a1 << " rating= " << a2 << "\n";
                
                read(a1, a2);
                
                cout << "\n SENDING intervals length = " << len;
                
                send(len, intervals);
                
            } else if( std::strcmp( m.AddressPattern(), "/compose" ) == 0 ){
                
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                
                osc::int32 len;
                args >> len >> osc::EndMessage;
                
                std::cout << "received '/compose' message with argument: "
                << len << "\n";
                
                compose(len);
                
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
        << osc::BeginMessage( "/compose" ) << len;
        
        for (int i = 0;i<len;i++) {
            p << melody[i];
        }
        p << osc::EndMessage << osc::EndBundle;
        
        transmitSocket.Send(p.Data(), p.Size());
    }
    
    // Compose a new motive and send it
    void compose(int len) {

        MotiveMatrix* mm = new MotiveMatrix();
        MotiveVariation* mv = new MotiveVariation();
        
        vector<pair<int,int>> mp = mv->selectPath(len, mm);
        cout << " Path is ";
        
        for (auto it = begin (mp); it != end (mp); ++it) {
            cout << " (" << it->first << ", " << it->second << ") ";
        }
        
        int* melody = mv->selectMelody(len, mp, mm);
        
        send(len, melody);
        
    }
    
    // SERIALIZE: Write the compressed array as a binary little endian record
    void write(int len, int* cm, int finality, int rating) {
        if (rating > 0) {
            // Open the knowledge base to append to the file (never overwrite!)
            fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app);
            
            if (file.is_open())
            {
                file.write((char*) &len, sizeof(int));
                file.write((char*) &finality, sizeof(int));
                file.write((char*) &rating, sizeof(int));
                
                cout << " Writing rated melody...";
                
                // Ignore default arguments sent, only write valid intervals
                for (int i = 0;i<len;i++) {
                    cout << "WRITE " << cm[i];
                    file.write((char*) &cm[i], sizeof(int));
                }
                
                file.close();
            } else {
                fprintf(stderr, "\nWrite: Error opening knowledgebase.bin\n\n");
                exit (1);
            }
        }
    }
    
    
    // DESERIALIZE: Read the compressed motive array from the binary file
    
    // TODO ONLINE SEARCH DISABLED
    
    // Retrieve a motive based on a finality value
    void read(int finality, int rating) {
        
        // Open the knowledge base to append to the file, and to read binary data
        // Construct MM object
        fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app | ios::beg);
        int f = 0;
        int r = 0;
        int l = 0;
        
        if (file.is_open())
        {
            
            // Find size of file
            int fileSize = file.tellg();
            // Store current position
            int pos = 0;
            
            // Navigate to the first position in the file
            // TODO RANDOM SEARCH START POSITION
            file.seekg (0, file.beg);
            
            while (pos < fileSize) {
                file.read((char *) &l, sizeof(int));
                file.read((char *) &f, sizeof(int));
                file.read((char *) &r, sizeof(int));
                intervals = new int[l];

                cout << "\n**************  " << " Len is  " << l << " Finality is  " << f << " Rating is  " << r << "\n";
                
                int values[l];
                len = l;
                
                file.read((char*)values, l*sizeof(int));
                
                if (f == finality && r == rating){
                    // If attributes match, read the melody data in as an array of size 18

                    for (int i=0;i<l;i++){
                        cout << "  Element [" << i << "] = " << values[i];
                        intervals[i] = values[i];
                    }
                    
                    cout << "FOUND MATCH ***********************************";
                    pos = fileSize + 1;
                }
                // Skip ahead by len, finality, and rating fields, + the length of the array fields
                pos = pos + sizeof(int)*(l + 3);

            }
        } else {
            fprintf(stderr, "\nRead: Error opening knowledgebase.bin\n\n");
            exit (1);
        }
        file.close();
    }
};

