#include <iostream>
#include <fas/base/EventLoop.h>
#include <fas/base/TcpServer.h>
#include <fas/base/Buffer.h>
#include <fas/base/TcpConnection.h>
#include <boost/bind.hpp>

using namespace fas;
using namespace std;

void TcpConnMessageCallback(TcpConnection *conn, Buffer *buffer, \
                            Timestamp time) {
  /*!
   * \brief str
   * 把收到的内容存到一个字符串中，供后面打印出来。
   */
  std::string str(buffer->retrieveAllAsString());
  std::cout << time.toFormattedString() << " from socket : " \
            << conn->getConnfd() <<" recv : " \
            << str << endl;
  /*!
   * 在把收到的字符串发回去。FAS框架会先把你发送的消息存储的发送buffer里面，等到套接字可读时发送出去。
   */
  conn->sendData(str.data(), str.length());
}

int main() {
    EventLoop *loop = new EventLoop;
    NetAddress seraddr(AF_INET, 8888, "127.0.0.1");
    TcpServer *ser = new TcpServer(loop, seraddr);

    ser->setMessageCallback(boost::bind(TcpConnMessageCallback, _1, _2, _3));

    ser->start();

    loop->loop();
    delete loop;
}

