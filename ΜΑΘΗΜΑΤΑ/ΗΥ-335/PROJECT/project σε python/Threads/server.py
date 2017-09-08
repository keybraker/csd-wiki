#------------------SERVER-------------------------
#MARIOS KYPRIANOU AM 3212
#ALEXANDROS SAVVOPOULOS AM 3307
#CHRISTOFOROS LEVENTIS AM 3217

import subprocess
import socket
import sys
import os

def Socket_Client (result_RTT,result_HOPS,ip_client,port_client):
	RECV_BUFFER_SIZE = 1024
	
	# Create a TCP/IP socket
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
     
	# Connect the socket to the port where the server is listening
	server_address = (ip_client, int(port_client))
	print >>sys.stderr, 'connecting to %s port %s' % server_address
	sock.connect(server_address)
     
	try:
		# Send data
		message = result_RTT 
		sock.sendall(message)
		
		message = result_HOPS
                print >>sys.stderr, 'sending "%s"' % message
                sock.sendall(message)
		
		# Look for the response
		amount_received = 0
		amount_expected = len(message)
     
		while amount_received < amount_expected:
			data = sock.recv(RECV_BUFFER_SIZE)
			amount_received += len(data)
			print >>sys.stderr, 'received "%s"' % data
  
	finally:
		print >>sys.stderr, 'closing socket'
		sock.close()
 
def Socket_Server(port_client):
	
	RECV_BUFFER_SIZE = 1024
	
	file=open("Result.txt","w")
	i=0
	# Create a TCP/IP socket
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# Bind the socket to the port

	#By setting the host name to the empty string, it tells the bind() method to fill in the address of the current machine.
	server_address = ('', int(port_client))
	print >>sys.stderr, 'starting up on %s port %s' % server_address
	sock.bind(server_address)

	# Listen for incoming connections
	sock.listen(1)
	
	while i==0:

		# Wait for a connection
		print >>sys.stderr, 'waiting for a connection'
		connection, client_address = sock.accept()
		try:
			print >>sys.stderr, 'connection from', client_address
			# Receive the data in small chunks and retransmit it
			while i==0:
				data = connection.recv(RECV_BUFFER_SIZE)
				
				file.write(data)
				
				print >>sys.stderr, 'received :\n"'
				print >>sys.stderr, "%s"%data
				if data:
					print >>sys.stderr, 'sending data back to the client'
					connection.sendall(data)
				else:
					print >>sys.stderr, 'no more data from', client_address
					i+=1
					break  
		finally:
			connection.close()
	return
 
def Traceroute(hostname,hostname_ip,name_relay):
     	result_HOPS=""
        try:
        	traceroute = subprocess.check_output(["traceroute",hostname])
        	print "The trace route is :"+traceroute
        	hop = traceroute.split('\n')
		result_HOPS+="%(name)s:%(Hostname)s:%(num)d\n"%{"name":name_relay,"Hostname":hostname,"num":len(hop)-3}
     	except:
        	print "print connection not found"
	return result_HOPS
 
 
def Ping(Num_ping,filename,name_relay):
        result=""
	file=open(filename,"r")
        lines=file.readlines()
        for line in lines:
		try:
                	server=line.split(',')
                	if not line:#telos arxeioy
 				break
                	print "***The hostname now is "+server[0]+"***"
                	time= subprocess.Popen(
                	["ping","-c",str(Num_ping),server[0]],
                	stdout = subprocess.PIPE,
                	stderr = subprocess.PIPE
                	)
                	out, error = time.communicate()
                        print out
                        RTT=out.split('/')
			result+=("%(name)s:%(hostname)s:%(rtt)s\n"%{"name":name_relay,"hostname": server[0],"rtt": RTT[4]})
			print"The trace traceroute of "+server[0]
                        result+=Traceroute(server[0],server[1],name_relay)
		except:
                        print "***Here we have packet loss****"
        return result

def Main():
	
	result_RTT=""
	result_HOPS=""

	ip_client=raw_input("\nPlease give me the ip of client: ")
	port_client=raw_input("Please give me the port of client:  ")
        port_relay=raw_input("\nPlease give me the port of relay:  ")
	Socket_Server(port_relay)
	
	#Result.txt->Relays_List.txt->Server_end_servers.txt
	file=open("Result.txt","r")
	file1=open("Relay_List.txt","w")
	file2=open("Server_end_servers.txt","w")
	lines=file.readlines()
	k=0
	for line in lines:
		if not line :
			break
		if(line=="NO_DATA\n"):
			file1.close()
			k=1
			continue
		if(k==0):
			file1.write(line)
		if(k==1):
			file2.write(line)
	file.close()
	file2.close()
	#FINISH
	

	num_ping=raw_input("Please give me number of pings: ")
	name_relay=raw_input("Please give me name_relay: ")
	result=Ping(num_ping,"Server_end_servers.txt",name_relay)
	List=result.split('\n')
	i=0
	for i in range(len(List)):#Separate string(result) to two strings(result_RTT and result_HOPS) 
		if (i%2)==0:#Even=RTT
			result_RTT+=List[i]
			if (i+2)<len(List):
				result_RTT+="\n"
		else:#Odd=HOPS
			result_HOPS+=List[i]
			if (i+1)<len(List):#itan i+1 an yparxei problima
                        	result_HOPS+="\n"
		i+=1	

	Socket_Client(result_RTT,result_HOPS,ip_client,port_client)

Main()

