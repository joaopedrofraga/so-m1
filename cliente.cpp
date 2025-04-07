#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include "banco.hpp"

using namespace std;

int main(){
    const char* fifoPath = "/tmp/fifo_banco";
    mkfifo(fifoPath, 0666);
    char opcao = '0';

    cout << "Cliente iniciado!" << endl;

    while(true){
        cout << "\nEscolha uma opção:" << endl;
        cout << "1 - Inserir" << endl;
        cout << "2 - Atualizar" << endl;
        cout << "3 - Deletar" << endl;
        cout << "4 - Selecionar" << endl;
        cout << "5 - Sair\n" << endl;
        cout << "SELECIONADO: ";
        cin >> opcao;

       if(validarOpcao(opcao)){
            int fd = open(fifoPath, O_WRONLY);
            write(fd, &opcao, sizeof(opcao));
            close(fd);

            cout << getMensagemDoServidor() << endl;
       }
    }
}

bool validarOpcao(char op){
    if(op == '5'){
        cout << "\n\nSaindo do cliente..." << endl;
        exit(0);
    }
    if(op < '1' || op > '4'){
        cout << "\n\nOpção inválida! Tente novamente." << endl;
        return false;
    }
    return true;
}

string getMensagemDoServidor(){
    int fd = open("/tmp/fifo_cliente", O_RDONLY);
    char buffer[100] = {0}; // zerar buffer
    read(fd, buffer, sizeof(buffer));
    close(fd);
    return string(buffer);
}