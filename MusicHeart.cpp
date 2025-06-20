// Bibliotecas utilizadas no programa todo.
#include<iostream>			// Biblioteca essencial para a execução do programa
#include<iomanip>			// Biblioteca de definição de casas decimais.
#include<fstream>			// Biblioteca para integração de arquivos no programa
#include<string.h>			// Biblioteca para uso de comandos strings/char
#include<stdlib.h>			// Biblioteca sistema para limpar tela do terminal
#include<locale.h>			// Biblioteca locale para integrar caracteres do português
using namespace std;

// Estrutura struct de dados de um produto
struct Produto {
    int codigo;             // Código do produto
    char nome[50];          // Nome do produto
    char tipo[50];          // Tipo do produto [ Corda, Tecla, Acessório, etc ]
    float preco;            // Preço do produto
    int quantidade;         // Quantidade em estoque do produto
};
// Estrutura struct para históricos de vendas.
struct HistoricoVendas{
	char nome_prod[50];		// Nome do produto vendido.
	char nome_user[50];		// Nome do Usuário que comprou o produto.
	int quantidade;			// Quantidade que o produto foi comprado.
	float preco_total;		// Preço total da Venda.
};
// Estrutura struct para historico de ações do usuario administrador
struct HistoricoAcoes{
	int codigo;				// Id da ação
	char nome_admin[50];	// Nome do Administrador responsável pela ação
	char tipo[30];			// Tipo da ação
	char nome_produto[50];	// Produto modificado.
};
// Estrutura struct para usuarios administradores.
struct Admin{
	char nome[50];			// Nome de Usuário Administrador
	int senha;				// Senha do Administrador
};

// Função que coleta todos os dados do produto e os armazena no vetor Produtos
int lerProdutoArquivo(Produto produtos[], fstream &produtos_arq) {
	// Criando um novo Produto responsável por coletar os dados do arquivo
    Produto lista;
    
    // Definindo a quantidade inicial como 0 para fazer a contagem
    int QuantidadeProduto =0;
    
    // Limpando o arquivo antes de escrever os produtos na lista
    produtos_arq.seekg(0, produtos_arq.beg);
    
    // Enquanto houver dados a serem lidas, estes dados serão armazenados na lista e posteriormente alocado no vetor.
    while(produtos_arq.read((char*)&lista, sizeof(lista))){
        produtos[QuantidadeProduto] = lista;
        
        // Contando mais um de produto alocado.
        QuantidadeProduto++;
	}
	// Limpa o estado do arquivo
    produtos_arq.clear();
    return QuantidadeProduto;
}

// Função que coleta todos os dados do histórico e os armazena no vetor Ações
int lerHistoricoAcoes(HistoricoAcoes acoes[], fstream &historico_acoes_arq) {
	// Criando um novo Histórico responsável por coletar os dados do arquivo
    HistoricoAcoes lista;
    
    // Definindo a quantidade inicial como 0 para fazer a contagem
    int QuantidadeHistorico=0;
    
    // Limpando o arquivo antes de escrever os históricos
    historico_acoes_arq.seekg(0, historico_acoes_arq.beg);
    
    // Enquanto houver dados a serem lidas, estes dados serão armazenados na lista e posteriormente alocado no vetor
    while(historico_acoes_arq.read((char*)&lista, sizeof(lista))){
        acoes[QuantidadeHistorico] = lista;
        
        // Contando mais um de produto alocado.
        QuantidadeHistorico++;
	}
	// Limpa o estado do arquivo
    historico_acoes_arq.clear();
    return QuantidadeHistorico;
}

// Função que coleta todos os dados do histórico e os armazena no vetor Ações
int lerHistoricoVendas(HistoricoVendas vendas[], fstream &historico_vendas_arq) {
	// Criando um novo Histórico responsável por coletar os dados do arquivo
    HistoricoVendas lista;
    
    // Definindo a quantidade inicial como 0 para fazer a contagem
    int QuantidadeHistorico=0;
    
    // Limpando o arquivo antes de escrever os históricos
    historico_vendas_arq.seekg(0, historico_vendas_arq.beg);
    
    // Enquanto houver dados a serem lidas, estes dados serão armazenados na lista e posteriormente alocado no vetor
    while(historico_vendas_arq.read((char*)&lista, sizeof(lista))){
        vendas[QuantidadeHistorico] = lista;
        
        // Contando mais um de produto alocado.
        QuantidadeHistorico++;
	}
	// Limpa o estado do arquivo
    historico_vendas_arq.clear();
    return QuantidadeHistorico;
}

// Função que coleta todos os dados de administradores e os armazena no vetor User
int lerAdministradorArq(Admin user[], fstream &admin_arq){
	// Criando um novo Admin responsável por coletar os dados do arquivo.
	Admin lista;
	
	// Definindo a quantidade inicial como 0 para fazer a contagem
	int QuantidadeAdmin=0;
	
	// Limpando o arquivo antes de escrever os usuários
	admin_arq.seekg(0,admin_arq.beg);
	
	// Enquanto houver dados a serem lidas, estes dados serão armazenados na lista e posteriormente alocado no vetor
	while(admin_arq.read((char*)&lista, sizeof(lista))){
		user[QuantidadeAdmin] = lista;
		
		// Contando mais um de produto alocado.
		QuantidadeAdmin++;
	}
	// Limpa o estado do arquivo
	admin_arq.clear();
	return QuantidadeAdmin;
}


