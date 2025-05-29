#include<iostream>
#include<locale.h>
using namespace std;

// Estrutura que representa um produto
struct Produto {
    char nome[50];        // Nome do produto
    float preco;        // Preço do produto
    int quantidade;     // Quantidade em estoque do produto
};

// Função para cadastrar um produto
int cadastro_de_produto(Produto produtos[], int total) {
    // Verificando a senha administradora para acessar o cadastro de produto
    int password;
    cout << "Digite a senha para acessar o cadastro de produtos: ";
    cin >> password;
    
    // Se a senha for correspondente, o usuário pode cadastrar um novo produto
    if (password == 2025) {
        Produto novo;
        cin.ignore();
        // Entrada no nome do produto.
        cout << "Nome do produto: ";
        cin.getline(novo.nome, 50);

        // Entrada no preço do produto.
        cout << "Preço do produto: ";
        cin >> novo.preco;

        // Entrada na quantidade do produto.
        cout << "Quantidade em estoque: ";
        cin >> novo.quantidade;

        // Inserindo o novo produto no array de produtos
        produtos[total] = novo;
        total++;

        cout << "Produto cadastrado com sucesso!" << endl << endl;;
    } 
    // Se a senha for incorreta, o usuário não pode cadastrar um novo produto, retornando ao menu principal
    else {
        cout << "Senha incorreta!" << endl << endl;
    }
    return total;
}
// Função para listar todos os produtos
void listar_produtos(Produto produtos[], int total) {
    // Verifica se há produtos cadastrados, se não houver, informa ao usuário que não há produtos cadastrados
    if (total == 0) {
        cout << "Nenhum produto cadastrado ainda!" << endl;
        return;
    }
    // Se houver produtos cadastrados, exibe a lista de produtos
    cout << "--------------------------------------" << endl;
    cout << "    Lista de produtos da loja" << endl;
    cout << "--------------------------------------" << endl;
    // Fazendo a leitura de todos os produtos registrados e exibindo suas informações
    for (int i = 0; i < total; i++) {
        cout << i << " - Nome: " << produtos[i].nome<<endl;
        cout << "Preço: R$" << produtos[i].preco<<endl;
        cout << "Quantidade: " << produtos[i].quantidade << endl;
        cout << "--------------------------------------" << endl;
    }
    cout << endl;
}
// Função para editar um produto
int editar_produto(Produto produtos[]) {
    // Verificando a senha administradora para acessar o editor de produto
    int password;
    cout << "Digite a senha para acessar o editor de produtos: ";
    cin >> password;

    // Se a senha for correspondente, o usuário pode editar um produto
    if( password == 2025) {
        int id_produto;
        // Entrada no ID do produto que deseja editar
        cout << "Digite o ID do produto que deseja editar: ";
        cin >> id_produto;

        cout << "Editando produto: " << produtos[id_produto].nome << endl;

        cin.ignore();
        // Entrada no nome do produto
        cout << "Nome do produto: ";
        cin.getline(produtos[id_produto].nome, 50);
    
        // Entrada no preço do produto
        cout << "Preço do produto: ";
        cin >> produtos[id_produto].preco;

        // Entrada na quantidade do produto
        cout << "Quantidade em estoque: ";
        cin >> produtos[id_produto].quantidade;

        cout << "Produto atualizado com sucesso!" << endl;
    }
    else{
        cout << "Senha incorreta!" << endl;
    }
    return 1; 
}
// Função para remover um produto
int remover_produto(Produto produtos[],int total) {
    // Verificando a senha administradora para acessar o removedor de produto
    int password;
    cout << "Digite a senha para acessar o removedor de produtos: ";
    cin >> password;

    // Se a senha for correspondente, o usuário pode remover um produto
    if (password == 2025) {
        int id_produto;
        int confirmacao;

        // Entrada no ID do produto que deseja remover
        cout << "Digite o ID do produto que deseja remover: ";
        cin >> id_produto;

        // Confirmando a remoção do produto
        cout << "Deseja remover o produto " << produtos[id_produto].nome << "? (1 - Sim, 0 - Não): ";
        cin >> confirmacao;

        // Se o usuário confirmar a remoção, o produto é removido do array
        if (confirmacao == 1) {
            for(int i = id_produto; i < total - 1; i++) {
                produtos[i] = produtos[i + 1]; // Move os produtos para preencher o espaço
            }
            total--;
            cout << "Produto removido com sucesso!" << endl << endl;
        }
        // Se o usuário não confirmar a remoção, uma mensagem é exibida
        else{
            cout << "Remoção cancelada!" << endl << endl;
        }
    } 
    else {
        cout << "Senha incorreta!" << endl << endl;
    }
    return total;
}
// Função principal
int main() {
    // Ativa os acentos
    setlocale(LC_ALL, "Portuguese");

    // Variáveis principais
    Produto produtos[1000]; // até 1000 produtos
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
        cout << "3 - Remover o produto do estoque" << endl;
        cout << "4 - Realizar venda(s)" << endl;
        cout << "5 - Atualizar dados de um produto" << endl;
        cout << "6 - Sair do programa" << endl;
        cout << "7 - Créditos" << endl << endl;

        // Entrada da opção das ferramentas do menu
        cout << "Por favor, escolha uma opção: ";
        cin >> op;
        cout << endl;

        // Verifica qual a opção correspondente do menu
        switch (op) {
            // Caso o usuário escolha a opção 1, o programa chama a função de cadastro de produto
            case 1:
                total_produtos = cadastro_de_produto(produtos, total_produtos);
                break;
            // Caso o usuário escolha a opção 2, o programa chama a função de listar produtos
            case 2:
                listar_produtos(produtos, total_produtos);
                break;
            // Caso o usuário escolha a opção 3, o programa chama a função de remover produto
            case 3:
                total_produtos = remover_produto(produtos, total_produtos);
                break;
            // Caso o usuário escolha a opção 4, o programa informa que essa funcionalidade ainda está em desenvolvimento
            case 4:
                cout << "Oops! O sistema está ainda em desenvolvimento!" << endl << endl;
                break;
            // Caso o usuário escolha a opção 5, o programa chama a função de editar produto
            case 5:
                editar_produto(produtos);
                break;
            // Caso o usuário escolha a opção 6, o programa encerra
            case 6:
                cout << "Saindo do programa! Obrigado por utilizá-lo!" << endl << endl;
                return 0;
            // Caso o usuário escolha a opção 7, o programa exibe os membros da equipe responsáveis pelo projeto
            case 7:
                cout << "--------------------------------------" << endl;
                cout << "Membros da equipe:" << endl;
                cout << "Diego Augusto Pereira Silva - 9870" << endl;
                cout << "Pedro Costa Tito - 1111" << endl;
                cout << "Felipe Vitor Pereira Dias - 9872" << endl;
                cout << "Kauan Gabriel Ribeiro - 859" << endl << endl;
                break;
            // Caso o usuário escolha uma opção inválida, o programa informa que a opção é inválida e volta ao menu principal
            default:
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }
    }
    return 0;
}