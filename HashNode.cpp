#include "HashNode.h"
#include <Log.h>
#include <boost/algorithm/string.hpp>

HashNode::HashNode(MD5 *md5, std::string initName, int nameNum) :
    keys_(),
    initName_(initName),
    nameNum_(nameNum),
    md5_(md5),
    mappedCount_(0) {

    std::string virName;

    for (int i = 0; i < nameNum_; i++) {
        srandom(i * i);
        virName = initName_ + std::to_string(i * random()) + std::to_string(i * random() * random());

        md5_->GenerateMD5(virName.c_str(), virName.length());
        keys_.push_back(md5_->ToULong32());    
		}
    std::vector<std::string> strs;
    boost::split(strs, initName_, boost::is_any_of(":"));
    //bugs
    //if error
    if (strs.size() != 2) {
      LOGGER_ERROR << " HashNode's initName_ error! " << fas::Log::CLRF;
    } else {
        boost::trim(strs[0]);
        ip_ = strs[0];
        boost::trim(strs[1]);
        port_ = static_cast<short>(std::atoi(strs[1].c_str()));
    }
}

const std::vector<HashNode::KeyType>& HashNode::getNodeKeys() const {
    return this->keys_;
}

std::string HashNode::getInitName() const {
    return initName_;
}

void HashNode::increaseMappedCount() {
    this->mappedCount_++;
}

unsigned long long HashNode::getMappedCount() const {
    return this->mappedCount_;
}


std::string HashNode::getIp() const {
  return this->ip_;
}

short HashNode::getPort() const {
  return this->port_;
}
