# CPSC 3600 - Networks and Network Programming

## Course Description
Introduction to computer networks and network programming. Topics include network protocols (TCP/IP, UDP), socket programming, client-server architecture, network security, and distributed systems. Students develop practical experience building networked applications and understanding network infrastructure.

## Learning Objectives
- Understand network protocols and the TCP/IP stack
- Master socket programming in Python
- Implement client-server applications
- Learn reliable data transfer protocols
- Understand network routing and switching
- Develop distributed network systems
- Debug and troubleshoot network applications
- Understand network security fundamentals

## Projects and Assignments

### Hands-on Activity 1: Creating a Simple Client-Server Application
Introduction to socket programming with basic TCP/UDP client-server communication.

### Hands-on Activity 2: Replicating Traceroute
Network diagnostic tool implementation using ICMP packets to trace routing paths.

### Hands-on Activity 3: Building a Self-Learning Switch
Simulated network switch with MAC address learning and frame forwarding capabilities.

### Major Project 1: Building a File Transfer Application
Complete file transfer protocol implementation with support for multiple file types and error handling.

### Major Project 2: Implementing a Reliable Data Transfer Protocol
Custom reliable transport protocol over UDP with acknowledgments, retransmission, and flow control.

### Major Project 3: Implementing a Distributed Server Network
Multi-server architecture with load balancing, failure detection, and distributed coordination implementing a text chat system similar to SMS texting.

## Technology Stack

### Programming Language
- **Python 3**: Primary language for all network programming

### Network Protocols
- TCP (Transmission Control Protocol)
- UDP (User Datagram Protocol)
- ICMP (Internet Control Message Protocol)
- HTTP/HTTPS
- Custom application-layer protocols

### Python Libraries
- `socket`: Core socket programming
- `threading`: Concurrent server implementations
- `struct`: Binary data packing/unpacking
- `select`: Multiplexed I/O
- `asyncio`: Asynchronous network programming

### Development Tools
- Python 3.6+
- Wireshark (packet analysis)
- netcat (network debugging)
- tcpdump (packet capture)
- Network simulation tools

### Debugging Tools
- **tcp_eco_client.py**: Helper file for debugging and testing TCP connections
- **udp_eco_client.py**: Helper file for debugging and testing UDP connections

### Environment
- Xubuntu Linux x86-64
- Network simulator or virtual machines for testing
- Command-line tools for network diagnostics

## Setup and Requirements
- Python 3.6 or later
- Basic understanding of networking concepts
- Linux/Unix or Windows with Python installed
- Network analysis tools (Wireshark recommended)
- Multiple machines or VMs for distributed testing

## Work Type
This class entails **individual work** written in Python 3.

### Helper Files
- `tcp_eco_client.py` and `udp_eco_client.py` are helper files for debugging and testing projects and assignments. 
