// Bibliotecas utilizadas no programa todo.
#include<iostream>			// Biblioteca essencial para a execu��o do programa
#include<iomanip>			// Biblioteca de defini��o de casas decimais.
#include<fstream>			// Biblioteca para integra��o de arquivos no programa
#include<string.h>			// Biblioteca para uso de comandos strings/char
#include<stdlib.h>			// Biblioteca sistema para limpar tela do terminal
#include<locale.h>			// Biblioteca locale para integrar caracteres do portugu�s
using namespace std;

// Estrutura struct de dados de um produto
struct Produto {
    int codigo;             // C�digo do produto
    char nome[50];          // Nome do produto
    char tipo[50];          // Tipo do produto [ Corda, Tecla, Acess�rio, etc ]
    float preco;            // Pre�o do produto
    int quantidade;         // Quantidade em estoque do produto
};
// Estrutura struct para hist�ricos de vendas.
struct HistoricoVendas{
	char nome_prod[50];		// Nome do produto vendido.
	char nome_user[50];		// Nome do Usu�rio que comprou o produto.
	int quantidade;			// Quantidade que o produto foi comprado.
	float preco_total;		// Pre�o total da Venda.
};
// Estrutura struct para historico de a��es do usuario administrador
struct HistoricoAcoes{
	int codigo;				// Id da a��o
	char nome_admin[50];	// Nome do Administrador respons�vel pela a��o
	char tipo[30];			// Tipo da a��o
	char nome_produto[50];	// Produto modificado.
};
// Estrutura struct para usuarios administradores.
struct Admin{
	char nome[50];			// Nome de Usu�rio Administrador
	int senha;				// Senha do Administrador
};

// Fun��o que coleta todos os dados do produto e os armazena no vetor Produtos
int lerProdutoArquivo(Produto produtos[], fstream &produtos_arq) {
	// Criando um novo Produto respons�vel por coletar os dados do arquivo
    Produto lista;
    
    // Definindo a quantidade inicial como 0 para fazer a contagem
    int QuantidadeProduto =0;
    
    // Limpando o arquivo antes de escrever os produtos na lista
    produtos_arq.seekg(0, produtos_arq.beg);
    
    // Enquanto houver dados a serem lidas, estes dados ser�o armazenados na lista e posteriormente alocado no vetor.
    while(produtos_arq.read((char*)&lista, sizeof(lista))){
        produtos[QuantidadeProduto] = lista;
        
        // Contando mais um de produto alocado.
        QuantidadeProduto++;
	}
	// Limpa o estado do arquivo
    produtos_arq.clear();
    return QuantidadeProduto;
}

// Fun��o que coleta todos os dados do hist�rico e os armazena no vetor A��es
int lerHistoricoAcoes(HistoricoAcoes acoes[], fstream &historico_acoes_arq) {
	// Criando um novo Hist�rico respons�vel por coletar os dados do arquivo
    HistoricoAcoes lista;
    
    // Definindo a quantidade inicial como 0 para fazer a contagem
    int QuantidadeHistorico=0;
    
    // Limpando o arquivo antes de escrever os hist�ricos
    historico_acoes_arq.seekg(0, historico_acoes_arq.beg);
    
    // Enquanto houver dados a serem lidas, estes dados ser�o armazenados na lista e posteriormente alocado no vetor
    while(historico_acoes_arq.read((char*)&lista, sizeof(lista))){
        acoes[QuantidadeHistorico] = lista;
        
        // Contando mais um de produto alocado.
        QuantidadeHistorico++;
	}
	// Limpa o estado do arquivo
    historico_acoes_arq.clear();
    return QuantidadeHistorico;
}