// Função para o usuário se verificar como administrador para poder modificar algo dentro do sistema
bool senha(Admin user[], int totalAdmin, char resUser[]){
	// Declaração das variáveis para a entrada
	int password;
	char nome[50];
	
	// Impressão do Acesso Restrito
    cout << " _______________________________________________" << endl;
	cout << "|                                               |" << endl;
	cout << "|     ACESSO APENAS PARA OS ADMINISTRADORES     |" << endl;
	cout << "|_______________________________________________|" << endl<<endl;
	cout << "_________________________________________________" << endl<<endl;
	
	// Entrada no nome e senha do administrador
	cin.ignore();
	cout << "    >> Digite o nome do administrador: ";
	cin.getline(nome,50);
	cout << "    >> Digite a senha para continuar: "; 
	cin >> password;
	
	// Limpando a tela do terminal para as próximas impressões.
	system("cls");
	
	// Fazendo a varredura para saber se os dados inserido conferem com os dados do administrado.
	for(int i=0; i<totalAdmin; i++){
		// Se caso o nome e a senha corresponderem, o acesso será autorizado e retornará como verdadeiro.
		if(strcmp(nome,user[i].nome) == 0 && password == user[i].senha){
			// Passando o nome do administrador ao resUser para inserir sua ação ao histórico.
			strcpy(resUser,nome);
			
			// Impressão do Acesso Autorizado.
			cout << "\033[1;32m";
			cout << " _______________________________________________" << endl;
        	cout << "|                                               |" << endl;
        	cout << "|               ACESSO AUTORIZADO!              |" << endl;
        	cout << "|_______________________________________________|" << endl << endl;
        	cout << "\033[0m";
        	return true;
		}
	}
	// Caso leu todos os dados e não retornou nenhum resultado, imprimir Acesso Não Autorizado e retornar falso.
	cout << "\033[1;31m";
	cout << " _______________________________________________" << endl;
	cout << "|                                               |" << endl;
	cout << "|         SENHA INCORRETA! ACESSO NEGADO        |" << endl;
	cout << "|_______________________________________________|" << endl;
	cout << "\033[0m";
	return false;
}

// Função para cadastrar um produto
int cadastro_de_produto(Produto produtos[], int total, fstream &arquivo, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac, Admin user[],int totalAdmin) {
	// Limpa a tela do console
	system("cls");
	
    // Verificando a senha administradora para acessar o cadastro de produto.
    char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Se a senha for correspondente, o usuário pode cadastrar um novo produto.
    if (verificadorSenha) {
    	// Criando novas variáveis stuct para serem adicionados posteriormente.
        Produto novo;
        HistoricoAcoes novoH;
        
        // Imprimindo a area de cadastro do produto.
        cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|             CADASTRO DE PRODUTO               |" << endl;
		cout << "|_______________________________________________|" << endl << endl;
		
		// Entrada no nome do produto
		cout << ">> Nome do produto: ";
		cin.ignore();
		cin.getline(novo.nome, 50);
		
		// Entrada no tipo do produto
		cout << endl << ">> Tipo do produto: ";
		cin.getline(novo.tipo, 50);
		
		// Entrada no preço do produto.
		cout << endl << ">> Preço do produto (ex: 99.90): R$ ";
		cin >> novo.preco;
		
		// Entrada na quantidade em estoque.
		cout << endl << ">> Quantidade em estoque: ";
		cin >> novo.quantidade;

        // Atribuindo o código do produto como o total de produtos cadastrados.
        novo.codigo = total;
        // Inserindo o novo produto no array de produtos.
        produtos[total] = novo;
        total++;
        
        // Registrando a ação do administrador para inserir-lo no histórico.
        novoH.codigo = total_acoes;
        strcpy(novoH.nome_admin,resUser);
        strcpy(novoH.tipo, "Cadastro de produto");
		strcpy(novoH.nome_produto, novo.nome);
		acoes[total_acoes] = novoH;
		
		// Escrevendo os dado do produto no arquivo.
        arquivo.seekp(0, arquivo.end);
	    arquivo.write((char *)&novo, sizeof(novo));
        arquivo.clear();
        
        // Escrevendo os dados da ação no arquivo.
        arquivo_ac.seekp(0,arquivo_ac.end);
        arquivo_ac.write((char *)&novoH,sizeof(novoH));
        total_acoes++;
        arquivo_ac.clear();

		// Limpando o terminal para imprimir que o produto foi registrado com sucesso.
        system("cls");
        cout << "\033[1;32m";
		cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|         PRODUTO CADASTRADO COM SUCESSO!       |" << endl;
		cout << "|_______________________________________________|" << endl << endl;
		cout << "\033[0m";

    } 
    // Se a senha for incorreta, o usuário não pode cadastrar um novo produto, retornando ao menu principal
    return total;
}
// Função para listar todos os produtos
void listar_produtos(Produto produtos[], int total) {
	// Limpando a tela no sistema para mostrar a lista.
	system("cls");
    // Verifica se há produtos cadastrados, se não houver, informa ao usuário que não há produtos cadastrados.
	if (total == 0) {
		cout << "\033[1;31m";
	    cout << " _______________________________________________" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|     Nenhum produto cadastrado no momento!     |" << endl;
	    cout << "|_______________________________________________|" << endl << endl;
	    cout << "\033[0m";
	    return;
	}
	
	// Se houver produtos cadastrados, exibe a lista de produtos.
	cout << " _______________________________________________" << endl;
	cout << "|                                               |" << endl;
	cout << "|          <<< LISTA DE PRODUTOS >>>            |" << endl;
	cout << "|_______________________________________________|" << endl << endl;
	
	// Imprimindo produto por produto.
	for (int i = 0; i < total; i++) {
	    cout << " _______________________________________________" << endl;
	    cout << endl;
	    cout << "  ID: " << i << endl;
	    cout << "  Nome: " << produtos[i].nome << endl;
	    cout << "  Tipo do produto: " << produtos[i].tipo << endl;
	    cout << fixed << setprecision(2);
	    cout << "  Preço: R$" << produtos[i].preco << endl;
	    cout << "  Quantidade: " << produtos[i].quantidade << endl;
	    cout << " _______________________________________________" << endl << endl;
	}
}

