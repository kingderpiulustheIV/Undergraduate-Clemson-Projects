# Sean Farrell 
# spfarre@clemson.edu
# 9/19/2024
# CPSC 3600 Professor Robb
# Introduction to Network Programming: TCP Calculator Server

# libraries needed for the client.
import socket
import sys

# class TCPClient to handle client-side operations for a calculator that runs on a tcp server.
class TCPClient:
        def __init__(self, host='127.0.0.1', port=65432):
                """
                Initialize the TCPClient instance with host and port. Also creates a socket that is unbound. 
                Server is not running initially.
        
                Parameters:
                -----------
                self : TCPClient tells the current instance of the class TCPClient to be initialized.
                host : str
                The hostname or IP address of the Client
                port : int
                The port number on which the Client will listen for incoming connections
                """

                self.host = host
                self.port = port
                self.client_socket = None
                self.is_running = False
        
        def start(self):
                """
                Start the client by creating a socket, binding it to the specified host and port specified in the initiation,
                and setting it to listen for incoming connections. The client is marked as running. displays a message indicating the client has started.
        
                Parameters:
                -----------
                self :  Tells the current instance of the class TCPClient to be started.
                """

                self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.client_socket.connect((self.host, self.port))
                self.is_running = True
                print(f'Connected to server at {self.host}:{self.port}')
        
        def run(self):
                """
                Run the client loop to accept incoming connections and process server requests  if the client is running.	
                these requests will require user input that will be processed by the server.
                The client will continue running until the shutdown method is called.
                
                Parameters:
                -----------
                self : TCPServer tells the current instance of the class TCPserver to be started.

                Raises:
                -------
                Quit command
                         If user enters the quit prompt the client breaks the loop and shutdown
                """

                # Receive welcome message from server.
                welcomeMessage = self.client_socket.recv(1024)

                # Print the welcome message.
                print(welcomeMessage.decode())     

                # Main loop for client interaction.
                while self.is_running == True:
                    
                    # Get the user's input.
                    user_input = input()
                    
                    # Send user's input to server.
                    self.client_socket.sendall(user_input.encode())
                    
                    # Check for quit command.
                    if user_input.upper() == 'QUIT':
                        # Shutdown the client breaks the loop.
                        self.shutdown()
                        break
                    
                    # Receive and print the server's response.
                    response = self.client_socket.recv(1024)
                    print(f'Server response: {response.decode()}')    

        def shutdown(self):
                """
                Shutdown the server  by closing the server socket and stopping the running loop. 

                Parameters:
                -----------
                self : TCPServer tells the current instance of the class TCPserver is being used to close.	
                """      

                self.client_socket.close()
                self.is_running = False