// Fun��o que coleta todos os dados do hist�rico e os armazena no vetor A��es
int lerHistoricoVendas(HistoricoVendas vendas[], fstream &historico_vendas_arq) {
	// Criando um novo Hist�rico respons�vel por coletar os dados do arquivo
    HistoricoVendas lista;
    
    // Definindo a quantidade inicial como 0 para fazer a contagem
    int QuantidadeHistorico=0;
    
    // Limpando o arquivo antes de escrever os hist�ricos
    historico_vendas_arq.seekg(0, historico_vendas_arq.beg);
    
    // Enquanto houver dados a serem lidas, estes dados ser�o armazenados na lista e posteriormente alocado no vetor
    while(historico_vendas_arq.read((char*)&lista, sizeof(lista))){
        vendas[QuantidadeHistorico] = lista;
        
        // Contando mais um de produto alocado.
        QuantidadeHistorico++;
	}
	// Limpa o estado do arquivo
    historico_vendas_arq.clear();
    return QuantidadeHistorico;
}

// Fun��o que coleta todos os dados de administradores e os armazena no vetor User
int lerAdministradorArq(Admin user[], fstream &admin_arq){
	// Criando um novo Admin respons�vel por coletar os dados do arquivo.
	Admin lista;
	
	// Definindo a quantidade inicial como 0 para fazer a contagem
	int QuantidadeAdmin=0;
	
	// Limpando o arquivo antes de escrever os usu�rios
	admin_arq.seekg(0,admin_arq.beg);
	
	// Enquanto houver dados a serem lidas, estes dados ser�o armazenados na lista e posteriormente alocado no vetor
	while(admin_arq.read((char*)&lista, sizeof(lista))){
		user[QuantidadeAdmin] = lista;
		
		// Contando mais um de produto alocado.
		QuantidadeAdmin++;
	}
	// Limpa o estado do arquivo
	admin_arq.clear();
	return QuantidadeAdmin;
}


// Fun��o para o usu�rio se verificar como administrador para poder modificar algo dentro do sistema
bool senha(Admin user[], int totalAdmin, char resUser[]){
	// Declara��o das vari�veis para a entrada
	int password;
	char nome[50];
	
	// Impress�o do Acesso Restrito
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
	
	// Limpando a tela do terminal para as pr�ximas impress�es.
	system("cls");
	
	// Fazendo a varredura para saber se os dados inserido conferem com os dados do administrado.
	for(int i=0; i<totalAdmin; i++){
		// Se caso o nome e a senha corresponderem, o acesso ser� autorizado e retornar� como verdadeiro.
		if(strcmp(nome,user[i].nome) == 0 && password == user[i].senha){
			// Passando o nome do administrador ao resUser para inserir sua a��o ao hist�rico.
			strcpy(resUser,nome);
			
			// Impress�o do Acesso Autorizado.
			cout << "\033[1;32m";
			cout << " _______________________________________________" << endl;
        	cout << "|                                               |" << endl;
        	cout << "|               ACESSO AUTORIZADO!              |" << endl;
        	cout << "|_______________________________________________|" << endl << endl;
        	cout << "\033[0m";
        	return true;
		}
	}
	// Caso leu todos os dados e n�o retornou nenhum resultado, imprimir Acesso N�o Autorizado e retornar falso.
	cout << "\033[1;31m";
	cout << " _______________________________________________" << endl;
	cout << "|                                               |" << endl;
	cout << "|         SENHA INCORRETA! ACESSO NEGADO        |" << endl;
	cout << "|_______________________________________________|" << endl;
	cout << "\033[0m";
	return false;
}

