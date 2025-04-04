#include <iostream>

using namespace std;

int main(){
    const char* fifoPath = "/tmp/fifo_banco";
    char opcao = '0';

    while(true){
        cout << 'Digite um numero: ' << endl;
        cin >> opcao;

        int fd = open(fifoPath, O_WRONLY);
        write(fd, &opcao, sizeof(opcao));
        close(fd);

        cout << "Comando enviado para o servidor: " << opcao << endl;
    }
}