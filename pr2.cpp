#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

char buff[5];

void checkValue(char *buff) //проверка полученных данных
{
    int value = atoi(buff);
    if(value>99 && value%32 == 0)
    {
        cout <<"Correct data: "<< value << endl;
    } 
    else
    { 
        cout <<"Error! Incorrect data"<< endl;
    }
}

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    listen(listener, 1);
    while (true)
    {    
        
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
        
        while (true)
        {
            int bytes=recv(sock, buff, sizeof(buff),0);
            if(bytes<=0)
            {
                break;
            }   
            checkValue(buff);

        }
        close(sock);
        
        
    }
    return 0;
}
