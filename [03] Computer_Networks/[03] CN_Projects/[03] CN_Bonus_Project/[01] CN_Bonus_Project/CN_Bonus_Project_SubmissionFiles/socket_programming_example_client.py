# Socket programming example: client side config.
import socket

def socket_example_client():
    """
    Client side socket programming example.
    Creates a client that connects to the server and sends messages.
    """
    # Create a TCP/IP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Server connection details
    server_host = '127.0.0.1'  # Server IP
    server_port = 65525        # Server port number
    
    # Send data and receive response in a try/except block to handle any errors that may occur.
    try:
        # Connect to the server
        print(f"Connecting to the server at {server_host}:{server_port}")
        client_socket.connect((server_host, server_port))
        
        # Send data
        message = "Hello server, I am the client!"
        print(f"Sending: {message}")
        client_socket.send(message.encode())
        
        # Receive response
        data = client_socket.recv(1024).decode()
        print(f"Received response: {data}")
        
    except ConnectionRefusedError:
        print("Connection failed. Please make sure the server is running.")
    except Exception as e:
        print(f"Client error: {e}")
    finally:
        # Clean up the connection
        client_socket.close()
        print("Connection closed")

if __name__ == "__main__":
    socket_example_client()