// Função que imprime o histórico de ações realizadas pelo Administrador
void visualizar_historicoAc(HistoricoAcoes acoes[],int total){
	system("cls");
    // Verifica se há produtos cadastrados, se não houver, informa ao usuário que não há produtos cadastrados
	if (total == 0) {
		cout << "\033[1;31m";
	    cout << " _______________________________________________" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|     Nenhuma ação foi realizada no momento     |" << endl;
	    cout << "|_______________________________________________|" << endl << endl;
	    cout << "\033[0m";
	    return;
	}
	
	// Se houver produtos cadastrados, exibe a lista de produtos
	cout << " _______________________________________________" << endl;
	cout << "|                                               |" << endl;
	cout << "|          <<< HISTÓRICO DE AÇÕES >>>           |" << endl;
	cout << "|_______________________________________________|" << endl << endl;
	
	// Imprimindo histórico por histórico
	for (int i = 0; i < total; i++) {
	    cout << " _______________________________________________" << endl;
	    cout << endl;
	    cout << "  ID: " << acoes[i].codigo << endl;
	    cout << "  Nome: " << acoes[i].nome_admin << endl;
	    cout << "  Tipo de Ação: " << acoes[i].tipo << endl;
	    cout << "  Produto: " << acoes[i].nome_produto << endl;
	    cout << " _______________________________________________" << endl << endl;
	}
}

void visualizar_historicoV(HistoricoVendas hisVendas[],int totalVendas){
	system("cls");
	
	float TotalVendasPreco = 0;
	
    // Verifica se há produtos cadastrados, se não houver, informa ao usuário que não há produtos cadastrados
	if (totalVendas == 0) {
		cout << "\033[1;31m";
	    cout << " _______________________________________________" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|    Nenhuma venda foi realizada no momento     |" << endl;
	    cout << "|_______________________________________________|" << endl << endl;
	    cout << "\033[0m";
	    return;
	}
	
	// Se houver produtos cadastrados, exibe a lista de produtos
	cout << " _______________________________________________" << endl;
	cout << "|                                               |" << endl;
	cout << "|         <<< HISTÓRICO DE VENDAS >>>           |" << endl;
	cout << "|_______________________________________________|" << endl << endl;
	
	// Imprimindo histórico por histórico
	for (int i = 0; i < totalVendas; i++) {
		TotalVendasPreco += hisVendas[i].preco_total;
	    cout << " _______________________________________________" << endl;
	    cout << endl;
	    cout << "  ID: " << i << endl;
	    cout << "  Usuário que comprou o produto: " << hisVendas[i].nome_user << endl;
	    cout << "  Produto: " << hisVendas[i].nome_prod << endl;
	    cout << "  Quantidade: " << hisVendas[i].quantidade << endl;
	    cout << "  Preço total: " << hisVendas[i].preco_total << endl;
	    cout << " _______________________________________________" << endl << endl;
	}
	cout << " >> LUCRO TOTAL: " << TotalVendasPreco << endl; 
	cout << " _______________________________________________" << endl << endl;
}

