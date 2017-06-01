#include "mdmInfoLoader.h"
#include <json/json.h>
#include <fstream>
#include <Log.h>

mdmInfoLoader::mdmInfoLoader(const std::string& infofile) :
  infofile_(infofile),
  mdmInfo_(),
  HashAddrMgrInfo_(),
  infos_() {

  infos_["mdmInfo"] = &mdmInfo_;
  infos_["HashAddrMgrInfo"] = &HashAddrMgrInfo_;
}


bool mdmInfoLoader::loadInfo() {
  std::ifstream in;

  in.open(infofile_, std::ios_base::in);

  if (!in.is_open()) {
    LOGGER_ERROR << " Open info file " << infofile_ << " error!" << fas::Log::CLRF;
    return false;
  }

  Json::Reader jsonReader;
  Json::Value root;

  if (!jsonReader.parse(in, root)) {
    LOGGER_ERROR << " Parse info file " << infofile_ << " error!" << fas::Log::CLRF;
    return false;
  }

  if (root.isMember("mdmInfo")) {
    mdmInfo_["PollInCmdHandleTimeOut"] = root["mdmInfo"]["PollInCmdHandleTimeOut"].asString();
    mdmInfo_["mdmServerIp"] = root["mdmInfo"]["mdmServerIp"].asString();
    mdmInfo_["mdmServerPort"] = root["mdmInfo"]["mdmServerPort"].asString();
    mdmInfo_["mdmServerThreadNum"] = root["mdmInfo"]["mdmServerThreadNum"].asString();
    mdmInfo_["HashVirtualNode"] = root["mdmInfo"]["HashVirtualNode"].asString();
  } else {
    LOGGER_ERROR << " can not find mdminfo!" << fas::Log::CLRF;
  }

  if (root.isMember("HashAddrMgrInfo")) {
    HashAddrMgrInfo_["master"] = root["HashAddrMgrInfo"]["master"].asString();
    HashAddrMgrInfo_["slave"] = root["HashAddrMgrInfo"]["slave"].asString();
  } else {
    LOGGER_ERROR << " can not find HashAddrMgrInfo!" << fas::Log::CLRF;
  }

  return true;
}

std::string mdmInfoLoader::getValue(const std::string& root, const std::string& key) const {
  std::string value = "";

  auto info = infos_.find(root);
  if (info != infos_.end()) {
    auto viter = info->second->find(key);
    if (viter != info->second->end()) {
      value = viter->second;
    }
  }

  return value;
}

std::string mdmInfoLoader::getmdmInfoValue(const std::string& key) const {
  return getValue("mdmInfo", key);
}

std::string mdmInfoLoader::getHashAddrMgrInfoValue(const std::string& key) const {
  return getValue("HashAddrMgrInfo", key);
}
