#include <iostream>
#include <pthread>
#include <fcntl.h>
#include <unistd.h>
#include "banco.hpp"

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    pthread_t tr_i, tr_u, tr_d, tr_s;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    const char* fifoPath = "/tmp/fifo_banco";
    mkfifo(fifoPath, 0666);
    char buffer[100];

    while(true){
        int fd = open(fifoPath, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        close(fd);

        cout << "Comando recebido do cliente: " << buffer << endl;
    }
}