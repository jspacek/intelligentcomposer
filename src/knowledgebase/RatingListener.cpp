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

class RatingListener : public osc::OscPacketListener {
    public:
    
    int ratingID;
    int rating;
    int* intervals;
    
    protected:
    
    virtual void ProcessMessage( const osc::ReceivedMessage& m,
                                const IpEndpointName& remoteEndpoint )
    {
        (void) remoteEndpoint; // suppress unused parameter warning
        
        try {
            // Check for the type of message
            if ( std::strcmp( m.AddressPattern(), "/rate" ) == 0 ){
                // Receive a rating
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                osc::int32 id;
                osc::int32 r;
                osc::int32 a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18;
                
                args >> id >> r >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8 >> a9 >> a10 >> a11 >> a12 >> a13 >> a14 >> a15 >> a16 >> a17 >> a18 >> osc::EndMessage;
                
                ratingID = id;
                rating = r;
                
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
                
                std::cout << "received '/rate' message with id " << ratingID << " rating = " << rating
                << " and a1 = " << a1 << " a18 = " << a18 << "\n";
                
                write(ratingID, intervals, 1, 18);
                
                // now read it back for testing
                
                read(1);
                
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
    
    // SERIALIZE: Write the compressed array as a binary little endian record
    void write(int id, int* cm, int rating, int len) {
        if (rating > 0) {
            // Open the knowledge base to append to the file (never overwrite!)
            fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app);
            
            if (file.is_open())
            {
                file.write((char*) &rating, sizeof(int));
                file.write((char*) &id, sizeof(int));
                for (int i = 0;i<len;i++) {
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
    
    // TODO: Scan through different positions in fixed format records (use variable pos)
    int* read(int finality) {
        
        // Open the knowledge base to append to the file, and to read binary data
        // Construct MM object
        fstream file ("bin/knowledgebase.bin", ios::out | ios::in | ios::binary | ios::app | ios::beg);
        int* cm;
        
        if (file.is_open())
        {
            // Navigate to the first position in the file TODO use pos or search
            file.seekg (0, file.beg);
            
            int rating = 0;
            file.read((char *) &rating, sizeof(18));
            cm = new int[18];
            cout << " Rating is  " << rating << "\n";
            
            // Read the data in as an array of size N
            int values[18];
            
            file.read((char*)values, 18*sizeof(int));
            for (int i=0;i<18;i++){
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
    
};

