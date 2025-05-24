#include<iostream>
#include<locale.h>
using namespace std;

// Estrutura que representa um produto
struct Produto {
    string nome;
    float preco;
    int quantidade;
};

// Função para cadastrar um produto
int cadastro_de_produto(Produto produtos[], int &total) {
    int password;
    cout << "Digite a senha para acessar o cadastro de produtos: ";
    cin >> password;
    
    if (password == 0) {
        Produto novo;

        cin.ignore(); // Limpa o buffer
        cout << "Nome do produto: ";
        getline(cin, novo.nome);
        
        cout << "Preço do produto: ";
        cin >> novo.preco;

        cout << "Quantidade em estoque: ";
        cin >> novo.quantidade;

        produtos[total] = novo;
        total++;

        cout << "Produto cadastrado com sucesso!" << endl;
    } else {
        cout << "Senha incorreta!" << endl;
    }

    return 1;
}

// Função para listar todos os produtos
void listar_produtos(Produto produtos[], int total) {
    if (total == 0) {
        cout << "Nenhum produto cadastrado ainda!" << endl;
        return;
    }

    cout << "\n=== Lista de Produtos ===" << endl;
    for (int i = 0; i < total; i++) {
        cout << i + 1 << " - Nome: " << produtos[i].nome
             << ", Preço: R$" << produtos[i].preco
             << ", Quantidade: " << produtos[i].quantidade << endl;
    }
}

// Função principal
int main() {
    // Ativa os acentos
    setlocale(LC_ALL, "Portuguese");

    // Variáveis principais
    Produto produtos[100]; // até 100 produtos
    int total_produtos = 0;
    int op = 0;

    // Loop do menu principal
    while (op != 6) {
        cout << "--------------------------------------" << endl;
        cout << "    ♫ Bem-vindo ao Heart's Music ♫" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Escolha uma opção que deseja fazer:" << endl << endl;
        cout << "1 - Cadastrar um produto" << endl;
        cout << "2 - Listar todos os produtos" << endl;
        cout << "3 - [Função em desenvolvimento]" << endl;
        cout << "4 - Realizar venda(s)" << endl;
        cout << "5 - Atualizar dados de um produto" << endl;
        cout << "6 - Sair do programa" << endl;
        cout << "7 - Créditos" << endl << endl;
        cout << "Por favor, escolha uma opção: ";
        cin >> op;
        cout << endl;

        switch (op) {
            case 1:
                cadastro_de_produto(produtos, total_produtos);
                break;
            case 2:
                listar_produtos(produtos, total_produtos);
                break;
            case 3:
                cout << "Oops! O sistema está ainda em desenvolvimento!" << endl << endl;
                break;
            case 4:
                cout << "Oops! O sistema está ainda em desenvolvimento!" << endl << endl;
                break;
            case 5:
                cout << "Oops! O sistema está ainda em desenvolvimento!" << endl << endl;
                break;
            case 6:
                cout << "Saindo do programa! Obrigado por utilizá-lo!" << endl << endl;
                return 0;
            case 7:
                cout << "--------------------------------------" << endl;
                cout << "Membros da equipe:" << endl;
                cout << "Diego Augusto Pereira Silva - 9870" << endl;
                cout << "Pedro Costa Tito - 1111" << endl;
                cout << "Felipe Vitor Pereira Dias - 9872" << endl;
                cout << "Kauan Gabriel Ribeiro - 859" << endl << endl;
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }
        
    }
    return 0;
}