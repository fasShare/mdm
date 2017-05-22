#include "mcacheTaskHandle.h"
#include <boost/core/ignore_unused.hpp>


mcacheTaskHandle::mcacheTaskHandle() {

}

void mcacheTaskHandle::OnMessageCallback(fas::TcpConnection *conn, fas::Buffer* buffer, fas::Timestamp time) {
  boost::ignore_unused(conn, buffer, time);
}

mcacheTaskHandle::~mcacheTaskHandle() {

}

