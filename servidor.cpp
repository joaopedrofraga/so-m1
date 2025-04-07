#include <iostream>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
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
        cout << "Comando recebido: " << buffer << endl;
        char opcao = buffer[0];

        switch(opcao){
            case '1':
                //pthread_create(&tr_i, &attr, inserir, (void*)buffer);
                escreverMensagemParaCliente("Inserido com sucesso!");
                break;
            case '2':
                //pthread_create(&tr_u, &attr, atualizar, (void*)buffer);
                escreverMensagemParaCliente("Atualizado com sucesso!");
                break;
            case '3':
                //pthread_create(&tr_d, &attr, deletar, (void*)buffer);
                escreverMensagemParaCliente("Deletado com sucesso!");
                break;
            case '4':
                //pthread_create(&tr_s, &attr, selecionar, (void*)buffer);
                escreverMensagemParaCliente("Selecionado com sucesso!");
                break;
            default:
                escreverMensagemParaCliente("ERRO AO PROCESSAR!");
        }
    }
}

void escreverMensagemParaCliente(const char* mensagem){
    int fd = open("/tmp/fifo_cliente", O_WRONLY);
    write(fd, mensagem, strlen(mensagem) + 1); // CORRETO
    close(fd);
}