# 简介

库如起名，传包要猛

假设有服务端S和客户端C，需要在CS之间传输数据，传输的数据内容格式可变，传输的网络协议可变


Client 和 Server 要配套

上层只管将一个数据交给client，而不需要关心数据通过什么格式，经过什么协议传递给Server（这里是库本身不需要管，所有组装包的逻辑都可以交由外部注入猛，但是库本身需要提供常见的诸如tcp，udp之类的协议传输功能）

但这里有个问题，发出去的包需要能被Server接收，

常见的Server可能使用http，tcp，udp，quic等协议之后，用户在使用client的时候利用是知道需要用什么协议以及什么格式发送给server


# Client

interface Client {
    Send(msg)
    RegistEncoder()
    RegistDecoder()
}

- TCPClient
- UDPClient
- QUICClient

