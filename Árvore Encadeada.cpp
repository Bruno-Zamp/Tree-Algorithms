/*/ ==========================================

                Programa: Árvore Encadeada em C++
        Descrição: Árvore encadeada com filhos ilimitados
                    Bruno de Almeida Zampirom
                          158788@upf.br

                  Ciências da Computação - UPF
                             2017

=========================================== /*/

#include <iostream>
#include <vector>
using namespace std;
struct nodo
{
    string info;
    nodo *pai;
    vector<nodo*> filho;
};
nodo* raiz=nullptr;

//==============================================================================
bool alocarRaiz( nodo* &raiz, string valor)
{
    raiz=new(nothrow) nodo;
    raiz->pai=nullptr;
    raiz->info=valor;
    return true;
}

//==============================================================================
nodo *localizar(string rotulo, nodo*end)
{
    nodo *achou;
    if(end->info==rotulo)return end;
    for(auto ita : end->filho)
    {
        achou=localizar(rotulo, &*ita );
        if(achou!=nullptr)return achou;
    }
    return(nullptr);
}

//==============================================================================
bool inserirfilho(nodo*raiz, string valor,string valorpai)
{
    nodo *pai=localizar(valorpai, raiz);
    if(pai==nullptr || localizar(valor, raiz)!=nullptr)return false;     // Caso o valor pai não foi encontrado ou o valor a ser inserido já exista
    nodo *novo= new(nothrow) nodo;
    novo->info=valor;
    novo->pai=pai;
    pai->filho.push_back(&*novo);
    return true;
}

//==============================================================================
void mostra( nodo *end )
{
    static int cont;
    if ( end == raiz )
        cont = 0;
    for(int i = 0 ; i < cont ; i++)
        cout << "  ";
    cout<<end->info;
    for(int i = 0 ; i < 21-(cont*2+end->info.size()) ; i++)
        cout<<".";
    cout<<endl;
    for(auto ita : end->filho)
    {
        cont++;
        mostra(&*ita);
        cont--;
    }
}

//==============================================================================
bool removernodo(string rotulo)
{
    nodo *exc=localizar(rotulo, raiz);
    if(exc==nullptr)return false;
    if(exc==raiz)raiz=nullptr;
    else
    {
        for(auto it=exc->pai->filho.begin() ; it != exc->pai->filho.end() ; ++it ) //   O pai para de apontar para ele
        {
            if(*it == exc)
            {
                exc->pai->filho.erase(it);
                break;
            }
        }
    }
    exc->filho.clear();                          // Removendo filho
    delete exc;
}

//==============================================================================
int main()
{
    int n;
    cout<<"Bruno de Almeida Zampirom - 158788@upf.br \n\n";
    while(1)
    {
        cout<<"0 - Para sair"<<endl;
        cout<<"1 - Para inserir novo Nodo"<<endl;
        cout<<"2 - Para remover um Nodo"<<endl;
        cout<<"3 - Para buscar um Nodo"<<endl;
        cout<<"4 - Para Mostrar a arvore"<<endl;
        cin>>n;
        cout<<endl;
        if(n==0)
            break;
        if(n==1)
        {
            string info,infopai;
            cout<<"Digite o valor a ser incluido : ";
            cin>>info;
            if(raiz==nullptr)
                if(alocarRaiz(raiz,info))
                    cout<<"Valor inserido com sucesso!\n";
                else
                    cout<<"------( Erro na inclusao )------\n";
            else
            {
                cout<<"Digite o seu respectivo pai : ";
                cin>>infopai;
                if(inserirfilho(raiz,info,infopai))
                    cout<<"Valor inserido com sucesso!\n";
                else
                    cout<<"------( Erro na inclusao )------\n";
            }
        }
        if(n==2)
        {
            string info;
            cout<<"Digite o valor a ser removido : ";
            cin>>info;
            if(removernodo(info))
                cout<<"Valor removido com sucesso!\n";
            else
                cout<<"------( Erro na remocao )------\n";
        }
        if(n==3)
        {
            if(raiz==nullptr)cout<<"Arvore vazia\n"<<endl;
            else
            {
            string info;
            cout<<"Digite o valor a ser buscado na arvore : ";
            cin>>info;
            if(localizar(info,raiz)==nullptr)
                cout<<"Valor nao esta presente"<<endl;
            else if(localizar(info,raiz)==raiz)
                cout<<"Valor e a raiz da arvore"<<endl;
            else
                cout<<"Valor esta presente na arvore"<<endl;
            cout<<endl;
            }
        }
        if(n==4)
        {
            if(raiz!=nullptr)mostra(raiz);
            cout<<endl;
        }
    }
}
