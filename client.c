#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>

#define PORT_NUM 7995

int main(int argc, char *argv[])
{
	printf("strating \n");
	int portno, sockfd, n;
	struct hostent *hp;
  	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256] = "Hello from fucking server.\0";
	char recbuf[256];
	portno = 7995;
	printf("socket below\n");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("cant create client socket");
		exit(1);
	}
	printf("gethostby name below");
	if ((hp = gethostbyname(argv[1])) == 0) {
		perror("Ошибка gethostbyname9() блять");
		exit(1);
	}
	printf("bzero below\n");
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	printf("bcopy below\n");
	bcopy((char *)hp->h_addr,
	     (char *)&serv_addr.sin_addr.s_addr,
	      hp->h_length);
	printf("htons is %d\n", htons(7995));
	printf("htons below\n");
	serv_addr.sin_port = htons(7995);
	printf("connection bellow.\n");
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("Unable to connect");
		exit(1);
	}
	printf("writing below\n");
	write(sockfd, buffer, sizeof(buffer));
	printf("reding below.\n");
	if (read(sockfd, recbuf, sizeof(recbuf)) < 0) {
		perror("error reading from socket");
		exit(1);
	}
	recbuf[255] = '\0';
	printf("shoul be recieved\n");
	printf("Message recieved: %s\n", recbuf);
	
	close(sockfd);
	exit(0);

}
