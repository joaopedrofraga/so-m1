#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include "banco.hpp"

using namespace std;

int main(){
    const char* fifoPath = "/tmp/fifo_opcao_menu";
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

            if (opcao == '1') insert();
            else if (opcao == '2') update();
            else if (opcao == '3') remove();
            else if (opcao == '4') select();

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
    int fd = open("/tmp/fifo_server_message", O_RDONLY);
    char buffer[10000] = {0}; // zerar buffer
    read(fd, buffer, sizeof(buffer));
    close(fd);
    return string(buffer);
}

void insert(){
    Data dado;
    cout << "Digite o ID: ";
    cin >> dado.id;
    cout << "Digite o nome: ";
    cin >> dado.nome;

    string registro = to_string(dado.id) + ";" + dado.nome;

    const char* fifoPath = "/tmp/fifo_insert_registro";
    int fd = open(fifoPath, O_WRONLY);
    write(fd, registro.c_str(), registro.size() + 1);
    close(fd);
}

void update() {
    string registro;
    char opcao = '0';
    cout << "1 - Atualizar Nome" << endl;
    cout << "2 - Atualizar ID" << endl;
    cout << "Selecionado: ";
    cin >> opcao;

    if (opcao == '1') {
        string id, novoNome;
        cout << "Digite o ID: ";
        cin >> id;
        cout << "Digite o novo nome: ";
        cin >> novoNome;

        registro = "1;" + id + ";" + novoNome;
    } else if (opcao == '2') {
        string nome, novoId;
        cout << "Digite o Nome: ";
        cin >> nome;
        cout << "Digite o novo ID: ";
        cin >> novoId;

        registro = "2;" + novoId + ";" + nome;
    } else {
        cout << "Opção inválida!" << endl;
        return;
    }

    const char* fifoPath = "/tmp/fifo_update_registro";
    int fd = open(fifoPath, O_WRONLY);
    write(fd, registro.c_str(), registro.size() + 1);
    close(fd);
}

void remove(){
    string id;
    cout << "Digite o ID do registro a ser deletado: ";
    cin >> id;

    const char* fifoPath = "/tmp/fifo_delete_registro";
    int fd = open(fifoPath, O_WRONLY);
    write(fd, id.c_str(), id.size() + 1);
    close(fd);
}

void select(){
    string registro;
    char opcao = '0';
    cout << "Selecionando registros..." << endl;
    cout << "1- Selecionar todos os registros" << endl;
    cout << "2- Selecionar registro por ID" << endl;
    cout << "3- Selecionar registro por Nome" << endl;
    cout << "Selecionado: ";
    cin >> opcao;

    if(opcao == '1'){
        cout << "Selecionando todos os registros..." << endl;
        registro = "1;";
    } else if(opcao == '2'){
        string id;
        cout << "Digite o ID: ";
        cin >> id;
        registro = "2;" + id;
    } else if(opcao == '3'){
        string nome;
        cout << "Digite o Nome: ";
        cin >> nome;
        registro = "3;" + nome;
    } else {
        cout << "Opção inválida!" << endl;
        return;
    }

    const char* fifoPath = "/tmp/fifo_select_registro";
    int fd = open(fifoPath, O_WRONLY);
    write(fd, registro.c_str(), registro.size() + 1);
    close(fd);
}