#ifndef FAS_MCACHETASKHANDLE_H
#define FAS_MCACHETASKHANDLE_H
#include <Timestamp.h>
#include <TcpConnection.h>
#include <Socket.h>
#include <NetAddress.h>
#include <Handle.h>
#include <Buffer.h>
#include "mcacheTask.h"
#include "mdmtypes.h"

class mcacheTaskHandle
{
public:
  mcacheTaskHandle(hashSPtr hash);
  ~mcacheTaskHandle();
  void OnMessageCallback(fas::TcpConnShreadPtr conn, fas::Buffer* buffer, fas::Timestamp time);

  void sendDataToMemcached();
private:
  mcacheTask mTask_;
  hashSPtr hash_;
};

#endif // FAS_MCACHETASKHANDLE_H
