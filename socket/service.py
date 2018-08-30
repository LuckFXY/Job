import socket

HOST = 'localhost'      # 服务器主机地址
PORT = 5000             # 服务器监听端口
BUFFER_SIZE = 2048      # 读取数据大小

# 创建一个套接字
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
# 绑定主机和端口
sock.bind((HOST, PORT))
# 开启socket监听
sock.listen(5)


print ('Server start, listening {}'.format(PORT))


while True:
    # 建立连接，连接为建立的时候阻塞
    conn, addr = sock.accept()
    while True:
        # 读取数据，数据还没到来阻塞
        data = conn.recv(BUFFER_SIZE)
        if len(data):
            print ('Server Recv Data: {}'.format(data))
            conn.send(data)
            print ('Server Send Data: {}'.format(data))
        else:
            print ('Server Recv Over')
            break
    conn.close()
sock.close()
