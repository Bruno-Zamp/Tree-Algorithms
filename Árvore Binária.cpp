/* =======================================

        Programa: Árvore Binária em C++
            Bruno de Almeida Zampirom
                   158788@upf.br

          Ciências da Computação - UPF
					2017

==========================================*/

#include <iostream>
using namespace std;
struct nodo
{
    string info;
    nodo *esq,*dir,*pai;                                        // Como é arvore binaria contém 2 filhos e um pai para facilitar a programação
};
nodo* raiz=nullptr;
bool alocarRaiz( nodo* &raiz, string valor)
{
    raiz=new(nothrow) nodo;
    raiz->esq= raiz->dir= nullptr;
    raiz->pai=nullptr;
    raiz->info=valor;
    return true;
}
nodo *localizar(string rotulo, nodo*end)             // Procura o valor e retorna o nodo do rotulo buscado através de recursividade
{
    nodo *achou;
    if (end->info == rotulo )  return end;               // Caso valor seja do nodo end
    else
    {
        if (end->esq != nullptr)
        {
            achou = localizar( rotulo, end->esq );    // Caso tenha filho a esquera continua a busca pela esq
            if (achou != nullptr) return achou;
        }
        if (end->dir != nullptr)
        {
            achou = localizar(rotulo, end->dir );       // Caso tenha filho a direita continua a busca pela dir
            if (achou != nullptr) return achou;
        }
    }
    return(nullptr);                                                // Caso não foi encontrado
}
bool inserirfilhoesq(nodo*raiz, string valor,string valorpai)
{
    auto *pai=localizar(valorpai, raiz);
    if(localizar(valor,raiz)!=nullptr)return false;     // Para não inserir valores iguais
    if(pai!=nullptr && pai->esq == nullptr)
    {
        nodo *novo= new(nothrow) nodo;
        novo->esq=novo->dir = nullptr;
        novo->info=valor;
        novo->pai=pai;
        pai->esq=novo;
        return true;
    }
    return false;
}
bool inserirfilhodir(nodo*raiz, string valor,string valorpai)
{
    auto *pai=localizar(valorpai, raiz);
    if(localizar(valor,raiz)!=nullptr)return false;     // Para não inserir valores iguais
    if(pai!=nullptr && pai->dir == nullptr)
    {
        nodo *novo= new(nothrow) nodo;
        novo->esq=novo->dir = nullptr;
        novo->info=valor;
        novo->pai=pai;
        pai->dir=novo;
        return true;
    }
    return false;
}
void mostra( nodo *raiz, nodo *end )
{
    static int cont;
    int i;
    if ( end == raiz )
        cont = 0;
    cout << "\n";
    for(i = 0 ; i < cont ; i++)
        cout << "  ";
    cout << end->info;
    if ( end->esq != nullptr )
    {
        cont++;
        mostra( raiz, end->esq );
        cont--;
    }
    if ( end->dir != nullptr )
    {
        cont++;
        mostra( raiz, end->dir );
        cont--;
    }
}
void pre_esq(nodo*it)
{
    cout<< it->info <<" ";       // R
    if(it->esq !=nullptr)           // E
        pre_esq(it->esq);
    if(it->dir!= nullptr)             // D
        pre_esq(it->dir);
}
void pre_dir(nodo*it)
{
    cout<< it->info <<" ";       // R
    if(it->dir!= nullptr)             // D
        pre_dir(it->dir);
    if(it->esq !=nullptr)           // E
        pre_dir(it->esq);
}
void infix_esq(nodo*it)
{
    if(it->esq !=nullptr)           // E
        infix_esq(it->esq);
    cout<< it->info <<" ";       // R
    if(it->dir!= nullptr)             // D
        infix_esq(it->dir);
}
void infix_dir(nodo*it)
{
    if(it->dir!= nullptr)             // D
        infix_dir(it->dir);
    cout<< it->info <<" ";       // R
    if(it->esq !=nullptr)           // E
        infix_dir(it->esq);
}
void pos_esq(nodo*it)
{
    if(it->esq !=nullptr)           // E
        pos_esq(it->esq);
    if(it->dir!= nullptr)             // D
        pos_esq(it->dir);
    cout<< it->info <<" ";       // R
}
void pos_dir(nodo*it)
{
    if(it->dir!= nullptr)             // D
        pos_dir(it->dir);
    if(it->esq !=nullptr)           // E
        pos_dir(it->esq);
    cout<< it->info <<" ";       // R
}
bool retirafolha(nodo *raiz, string valor)
{
    auto aux= localizar(valor,raiz);
    if(aux==nullptr || aux->esq!=nullptr || aux->dir!=nullptr)return false; //Caso o nodo procurado não seja um nodo folha...
    if(aux==raiz) //Caso o nodo bucado seja raiz;
        raiz=nullptr;
    else
    {
        if(aux->pai->esq==aux)
            aux->pai->esq=nullptr;
        if(aux->pai->dir==aux)
            aux->pai->dir=nullptr;
    }
    delete aux;
    return true;
}
int main()
{
    int n;
    cout<<"Bruno de Almeida Zampirom - (158788@upf.br) \n"<<endl;
    while(1)
    {
        cout<<"0 - Para sair"<<endl;
        cout<<"1 - Para inserir Raiz"<<endl;
        cout<<"2 - Para inserir Filho"<<endl;
        cout<<"3 - Para mostrar a Arvore"<<endl;
        cout<<"4 - Para retirar um nodo folha"<<endl;
        cout<<"5 - Para inserir valores automaticamente"<<endl;
        cout<<"6 - Para mostrar percurso com diferentes caminhamentos"<<endl;
        cin>>n;
        if(n==0)
            break;
        if(n==1)
        {
            if(raiz!=nullptr)
            {
                cout<<"Raiz ja existe!"<<endl;
            }
            else
            {
                string valor;
                cout<<"Digite o valor a ser inserido na Raiz: ";
                cin>>valor;
                if(alocarRaiz(raiz,valor))
                    cout<<"Raiz incluida com sucesso!"<<endl;
                else
                    cout<<"Erro na inclusao"<<endl;
            }
        }
        if(n==2)
        {
            if(raiz==nullptr)
            {
                cout<<"Nao pode inserir um filho sem ter uma raiz!"<<endl;
            }
            else
            {
            string v,vpai;
            char pos;
            bool aux=false;
            cout<<"Digite o valor a ser inserido: ";
            cin>>v;
            cout<<"Digite qual sera o pai do valor inserido: ";
            cin>>vpai;
            cout<<"Digite 'e' para incluir a esquerda ou 'd' para incluir a direita: ";
            cin>>pos;
            if(pos=='e')
                aux=inserirfilhoesq(raiz,v,vpai);
            else
                aux=inserirfilhodir(raiz,v,vpai);
            if(aux==true)
                cout<<"Filho incluido com sucesso!"<<endl;
            else
                cout<<"Erro na inclusao"<<endl;
            }
        }
        if(n==3)
        {
            if(raiz==nullptr)
            {
                cout<<"Arvore inexistente"<<endl;
            }
            else
            mostra(raiz,raiz);
            cout<<endl;
        }
        if(n==4)
        {
            if(raiz!=nullptr)
            {
            string aux;
            cout<<"Digite o valor a ser retirado: ";
            cin>>aux;
            if(retirafolha(raiz,aux))
                cout<<"Folha retirada com sucesso!"<<endl;
            else
                cout<<"Erro na exclusao"<<endl;
            }
            else
                cout<<"Arvore vazia!"<<endl;
        }
        if(n==5)
        {
            string aux="A",aux2;
            alocarRaiz(raiz,aux);
            for(int i=0; i<4; i++) // Código simples para inserir valores automaticamente, funciona inserindo inicialmente A como raiz. Então insere como filho à direita a próxima letra, seguido do filho a esquerda. Seguindo esse padrão por todo o for
            {
                aux2=aux;
                aux[0]++;
                inserirfilhodir(raiz,aux,aux2);
                aux[0]++;
                inserirfilhoesq(raiz,aux,aux2);
            }
        }
        if(n==6)
        {
            cout<<"   1 - Para caminhamento Pre-fixado a esquerda"<<endl;
            cout<<"   2 - Para caminhamento Pre-fixado a direita"<<endl;
            cout<<"   3 - Para caminhamento Infixado a esquerda"<<endl;
            cout<<"   4 - Para caminhamento Infixado a direita"<<endl;
            cout<<"   5 - Para caminhamento Pos-fixado a esquerda"<<endl;
            cout<<"   6 - Para caminhamento Pos-fixado a direita"<<endl;
            cout<<endl;
            cout<<"    Digite o numero da opcao (0 para sair) ";
            int a;
            cin>>a;
            if(a==0 || raiz==nullptr);
            else if(a==1)pre_esq(raiz);
            else if(a==2)pre_dir(raiz);
            else if(a==3)infix_esq(raiz);
            else if(a==4)infix_dir(raiz);
            else if(a==5)pos_esq(raiz);
            else if(a==6)pos_dir(raiz);
            cout<<endl;
        }
    }
}
