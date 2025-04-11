## 📡 Projeto Cliente-Servidor em C++

Este projeto implementa uma aplicação **cliente-servidor** utilizando **C++**, comunicação por **FIFO (Named Pipes)** e controle de concorrência com **threads POSIX (`pthread`)**.

---

## ℹ️ Dados do Projeto

Disciplina de Sistemas Operacionais - UNIVALI <br>
Professor Felipe Viel<br><br>
Alunos:
  - João Fraga
  - Bruno Petroski
  - Gabriel Bortolocci

---

## 🧠 Descrição

O objetivo do projeto é simular a interação entre um cliente e um servidor através de mensagens enviadas por pipes nomeados. O servidor é responsável por escutar mensagens dos clientes, processá-las (como inserção de registros) e retornar uma resposta.

---

## 🛠️ Tecnologias e Ferramentas

- Linguagem: **C++**
- Comunicação: **FIFO (Named Pipes)**
- Concorrência: **pthread**
- Compilador: **g++**
- Plataforma: **Linux/WSL (Windows Subsystem for Linux)**

---

## 🆘 Como Rodar o Projeto

1. Crie os arquivos executáveis usando os comandos: <br>
```g++ servidor.cpp -o <nome_do_arquivo>```<br>
```g++ cliente.cpp -o <nome_do_arquivo>```

2. Execute os arquivos com o comando:<br>
```./<nome_do_arquivo>``` <br><br>

OBS: O segundo passo precisa ser executado em cada um dos terminais.
