#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct data
{
  char tag[20];
  int a;
  int b;
};

#define SK "aaaz"

char *socket_path = "/tmp/echo";

int main(int argc, char **argv)
{
  struct sockaddr_un addr;
  char buf[100];
  int fd, rc;
  int clilen;

  if (argc > 1)
    socket_path = argv[1];

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
  {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  if (*socket_path == '\0')
  {
    *addr.sun_path = '\0';
    strncpy(addr.sun_path + 1, socket_path + 1, sizeof(addr.sun_path) - 2);
  }
  else
  {
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
  }

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
    perror("connect error");
    exit(-1);
  }
  clilen = sizeof(addr);
  struct data d;

  strcpy(d.tag, "sample");
  d.a = 4;
  d.b = 12;
  // if (write(fd, &d, sizeof(d)) < 0)
  //   perror("writing on stream socket");

  if (sendto(fd, (void *)&d, sizeof(d), 0,
             (struct sockaddr *)&addr, clilen) < 0)
  {
    perror("send error : ");
    exit(0);
  }

  close(fd);

  return 0;
}