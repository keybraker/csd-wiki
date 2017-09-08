#------------------------------------CLIENT--------------------
#MARIOS KYPRIANOU AM 3212
#ALEXANDROS SAVVOPOULOS AM 3307
#CHRISTOFOROS LEVENTIS AM 3217

import subprocess
import socket
import sys
import os
import threading
def Socket_Client(file,relay_ip,relay_port):
	RECV_BUFFER_SIZE = 1024
     
	# Create a TCP/IP socket
 	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
     
 	# Connect the socket to the port where the server is listening
	server_address = (relay_ip, int(relay_port))
 	print >>sys.stderr, 'connecting to %s port %s' % server_address
 	sock.connect(server_address)
	file.close()
	file=open("relays_list.txt","r")
	file2=open("end_servers.txt","r")
 	try:
		# Send data
		message = file.read(1024)
		print >>sys.stderr, 'sending "%s"' % message
 		sock.sendall(message)
 		
		message1 = "NO_DATA\n"
                print >>sys.stderr, 'sending "%s"' % message1
                sock.sendall(message1)

		message2 = file2.read(1024)
                print >>sys.stderr, 'sending "%s"' % message2
                sock.sendall(message2)
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

def Socket_server(file3,file4,port_client):
	RECV_BUFFER_SIZE = 1024
	
	i=0
	j=0
	# Create a TCP/IP socket
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
 	# Bind the socket to the port

 	#By setting the host name to the empty string, it tells the bind() method to fill in the address of the current machine.
 	server_address = ('', int(port_client))
 	print >>sys.stderr,'starting up on %s port %s' % server_address
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
				if j==0:
					file3.write(data)
					j+=1
				else:
					file4.write(data)	
							
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
			sock.close()

def Traceroute(hostname,hostname_ip,filename3,filename1):

        try:
		if (filename1=="relays_list.txt"):
                	traceroute = subprocess.check_output(["traceroute",hostname_ip])#ME IP
                else:
			traceroute = subprocess.check_output(["traceroute",hostname])#ME NAME

		print "The trace route is :"+traceroute
                hop = traceroute.split('\n')
		filename3.write("%(Hostname)s:%(Hops)d\n"%{"Hostname":hostname,"Hops":len(hop)-3})

        except:
                print "connection not found"


def Ping(Num_ping,filename1,filename2,filename3,nameserver):
	file=open(filename1,"r")
        lines=file.readlines()
        for line in lines:
                try:
                	server=line.split(',')

                	if not line:#telos arxeioy
                        	break

                	print "***The hostname now is "+server[0]+"***"	#server[0] = hostname ,server[1]=ip of hostname
                	
			if(filename1=="relays_list.txt"):
				time= subprocess.Popen(
				["ping","-c",str(Num_ping),server[1]],#ME IP
					stdout = subprocess.PIPE,
 					stderr = subprocess.PIPE
                		)
                		out, error = time.communicate()
			else:
				time= subprocess.Popen(
                                ["ping","-c",str(Num_ping),server[0]],#ME NAME
                                        stdout = subprocess.PIPE,
                                        stderr = subprocess.PIPE
                                )
                                out, error = time.communicate()
                
			print out
                	RTT=out.split('/')
			nameserver=[server[0],server[1]]
			print nameserver
			raw_input("lalalalala")
                	filename2.write("%(hostname)s:%(rtt)s\n"%{"hostname": server[0],"rtt": RTT[4]})
                	print"The trace traceroute of "+server[0]
                	#Traceroute(server[0],server[1],filename3,filename1)
                
		except :
                        print "***Here we have packet loss****"
        return 

def Results(file1,file2,file3,file4,file5,file6):
	
	#ADD RTT
	List_file3=file3.readlines()
	List_file5=file5.readlines()
        for line5 in List_file5:
		
                line5=line5.strip()
                List5=line5.split(':')

		for line3 in List_file3:
			
			line3=line3.strip()
			List3=line3.split(':')
						
			if(List3[0]==List5[0]):
				res=float(List3[2])+float(List5[1])
				file1.write("%(List3[0])s:%(List3[1])s:%(res)f\n"%{"List3[0]":List3[0],"List3[1]":List3[1],"res":res})
				
				if not line3:
					break

		if not line5:
                	break
	
	#ADD HOPS
	List_file4=file4.readlines()
	List_file6=file6.readlines()
	for line6 in List_file6:
		
		line6=line6.strip()
		List6=line6.split(':')
		
		for line4 in List_file4:
			
			line4=line4.strip()
			List4=line4.split(':')
			
			if(List4[0]==List6[0]):
				res=float(List4[2])+float(List6[1])
				file2.write("%(List4[0])s:%(List4[1])s:%(res)f\n"%{"List4[0]":List4[0],"List4[1]":List4[1],"res":res})

				if not line4:
					break
		if not line6:
				break
				
	return 
 	
def Main():
	threadLock = threading.Lock()
        threads = []
	file1=open("Rtt.txt","w")
	file2=open("Hops.txt","w")
	
	file3=open("Relay_Rtt.txt","w")
	file4=open("Relay_Hops.txt","w")

	file5=open("My_Relay_Rtt.txt","w")
	file6=open("My_Relay_Hops.txt","w")
	
	num_ping=raw_input("Please give me number of pings: ")
	
	#direct ping
	server=[]
	t = threading.Thread(target=Ping(num_ping,"end_servers.txt",file1,file2,server), args=( ) )
        t.setDaemon(True)
        threads.append(t)   #save the threads on a list
        t.start() 
	
	#Read relays_list.txt
	file7=open("relays_list.txt","r")
	lines7=file7.readlines()
	i=len(lines7)
	k=0
	while(1):
		if (k == len(lines7)):
                        break
		copyrelay=lines7[k].split(',')
		relay_ip=copyrelay[1]
		relay_port=copyrelay[2]
		k+=1
		Socket_Client(file7,relay_ip,relay_port)
	#END

	j=0
	while(1):
	
		port_client=raw_input("\nPlease give me the port of client:  ")
		Socket_server(file3,file4,port_client)
		if(j==(i-1)):
			break
		j+=1
	
	#thread 1
	t2 = threading.Thread(target=Ping(num_ping,"relays_list.txt",file5,file6,server), args=( ) )
    	t2.setDaemon(True)
    	threads.append(t2)   #save the threads on a list
    	t2.start()
	 
	print server[0]
	print server[1]
	raw_input("here we are at server")
	#server=Ping(num_ping,"relays_list.txt",file5,file6)
	#Traceroute(copy_server[0],copy_server[1],filename3,filename1)
	
	#Thread 2
	t3 = threading.Thread(target=Traceroute(server[0],server[1],filename3,filename1), args=( ) )
        t3.setDaemon(True)
        threads.append(t3)   #save the threads on a list
        t3.start()

	threads[0].join();
	threads[1].join();
	threads[2].join();

	file3.close()
	file4.close()
	
	file5.close()
	file6.close()

	file3=open("Relay_Rtt.txt","r")
	file4=open("Relay_Hops.txt","r")

	file5=open("My_Relay_Rtt.txt","r")
	file6=open("My_Relay_Hops.txt","r")

	Results(file1,file2,file3,file4,file5,file6)

	#DELETE FILES
	os.remove("Relay_Rtt.txt")
	os.remove("Relay_Hops.txt")
	os.remove("My_Relay_Rtt.txt")
	os.remove("My_Relay_Hops.txt")
Main()
