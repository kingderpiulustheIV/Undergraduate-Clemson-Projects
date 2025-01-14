# Sean Farrell
# spfarr@clemson.edu
# 10-10-2024
# CPSC-3600 Robb
# Major Project: Building a File Transfer Application
# server.py

from socket import *
from struct import pack, unpack
import os, hashlib, sys, logging, math, struct


class FileTransferServer:
    def __init__(self, port, recv_length):
        """
        Initialize a new FileTransferServer instance.

        This constructor sets up logging for the server, creates a directory to store 
        received files, and stores the provided network parameters for use when listening
        for client connections.

        Args:
            port (int): The port number on which to listen for client connections.
            recv_length (int): The maximum size in bytes of data to request from a client
                socket in a single recv call.

       Note:
            The logging setup should not be modified, as it is configured to provide useful 
            debugging output to students working on this project.
            
            The recv_length parameter puts a limit on the maximum chunk size that can be 
            used during file transfers. Make sure your server will never request more than recv_length
            bytes from a client socket at a time.
        """

        # Do not modify this logger code. You can continue to use print() commands for your code.
        # The logger is in place to ensure that you receive proper output and debugging messages from the tester
        self.logger = logging.getLogger("SERVER")
        self.handler = logging.StreamHandler(sys.stdout)
        formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")
        self.handler.setFormatter(formatter)
        self.logger.addHandler(self.handler)
        self.logger.propagate = False
        self.logger.info("Initializing server...")
        # End of logger code

        # Create a directory to store received files
        if not os.path.exists("received_files"):
            os.makedirs("received_files")

        self.port = port
        self.recv_length = recv_length
        self.server_socket = None
        self.is_running = True


    def start(self):
        """
        Start the server listening for client connections.

        This method creates a TCP socket, binds it to the host and port specified during
        server initialization, and begins listening for incoming client connections.         
        
        IMPORTANT
        - The method should also configures the server socket with a timeout of 1 second.
        - Do NOT attempt to accept a connection or receive any messages from the client in 
            this function. That will be done in the run() function.

        Returns:
            bool: True if the server was started successfully, False otherwise.
        
        Exceptions:
            - OSError: Indicates a problem with socket creation, binding, or listening, which
            is logged for debugging purposes.

        Usage Example:
            server = FileTransferServer(port=12345)
            if server.start():
                server.run()
        """
        # TODO: Implement the functionality described in this function's docstring.
        try:
            # Create a TCP socket and bind it to the host and port specified during server initialization
            self.server_socket = socket(AF_INET, SOCK_STREAM)  
            self.server_socket.bind(("localhost", self.port))
            self.server_socket.listen()

            # Configure the server socket with a timeout of 1 second.
            self.server_socket.settimeout(1.0)
            
            # Set the server to be running.
            self.is_running = True
            return True
        
        # Handles any OS errors that occur during the server start process.
        except OSError as e:
            self.logger.error(f"Error starting server: {e}")
            self.is_running = False
            return False




    def write_file(self, filename, data):
        """
        Save the provided file data using the specified filename.
        
        This is a helper function that saves the provided bytes to a file in a directory
        named "received_files" in the current working directory.

        Args:
            filename (str): The name to use when saving the file.
            data (bytes): The raw bytes of the file to be saved.

        Note: 
            This helper function is provided for use when implementing the run method.
            It should not be modified by students.
        """
        # Opens the file in binary write mode. that file will be created and used to copy filedata from the client.
        with open(os.path.join("received_files", filename), "wb") as file:
            file.write(data)


    def run(self):
        """
        Run the server, accepting client connections and handling file transfer requests.

        This method implements the core functionality of the server. It runs in an infinite 
        loop, waiting for client connections. It only handles a single client connection at a time.
        
        Once a connection has been established, begin listening for file transfer request messages from the 
        currently connected client. When you receive a message, send an ACK message with a chunk_number of 0 
        (i.e. the first chunk needed) and then begin receiving the file. Once a file has been received write 
        it to disk using self.write_file() and  begin listening for another file transfer request from the same 
        client. If the client disconnects, attempt to accept a new connection from another client.
        
        Given the pattern where we 1) attempt to accept a connection from a new client, and then 2) attempt to 
        receive multiple files from a single client, you will need to use two nested while loops. Set each of these
        while loops to continue so long as self.is_running is True.

        Exceptions:
            - TimeoutError: Occurs when accepting a connection times out. This is an EXPECTED exception and 
                            does not indicate a problem has occurred. Simply continue code execution when 
                            handling this exception. 
            - OSError: Indicates an issue with handling the socket connection, logged for debugging.
            - Exception: Catches and logs any unforeseen errors to avoid crashing the server.

        Usage Example:
            server = FileTransferServer(5000)
            if server.start():
                server.run()

        Note:
            This method is blocking; it will continuously run until the server is explicitly
              shutdown with the shutdown() method. We add a timeout to the server socket in order
              to ensure that we don't get stuck blocking and never see that is_running has been 
              changed to false.
        """
        # TODO: Implement the functionality described in this function's docstring

        # Logs and prints a message indicating that the server has started.
        self.logger.info(f'Server started on local host:{self.port}')
        print(f'Server started on local host:{self.port}')

        # Run the server until it is stopped or crashes.
        while self.is_running:
            try:

                # Accept a connection from a client.
                connection, address = self.server_socket.accept()
                self.logger.info(f'Connection from {address}')
                print(f'Connection from {address}')
                while self.is_running:
                    try:
                        #receive the transfer request message from the client.
                        incoming_data = connection.recv(self.recv_length)    
                        if incoming_data:

                            #Unpacks the transfer request  data message from client.
                            filename, file_size, chunk_size, checksum_length = self.unpack_transfer_request_message(incoming_data)  
                            self.logger.info(f"Received file transfer request for {filename} ({file_size} bytes)")
                            
                            #Send an ACK message with a chunk number of 0.
                            ack_message = self.pack_ack_message(0)
                            connection.sendall(ack_message)
                            
                            #Receive the file data from the client.
                            file_data = self.receive_file(connection, file_size, chunk_size, checksum_length)
                            if file_data:
                                self.write_file(filename.decode('utf-8'), file_data)
                                self.logger.info(f"File {filename} received and saved")
                            else:
                            # If the file data is not received, log an error message.
                                self.logger.error(f"Error receiving file {filename}")

                        # If the client disconnects, log an error message and break out of the loop
                        else:
                            self.logger.error(f"Client disconnected") 
                            break

                    # Handles any exceptions that occur during the file transfer process that cause timeouts.
                    except  TimeoutError:
                        continue

                    # Handles any OS errors that occur during the file transfer process.
                    except OSError as e:
                        self.logger.error(f"OS Error running server: {e}")
                        break

                    # Handles any unexpected errors that occur during the file transfer process.
                    except Exception as e:
                        self.logger.error(f"Unexpected error: {e}")
                        break

            # Handles any exceptions that occur during the connection process that cause timeouts.                         
            except  TimeoutError:
                continue

            # Handles any OS errors that occur during the connection process.
            except OSError as e:
                self.logger.error(f"OS Error running server: {e}")
                break

            # Handles any unexpected errors that occur during the connection process.
            except Exception as e:
                self.logger.error(f"Unexpected error: {e}")
                break
            


    def receive_file(self, conn, file_size, chunk_size, checksum_length):
        """
        Receive a file from a client connection, chunk by chunk.

        This method implements the server-side logic for receiving a file from a connected
        client. The client's socket is passed in as a parameter so we can talk to the client. On starting to 
        receive the file, repeatedly call self.receive_chunk() to receive each chunk from the client and then 
        send an ACK message requesting the next chunk. Return the received filedata once it has all been received.
        Be careful to never request more data than is actually remaining to be transferred. So long as the amount 
        Be careful to never request more data than is actually remaining to be transfered. So long as the amount 
        of remaining data is larger than the chunk size, request an amount of data equal to the chunk size. 
        However, the final chunk will almost certainly be smaller than the chunk size. In this case be careful 
        to request exactly how much data still needs to be transferred.
        
        You will need to handle if a client disconnects while attempting to receive a chunk. Since you're not 
        actually reading from a socket in this function you will have to detect this in self.receive_chunk() and 
        then use whatever values are returned by that function to determine the client has disconnected and how 
        to proceed from there (i.e. pass that information back up to run() where this function was called).

        Args:
            conn (socket): The socket representing the client connection.
            file_size (int): The total size of the file being received.
            chunk_size (int): The size of each chunk of the file to be received.
            checksum_length (int): The length in bytes of the checksum hash used.
        
        Returns:
            bytes: The complete file data received from the client, or None if the transfer
                fails or the client disconnects.

        Usage Example:
            file = self.receive_file(conn, file_size, chunk_size, checksum_length)
        """
        # TODO: Implement the functionality described in this function's docstring

        # Initialize the file data buffer, remaining data size, and chunk number variables.
        file_data = bytearray()
        remaining_data_size = file_size
        chunk_number = 0
        
        # Receive the file data from the client chunk by chunk.
        while remaining_data_size > 0:
            current_chunk_size = min(chunk_size, remaining_data_size)
            next_chunk_number, chunk_data = self.receive_chunk(conn, current_chunk_size, checksum_length)
            
            # If the client disconnects, log an error message and return None.
            if next_chunk_number == -1:
                self.logger.error("Client disconnected while receiving file")
                return None
            
            # If the checksums do not match, log an error message and request the chunk again.
            if  next_chunk_number != chunk_number:
                ack_message = self.pack_ack_message(chunk_number)
                conn.sendall(ack_message)
                self.logger.error(f"checksum mismatch, resending requested chunk {chunk_number}")
                continue

            # If the checksums match, append the chunk data to the file data buffer and update the remaining data size.
            file_data.extend(chunk_data)
            remaining_data_size -= len(chunk_data)
            chunk_number += 1
            ack_message = self.pack_ack_message(chunk_number)
            conn.sendall(ack_message)

        # Return the complete file data received from the client.    
        return bytes(file_data)



    def receive_chunk(self, conn, chunk_size, checksum_length):
        """
        Receive a single chunk of a file from a connected client.

        Attempts to receive a chunk of the file. Remember the format used for sending a chunk, which includes:
        * the chunk number (int)
        * the content of the chunk
        Make sure you correctly receive all of this information and don't accidentally treat the chunk number as 
        Make sure you correctly receive all of this information and don't accidently treat the chunk number as 
        part of the chunk data, or vice versa.

        You will not be able to read all of the chunk data at once, due to the chunk size being larger than 
        self.recv_length, the maximum amount of data you are allowed to request from a socket in this program. 
        As such, you will need to recv data and buffer it until you've received the entire chunk. Make sure you
        do not attempt to read more data than is actually remaining in the chunk; the final piece of the chunk 
        may be smaller than self.recv_length, in which case you must detect this and request the appropriate 
        smaller value.

        Once you have received the chunk number and the content of the chunk, make sure you also receive the 
        checksum. Compare the received checksum against a checksum you generate based on the chunk number and
        chunk data you have received. If the checksums match, request the next chunk. If they do not match, 
        request that this chunk be sent again. You can either send that ACK inside of this function, or inside of
        receive_file() upon this function returning.

        Make sure that you don't return bad data in the event that the checksums don't match. In this case make 
        sure you don't use the chunk data you've received as it isn't trustworthy.

        If you detect that the client has disconnected which receiving a chunk, make sure you inform the 
        receive_file() function of this when you return (how you do so is up to you).

        Args:
            conn (socket): The socket representing the client connection.
            chunk_size (int): The size of the chunk to receive.
            checksum_length (int): The length in bytes of the checksum hash used.

        Returns:
            tuple: A tuple (chunk_number, chunk_data), where:
                chunk_number (int): The sequence number of the received chunk, incremented by 1
                    if the chunk was received successfully, or the received sequence number if
                    the checksum does not match. If the client disconnects, this is -1.
                chunk_data (bytes): The raw bytes of the received chunk data, or None if the 
                    chunk was not received successfully or the client disconnected.

        Usage Example:  # Correct spelling
            next_chunk_number, data = self.receive_chunk(conn, amount_of_data_to_recv, checksum_length)
        """
        # TODO: Implement the functionality described in this function's docstring
        try:

        # Receive the chunk number (4 bytes for an unsigned int)
            chunk_number_data = conn.recv(4)

            # If the client disconnects, return -1 and None.
            if not chunk_number_data:
                return -1, None
            
            # Unpack the chunk numbers data.
            chunk_number = unpack('!I', chunk_number_data)[0]

            # Buffer to store the received chunk data.
            chunk_data = bytearray()

            # Calculate the remaining data to receive.
            remaining_data = chunk_size

            # Receive the chunk data.
            while remaining_data > 0:
                data = conn.recv(min(self.recv_length, remaining_data))
                if not data:
                    return -1, None
                chunk_data.extend(data)
                remaining_data -= len(data)

            # Receives the checksum.
            checksum_data = conn.recv(checksum_length)

            # If the client disconnects from retrieving checksum, return -1 and None.
            if not checksum_data:
                return -1, None

        # Compute the checksum of the received chunk data to verify its integrity.
            packed_data = pack(f"!I{chunk_size}s", chunk_number, chunk_data)
            computed_checksum = self.compute_hash(packed_data, checksum_length)

        # Verify the checksum and return the chunk number and chunk data if the checksums match.
            if checksum_data == computed_checksum:
                return chunk_number, bytes(chunk_data)
            else:
                return chunk_number, None
            
        # Handles any exceptions that occur during the chunk receiving process.
        except Exception as e:
            print(f"Error receiving chunk: {e}")
            return -1, None



            
        

    def unpack_transfer_request_message(self, bytes):
        """
        Unpack a client transfer request message into its component fields.
        
        A transfer request message consists of the following fields:
        - Filename length (unsigned short)
        - Filename (string of variable length) 
        - File size in bytes (unsigned int)
        - Chunk size in bytes (unsigned short) 
        - Checksum length in bytes (unsigned char)

        Since you don't know how long the filename is you'll want to first unpack the filename_length
        field and then use that to unpack the rest of the message.

        Args:
            bytes (bytes): The packed binary transfer request message from the client.
        
        Returns:
            tuple: A tuple (filename, file_size, chunk_size, checksum_length), where:
                - filename (str): The name of the file being transferred.
                - file_size (int): The total size of the file in bytes.
                - chunk_size (int): The size of each chunk of the file to be sent.
                - checksum_length (int): The length in bytes of the checksum hash used.
        Usage Example:
        Useage Example:
            filename, file_size, chunk_size, checksum_length = self.unpack_transfer_request_message(data)
        # """
        # TODO: Implement the functionality described in this function's docstring
        
        # If the bytes are None, raise a ValueError.
        if bytes is None:
            raise ValueError("Received None instead of bytes for unpacking transfer request message")

        # unpack the filename length.
        filename_length = unpack('!H', bytes[:2])[0]
        filename, file_size, chunk_size, checksum_length = unpack(f'!{filename_length}sIHB', bytes[2:])  
        
        # Return unpacked variables for filename, file size, chunk size, and checksum length.
        return  filename,file_size, chunk_size, checksum_length

    

    def pack_ack_message(self, next_chunk_number):
        """
        Generate the packed binary data for a server acknowledgement message.

        A server acknowledgement message consists of the following fields:
        - ACK type (unsigned char), where 0 indicates a normal ACK  
        - Next expected chunk number (unsigned int)

        Args:
            next_chunk_number (int): The sequence number of the next expected chunk.
            
        Returns:
            bytes: The packed binary representation of the acknowledgement message.

        Useage Example:
            ack_msg = self.pack_ack_message(next_chunk_number)
        """
        # TODO: Implement the functionality described in this function's docstring
        
        # Set the ack type to 0.
        act_type = 0

        # Packs the ack type and next chunk number into a binary message.
        return  pack('!BI', act_type, next_chunk_number)
         


    def compute_hash(self, data, hash_length):
        """
        Generates a hash of the provided data using the SHAKE-128 algorithm.

        In this assignment, we'll use the hashlib library to compute a hash of the data
        being shared between the client and the server. A hash is a fixed-length string
        generated based on arbitrary input data. The same data will result in the same
        hash, and any change to the data will result in a different hash.  We're using this 
        very simplistically to introduce the idea of hashing and integrity checking, which 
        we'll be exploring in more detail later in the semester.

        1. Import hashlib and call hashlib.shake_128() to create a new SHAKE-128 hash object.
        2. Use the update() method to add the data to the hash object.
        3. Use the digest() method to retrieve the hash value and return it.

        The shake_128 algorithm is convenient for us since we can specify the length of the
        hash it produces. This allows us to generate a short hash for use in our tests.
        
        Parameters:
            - data (bytes): Data for which the hash will be computed.
            - hash_length (int): Specifies the desired length of the hash output in bytes.

        Returns:
            - bytes: The computed hash of the data, which can be used for integrity checks.

        Note:
            - This method is used within the file transfer process to ensure the integrity
            of received data by comparing the computed hash with one provided by the client.
        """
        # TODO: Implement the functionality described in this function's docstring
        
        # Create a new SHAKE-128 hash object and add the data to it.
        hash = hashlib.shake_128()
        
        # Update the hash object with the provided data.
        hash.update(data)

        # Return the hash value of the data.
        return hash.digest(hash_length)


    def shutdown(self):
        """
        Shuts down the server by stopping its operation and closing the socket.

        This method safely terminates the server's operation. It stops the server from
        running, removes the logger handler, and closes the server socket if it is open.

        The method logs the shutdown process, providing visibility into the client's
        state transitions. It's designed to be safely callable even if the socket is
        already closed or not initialized, preventing any unexpected exceptions during
        the shutdown process.

        Usage Example:
            server.shutdown()

        Note:
            - Call this method to cleanly shut down the server after use or in case of an error.            
            - Do NOT set server_socket to None in this method. The auto-grader will examine
                server_socket to ensure it is closed properly.
        """
        self.logger.info('Server is shutting down...')

        # TODO: Implement the functionality described in this function's docstring
        
        # Stops the server from running.
        self.is_running = False

        # Closes the server socket if it is open.
        self.server_socket.close()

        # Logs the shutdown process.
        self.logger.info("Server is shutdown")
        self.logger.removeHandler(self.handler)

if __name__ == "__main__":
    server = FileTransferServer(5000, 1024)
    if server.start():
        server.run()
