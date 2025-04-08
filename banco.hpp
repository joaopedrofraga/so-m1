#ifndef BANCO_HPP
#define BANCO_HPP
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Data{
public:
    int id;
    string nome;
};

void *db_insert(void *param);
void *db_update(void *param);
void *db_delete(void *param);
void *db_select(void *param);
void escreverMensagemParaCliente(const char* mensagem);
vector<string> getPartes(char* buffer[100]);

bool validarOpcao(char op);
string getMensagemDoServidor();
void insert();
void update();
void remove();
void select();

#endif