// Função para editar um produto existente na lista.
int editar_produto(Produto produtos[], fstream &arquivo, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac, Admin user[],int totalAdmin ) {
	// Limpa a tela para mostrar o editor de produto
    system("cls");
	// Verificando a senha administradora para acessar o editor de produto
    char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);

    // Se a senha for correspondente, o usuário pode editar um produto
    if(verificadorSenha) {
    	// Criando novas variáveis com struct que serão responsáveis para inserirem no arquivo.
    	Produto editar;
    	HistoricoAcoes novoH;
    	
    	// Variáveis para identificar um produto dentro da lista.
        int id_produto;
        bool encontrado = false;
        
        // Impressão do Editor de Produto
        cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|              EDITOR  DE PRODUTO               |" << endl;
		cout << "|_______________________________________________|" << endl << endl;
		
        // Entrada no ID do produto que deseja editar
        cout << ">> Digite o ID do produto que deseja editar: ";
        cin >> id_produto;

		// Limpa o estado antes de fazer a varredura
        arquivo.clear(); 
        arquivo.seekg(0, arquivo.beg);
        
        while(arquivo.read((char*)&editar, sizeof(editar))){
		    if(editar.codigo == id_produto){
		    	encontrado = true;
		    	system("cls");
		    	
		    	cout << "\033[1;32m";
		    	cout << " _______________________________________________" << endl;
				cout << "|                                               |" << endl;
				cout << "|             PRODUTO ENCONTRADO!               |" << endl;
				cout << "|_______________________________________________|" << endl << endl;
				cout << "\033[0m";
				
			    cout << ">> Editando produto: " << produtos[id_produto].nome << endl;
                cin.ignore();
                // Entrada no nome do produto
                cout << endl <<  ">> Nome do produto: ";
                cin.getline(editar.nome, 50);
                
                // Entrada na descrição do produto
                cout << endl <<  ">> Tipo do produto: ";
                cin.getline(editar.tipo, 50);
    
                // Entrada no preço do produto
                cout << endl << ">> Preço do produto: ";
                cin >> editar.preco;

                // Entrada na quantidade do produto
                cout << endl << ">> Quantidade em estoque: ";
                cin >> editar.quantidade;

				// Inserindo o produto editado ao array de produto.		
                produtos[id_produto] = editar;

				// Limpando a tela para imprimir que o editar executou com sucesso.
                system("cls");
                
                // Impressão do editado
                cout << "\033[1;32m";
		    	cout << " _______________________________________________" << endl;
				cout << "|                                               |" << endl;
				cout << "|        PRODUTO ATUALIZADO COM SUCESSO!        |" << endl;
				cout << "|_______________________________________________|" << endl << endl;
				cout << "\033[0m";
			
				// Reescrevendo o dado modificado.
			    arquivo.seekp(-streamoff(sizeof(editar)), arquivo.cur);
			    arquivo.write((char*)&editar, sizeof(editar));
			    
			    // Registrando a ação do administrador para inserir-lo no histórico.
		        novoH.codigo = total_acoes;
		        strcpy(novoH.nome_admin,resUser);
		        strcpy(novoH.tipo, "Editador de produto");
				strcpy(novoH.nome_produto, editar.nome);
				acoes[total_acoes] = novoH;
				
				// Escrevendo os dados da ação no arquivo.
				arquivo_ac.seekp(0,arquivo_ac.end);
        		arquivo_ac.write((char *)&novoH,sizeof(novoH));
        		arquivo_ac.clear();
        		total_acoes++;

			    return 0;
		    }
	    }
	    // Se caso varreu todos os número e não encontrou, imprimir que o produto não foi encontrado.
	    if(!encontrado){
			system("cls");
			cout << "\033[1;31m";
			cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|            PRODUTO NÃO ENCONTRADO!            |" << endl;
			cout << "|_______________________________________________|" << endl << endl;
			cout << "\033[0m";
		}
        arquivo.clear();
    }
    return 1; 
}
// Função para remover um produto
int remover_produto(Produto produtos[],int total, fstream &arquivo, Admin user[],int totalAdmin, HistoricoAcoes hisA[], fstream &arquivo_ac,int &total_acoes) {
	// Limpando a tela para imprimir a parte de remover produto
	system("cls");
    // Verificando a senha administradora para acessar o removedor de produto
    char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Caso retornar verdadeiro, executar o programa normalmete.
    if(verificadorSenha){
    	// Criando variáveis para pesquisa e confirmação
		int id_produto;
        int confirmacao;
        HistoricoAcoes novoH;
        
        // Impressão do Editor de Produto
        cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|             REMOVEDOR DE PRODUTO              |" << endl;
		cout << "|_______________________________________________|" << endl << endl;

        // Entrada no ID do produto que deseja remover
        cout << " >> Digite o ID do produto que deseja remover: ";
        cin >> id_produto;

        // Confirmando a remoção do produto
        cout << endl << " >> Deseja remover o produto " << produtos[id_produto].nome << "? (1 - Sim, 0 - Não): ";
        cin >> confirmacao;

        // Se o usuário confirmar a remoção, o produto é removido do array
        if (confirmacao == 1) {
        	// Registrando a ação do administrador para inserir-lo no histórico.
	        novoH.codigo = total_acoes;
	        strcpy(novoH.nome_admin,resUser);
	        strcpy(novoH.tipo, "Removeu um produto");
			strcpy(novoH.nome_produto, produtos[id_produto].nome);
			hisA[total_acoes] = novoH;
        	
        	// Apagando aquele dado e passando todos produtos a frente dele para uma casa atrás.
            for(int i = id_produto; i < total - 1; i++) {
                produtos[i] = produtos[i + 1]; // Move os produtos para preencher o espaço.
            }
            // Subtraindo menos um do total de produtos.
            total--;
            
            // Limpndo a tela para imprimir o sucesso da remoção.
            system("cls");
            
            // Impressão do resultado.
            cout << "\033[1;32m";
            cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|          PRODUTO REMOVIDO COM SUCESSO         |" << endl;
			cout << "|_______________________________________________|" << endl << endl;
			cout << "\033[0m";

			// Fechando e reabrindo com trunc para limpar o arquivo.
            arquivo.close();
            arquivo.open("lista_produtos.txt", ios::in | ios::out | ios::binary | ios::trunc);
            
            // Reescrevendo cada dado atual no arquivo
            for (int i = 0; i < total; i++) {
                arquivo.write((char*)&produtos[i], sizeof(produtos));
            }
            // Fechando e reabrinod como normal por agora.
            arquivo.close();
            arquivo.open("lista_produtos.txt", ios::in | ios::out | ios::binary);
            
            
            // Escrevendo os dados da ação no arquivo.
			arquivo_ac.seekp(0,arquivo_ac.end);
        	arquivo_ac.write((char *)&novoH,sizeof(novoH));
       		arquivo_ac.clear();
       		total_acoes++;
        }
        // Se o usuário não confirmar a remoção, uma mensagem é exibida
        else{
        	// Limpando a tela para imprimir o resultado.
        	system("cls");
        	
        	// Impressão do resultado.
        	cout << "\033[1;31m";
        	cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|               REMOÇÃO CANCELADA!              |" << endl;
			cout << "|_______________________________________________|" << endl << endl;
			cout << "\033[0m";
        }
        return total;
	}
    return total;
}

