#------------------------------------CLIENT--------------------
#MARIOS KYPRIANOU AM 3212
#ALEXANDROS SAVVOPOULOS AM 3307
#CHRISTOFOROS LEVENTIS AM 3217

import subprocess
import socket
import sys
import os
import urllib
import urlparse
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
	file=open("relay_nodes.txt","r")
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
		print"The trace traceroute of "+hostname
		if (filename1=="relay_nodes.txt"):
                	traceroute = subprocess.check_output(["traceroute",hostname_ip])#ME IP
                else:
			traceroute = subprocess.check_output(["traceroute",hostname])#ME NAME

		print "The trace route is :"+traceroute
                hop = traceroute.split('\n')
		filename3.write("%(Hostname)s:%(Hops)d\n"%{"Hostname":hostname,"Hops":len(hop)-3})

        except:
                print "connection not found"
		k=2
		filename3.write("%(Hostname)s:%(Hops)d\n"%{"Hostname":hostname,"Hops":k-3})


def Ping(Num_ping,filename1,filename2,filename3):
        
	file=open(filename1,"r")
        lines=file.readlines()
        for line in lines:
                try:
                	server=line.split(',')

                	if not line:#telos arxeioy
                        	break

                	print "***The hostname now is "+server[0]+"***"	#server[0] = hostname ,server[1]=ip of hostname
                	
			if(filename1=="relay_nodes.txt"):
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
                	filename2.write("%(hostname)s:%(rtt)s\n"%{"hostname": server[0],"rtt": RTT[4]})
                
		except :
                        print "***Here we have packet loss****"
			k=-1
			filename2.write("%(hostname)s:%(rtt)s\n"%{"hostname": server[0],"rtt": k})
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

def Find_Best(file1,file2,RTT_HOP,server_name):
	cnt=0
        if (RTT_HOP== "RTT"):
                #FIND BEST RTT
                file1=open(file1,"r")
                lines1=file1.readlines()
                k=0
                for line1 in lines1:
                        line1=line1.strip()
                        List=line1.split(':')

                        tmp=len(List)

                        if not line1:
                                break

                        if(tmp==2):
                                tmp_rtt_num=float(List[1])
                                tmp_rtt_name=List[0]

				if(tmp_rtt_name!=server_name):
					continue

                                if(k==0):
                                        Rtt=tmp_rtt_num
                                        Rtt_name=tmp_rtt_name
                                        k=1
                                        continue

				if(Rtt>tmp_rtt_num):
                                	Rtt=tmp_rtt_num
                                	Rtt_name=tmp_rtt_name
					cnt=0
                        else:
                                tmp_rtt_num=float(List[2])
                                tmp_rtt_name=List[1]
				tmp_rtt_name2=List[0]

				if(tmp_rtt_name!=server_name):
					continue
 
				if(Rtt>tmp_rtt_num):
                                	Rtt=tmp_rtt_num
					Rtt_name=tmp_rtt_name
					Rtt_name2=tmp_rtt_name2
					cnt=1

                #END FOR
	else:
		#FIND BEST HOP
                file2=open(file2,"r")
		lines2=file2.readlines()
		k=0
		for line2 in lines2:
			line2=line2.strip()
			List2=line2.split(':')
			
			tmp2=len(List2)
			
			if not line2:
				break
			
			if(tmp2==2):
				tmp_hop_num=float(List2[1])
				tmp_hop_name=List2[0]
				
				if(tmp_hop_name!=server_name):
					continue

				if(k==0):
                                	Hop=tmp_hop_num
                                	Hop_name=tmp_hop_name
                                	k=1
                                	continue
                        	
				if(Hop>tmp_hop_num):
                                	Hop=tmp_hop_num
                                	Hop_name=tmp_hop_name
					cnt=0
			else:
                        	tmp_hop_num=float(List2[2])
                        	tmp_hop_name=List2[1]
				tmp_hop_name2=List2[0]

				if(tmp_hop_name!=server_name):
					continue

                        	if(Hop>tmp_hop_num):
                                	Hop=tmp_hop_num
                               		Hop_name=tmp_hop_name
					Hop_name2=tmp_hop_name2
					cnt=1
                #END FOR
	
	if(RTT_HOP=="RTT"):
		if(cnt==0):
			Res=Rtt_name+':'+str(Rtt)
		else:
			Res=Rtt_name2+':'+Rtt_name+':'+str(Rtt)
		
	else:
		if(cnt==0):
			Res=Hop_name+':'+str(Hop)
		else:
			Res=Hop_name2+':'+Hop_name+':'+str(Hop)
	return Res
	
