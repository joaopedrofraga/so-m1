#ifndef BANCO_HPP
#define BANCO_HPP
#include <iostream>
#include <string>

using namespace std;

class Data{
    int id;
    string nome;
};

void *db_insert();
void *db_update();
void *db_delete();
void *db_select();
void escreverMensagemParaCliente(const char* mensagem);

bool validarOpcao(char op);
string getMensagemDoServidor();

#endif