// Função que cadastrar um usuário Administrador ao sistema
void cadastro_admin(Admin user[],int &totalAdmin, fstream &admin_arq, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac){
	// Declarando a variável responsável por trazer o nome do administrador que será responsável pelo cadastro
	char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Limpando a tela para a impressão do programa.
    system("cls");
    
    // Se caso o sistema de verificação retornar verdadeiro, prosseguir com o programa.
	if(verificadorSenha){
		// Criando novas variáveis para o armazenamento e integração ao arquivo.
		Admin novo;
		HistoricoAcoes novoH;
		
		// Impressão do cadastro de admin
		cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|               CADASTRO DE ADMIN               |" << endl;
		cout << "|_______________________________________________|" << endl << endl;
		
		// Entrada no nome do produto
		cout << ">> Nome do administrador: ";
		cin.ignore();  // Para limpar o buffer antes de getline
		cin.getline(novo.nome, 50);
		
		cout << endl << ">> Senha do administrador: ";
		cin >> novo.senha;
		
		// Inserindo o novo produto no array de produtos
        user[totalAdmin] = novo;
        totalAdmin++;
        
        // Registrando a ação do admin do cadastro de admin.
        novoH.codigo = total_acoes;
        strcpy(novoH.nome_admin,resUser);
        strcpy(novoH.tipo, "Cadastro de usuário administrador");
		strcpy(novoH.nome_produto," ");
		acoes[total_acoes] = novoH;
		
		// Registrando o novo admin no arquivo.
        admin_arq.seekp(0, admin_arq.end);
	    admin_arq.write((char *)&novo, sizeof(novo));
        admin_arq.clear();
        
        // Registrando o histórico de ação do admin no arquivo
        arquivo_ac.seekp(0,arquivo_ac.end);
        arquivo_ac.write((char *)&novoH,sizeof(novoH));
        total_acoes++;
        arquivo_ac.clear();
        
        // Limpa a tela do terminal para impressão do resultado
        system("cls");
        
        // Impressão do resultado
        cout << "\033[1;32m";
		cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|          ADMIN CADASTRADO COM SUCESSO!        |" << endl;
		cout << "|_______________________________________________|" << endl << endl;
		cout << "\033[0m";
	}
}

