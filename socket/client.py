import socket

HOST = 'localhost'
PORT = 5000
BUFFER_SIZE = 1024

# 创建客户端套接字
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 连接到服务器
sock.connect((HOST, PORT))

try:
    message = "Hello67890"*2
    # 发起数据给服务器
    sock.sendall(message.encode(encoding='utf-8'))
    amount_received = 0
    amount_expected = len(message)
    while amount_received < amount_expected:
        # 接收服务器返回的数据
        data = sock.recv(10)
        amount_received += len(data)
        print ('Client Received: {}'.format(data))


except Exception as e:
    print("exception: ",e)
finally:
    print ('Closing connection to the server')
    sock.close()