def Sent_Url(file1,file2):	

	file1=open(file1,"r")#URL.txt
	file2=open(file2,"r")#BEST.txt	
	lines1=file1.readlines()
	lines2=file2.readlines()
	i=0
	for line2 in lines2:
		
		line2=line2.strip()
		List2=line2.split(':')

		if not line2:
			break

		if(len(List2)==2):
			name=List2[0]
		
			if(float(List2[1])<float(0)):
				continue

			for line1 in lines1:	
		
				line1=line1.strip()
				
				if not line1:
					break

				tmp=line1
				server_name=tmp.split("//")[-1].split("/")[0]
				
				server_name1=server_name.split('.')#Some url is=server_name. ,but i want www.server_name
				if(len(server_name1)==2):
					server_name="www."+server_name
		
				if(name!=server_name):
					continue

				file3=open('URL'+str(i)+'.png',"w")#IMAGE
				i+=1
				page = urllib.urlopen(line1)
				content = page.read()
				file3.write(content)
				file3.close()
		
	return

def Help_me_threads(file,filename3):
        file1=open(file,"r")
        lines7=file1.readlines()
        for line in lines7:
                line=line.strip()
                relay=line.split(",")
                relay_ip=relay[1]
                relay_name=relay[0]
                Traceroute(relay_name,relay_ip,filename3,file)
	
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
	
	#Read relay_nodes.txt
	file7=open("relay_nodes.txt","r")
	lines7=file7.readlines()
	i=len(lines7)
	k=0
	#direct ping with Thread
        t = threading.Thread(target=Ping(num_ping,"end_servers.txt",file1,file2), args=( ) )
        t.setDaemon(True)
        threads.append(t)   #save the threads on a list
        t.start()
        #direct Traceroute with Thread
        
        t1 = threading.Thread(target=Help_me_threads("end_servers.txt",file2), args=( ) )
        t1.setDaemon(True)
        threads.append(t1)   #save the threads on a list
        t1.start()
        

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

	
	#thread 3
        t2 = threading.Thread(target=Ping(num_ping,"relay_nodes.txt",file5,file6), args=( ) )
        t2.setDaemon(True)
        threads.append(t2)   #save the threads on a list
        t2.start()


        #Thread 4
        t3 = threading.Thread(target=Help_me_threads("relay_nodes.txt",file6), args=( ) )
        t3.setDaemon(True)
        threads.append(t3)   #save the threads on a list
        t3.start()

        threads[0].join();
        threads[1].join();
        threads[2].join();
        threads[3].join();


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
	
	#file1 ->Rtt
	#file2 ->Hop

	file1.close()
	file2.close()
	RTT_HOP=raw_input("\nRTT OR HOP: ")
	file9=open("BEST.txt","w")
	file8=open("end_servers.txt","r")
	lines8=file8.readlines()
	
	#BEGIN FOR
	for line8 in lines8:
		line8=line8.strip()
		List8=line8.split(',')

		if (len(List8)==3):
			break
		
		server_name=List8[0]
		Res=Find_Best("Rtt.txt","Hops.txt",RTT_HOP,server_name)

		Res=Res+"\n"
                file9.write(Res)
	#END FOR

        file9.close()
	Sent_Url("URL.txt","BEST.txt")

	#DELETE FILES
	os.remove("Rtt.txt")
	os.remove("Hops.txt")
	
Main()