// Função de realizar venda de um produto.
int realizarVenda(Produto produtos[], int totalProduto, fstream &arquivo, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac, Admin user[],int totalAdmin, int &total_vendas, fstream &vendasArq, HistoricoVendas hisVenda[]){
	// Limpa a tela para mostrar só a parte de venda
	system("cls");
	
	// Declarando a variável responsável por trazer o nome do administrador que será responsável pelo cadastro
	char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Dando cin.ignore para não houve conflitos com as entradas a seguir
    cin.ignore();
    
    // Se a senha for correspondente, o usuário pode editar um produto
    if(verificadorSenha){
    	// Criando novas variáveis struct para armazenar os histórico.
		HistoricoAcoes novoH;
		
		// Variáveis para a pesquisa, inserir quantidade e confirmar a compra do produto
		char pesquisaProduto[50];
		bool confirmed = false;
		int quantidade;
		
		// Enquanto a compra ainda não for confirmada, imprime novamente o menu de venda.
		while(!confirmed){
			// Impressão do menu de venda.
			cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|                REALIZAR VENDA                 |" << endl;
			cout << "|_______________________________________________|" << endl << endl;
		
			cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|                PRODUTOS ATUAIS                |" << endl;
			cout << "|_______________________________________________|" << endl <<endl;
			
			// Imprimindo produto por produto, com seus preços por unidade.
			cout << fixed << setprecision(2);
			for(int i=0; i<totalProduto; i++){
				cout << " >> " << produtos[i].nome << " - R$ "<<produtos[i].preco << endl;
			}
			cout << "_________________________________________________"<< endl << endl;
			
			// Entrada do nome do produto para fazer a busca.
			cout << " >> Digite o nome do produto que deseja comprar: "; 
			cin.getline(pesquisaProduto,50);
			
			// Verificando se o produto pesquisado existe na lista.
			for(int i=0; i<totalProduto; i++){
				// Caso encontrado ir para a parte de selecionar a quantidade desejada pelo produto
				if(strcmp(pesquisaProduto,produtos[i].nome) == 0){
					// Limpando a tela 
					system("cls");
					// Imprimindo o produto encontrado.
					cout << "\033[1;32m";
					cout << " _______________________________________________" << endl;
					cout << "|                                               |" << endl;
					cout << "|              PRODUTOS ENCONTRADO              |" << endl;
					cout << "|_______________________________________________|" << endl <<endl;
					cout << "\033[0m";
					// Se enquanto o usuário for inserindo quandidade maiores que o produto já tem no estoque, repetir a pergunta
					while(quantidade > produtos[i].quantidade){
						// Imprimindo o nome do produto.
						cout << endl << " >> Produto Selecionado: "<<produtos[i].nome << endl;
						
						// Entrada na quantidade desejada.
						cout << endl << " >> Digite a quantidade que deseja levar: ";
						cin >> quantidade;
						
						// Caso o usuário inseriu uma quantidade maior do que existe no estoque, emitir um alerta.
						if(quantidade > produtos[i].quantidade){
							system("cls");
							cout << " >> Ops! Você selecionou uma quantidade ultrapassada, por favor insira uma quantidade menor " << endl;
	  	  	  	  	    }	
					}
					// Calculando o preço total do produto.
					double preco_total = quantidade * produtos[i].preco;
					
					// Emitindo o resultado ao escolher o produto e a quantidade.
					cout << "_________________________________________________"<< endl << endl;
					cout << " >> Nome do produto: "<< produtos[i].nome << endl;
					cout << " >> Quantidade: "<< quantidade << endl;
					cout << " >> Preço total: " << preco_total << endl;
					cout << "_________________________________________________"<< endl << endl;
					
					// Confirmação para finalizar a compra.
					char op;
					cout << " >> Deseja confirmar esta compra? (Y/N): ";
					cin >> op;
					// Se caso escolher Y, confirmar a compra
					if(tolower(op) == 'y'){
						// Mudando para true para finalizar o sistema de venda
						confirmed = true;
						char username[50];
						
						cin.ignore();
						cout << endl << " >> Insira seu nome para poder finalizar: ";
						cin.getline(username,50);
						
						// Limpa a tela para emitir a compra confirmada.
						system("cls");
						
						// Impressão do resultado.
						cout << "\033[1;32m";
						cout << " _______________________________________________" << endl;
						cout << "|                                               |" << endl;
						cout << "|               COMPRA CONFIRMADA!              |" << endl;
						cout << "|_______________________________________________|" << endl <<endl;
						cout << "\033[0m";
						
						// Subtraindo a quantidade do produto
						produtos[i].quantidade -= quantidade;
						
						// Caso a quantidade for menor ou igual a 0 (Ou seja, esgotado), o eliminar do estoque.
						if(produtos[i].quantidade <= 0){
							for(int j = i; j < totalProduto - 1; j++) {
								// Move os produtos para preencher o espaço
                				produtos[i] = produtos[j + 1];
            				}
            				// Subtraindo menos um da quantidade total de produtos.
            				totalProduto--;

							// Fechando e reabrindo como trunc para limpar todo arquivo e reescrevelo
            				arquivo.close();
            				arquivo.open("lista_produtos.txt", ios::in | ios::out | ios::binary | ios::trunc);
            				
            				// Escrevendo cada produto na lista.
            				for (int j = 0; j < totalProduto; j++) {
							    arquivo.write((char*)&produtos[j], sizeof(produtos[j]));
							}

							// Fechando e reabrindo normalmente.
            				arquivo.close();
            				arquivo.open("lista_produtos.txt", ios::in | ios::out | ios::binary);
            				
            				return totalProduto;
						}
						else{
							// Reescrevendo o dado modificado.
			    			arquivo.seekp(-streamoff(sizeof(produtos[i])), arquivo.cur);
    						arquivo.write((char*)&produtos[i], sizeof(produtos[i]));
						}
						
						// Registrando a ação do administrador para inserir-lo no histórico.
				        novoH.codigo = total_acoes;
				        strcpy(novoH.nome_admin,resUser);
				        strcpy(novoH.tipo, "Vendeu um produto ao usuário");
						strcpy(novoH.nome_produto, produtos[i].nome);
						acoes[total_acoes] = novoH;
						
						// Escrevendo os dados da ação no arquivo.
						arquivo_ac.seekp(0,arquivo_ac.end);
				        arquivo_ac.write((char *)&novoH,sizeof(novoH));
				        total_acoes++;
				        arquivo_ac.clear();
				        
				        // Registrando o histórico de venda de um usuário
				        HistoricoVendas novoV;
				        strcpy(novoV.nome_prod,produtos[i].nome);
				        strcpy(novoV.nome_user,username);
				        novoV.quantidade = quantidade;
				        novoV.preco_total = preco_total;
				        hisVenda[total_vendas] = novoV;
				        
				        // Inserindo o registro no arquivo de histórico de vendas
				        vendasArq.seekp(0,vendasArq.end);
				        vendasArq.write((char *)&novoV,sizeof(novoV));
				        total_vendas++;
				        vendasArq.clear();
					}
					// Caso o usuário escreva N ou n, cancelar a compra e retornar ao menu;
					else{
						// Limpando a tela para a impressão do resultado
						system("cls");
						
						// Impressão do resultado.
						cout << "\033[1;31m";
						cout << " _______________________________________________" << endl;
						cout << "|                                               |" << endl;
						cout << "|               COMPRA CANCELADA                |" << endl;
						cout << "|_______________________________________________|" << endl <<endl;
						cout << "\033[0m";
						
						
						return totalProduto;
					}
				}
			}	
		}
	}
}

