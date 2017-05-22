#ifndef FAS_MCACHETASKHANDLE_H
#define FAS_MCACHETASKHANDLE_H
#include <Timestamp.h>
#include <TcpConnection.h>
#include <Buffer.h>

class mcacheTaskHandle
{
public:
  mcacheTaskHandle();
  ~mcacheTaskHandle();
  void OnMessageCallback(fas::TcpConnection *conn, fas::Buffer* buffer, fas::Timestamp time);
};

#endif // FAS_MCACHETASKHANDLE_H
