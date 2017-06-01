#ifndef FAS_MCACHETASK_H
#define FAS_MCACHETASK_H
#include <Buffer.h>
#include "mdmtypes.h"
#include <Socket.h>
#include "memcachedProtocol.h"
#include <Types.h>

class mcacheTask
{
public:
  enum TaskState {
    BAD,     //TcpConnection will be closed!
    BEGIN_NEW_TASK,
    PARSE_PROTOCOL,
    BEGIN_HANDLE_CMD,
    WAIT_ENOUGH_DATA,
    GET_ALL_DATA,
  };
  mcacheTask(hashSPtr hash);

  void renew();

  TaskState getState() const;
  void setState(TaskState state);

  int getHasReadBytes() const;
  void add2HasReadBytes(int bytes);

  bool handleStrogeCmd(fas::TcpConnShreadPtr conn, fas::Buffer *buffer);
  bool handleRetriveCmd(fas::TcpConnShreadPtr conn, fas::Buffer *buffer);
  bool handleDeleteCmd(fas::TcpConnShreadPtr conn, fas::Buffer *buffer);
  bool handleIncrDecrCmd(fas::TcpConnShreadPtr conn, fas::Buffer *buffer);
  bool handleOtherCmd(fas::TcpConnShreadPtr conn, fas::Buffer *buffer);

  bool getSocketFromKey(const string& key, fas::Socket& sock);
  std::string getMethod() const;
  std::string getKey() const;
  std::string getFlag() const;
  std::string getExptime() const;
  int getBytes() const;

  bool taskCommunition(fas::TcpConnShreadPtr conn, fas::Buffer *buffer);
private:
  TaskState taskState_; //链接应该被关闭

  std::string head_;
  std::vector<std::string> headerItems_;


  std::string method_;
  std::string key_;
  std::vector<std::string> keys_;
  std::string flag_;
  std::string exptime_;
  int bytes_;
  std::string cas_unique_;
  std::string noreply_;

  int hasReadBytes_;

  hashSPtr hash_;
  serNodeSptr server_;

  memcachedProtocol protocol_;
};

int writeSizeBytes2NoBlockSock(int sock, const char *buf, int size);
int readUntilStrWithEnd(int sock, std::string& str, std::string end);

#endif // FAS_MCACHETASK_H
