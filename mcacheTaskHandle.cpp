#include "mcacheTaskHandle.h"
#include "ConsistencyHash.h"
#include "HashNode.h"
#include <boost/core/ignore_unused.hpp>
#include <EventLoop.h>
#include <Log.h>

mcacheTaskHandle::mcacheTaskHandle(hashSPtr hash) :
  mTask_(hash),
  hash_(hash) {

}

void mcacheTaskHandle::OnMessageCallback(fas::TcpConnShreadPtr conn, fas::Buffer* buffer, fas::Timestamp time) {
  boost::ignore_unused(conn, time);

  if (!mTask_.taskCommunition(conn, buffer)) {
    if (mTask_.getState() == mcacheTask::TaskState::BAD) {
       conn->shutdown();
     }
     return;
  }
}

void mcacheTaskHandle::sendDataToMemcached() {

}

mcacheTaskHandle::~mcacheTaskHandle() {

}

