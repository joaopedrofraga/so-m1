#include <iostream>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <list>
#include "banco.hpp"

using namespace std;

list<Data> bancoDeDados;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    pthread_t tr_i, tr_u, tr_d, tr_s;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    const char* fifoOpcao = "/tmp/fifo_opcao_menu";
    const char* fifoInsert = "/tmp/fifo_insert_registro";
    const char* fifoUpdate = "/tmp/fifo_update_registro";
    const char* fifoDelete = "/tmp/fifo_delete_registro";
    const char* fifoSelect = "/tmp/fifo_select_registro";
    const char* fifoResposta = "/tmp/fifo_server_message";

    mkfifo(fifoOpcao, 0666);
    mkfifo(fifoInsert, 0666);
    mkfifo(fifoUpdate, 0666);
    mkfifo(fifoDelete, 0666);
    mkfifo(fifoSelect, 0666);
    mkfifo(fifoResposta, 0666);

    char buffer[100];

    while(true){
        int fd = open(fifoOpcao, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        close(fd);
        char opcao = buffer[0];

        switch(opcao){
            case '1':
                pthread_create(&tr_i, &attr, db_insert, NULL);
                pthread_join(tr_i, NULL); 
                escreverMensagemParaCliente("\nInserido com sucesso!");
                break;
            case '2':
                pthread_create(&tr_u, &attr, db_update, NULL);
                pthread_join(tr_u, NULL);
                escreverMensagemParaCliente("Atualizado com sucesso!");
                break;
            case '3':
                pthread_create(&tr_d, &attr, db_delete, NULL);
                pthread_join(tr_d, NULL);
                escreverMensagemParaCliente("Deletado com sucesso!");
                break;
            case '4':
                pthread_create(&tr_s, &attr, db_select, NULL);
                pthread_join(tr_s, NULL);
                escreverMensagemParaCliente("Selecionado com sucesso!");
                break;
            default:
                escreverMensagemParaCliente("ERRO AO PROCESSAR!");
        }
    }
}

void escreverMensagemParaCliente(const char* mensagem){
    int fd = open("/tmp/fifo_server_message", O_WRONLY);
    write(fd, mensagem, strlen(mensagem) + 1); 
    close(fd);
}

void *db_insert(void *param){
    int fd = open("/tmp/fifo_insert_registro", O_RDONLY);
    char buffer[100] = {0}; 
    read(fd, buffer, sizeof(buffer));
    close(fd);

    cout << "Registro recebido para inserir: " << buffer << endl;

    pthread_mutex_lock(&mutex);
    // NAO ESQUECER DE COLOCAR AQUI A LOGICA
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *db_update(void *param){
    int fd = open("/tmp/fifo_update_registro", O_RDONLY);
    char buffer[100] = {0}; 
    read(fd, buffer, sizeof(buffer));
    close(fd);

    cout << "Registro recebido para atualizar: " << buffer << endl;

    pthread_mutex_lock(&mutex);
    // NAO ESQUECER DE COLOCAR AQUI A LOGICA
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *db_delete(void *param){
    int fd = open("/tmp/fifo_delete_registro", O_RDONLY);
    char buffer[100] = {0}; 
    read(fd, buffer, sizeof(buffer));
    close(fd);

    cout << "Registro recebido para deletar: " << buffer << endl;

    pthread_mutex_lock(&mutex);
    // NAO ESQUECER DE COLOCAR AQUI A LOGICA
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *db_select(void *param){
    int fd = open("/tmp/fifo_select_registro", O_RDONLY);
    char buffer[100] = {0}; 
    read(fd, buffer, sizeof(buffer));
    close(fd);

    cout << "Registro recebido para selecionar: " << buffer << endl;

    pthread_mutex_lock(&mutex);
    // NAO ESQUECER DE COLOCAR AQUI A LOGICA
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}