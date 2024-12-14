# Socket programming example: server side config.
import socket

def socket_example_server():
    """
    Server side socket programming example.
    Creates a server that listens for incoming connections and receives messages.
    """

    # Create a TCP/IP socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Server config
    host = '127.0.0.1'  # Localhost IP
    port = 65525        # Port to listen on
    
    try:
        # Bind the socket to the port
        server_socket.bind((host, port))
        
        # Listen for incoming connections
        server_socket.listen(5)
        print(f"Server is listening on {host}:{port}")
        
        while True:
            # Wait for a connection
            print("Waiting for a connection...")
            client_socket, client_address = server_socket.accept()
            
            try:
                print(f"Connected to client: {client_address}")
                
                # Receive the data in small chunks and retransmit it
                while True:
                    data = client_socket.recv(1024).decode()
                    if data:
                        print(f"Received: {data}")
                        # Send acknowledgment
                        response = "Hello, I am the server, received your message: " + data
                        client_socket.send(response.encode())
                    else:
                        print("No more data from client")
                        break
                    
            except Exception as e:
                print(f"Error handling client: {e}")
            finally:
                # Clean up the connection
                client_socket.close()
                print("Connection closed")
                
    except Exception as e:
        print(f"Server error: {e}")
    finally:
        server_socket.close()
        print("Server shutdown")

if __name__ == "__main__":
    socket_example_server()