// Fun��o para cadastrar um produto
int cadastro_de_produto(Produto produtos[], int total, fstream &arquivo, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac, Admin user[],int totalAdmin) {
	// Limpa a tela do console
	system("cls");
	
    // Verificando a senha administradora para acessar o cadastro de produto.
    char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Se a senha for correspondente, o usu�rio pode cadastrar um novo produto.
    if (verificadorSenha) {
    	// Criando novas vari�veis stuct para serem adicionados posteriormente.
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
		
		// Entrada no pre�o do produto.
		cout << endl << ">> Pre�o do produto (ex: 99.90): R$ ";
		cin >> novo.preco;
		
		// Entrada na quantidade em estoque.
		cout << endl << ">> Quantidade em estoque: ";
		cin >> novo.quantidade;

        // Atribuindo o c�digo do produto como o total de produtos cadastrados.
        novo.codigo = total;
        // Inserindo o novo produto no array de produtos.
        produtos[total] = novo;
        total++;
        
        // Registrando a a��o do administrador para inserir-lo no hist�rico.
        novoH.codigo = total_acoes;
        strcpy(novoH.nome_admin,resUser);
        strcpy(novoH.tipo, "Cadastro de produto");
		strcpy(novoH.nome_produto, novo.nome);
		acoes[total_acoes] = novoH;
		
		// Escrevendo os dado do produto no arquivo.
        arquivo.seekp(0, arquivo.end);
	    arquivo.write((char *)&novo, sizeof(novo));
        arquivo.clear();
        
        // Escrevendo os dados da a��o no arquivo.
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
    // Se a senha for incorreta, o usu�rio n�o pode cadastrar um novo produto, retornando ao menu principal
    return total;
}
// Fun��o para listar todos os produtos
void listar_produtos(Produto produtos[], int total) {
	// Limpando a tela no sistema para mostrar a lista.
	system("cls");
    // Verifica se h� produtos cadastrados, se n�o houver, informa ao usu�rio que n�o h� produtos cadastrados.
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
	    cout << "  Pre�o: R$" << produtos[i].preco << endl;
	    cout << "  Quantidade: " << produtos[i].quantidade << endl;
	    cout << " _______________________________________________" << endl << endl;
	}
}

// Fun��o que imprime o hist�rico de a��es realizadas pelo Administrador
void visualizar_historicoAc(HistoricoAcoes acoes[],int total){
	system("cls");
    // Verifica se h� produtos cadastrados, se n�o houver, informa ao usu�rio que n�o h� produtos cadastrados
	if (total == 0) {
		cout << "\033[1;31m";
	    cout << " _______________________________________________" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|     Nenhuma a��o foi realizada no momento     |" << endl;
	    cout << "|_______________________________________________|" << endl << endl;
	    cout << "\033[0m";
	    return;
	}
	
	// Se houver produtos cadastrados, exibe a lista de produtos
	cout << " _______________________________________________" << endl;
	cout << "|                                               |" << endl;
	cout << "|          <<< HIST�RICO DE A��ES >>>           |" << endl;
	cout << "|_______________________________________________|" << endl << endl;
	
	// Imprimindo hist�rico por hist�rico
	for (int i = 0; i < total; i++) {
	    cout << " _______________________________________________" << endl;
	    cout << endl;
	    cout << "  ID: " << acoes[i].codigo << endl;
	    cout << "  Nome: " << acoes[i].nome_admin << endl;
	    cout << "  Tipo de A��o: " << acoes[i].tipo << endl;
	    cout << "  Produto: " << acoes[i].nome_produto << endl;
	    cout << " _______________________________________________" << endl << endl;
	}
}

void visualizar_historicoV(HistoricoVendas hisVendas[],int totalVendas){
	system("cls");
	
	float TotalVendasPreco = 0;
	
    // Verifica se h� produtos cadastrados, se n�o houver, informa ao usu�rio que n�o h� produtos cadastrados
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
	cout << "|         <<< HIST�RICO DE VENDAS >>>           |" << endl;
	cout << "|_______________________________________________|" << endl << endl;
	
	// Imprimindo hist�rico por hist�rico
	for (int i = 0; i < totalVendas; i++) {
		TotalVendasPreco += hisVendas[i].preco_total;
	    cout << " _______________________________________________" << endl;
	    cout << endl;
	    cout << "  ID: " << i << endl;
	    cout << "  Usu�rio que comprou o produto: " << hisVendas[i].nome_user << endl;
	    cout << "  Produto: " << hisVendas[i].nome_prod << endl;
	    cout << "  Quantidade: " << hisVendas[i].quantidade << endl;
	    cout << "  Pre�o total: " << hisVendas[i].preco_total << endl;
	    cout << " _______________________________________________" << endl << endl;
	}
	cout << " >> LUCRO TOTAL: " << TotalVendasPreco << endl; 
	cout << " _______________________________________________" << endl << endl;
}

