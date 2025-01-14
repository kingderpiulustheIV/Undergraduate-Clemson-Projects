from socket import *

# Define the server and port we'll attempt to connect to
SERVER_HOST = "3.86.222.143"
SERVER_PORT = 3602
# Define the size of the buffer we'll request every time we read from the socket
BUFFER_SIZE = 16

# Define the number of echo requests we'll make before quitting
NUM_ECHOS = 3
current_echo_count = 0

# Create a TCP socket. We know it's a TCP socket because we use SOCK_STREAM
tcpClientSocket = socket(AF_INET, SOCK_STREAM)
# Connect the socket to a server listening at the specified network address. Note that the connect function 
#accepts a single parameter (a tuple containing the network address), not two separate parameters.
tcpClientSocket.connect((SERVER_HOST, SERVER_PORT))

# Loop until we've received the desired number of echos
while current_echo_count < NUM_ECHOS:
    # Read in an input statement from the user
    message = input('Input: ')
    # Send the message the user wrote into the socket. We need to encode the string before sending it.
    tcpClientSocket.send(message.encode())
    # Wait to receive a response from the server, up to BUFFER_SIZE in length
    response =  tcpClientSocket.recv(BUFFER_SIZE)
    # Print that response to the console
    print('Received "', response.decode(), '" from the server')
    # Increment our counter of the echos we've received
    current_echo_count += 1
# Close the socket once we're done with it
tcpClientSocket.close()