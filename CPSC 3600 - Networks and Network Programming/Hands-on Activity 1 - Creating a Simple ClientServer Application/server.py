# Sean Farrell 
# spfarre@clemson.edu
# 9/19/2024
# CPSC 3600 Professor Robb
# Introduction to Network Programming: TCP Calculator Server

# libraries needed for the server.
import socket
import sys 

# TCPClient class to handle client-side operations for a calculator server.
class TCPServer:
    def __init__(self, host='127.0.0.1', port=65432):
        """
        Initialize the TCPServer instance with host and port. Also creates a socket that is unbound. 
        Server is not running initially.
        
        Parameters:
        -----------
        self : TCPServer tells the current instance of the class TCPserver to be initialized.
        host : str
            The hostname or IP address of the server
        port : int
            The port number on which the server will listen for incoming connections
         """
        
        self.is_running = False
        self.host = host
        self.port = port
        self.server_socket = None

    def start(self):
        """
        Start the server by creating a socket, binding it to the specified host and port specified in the initiation,
        and setting it to listen for incoming connections. The server is marked as running. displays a message indicating the server has started.
        
        Parameters:
        -----------
        self :  Tells the current instance of the class TCPserver to be started.

        """

        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen()
        self.server_socket.settimeout(1.0)
        self.is_running = True
        print(f'Server started on {self.host}:{self.port}')


    def run(self):
        """
        Run the server loop to accept incoming connections and process client requests.	
        these requests will have the  revive the clients user input that  will be processed by the process_request method if no errors.
        The server will continue running until the shutdown method is called.
        
        Parameters:
        -----------
        self : TCPServer tells the current instance of the class TCPserver to be started.

        Raises:
        -------
        socket.timeout
            If no connection is made within the timeout period. displays a message indicating the server is running and waiting for a connection.
            continues to wait for a connection.
        Exception as e
            For any other exceptions that may occur during the server's operation. Displays an error message.
        """

        while self.is_running:
            # tells the user that the server is running and waiting for a connection.
            print('Server is running. Waiting for a connection...')
            
            # try-except block to handle potential errors.
            try:
                # Accept a new client connection
                client, address = self.server_socket.accept()

                # tells the user that a client has connected.
                print('Connected to client: ', address)
                
                # Send a welcome message to the client.
                WelcomeMessage = 'Welcome to the calculator server. Enter operation (ADD/SUB/DIV/MUL) and operands (e.g., ADD 5 10) or quit to exit:'
                client.send(WelcomeMessage.encode())
                
                # Handle client requests in a loop.
                while self.is_running:
                    
                    # try-except block to handle potential errors.
                    try:
                        # Receive data from the client.
                        data = client.recv(1024).decode()
                        
                        # Check if the client has disconnected or sent a quit command.
                        if not data or data.upper() == 'QUIT':
                            break
                        # Process the request and send the response back to the client.
                        response = self.process_request(data) 
                        client.sendall(response.encode())
                    
                    # Catch any exceptions that occur during request processing.
                    except Exception as e:
                        print(f'Error: {str(e)}')

                # Close the client connection. and display a message indicating the client has disconnected.        
                client.close()
                print(f'Client disconnected at {address}.')

            # Catch socket timeout exceptions to continue waiting for connections.
            except socket.timeout: 
                continue
                print('No connection yet...')

            # Catch any other exceptions that occur during the server's operation.
            except Exception as e:
                print(f'Sever error: {str(e)}')


    def shutdown(self):
         """
        Shutdown the server  by closing the server socket and stopping the running loop. 

        Parameters:
        -----------
        self : TCPServer tells the current instance of the class TCPserver is being used to close.
         """

         self.is_running = False
         self.server_socket.close()


    def process_request(self, data): 
        """
        Process a client request and perform the specified arithmetic operation.
        This method parses the input string, validates the operation and operands,
        performs the requested arithmetic operation, and returns the result.
        It handles addition, subtraction, multiplication, and division operations.

        Parameters:
        -----------
        data : str
            A string containing the operation and operands in the format:
            "<OPERATION> <OPERAND1> <OPERAND2>"
            e.g., "ADD 5 3" or "DIV 10 2"

        Returns:
        --------
        str
            The result of the arithmetic operation as a string, or an error message
            if the input is invalid or an error occurs during processing.

        Raises:
        -------
        ValueError
            If the operands are not valid integers.
        ZeroDivisionError
            If a division by zero is attempted.
        Exception as e
            For any other exceptions that may occur.
        wrong size of parameters
             if the number of parameters is not 3
        
        

        Examples:
        ---------
        >>> server = TCPServer()
        >>> server.process_request("ADD 5 3")
        '8'
        >>> server.process_request("DIV 10 2")
        '5.0'
        >>> server.process_request("MUL 4 6")
        '24'
        >>> server.process_request("SUB 15 7")
        '8'
        >>> server.process_request("ADD 5 abc")
        'ERROR: Operands must be valid integers'
        >>> server.process_request("DIV 10 0")
        'ERROR: Division by zero error. The second operand cannot be zero.'
        >>> server.process_request("XOR 1 2")
        'ERROR: Invalid operation. Valid operations are ADD, SUB, DIV, and MUL'

        Note:
        -----
        This method assumes that the input string has been properly received
        and decoded from bytes to a string before being passed as an argument.
        """

        # Split the input data into 3 parts.
        parts= data.strip().split()
        operation = parts[0].upper()

        # Check if the operation is QUIT.
        if operation == 'QUIT':
            return 'Goodbye!'
        
        # try-except block to handle potential errors to check if user input is valid.
        try:
            # Store operands as integers.
            operand1 = int(parts[1])
            operand2 = int(parts[2])
            
            # Checks if the number of parameters is correct.
            if  len(parts) != 3: 
                return 'ERROR: Invalid number of parameters. Valid format is: <OPERATION> <OPERAND1> <OPERAND2>'
        
        # Catch ValueError if operands are not valid integers.
        except ValueError:
            return 'ERROR: Operands must be valid integers'
        
        # Catch IndexError if there are not enough parameters.
        except Exception as e:
            return f'ERROR: {str(e)}'
        
        # Perform the requested operations.
        if operation == 'ADD':
            return str(operand1 + operand2)
        elif operation == 'SUB':
            return str(operand1 - operand2)
        elif operation == 'MUL':
            return str(operand1 * operand2)
        elif operation == 'DIV':

            # Check for division by zero if so returns an error message.
            if operand2 == 0:
                return 'ERROR: Division by zero error. The second operand cannot be zero.'
            return str(operand1 / operand2)
        
        # If the operation is not recognized, return an error message.
        else:
            return 'ERROR: Invalid operation. Valid operations are ADD, SUB, DIV, and MUL'	
        