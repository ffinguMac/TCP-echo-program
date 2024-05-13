#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    int c_socket; // 클라이언트 소켓
    struct sockaddr_in serv_addr; // 서버 주소 구조체
    char msg[1024]; // 메시지 송수신을 위한 버퍼

    // 소켓 생성
    c_socket = socket(PF_INET, SOCK_STREAM, 0); 

    // 서버 주소 구조체 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 서버 IP 주소 설정
    serv_addr.sin_port = htons(atoi(argv[2])); // 서버 포트 번호 설정

    // 서버에 연결
    connect(c_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    while(1) {
        printf("send msg: ");
        fgets(msg, sizeof(msg), stdin);
        send(c_socket, msg, sizeof(msg), 0); // 서버로 메시지 전송
        recv(c_socket, msg, sizeof(msg), 0); // 서버로부터 메시지 수신
        printf("receive msg: %s", msg);
        memset(msg, 0, sizeof(msg));
    }

    close(c_socket); // 소켓 닫기
    return 0;
}
