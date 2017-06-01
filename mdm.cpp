#include <EventLoop.h>
#include <NetAddress.h>
#include "mcacheTaskServer.h"
#include "ConsistencyHash.h"
#include "mdmInfoLoader.h"
#include <Log.h>
#include <iostream>
#include <SigIgnore.h>

using namespace std;
using namespace fas;

fas::SigIgnore sigignore;

int main()
{

  mdmInfoLoader infoloader("./info/mdm.info");

  if (!infoloader.loadInfo()) {
    LOGGER_ERROR << "Load info file Error!" << fas::Log::CLRF;
    return -1;
  }
  EventLoop *loop = new EventLoop;
  hashSPtr hash(new ConsistencyHash(std::atoi(infoloader.getmdmInfoValue("HashVirtualNode").c_str())));

  hash->addHashNodesFromString("127.0.0.1:11211");
  hash->addHashNodesFromString("127.0.0.1:11311");
  hash->addHashNodesFromString("127.0.0.1:11411");
  hash->addHashNodesFromString("127.0.0.1:11511");


////  hash->ShowNodeMsg();

////  for (int i = 0; i <= 1000; i++) {
////    hash->getMappingNodeFromKeyString("key" + i);
////  }

////  hash->ShowMappingStatisticMsg();

  mcacheTaskServer *server = new mcacheTaskServer(hash, loop, NetAddress(AF_INET,\
                 std::atoi(infoloader.getmdmInfoValue("mdmServerPort").c_str()), \
                 infoloader.getmdmInfoValue("mdmServerIp").c_str()), \
                 std::atoi(infoloader.getmdmInfoValue("mdmServerThreadNum").c_str()));

  server->start();

  loop->loop();
  return 0;
}

