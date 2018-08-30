## 0. 通信标识

网络层的“ip地址”可以唯一标识网络中的主机，而传输层的“协议+端口”可以唯一标识主机中的应用程序（进程）。这样利用三元组（ip地址，协议，端口）就可以标识网络的进程了，网络中的进程通信就可以利用这个标志与其它进程进行交互。

## 1. 基本概念

* Socket是应用层与TCP/IP协议族通信的中间软件抽象层，它是一组接口。
* 在设计模式中，Socket其实就是一个门面模式，它把复杂的TCP/IP协议族隐藏在Socket接口后面，对用户来说，一组简单的接口就是全部，让Socket去组织数据，以符合指定的协议。
* 门面模式，用自己的话说，就是系统对外界提供单一的接口，外部不需要了解内部的实现。
* socket可以理解为一种特殊的文件，一些socket函数就是对其进行的操作（读/写IO、打开、关闭）

## 2. socket通信过程简单描述

### 2.1 TCP级别
![tcp_socket](..\img\tcp_socket.gif)

### 2.2 socket级别

![tcp_socket](F:\GitHub\Job\img\socket_communicate_process.jpg)

## 3.  socket的基本操作

### 3.1、socket()函数

```
int socket(int domain, int type, int protocol);
```

socket函数对应于普通文件的打开操作。普通文件的打开操作返回一个文件描述字，而**socket()**用于创建一个socket描述符（socket descriptor），它唯一标识一个socket。这个socket描述字跟文件描述字一样，后续的操作都有用到它，把它作为参数，通过它来进行一些读写操作。 

- domain：即协议域，又称为协议族（family）。常用的协议族有，AF_INET、AF_INET6、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等等。协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合、AF_UNIX决定了要用一个绝对路径名作为地址。
- type：指定socket类型。常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等（socket的类型有哪些？）。
- protocol：故名思意，就是指定协议。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议（这个协议我将会单独开篇讨论！）。

### 3.2、bind()函数

当我们调用**socket**创建一个socket时， 没有一个具体的地址。如果想要给它赋值一个地址，就必须调用bind()函数 ，否则就当调用connect()、listen()时系统会自动随机分配一个端口。 

```
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

- sockfd：即socket描述字，它是通过socket()函数创建了，唯一标识一个socket。bind()函数就是将给这个描述字绑定一个名字。
- addr：一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。这个地址结构根据地址创建socket时的地址协议族的不同而不同 
- addrlen：对应的是地址的长度。

### 3.3、listen()、connect()函数

发送和监听。如果作为一个服务器，在调用socket()、bind()之后就会调用listen()来监听这个socket，如果客户端这时调用connect()发出连接请求，服务器端就会接收到这个请求。 

```cpp
int listen(int sockfd, int backlog);
//listen函数的第一个参数即为要监听的socket描述字
//第二个参数为相应socket可以排队的最大连接个数
//socket()函数创建的socket默认是一个主动类型的，listen函数将socket变为被动类型的，等待客户的连接请求。
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//connect函数的第一个参数即为客户端的socket描述字
//第二参数为服务器的socket地址
//第三个参数为socket地址的长度。客户端通过调用connect函数来建立与TCP服务器的连接。
```

### 3.4、accept()函数

TCP服务器端依次调用socket()、bind()、listen()之后，就会监听指定的socket地址了。TCP客户端依次调用socket()、connect()之后就想TCP服务器发送了一个连接请求。TCP服务器监听到这个请求之后，就会调用accept()函数取接收请求，这样连接就建立好了。之后就可以开始网络I/O操作了，即类同于普通文件的读写I/O操作。 

```cpp
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//第一个参数为服务器的socket描述字
//第二个参数为指向struct sockaddr *的指针，用于返回客户端的协议地址
//第三个参数为协议地址的长度。
//如果accpet成功，那么其返回值是由内核自动生成的一个全新的描述字，代表与返回客户的TCP连接。 
```

### 3.5 网络字节序与主机字节序

* **主机字节序**就是我们平常说的大端和小端模式：不同的CPU有不同的字节序类型，这些字节序是指整数在内存中保存的顺序，这个叫做主机序。引用标准的Big-Endian和Little-Endian的定义如下：

　　a) Little-Endian就是低位字节排放在内存的低地址端，高位字节排放在内存的高地址端。

　　b) Big-Endian就是高位字节排放在内存的低地址端，低位字节排放在内存的高地址端。

* **网络字节序**：4个字节的32 bit值以下面的次序传输：首先是0～7bit，其次8～15bit，然后16～23bit，最后是24~31bit。这种传输次序称作大端字节序。**由于TCP/IP首部中所有的二进制整数在网络中传输时都要求以这种次序，因此它又称作网络字节序。**字节序，顾名思义字节的顺序，就是大于一个字节类型的数据在内存中的存放顺序，一个字节的数据没有顺序的问题了。

所以：在将一个地址绑定到socket的时候，请先将主机字节序转换成为网络字节序，而不要假定主机字节序跟网络字节序一样使用的是Big-Endian。由于这个问题曾引发过血案！公司项目代码中由于存在这个问题，导致了很多莫名其妙的问题，所以请谨记对主机字节序不要做任何假定，务必将其转化为网络字节序再赋给socket。

### 3.6、read()、write()函数等

read()/write()

recv()/send()

readv()/writev()

recvmsg()/sendmsg()

recvfrom()/sendto()



- read函数是负责从fd中读取内容.当读成功时，read返回实际所读的字节数，如果返回的值是0表示已经读到文件的结束了，小于0表示出现了错误。如果错误为EINTR说明读是由中断引起的，如果是ECONNREST表示网络连接出了问题。
- write函数将buf中的nbytes字节内容写入文件描述符fd.成功时返回写的字节数。失败时返回-1，并设置errno变量。 在网络程序中，当我们向套接字文件描述符写时有俩种可能。1)write的返回值大于0，表示写了部分或者是全部的数据。2)返回的值小于0，此时出现了错误。我们要根据错误类型来处理。如果错误为EINTR表示在写的时候出现了中断错误。如果为EPIPE表示网络连接出现了问题(对方已经关闭了连接)。

### 3.7、close()函数

在服务器与客户端建立连接之后，会进行一些读写操作，完成了读写操作就要关闭相应的socket描述字，好比操作完打开的文件要调用fclose关闭打开的文件。 

```
#include <unistd.h>
int close(int fd);
```

close一个TCP socket的缺省行为时把该socket标记为以关闭，然后立即返回到调用进程。该描述字不能再由调用进程使用，也就是说不能再作为read或write的第一个参数。

## python 版的socket通信

```python
//server
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
```

```python
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
```

##  