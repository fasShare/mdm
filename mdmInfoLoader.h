#ifndef FAS_INFOLOADER_H
#define FAS_INFOLOADER_H
#include <json/json.h>
#include <string>
#include <map>
#include <set>

class mdmInfoLoader
{
public:
  mdmInfoLoader(const std::string& infofile);
  bool loadInfo();
  std::string getValue(const std::string& root, const std::string& key) const;
  std::string getmdmInfoValue(const std::string& key) const;
  std::string getHashAddrMgrInfoValue(const std::string& key) const;
public:
  std::string infofile_;
  std::map<std::string, std::string> mdmInfo_;
  std::map<std::string, std::string> HashAddrMgrInfo_;
  std::map<std::string, std::map<std::string, std::string> *> infos_;
};

#endif // FAS_INFOLOADER_H
