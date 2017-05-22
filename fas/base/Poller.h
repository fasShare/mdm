#ifndef FAS_EVENTSPOLLER_H
#define FAS_EVENTSPOLLER_H
#include <vector>


#include <Timestamp.h>


#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

namespace fas {

class Events;
class Epoll;
class Poll;

/*!
 * \brief The Poller class
 * The Poller class difine the common interface between EventLoop and Epoll or Poll class
 * use those interface, we can add, del and mol IO events wait on epoll or poll.
 */
class Poller : boost::noncopyable {
public:
  Poller();
  boost::function<bool (Events* events)> events_add_;
  boost::function<bool (Events* events)> events_mod_;
  boost::function<bool (Events* events)> events_del_;
  boost::function<Timestamp (std::vector<Events> &events, int timeout)> loop_;
};

#define DEFAULT_POLLER Epoll

}
#endif // FAS_EVENTSPOLLER_H
