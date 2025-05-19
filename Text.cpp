#include<iostream>
#include<locale.h>
using namespace std;


int cadastro_de_produto(){
    int password;
    cout << "Digite a senha para acessar o cadastro de produtos: ";
    cin >> password;
    if (password == 2025){
        // . . . Toda funcionalidade do cadastro de produto
    }
    else{ 
        cout << "Senha incorreta!"<<endl;
    }
    return 1;
}

// Projeto de C02 - Loja de Instrumentos Heart's Music
int main(){
    //  Atrbuindo as caracteres portugueses como os acentos
    setlocale(LC_ALL, "Portuguese");
    // Declaração das variáveis
    int op;

    while(op!=6){
        // Menu principal da Loja
    cout << "--------------------------------------"<<endl;
    cout << "    ♫ Bem-vindo ao Heart's Music ♫"<<endl;
    cout << "--------------------------------------"<<endl;
    cout << "Escolha uma opção que deseja fazer:"<<endl<<endl;
    cout << "1 - Cadastrar um produto"<<endl;
    cout << "2 - Listar todos os produtos"<<endl;
    cout << "4 - Realizar venda(s)"<<endl;
    cout << "5 - Atualizar dados de um produto"<<endl;
    cout << "6 - Sair do programa"<<endl;
    cout << "7 - Créditos"<<endl<<endl;
    cout << "Por favor, escolha uma opção: ";
    
    // Entrada na opção
    cin >> op;
    
    // Função de opções do menu
    switch(op){
        case 1:
            cadastro_de_produto();
            break;
        case 2:
            cout << "Oops! O sistema está ainda em desenvolvimento!"<<endl<<endl;
            break;
        case 3:
            cout << "Oops! O sistema está ainda em desenvolvimento!"<<endl<<endl;
            break;
        case 4:
            cout << "Oops! O sistema está ainda em desenvolvimento!"<<endl<<endl;
            break;
        case 5:
            cout << "Oops! O sistema está ainda em desenvolvimento!"<<endl<<endl;
            break;
        case 6:
            cout << "Saindo do programa! Obrigado por utilizá-lo!"<<endl<<endl;
            return 0;
            break;
        case 7:
            cout << "--------------------------------------"<<endl;
            cout << "Membros da equipe:"<<endl;
            cout << "Diego Augusto Pereira Silva - 9870"<<endl;
            cout << "Pedro Costa Tito - 1111"<<endl;
            cout << "Felipe Vitor Pereira Dias - 9872"<<endl;
            cout << "Kauan Gabriel Ribeiro - 859";
            return 0;
            break;
        }
    }    
    return 0;
}