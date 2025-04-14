/* simple UDP receiver that acknowledges every datagram */

#include <cstdlib>
#include <iostream>

#include "socket.hh"
#include "contest_message.hh"

using namespace std;

int main( int argc, char *argv[] )
{
   /* check the command-line arguments */
  if ( argc < 1 ) { /* for sticklers */
    abort();
  }

  if ( argc != 2 ) {
    cerr << "Usage: " << argv[ 0 ] << " PORT" << endl;
    return EXIT_FAILURE;
  }

  /* create UDP socket for incoming datagrams */
  UDPSocket socket;

  /* turn on timestamps on receipt */
  socket.set_timestamps();

  /* "bind" the socket to the user-specified local port number */
  socket.bind( Address( "::0", argv[ 1 ] ) );

  cerr << "Listening on " << socket.local_address().to_string() << endl;

  uint64_t sequence_number = 0;

  /* counter for the number of received datagrams for Delayed ACK */
  int seq_counter = 0;

  // last received number
  uint64_t last_ack_num = 0;

  /* Loop and acknowledge every incoming datagram back to its source */
  while ( true ) {
    const UDPSocket::received_datagram recd = socket.recv();
    ContestMessage message = recd.payload;

    /* add the counter */
    seq_counter++;

    cout << "sequence_number : " << message.header.sequence_number
    << " last_ack_num : " << last_ack_num << endl;

    /* assemble the acknowledgment */
    if (message.header.sequence_number == last_ack_num + 1 || last_ack_num == 0){
      last_ack_num = message.header.sequence_number;
      message.transform_into_ack( sequence_number++, recd.timestamp );
    }else {
      message.header.sequence_number = last_ack_num;
      message.transform_into_ack( sequence_number++, recd.timestamp );
      // send the ack immediately
      if(seq_counter != 2){
        socket.sendto( recd.source_address, message.to_string() );
      }
    }

    /* timestamp the ack just before sending */
    message.set_send_timestamp();

    if(seq_counter == 2){
      /* send the ack */
      socket.sendto( recd.source_address, message.to_string() );
      /* reset the counter */
      seq_counter = 0;
    }

  }

  return EXIT_SUCCESS;
}