// Fun��o para editar um produto existente na lista.
int editar_produto(Produto produtos[], fstream &arquivo, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac, Admin user[],int totalAdmin ) {
	// Limpa a tela para mostrar o editor de produto
    system("cls");
	// Verificando a senha administradora para acessar o editor de produto
    char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);

    // Se a senha for correspondente, o usu�rio pode editar um produto
    if(verificadorSenha) {
    	// Criando novas vari�veis com struct que ser�o respons�veis para inserirem no arquivo.
    	Produto editar;
    	HistoricoAcoes novoH;
    	
    	// Vari�veis para identificar um produto dentro da lista.
        int id_produto;
        bool encontrado = false;
        
        // Impress�o do Editor de Produto
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
                
                // Entrada na descri��o do produto
                cout << endl <<  ">> Tipo do produto: ";
                cin.getline(editar.tipo, 50);
    
                // Entrada no pre�o do produto
                cout << endl << ">> Pre�o do produto: ";
                cin >> editar.preco;

                // Entrada na quantidade do produto
                cout << endl << ">> Quantidade em estoque: ";
                cin >> editar.quantidade;

				// Inserindo o produto editado ao array de produto.		
                produtos[id_produto] = editar;

				// Limpando a tela para imprimir que o editar executou com sucesso.
                system("cls");
                
                // Impress�o do editado
                cout << "\033[1;32m";
		    	cout << " _______________________________________________" << endl;
				cout << "|                                               |" << endl;
				cout << "|        PRODUTO ATUALIZADO COM SUCESSO!        |" << endl;
				cout << "|_______________________________________________|" << endl << endl;
				cout << "\033[0m";
			
				// Reescrevendo o dado modificado.
			    arquivo.seekp(-streamoff(sizeof(editar)), arquivo.cur);
			    arquivo.write((char*)&editar, sizeof(editar));
			    
			    // Registrando a a��o do administrador para inserir-lo no hist�rico.
		        novoH.codigo = total_acoes;
		        strcpy(novoH.nome_admin,resUser);
		        strcpy(novoH.tipo, "Editador de produto");
				strcpy(novoH.nome_produto, editar.nome);
				acoes[total_acoes] = novoH;
				
				// Escrevendo os dados da a��o no arquivo.
				arquivo_ac.seekp(0,arquivo_ac.end);
        		arquivo_ac.write((char *)&novoH,sizeof(novoH));
        		arquivo_ac.clear();
        		total_acoes++;

			    return 0;
		    }
	    }
	    // Se caso varreu todos os n�mero e n�o encontrou, imprimir que o produto n�o foi encontrado.
	    if(!encontrado){
			system("cls");
			cout << "\033[1;31m";
			cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|            PRODUTO N�O ENCONTRADO!            |" << endl;
			cout << "|_______________________________________________|" << endl << endl;
			cout << "\033[0m";
		}
        arquivo.clear();
    }
    return 1; 
}
// Fun��o para remover um produto
int remover_produto(Produto produtos[],int total, fstream &arquivo, Admin user[],int totalAdmin, HistoricoAcoes hisA[], fstream &arquivo_ac,int &total_acoes) {
	// Limpando a tela para imprimir a parte de remover produto
	system("cls");
    // Verificando a senha administradora para acessar o removedor de produto
    char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Caso retornar verdadeiro, executar o programa normalmete.
    if(verificadorSenha){
    	// Criando vari�veis para pesquisa e confirma��o
		int id_produto;
        int confirmacao;
        HistoricoAcoes novoH;
        
        // Impress�o do Editor de Produto
        cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|             REMOVEDOR DE PRODUTO              |" << endl;
		cout << "|_______________________________________________|" << endl << endl;

        // Entrada no ID do produto que deseja remover
        cout << " >> Digite o ID do produto que deseja remover: ";
        cin >> id_produto;

        // Confirmando a remo��o do produto
        cout << endl << " >> Deseja remover o produto " << produtos[id_produto].nome << "? (1 - Sim, 0 - N�o): ";
        cin >> confirmacao;

        // Se o usu�rio confirmar a remo��o, o produto � removido do array
        if (confirmacao == 1) {
        	// Registrando a a��o do administrador para inserir-lo no hist�rico.
	        novoH.codigo = total_acoes;
	        strcpy(novoH.nome_admin,resUser);
	        strcpy(novoH.tipo, "Removeu um produto");
			strcpy(novoH.nome_produto, produtos[id_produto].nome);
			hisA[total_acoes] = novoH;
        	
        	// Apagando aquele dado e passando todos produtos a frente dele para uma casa atr�s.
            for(int i = id_produto; i < total - 1; i++) {
                produtos[i] = produtos[i + 1]; // Move os produtos para preencher o espa�o.
            }
            // Subtraindo menos um do total de produtos.
            total--;
            
            // Limpndo a tela para imprimir o sucesso da remo��o.
            system("cls");
            
            // Impress�o do resultado.
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
            
            
            // Escrevendo os dados da a��o no arquivo.
			arquivo_ac.seekp(0,arquivo_ac.end);
        	arquivo_ac.write((char *)&novoH,sizeof(novoH));
       		arquivo_ac.clear();
       		total_acoes++;
        }
        // Se o usu�rio n�o confirmar a remo��o, uma mensagem � exibida
        else{
        	// Limpando a tela para imprimir o resultado.
        	system("cls");
        	
        	// Impress�o do resultado.
        	cout << "\033[1;31m";
        	cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|               REMO��O CANCELADA!              |" << endl;
			cout << "|_______________________________________________|" << endl << endl;
			cout << "\033[0m";
        }
        return total;
	}
    return total;
}

