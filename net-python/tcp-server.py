import socket

PORT = 1234
BUFSIZE = 1024
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("",PORT))
s.listen(0)

iscontinue=1
while iscontinue==1:
    try:
        cnx, addr = s.accept()
    except:
        print("Error!")
        s.close()
        exit(1)
        
    print("Access from address: ",addr)
    
    while True:
        msg = cnx.recv(BUFSIZE)
        msg = msg.decode("utf-8")
        print("client message: ",msg)
        if msg == "exit!":
            print("Disconnected ")
            break
      
        msg = input("> ")
        msg = msg.encode("utf-8")
        cnx.send(msg)
        
    if iscontinue==1:
        print("Listening to client")
    