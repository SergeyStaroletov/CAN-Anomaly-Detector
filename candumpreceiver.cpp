#include "candumpreceiver.h"

#include <ctype.h>
#include <errno.h>
#include <libgen.h>
//#include <linux/can.h>
//#include <linux/can/raw.h>
#include <net/if.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

void CanDumpReceiver::setup() {
  // ported from candump
  /*
fd_set rdfs;
char *ptr;
struct sockaddr_can addr;
int s;
struct canfd_frame frame;
struct iovec iov;
struct msghdr msg;
struct ifreq ifr;
int nbytes;
int maxdlen = 8;
char ctrlmsg[CMSG_SPACE(sizeof(struct timeval) + 3 * sizeof(struct timespec) +
                        sizeof(__u32))];
const int canfd_on = 1;
int ret;
bool running = true;
// runs in a thread
ptr = "can0";  // fixme
nbytes = strlen(ptr);
s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
if (s < 0) {
  perror("socket");
  return;
}
addr.can_family = AF_CAN;
memset(&ifr.ifr_name, 0, sizeof(ifr.ifr_name));
strncpy(ifr.ifr_name, ptr, nbytes);
if (strcmp(ANYDEV, ifr.ifr_name)) {
  if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {
    perror("SIOCGIFINDEX");
    exit(1);
  }
  addr.can_ifindex = ifr.ifr_ifindex;
} else
  addr.can_ifindex = 0;
setsockopt(s, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &canfd_on, sizeof(canfd_on));
if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
  perror("bind");
  return;
}
iov.iov_base = &frame;
msg.msg_name = &addr;
msg.msg_iov = &iov;
msg.msg_iovlen = 1;
msg.msg_control = &ctrlmsg;
int len = (frame.len > maxdlen) ? maxdlen : frame.len;
*/
}

CanData CanDumpReceiver::askForNewData() {
  CanData can;
  /*
  while (running) {
  FD_ZERO(&rdfs);
  FD_SET(s, &rdfs);
  if ((ret = select(s + 1, &rdfs, NULL, NULL, 0)) <= 0) {
    // perror("select");
    running = 0;
    continue;
  }
  if (FD_ISSET(s, &rdfs)) {
    iov.iov_len = sizeof(frame);
    msg.msg_namelen = sizeof(addr);
    msg.msg_controllen = sizeof(ctrlmsg);
    msg.msg_flags = 0;

    readWriteLock->lock();
    nbytes = recvmsg(s, &msg, 0);
    readWriteLock->unlock();

    if (nbytes < 0) {
      // if ((errno == ENETDOWN) && !down_causes_exit) {
      continue;
      //}
    }
    if ((size_t)nbytes == CAN_MTU)
      maxdlen = CAN_MAX_DLEN;
    else if ((size_t)nbytes == CANFD_MTU)
      maxdlen = CANFD_MAX_DLEN;

    if (frame.can_id & CAN_ERR_FLAG) continue;

    // check the RTD flag

    if (frame.can_id & CAN_RTR_FLAG) continue;

    // store the result frame
    //   printf("canid=%d\n", frame.can_id);
    can.push_back(frame.can_id);

    for (int i = 0; i < frame.len; i++) {
      can.push_back(frame.data[i]);
    }
    break;
  }
  */
  return can;
}

CanDumpReceiver::~CanDumpReceiver() = default;
