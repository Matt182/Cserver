#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PORT_NUM 7995

int main(int argc, char *argv[])
{
	int portn, sockfd, newsockfd, clilen, n;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portn = 7995;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portn);
	serv_addr.sin_addr.s_addr = INADDR_ANY;	
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}
	
	fprintf(stderr, "server started on %s\n", serv_addr.sin_addr.s_addr);
	if (listen(sockfd,5) < 0) {
		perror("error on listen");
		exit(1);
	}
	while(1) {
		int addrlen;
		bzero((char *) &cli_addr, sizeof(cli_addr));
		addrlen = sizeof(cli_addr);
		if (newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &addrlen) < 0) {
			perror("Ошибка accept");
			exit(1);
		}
		while (n = read(newsockfd, buffer, sizeof(buffer))!=0) {
			write(newsockfd, buffer, sizeof(buffer));
		}
		close(newsockfd);
		close(sockfd);
		exit(0);
	}
}

