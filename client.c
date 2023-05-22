#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define ROW1 "POST /api/1.0/pass/3518 HTTP/1.1"
#define ROW2 "HOST: 130.229.136.140"
#define ROW3 "Content-Type: application/json"
#define ROW4 "Accept: application/json"
#define ROW5 ""
#define ROW6 "{name : Filip}"

int main(int argc, char **argv) {

	WSADATA wsa;
	printf("\nInitialising Winsock...");

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised. ");
	printf("Web Client 0.1\n");

	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) return 1;

  printf("*** SOCKET Established...\n");
   
  struct sockaddr_in addr = { 0 };
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("130.229.136.140");
  addr.sin_port = htons(8080);

	if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1) return 2;

	printf("*** CONNECT Success...\n");

  char buf[1024];

	sprintf(buf, "%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n", ROW1, ROW2, ROW3, ROW4, ROW5, ROW6);
  printf("*** SENDING \n[%s]\n",buf);
  size_t len = strlen(buf);
	
	send(sock, buf, len, 0);
	
	printf("*** SEND Success...\n");
	
	len = recv(sock, buf, sizeof(buf), 0);
	buf[len] = '\0';
	if (len) printf("***[%s](%d)\n", buf, (int)len);
	
	closesocket(sock);
	WSACleanup();

	printf("*** CONNECTION CLOSED!\n");	
	printf("*** DONE...\n");

}