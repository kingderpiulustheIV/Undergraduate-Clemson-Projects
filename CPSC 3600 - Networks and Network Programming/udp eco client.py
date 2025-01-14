from socket import *

# Define the server and port we'll attempt to connect to
SERVER_HOST = '3.86.222.143'
SERVER_PORT = 3601
# Define the size of the buffer we'll request every time we read from the socket
BUFFER_SIZE = 16

# Define the number of echo requests we'll make before quitting
NUM_ECHOS = 3
current_echo_count = 0

# Create a UDP socket. We know it's a UDP socket because we use SOCK_DGRAM
udpClientSocket = socket(AF_INET, SOCK_DGRAM)

# Loop until we've received the desired number of echos
while current_echo_count < NUM_ECHOS:
    # Read in an input statement from the user
    message = input('Input: ')
    # Send the message the user wrote into the socket
    udpClientSocket.sendto(message.encode(), (SERVER_HOST, SERVER_PORT))
    # Wait to receive a response from the server, up to BUFFER_SIZE in length
    response, serverAddr =  udpClientSocket.recvfrom(BUFFER_SIZE)
    # Print that response to the console
    print('Received "', response.decode(), '" from the server')
    # Increment our counter of the echos we've received
    current_echo_count += 1
# Close the socket once we're done with it
udpClientSocket.close()