// Função principal do programa que dará início a tudo.
int main() {
    // Comando que integrará acentos e caracteres do português.
    setlocale(LC_ALL, "Portuguese");
    
    // Declarando as variáveis de structs
    Produto produtos[1000]; 		// Variável que armazenará cada produto
    HistoricoAcoes hisAcoes[1000];	// Variável que armazenará cada ação do administrador
    HistoricoVendas hisVendas[1000];// Variável que armazenará cada venda realizada.
    Admin user[10];					// Variável que armazenará cada administrador registrado
    
    // Declarando as variáveis de arquivo
    fstream produtos_arq;			// Variável que executa o arquivo de produtos
    fstream historico_acoes_arq;	// Variável que executa o arquivo de histórico de ações
    fstream admin_arq;				// Variável que executa o arquivo de administradores registrados
    fstream historico_vendas_arq;	// Variável que executa o arquivo de histórico de vendas;
    
    // Variáveis de contadores
    int total_produtos = 0;			// Total de Produtos
    int total_acoes = 0;			// Total de Histórico de Ações
    int totalAdmin = 0;				// Total de Administradores
    int totalVendas = 0;			// Total de vendas
    
    // Abrindo cada Arquivo e verificando se elas existem.
	
	// Lista com os dados do produto.
	produtos_arq.open("lista_produtos.txt", ios::in | ios::out | ios::binary);
	// Caso não encontrado a lista de produtos, criar um novo arquivo.
	if(!produtos_arq.is_open()){
		produtos_arq.open("lista_produtos.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
	
	// Lista com os históricos de ações do usuário
	historico_acoes_arq.open("historico_acoes.txt", ios::in | ios::out | ios::binary);
	// Caso não encontrado o histórico, criar um novo arquivo.
	if(!historico_acoes_arq.is_open()){
		historico_acoes_arq.open("historico_acoes.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
	
	// Lista com os dados dos administradores
	admin_arq.open("admin-user.txt", ios::in | ios::out | ios::binary);
	// Caso não encontrado a lista de administradores, criar um novo arquivo.
	if(!admin_arq.is_open()){
		admin_arq.open("admin-user.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
 
    // Lista com os históricos de venda.
    historico_vendas_arq.open("historico_vendas.txt", ios::in | ios::out | ios::binary );
    // Caso não encontrado o histórico, criar um novo arquivo.
    if(!historico_vendas_arq.is_open()){
		historico_vendas_arq.open("historico_vendas.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
	
	
    // Armazenando a contágem de cada contador.
	total_produtos = lerProdutoArquivo(produtos,produtos_arq);			// Contando a quantidade de produtos no arquivo.
	total_acoes = lerHistoricoAcoes(hisAcoes,historico_acoes_arq);		// Contando a quantidade de ações no arquivo.
	totalAdmin =  lerAdministradorArq(user,admin_arq);					// Contando a quantidade de Administradores no arquivo.
	totalVendas = lerHistoricoVendas(hisVendas,historico_vendas_arq);   // Contando a quantidade de vendas no arquivo.
	
	// Declarando a variável de opção para o menu principal
    int op = 0;
    
    // Loop do menu principal
    while (op != 9) {
        cout << " _______________________________________________" << endl;
        cout << "|                                               |" << endl;
    	cout << "|       <<<<<< HEART'S MUSIC SYSTEM >>>>>>      |" << endl;
	    cout << "|_______________________________________________|" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|              ESCOLHA UMA OPÇÃO                |" << endl;
	    cout << "|_______________________________________________|" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|  [1] Cadastrar um produto                     |" << endl;
	    cout << "|  [2] Listar todos os produtos                 |" << endl;
	    cout << "|  [3] Remover um produto do estoque            |" << endl;
	    cout << "|  [4] Realizar venda(s)                        |" << endl;
	    cout << "|  [5] Atualizar dados de um produto            |" << endl;
	    cout << "|  [6] Visualizar histórico de ações            |" << endl;
	    cout << "|  [7] Visualizar histórico de vendas           |" << endl;
	    cout << "|  [8] Adicionar um usuário administrador       |" << endl;
	    cout << "|  [9] Sair do programa                         |" << endl;
	    cout << "|  [10] Créditos                                |" << endl;
	    cout << "|_______________________________________________|" << endl<<endl;
	    
	   	// Entrada na opção do menu 
	    cout << "_________________________________________________" << endl<<endl;
	    cout << ">> Digite a opção desejada: ";
        cin >> op;

        // Verifica qual a opção inserida se corresponde as opções mostrada no menu
        switch (op) {
            // Caso o usuário escolha a opção 1, o programa chama a função de Cadastrar um Produto
            case 1:
                total_produtos = cadastro_de_produto(produtos, total_produtos, produtos_arq, hisAcoes,total_acoes, historico_acoes_arq,user,totalAdmin);
                break;
            // Caso o usuário escolha a opção 2, o programa chama a função de Listar os produtos
            case 2:
                listar_produtos(produtos, total_produtos);
                break;
            // Caso o usuário escolha a opção 3, o programa chama a função de Remover um Produto
            case 3:
                total_produtos = remover_produto(produtos, total_produtos, produtos_arq,user,totalAdmin,hisAcoes,historico_acoes_arq,total_acoes);
                break;
            // Caso o usuário escolha a opção 4, o programa chama a função de Realizar uma Venda
            case 4:
                realizarVenda(produtos, total_produtos, produtos_arq, hisAcoes,total_acoes,historico_acoes_arq,user,totalAdmin,totalVendas,historico_vendas_arq,hisVendas);
                break;
            // Caso o usuário escolha a opção 5, o programa chama a função de Editar um produto
            case 5:
                editar_produto(produtos,produtos_arq, hisAcoes,total_acoes, historico_acoes_arq,user,totalAdmin);
                break;
            // Caso o usuário escolha a opção 6, o programa chama a função de Listar o Histórico de Ações.
            case 6:
            	visualizar_historicoAc(hisAcoes,total_acoes);
            	break;
            // Caso o usuário escolha a opção 7, o programa chama a função de Listar o Histórico de Vendas.
            case 7:
            	visualizar_historicoV(hisVendas,totalVendas);
            	break;
            // Caso o usuário escolha a opção 8, o programa chama a função de Cadastrar um Administrador.
            case 8:
            	cadastro_admin(user, totalAdmin, admin_arq, hisAcoes,total_acoes,historico_acoes_arq);
            	break;
            // Caso o usuário escolha a opção 8, o programa encerrará
            case 9:
            	// Limpando a tela para a impressão da Saída.
            	system("cls");
            	
            	// Impressão de despedida.
            	cout << "\033[1;32m";
                cout << " _______________________________________________" << endl;
				cout << "|                                               |" << endl;
				cout << "|        SAINDO DO PROGRAMA... ATÉ LOGO!        |" << endl;
				cout << "|     Obrigado por utilizar o Heart's Music     |" << endl;
				cout << "|_______________________________________________|" << endl << endl;
				cout << "\033[0m";
				
				// Fechando os arquivos.
				produtos_arq.close();
				historico_acoes_arq.close();
				admin_arq.close();
				historico_vendas_arq.close();
				
				// Encerrando o programa.
				return 0;
				break;
            // Caso o usuário escolha a opção 10, o programa exibe os membros da equipe responsáveis pelo projeto
            case 10:
            	// Limpando a tela para a impressão dos Créditos
            	system("cls");
            	
            	// Impressão dos créditos
            	cout << "\033[1;36m";
                cout << " _______________________________________________" << endl;
				cout << "|                                               |" << endl;
				cout << "|             <<< CRÉDITOS FINAIS >>>           |" << endl;
				cout << "|_______________________________________________|" << endl;
				cout << "|                                               |" << endl;
				cout << "|               MEMBROS DA EQUIPE               |" << endl;
				cout << "|_______________________________________________|" << endl;
				cout << "|                                               |" << endl;
				cout << "|  Diego Augusto Pereira Silva   - 9870         |" << endl;
				cout << "|  Pedro Costa Tito              - 1111         |" << endl;
				cout << "|  Felipe Vitor Pereira Dias     - 9872         |" << endl;
				cout << "|  Kauan Gabriel Ribeiro         - 0859         |" << endl;
				cout << "|_______________________________________________|" << endl << endl;
				cout << "\033[0m";
                break;
            // Caso o usuário escolha uma opção inválida, o programa informa que a opção é inválida e volta ao menu principal
            default:
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }
    }
    // Fechando os arquivos.
	produtos_arq.close();
	historico_acoes_arq.close();
	admin_arq.close();
	historico_vendas_arq.close();
    return 0;
}