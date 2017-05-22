#include "mcacheTaskServer.h"
#include <EventLoop.h>
#include <boost/bind.hpp>
#include <Log.h>

mcacheTaskServer::mcacheTaskServer(fas::EventLoop* loop,
                                   const fas::NetAddress& addr,
                                   int threadNum) :
  loop_(loop),
  tcpSer_(loop_, addr, threadNum),
  reqHandles_() {
  tcpSer_.setOnConnectionCallBack(boost::bind(&mcacheTaskServer::OnNewConnection, this, _1));
  tcpSer_.setOnConnRemovedCallBack(boost::bind(&mcacheTaskServer::OnConnectionRemoved, this, _1));
}

void mcacheTaskServer::OnNewConnection(fas::TcpConnShreadPtr conn) {
  LOGGER_TRACE << fas::Log::CLRF;
  // req must not be shared_ptr, or conn will be referenced by itself.
  // you can analyse it by youself seriously.
  std::shared_ptr<mcacheTaskHandle> reqHandle = std::make_shared<mcacheTaskHandle>();

  conn->setOnMessageCallBack(boost::bind(&mcacheTaskHandle::OnMessageCallback, reqHandle, _1, _2, _3));
  this->reqHandles_[fas::connkey_t(conn->getConnfd(), conn.get())] = reqHandle;
}

void mcacheTaskServer::OnConnectionRemoved(fas::connkey_t key) {
  LOGGER_TRACE  << fas::Log::CLRF;
  loop_->assertInOwnerThread();
  if (this->reqHandles_.find(key) == this->reqHandles_.end()) {
      return;
  }

  int ret = this->reqHandles_.erase(key);
  assert(ret == 1);
  LOGGER_TRACE << fas::Log::CLRF;
}

bool mcacheTaskServer::start() {
  return tcpSer_.start();
}

mcacheTaskServer::~mcacheTaskServer() {

}
