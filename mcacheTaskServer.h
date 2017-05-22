#ifndef FAS_MCACHETASKSERVER_H
#define FAS_MCACHETASKSERVER_H
#include <TcpServer.h>
#include <mcacheTaskHandle.h>
#include <Types.h>

class TcpServer;
class EventLoop;
class NetAddress;

class mcacheTaskServer
{
public:
  mcacheTaskServer(fas::EventLoop* loop, const fas::NetAddress& addr, int threadNum);
  ~mcacheTaskServer();

  void OnNewConnection(fas::TcpConnShreadPtr conn);
  void OnConnectionRemoved(fas::connkey_t conn);

  bool start();
private:
  fas::EventLoop *loop_;
  fas::TcpServer tcpSer_;
  std::map<fas::connkey_t, std::shared_ptr<mcacheTaskHandle>> reqHandles_;
};

#endif // FAS_MCACHETASKSERVER_H
