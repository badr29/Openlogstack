#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
int main(int argc,char* argv[]){
  int clientSocket, portNum, nBytes;
  int cnt=1, n=2;
  char buffer[2048] = {0};
  struct sockaddr_in serverAddr;
  time_t now;
  socklen_t addr_size;
  int flags;
int yes = 1;
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
  flags = fcntl(clientSocket,F_GETFL);
  flags |= O_NONBLOCK;
  if ( (setsockopt (clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( yes )) < 0))
  {
    perror("Reusing ADDR failed");
  }
  serverAddr.sin_family = AF_INET;
  printf("port : %s", argv[1]);
  printf("port : %s", argv[2]);
  u_short port1 = htons(atoi(argv[1]));
  u_short port2 = htons(atoi(argv[2]));
  serverAddr.sin_addr.s_addr = inet_addr("172.18.0.5");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;
//snprintf(buffer, 2048, "PROGRAM:1 PRIORITY:notice MESSAGE:2018-08-01T19:29:59.116521+00:00 ip-10-176-1-243 ubuntu - - [timeQuality tzKnown=1 isSynced=1 syncAccuracy=995000] 2018 11:35:42,/Common/HA,/Common/Allow_HA,Permit_HA,MaheshC1,100.64.255.2,63298,100.64.255.1,443,Accept decisively,,,,,,/Common/HA,Unknown,Unknown ISODATE:%s HOST:10.176.1.243 FACILITY:user @timestamp:%s", ctime(&now), ctime(&now));
snprintf(buffer, 2048, "03 2018 12:24:36,/ENT/ENT,/ENT/Pioneer_Policy,LAN-ISP_Permit,TCP,192.168.200.184,58541,34.224.254.35,443,Accept decisively,,47.21.147.131,28481,34.224.254.35,443,/ENT/LAN,Unknown,US/NEW111");
/*  while(cnt<=n){*/
    printf("\n starting with %d", cnt);
    time(&now);
    int portChoice = 1;    
    while(1) {
      nBytes = strlen(buffer) + 1;
      switch(portChoice) {
        case 1:
          serverAddr.sin_port = port1;
          portChoice = 2;
          break;
        case 2:
          serverAddr.sin_port = port2;
          portChoice = 1;
          break;
      }
      sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
      cnt++;
      if( (cnt % 1000000) == 0) {
        time_t uptilNow;
        time(&uptilNow);
        double diff = difftime(uptilNow, now);
        printf("\nsent: %d, elapsed: %f, throughput: %f", cnt, diff, (cnt/diff));
      }
/*    usleep(50);*/
    }
  return 0;
}

