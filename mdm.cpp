#include <EventLoop.h>
#include <NetAddress.h>
#include "mcacheTaskServer.h"
#include "ConsistencyHash.h"

using namespace std;
using namespace fas;

int main()
{
  EventLoop *loop = new EventLoop;
  hashSPtr hash(new ConsistencyHash(5));

  hash->addHashNodesFromString("127.0.0.1:11211");
  hash->addHashNodesFromString("127.0.0.1:11311");
  hash->addHashNodesFromString("127.0.0.1:11411");
  hash->addHashNodesFromString("127.0.0.1:11511");


//  hash->ShowNodeMsg();

//  for (int i = 0; i <= 1000; i++) {
//    hash->getMappingNodeFromKeyString("key" + i);
//  }

//  hash->ShowMappingStatisticMsg();

  mcacheTaskServer *server = new mcacheTaskServer(hash, loop, NetAddress(AF_INET, 9999, "127.0.0.1"), 1);
  server->start();

  loop->loop();
  return 0;
}

