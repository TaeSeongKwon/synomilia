import socket
import time 

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 2911))
server.listen(3)

while True :
    client_socket, addr = server.accept()
    for i in range(10) :
        client_socket.send("hello_%d"%i)
        time.sleep(1)
        client_socket.send("data")
        time.sleep(1)
    client_socket.close()


