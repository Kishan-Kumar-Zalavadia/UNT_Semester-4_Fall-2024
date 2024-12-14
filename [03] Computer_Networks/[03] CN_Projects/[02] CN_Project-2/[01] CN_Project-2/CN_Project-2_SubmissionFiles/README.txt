Project Source code link: https://github.com/Kishan-Kumar-Zalavadia/CN_Socket_Programming_and_DDoS_Attack
_____________________________________________________________________________________________________________________________________________

Socket Programming and TCP SYN Flood Attack Project

Prerequisites:
- Python 3.x

_____________________________________________________________________________________________________________________________________________

Instructions to run the Project:

Part 1: Socket Programming Example: 
- Run the server using the following command: 'python3 main_server.py'.
- Run the client:
	- Make sure the below code is uncommented on:
		LINE 33: socket_example_client()
	- Make sure the below code is commented on:
		LINE 44: disPort = 65525
	    	LINE 45: num_requests = 100000
	    	LINE 46: disIP = '127.0.0.1'
    		LINE 47: tcp_syn_flood_attack(disIP, disPort, num_requests)


Part 2: TCP SYN Flood Attack
- Make sure Scapy is installed, or else it will not work. If you are using a Mac, below are the commands to install Scapy.
	python3 -m venv scapy-env
	source scapy-env/bin/activate
	pip install scapy

- Run the server using the following command: 'python3 main_server.py'.
- Run the client/attack:
	- Make sure the below code is commented on:
		LINE 33: socket_example_client()
	- Make sure the below code is uncommented on:
		LINE 44: disPort = 65525
	    	LINE 45: num_requests = 100000
	    	LINE 46: disIP = '127.0.0.1'
    		LINE 47: tcp_syn_flood_attack(disIP, disPort, num_requests)


Run both the parts together:
- Make sure the below code is uncommented on:
	LINE 33: socket_example_client()
	LINE 44: disPort = 65525
    	LINE 45: num_requests = 
    	LINE 46: disIP = '127.0.0.1'
    	LINE 47: tcp_syn_flood_attack(disIP, disPort, num_requests)
_____________________________________________________________________________________________________________________________________________

Wireshark
- Filter the results using the below command:
	tcp.port == 65525 (or) tcp.flags.syn == 1 and tcp.port == 65525

_____________________________________________________________________________________________________________________________________________