// Fun��o que cadastrar um usu�rio Administrador ao sistema
void cadastro_admin(Admin user[],int &totalAdmin, fstream &admin_arq, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac){
	// Declarando a vari�vel respons�vel por trazer o nome do administrador que ser� respons�vel pelo cadastro
	char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Limpando a tela para a impress�o do programa.
    system("cls");
    
    // Se caso o sistema de verifica��o retornar verdadeiro, prosseguir com o programa.
	if(verificadorSenha){
		// Criando novas vari�veis para o armazenamento e integra��o ao arquivo.
		Admin novo;
		HistoricoAcoes novoH;
		
		// Impress�o do cadastro de admin
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
        
        // Registrando a a��o do admin do cadastro de admin.
        novoH.codigo = total_acoes;
        strcpy(novoH.nome_admin,resUser);
        strcpy(novoH.tipo, "Cadastro de usu�rio administrador");
		strcpy(novoH.nome_produto," ");
		acoes[total_acoes] = novoH;
		
		// Registrando o novo admin no arquivo.
        admin_arq.seekp(0, admin_arq.end);
	    admin_arq.write((char *)&novo, sizeof(novo));
        admin_arq.clear();
        
        // Registrando o hist�rico de a��o do admin no arquivo
        arquivo_ac.seekp(0,arquivo_ac.end);
        arquivo_ac.write((char *)&novoH,sizeof(novoH));
        total_acoes++;
        arquivo_ac.clear();
        
        // Limpa a tela do terminal para impress�o do resultado
        system("cls");
        
        // Impress�o do resultado
        cout << "\033[1;32m";
		cout << " _______________________________________________" << endl;
		cout << "|                                               |" << endl;
		cout << "|          ADMIN CADASTRADO COM SUCESSO!        |" << endl;
		cout << "|_______________________________________________|" << endl << endl;
		cout << "\033[0m";
	}
}

// Fun��o de realizar venda de um produto.
int realizarVenda(Produto produtos[], int totalProduto, fstream &arquivo, HistoricoAcoes acoes[], int &total_acoes, fstream &arquivo_ac, Admin user[],int totalAdmin, int &total_vendas, fstream &vendasArq, HistoricoVendas hisVenda[]){
	// Limpa a tela para mostrar s� a parte de venda
	system("cls");
	
	// Declarando a vari�vel respons�vel por trazer o nome do administrador que ser� respons�vel pelo cadastro
	char resUser[50];
    bool verificadorSenha = senha(user,totalAdmin,resUser);
    
    // Dando cin.ignore para n�o houve conflitos com as entradas a seguir
    cin.ignore();
    
    // Se a senha for correspondente, o usu�rio pode editar um produto
    if(verificadorSenha){
    	// Criando novas vari�veis struct para armazenar os hist�rico.
		HistoricoAcoes novoH;
		
		// Vari�veis para a pesquisa, inserir quantidade e confirmar a compra do produto
		char pesquisaProduto[50];
		bool confirmed = false;
		int quantidade;
		
		// Enquanto a compra ainda n�o for confirmada, imprime novamente o menu de venda.
		while(!confirmed){
			// Impress�o do menu de venda.
			cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|                REALIZAR VENDA                 |" << endl;
			cout << "|_______________________________________________|" << endl << endl;
		
			cout << " _______________________________________________" << endl;
			cout << "|                                               |" << endl;
			cout << "|                PRODUTOS ATUAIS                |" << endl;
			cout << "|_______________________________________________|" << endl <<endl;
			
			// Imprimindo produto por produto, com seus pre�os por unidade.
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
					// Se enquanto o usu�rio for inserindo quandidade maiores que o produto j� tem no estoque, repetir a pergunta
					while(quantidade > produtos[i].quantidade){
						// Imprimindo o nome do produto.
						cout << endl << " >> Produto Selecionado: "<<produtos[i].nome << endl;
						
						// Entrada na quantidade desejada.
						cout << endl << " >> Digite a quantidade que deseja levar: ";
						cin >> quantidade;
						
						// Caso o usu�rio inseriu uma quantidade maior do que existe no estoque, emitir um alerta.
						if(quantidade > produtos[i].quantidade){
							system("cls");
							cout << " >> Ops! Voc� selecionou uma quantidade ultrapassada, por favor insira uma quantidade menor " << endl;
	  	  	  	  	    }	
					}
					// Calculando o pre�o total do produto.
					double preco_total = quantidade * produtos[i].preco;
					
					// Emitindo o resultado ao escolher o produto e a quantidade.
					cout << "_________________________________________________"<< endl << endl;
					cout << " >> Nome do produto: "<< produtos[i].nome << endl;
					cout << " >> Quantidade: "<< quantidade << endl;
					cout << " >> Pre�o total: " << preco_total << endl;
					cout << "_________________________________________________"<< endl << endl;
					
					// Confirma��o para finalizar a compra.
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
						
						// Impress�o do resultado.
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
								// Move os produtos para preencher o espa�o
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
						
						// Registrando a a��o do administrador para inserir-lo no hist�rico.
				        novoH.codigo = total_acoes;
				        strcpy(novoH.nome_admin,resUser);
				        strcpy(novoH.tipo, "Vendeu um produto ao usu�rio");
						strcpy(novoH.nome_produto, produtos[i].nome);
						acoes[total_acoes] = novoH;
						
						// Escrevendo os dados da a��o no arquivo.
						arquivo_ac.seekp(0,arquivo_ac.end);
				        arquivo_ac.write((char *)&novoH,sizeof(novoH));
				        total_acoes++;
				        arquivo_ac.clear();
				        
				        // Registrando o hist�rico de venda de um usu�rio
				        HistoricoVendas novoV;
				        strcpy(novoV.nome_prod,produtos[i].nome);
				        strcpy(novoV.nome_user,username);
				        novoV.quantidade = quantidade;
				        novoV.preco_total = preco_total;
				        hisVenda[total_vendas] = novoV;
				        
				        // Inserindo o registro no arquivo de hist�rico de vendas
				        vendasArq.seekp(0,vendasArq.end);
				        vendasArq.write((char *)&novoV,sizeof(novoV));
				        total_vendas++;
				        vendasArq.clear();
					}
					// Caso o usu�rio escreva N ou n, cancelar a compra e retornar ao menu;
					else{
						// Limpando a tela para a impress�o do resultado
						system("cls");
						
						// Impress�o do resultado.
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

// Fun��o principal do programa que dar� in�cio a tudo.
int main() {
    // Comando que integrar� acentos e caracteres do portugu�s.
    setlocale(LC_ALL, "Portuguese");
    
    // Declarando as vari�veis de structs
    Produto produtos[1000]; 		// Vari�vel que armazenar� cada produto
    HistoricoAcoes hisAcoes[1000];	// Vari�vel que armazenar� cada a��o do administrador
    HistoricoVendas hisVendas[1000];// Vari�vel que armazenar� cada venda realizada.
    Admin user[10];					// Vari�vel que armazenar� cada administrador registrado
    
    // Declarando as vari�veis de arquivo
    fstream produtos_arq;			// Vari�vel que executa o arquivo de produtos
    fstream historico_acoes_arq;	// Vari�vel que executa o arquivo de hist�rico de a��es
    fstream admin_arq;				// Vari�vel que executa o arquivo de administradores registrados
    fstream historico_vendas_arq;	// Vari�vel que executa o arquivo de hist�rico de vendas;
    
    // Vari�veis de contadores
    int total_produtos = 0;			// Total de Produtos
    int total_acoes = 0;			// Total de Hist�rico de A��es
    int totalAdmin = 0;				// Total de Administradores
    int totalVendas = 0;			// Total de vendas
    
    // Abrindo cada Arquivo e verificando se elas existem.
	
	// Lista com os dados do produto.
	produtos_arq.open("lista_produtos.txt", ios::in | ios::out | ios::binary);
	// Caso n�o encontrado a lista de produtos, criar um novo arquivo.
	if(!produtos_arq.is_open()){
		produtos_arq.open("lista_produtos.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
	
	// Lista com os hist�ricos de a��es do usu�rio
	historico_acoes_arq.open("historico_acoes.txt", ios::in | ios::out | ios::binary);
	// Caso n�o encontrado o hist�rico, criar um novo arquivo.
	if(!historico_acoes_arq.is_open()){
		historico_acoes_arq.open("historico_acoes.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
	
	// Lista com os dados dos administradores
	admin_arq.open("admin-user.txt", ios::in | ios::out | ios::binary);
	// Caso n�o encontrado a lista de administradores, criar um novo arquivo.
	if(!admin_arq.is_open()){
		admin_arq.open("admin-user.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
 
    // Lista com os hist�ricos de venda.
    historico_vendas_arq.open("historico_vendas.txt", ios::in | ios::out | ios::binary );
    // Caso n�o encontrado o hist�rico, criar um novo arquivo.
    if(!historico_vendas_arq.is_open()){
		historico_vendas_arq.open("historico_vendas.txt", ios::in | ios::out | ios::binary | ios::trunc);
	}
	
	
    // Armazenando a cont�gem de cada contador.
	total_produtos = lerProdutoArquivo(produtos,produtos_arq);			// Contando a quantidade de produtos no arquivo.
	total_acoes = lerHistoricoAcoes(hisAcoes,historico_acoes_arq);		// Contando a quantidade de a��es no arquivo.
	totalAdmin =  lerAdministradorArq(user,admin_arq);					// Contando a quantidade de Administradores no arquivo.
	totalVendas = lerHistoricoVendas(hisVendas,historico_vendas_arq);   // Contando a quantidade de vendas no arquivo.
	
	// Declarando a vari�vel de op��o para o menu principal
    int op = 0;
    
    // Loop do menu principal
    while (op != 9) {
        cout << " _______________________________________________" << endl;
        cout << "|                                               |" << endl;
    	cout << "|       <<<<<< HEART'S MUSIC SYSTEM >>>>>>      |" << endl;
	    cout << "|_______________________________________________|" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|              ESCOLHA UMA OP��O                |" << endl;
	    cout << "|_______________________________________________|" << endl;
	    cout << "|                                               |" << endl;
	    cout << "|  [1] Cadastrar um produto                     |" << endl;
	    cout << "|  [2] Listar todos os produtos                 |" << endl;
	    cout << "|  [3] Remover um produto do estoque            |" << endl;
	    cout << "|  [4] Realizar venda(s)                        |" << endl;
	    cout << "|  [5] Atualizar dados de um produto            |" << endl;
	    cout << "|  [6] Visualizar hist�rico de a��es            |" << endl;
	    cout << "|  [7] Visualizar hist�rico de vendas           |" << endl;
	    cout << "|  [8] Adicionar um usu�rio administrador       |" << endl;
	    cout << "|  [9] Sair do programa                         |" << endl;
	    cout << "|  [10] Cr�ditos                                |" << endl;
	    cout << "|_______________________________________________|" << endl<<endl;
	    
	   	// Entrada na op��o do menu 
	    cout << "_________________________________________________" << endl<<endl;
	    cout << ">> Digite a op��o desejada: ";
        cin >> op;

        // Verifica qual a op��o inserida se corresponde as op��es mostrada no menu
        switch (op) {
            // Caso o usu�rio escolha a op��o 1, o programa chama a fun��o de Cadastrar um Produto
            case 1:
                total_produtos = cadastro_de_produto(produtos, total_produtos, produtos_arq, hisAcoes,total_acoes, historico_acoes_arq,user,totalAdmin);
                break;
            // Caso o usu�rio escolha a op��o 2, o programa chama a fun��o de Listar os produtos
            case 2:
                listar_produtos(produtos, total_produtos);
                break;
            // Caso o usu�rio escolha a op��o 3, o programa chama a fun��o de Remover um Produto
            case 3:
                total_produtos = remover_produto(produtos, total_produtos, produtos_arq,user,totalAdmin,hisAcoes,historico_acoes_arq,total_acoes);
                break;
            // Caso o usu�rio escolha a op��o 4, o programa chama a fun��o de Realizar uma Venda
            case 4:
                realizarVenda(produtos, total_produtos, produtos_arq, hisAcoes,total_acoes,historico_acoes_arq,user,totalAdmin,totalVendas,historico_vendas_arq,hisVendas);
                break;
            // Caso o usu�rio escolha a op��o 5, o programa chama a fun��o de Editar um produto
            case 5:
                editar_produto(produtos,produtos_arq, hisAcoes,total_acoes, historico_acoes_arq,user,totalAdmin);
                break;
            // Caso o usu�rio escolha a op��o 6, o programa chama a fun��o de Listar o Hist�rico de A��es.
            case 6:
            	visualizar_historicoAc(hisAcoes,total_acoes);
            	break;
            // Caso o usu�rio escolha a op��o 7, o programa chama a fun��o de Listar o Hist�rico de Vendas.
            case 7:
            	visualizar_historicoV(hisVendas,totalVendas);
            	break;
            // Caso o usu�rio escolha a op��o 8, o programa chama a fun��o de Cadastrar um Administrador.
            case 8:
            	cadastro_admin(user, totalAdmin, admin_arq, hisAcoes,total_acoes,historico_acoes_arq);
            	break;
            // Caso o usu�rio escolha a op��o 8, o programa encerrar�
            case 9:
            	// Limpando a tela para a impress�o da Sa�da.
            	system("cls");
            	
            	// Impress�o de despedida.
            	cout << "\033[1;32m";
                cout << " _______________________________________________" << endl;
				cout << "|                                               |" << endl;
				cout << "|        SAINDO DO PROGRAMA... AT� LOGO!        |" << endl;
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
            // Caso o usu�rio escolha a op��o 10, o programa exibe os membros da equipe respons�veis pelo projeto
            case 10:
            	// Limpando a tela para a impress�o dos Cr�ditos
            	system("cls");
            	
            	// Impress�o dos cr�ditos
            	cout << "\033[1;36m";
                cout << " _______________________________________________" << endl;
				cout << "|                                               |" << endl;
				cout << "|             <<< CR�DITOS FINAIS >>>           |" << endl;
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
            // Caso o usu�rio escolha uma op��o inv�lida, o programa informa que a op��o � inv�lida e volta ao menu principal
            default:
                cout << "Op��o inv�lida! Tente novamente." << endl;
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