/*/ =====================================================================

              Programa: Árvore Binária de Pesquisa em C++
        Descrição: ABP com remoção e derivação de subárvores
                      Bruno de Almeida Zampirom
                            158788@upf.br

                    Ciências da Computação - UPF
                               2017

====================================================================== /*/

#include <iostream>
using namespace std;
struct nodo
{
    double info;                                        // Valor do programa em doble
    nodo *esq, *dir, *pai;
};
nodo* raiz = nullptr;
bool alocarRaiz(nodo* &raiz, double valor)
{
    raiz = new(nothrow) nodo;
    raiz->esq = raiz->dir = raiz->pai =nullptr; //pai, filho a esquerda e filho a direita recebem null
    raiz->info = valor; //raiz recebe o valor
    return true;
}
bool Busca(nodo*SUP, double valor)
{
    if (valor == SUP->info)
        return true;
    if (valor > SUP->info) //se o valor for maior que o nodo SUPerior continua a busca a direita
    {
        if (SUP->dir != nullptr) //caso ainda tenha filhos a direita
            Busca(SUP->dir, valor);
        else                  //Valor não encontrado
            return false;
    }
    else if (valor < SUP->info) //caso o valor seja maior que o nodo vai para direita
    {
        if (SUP->esq != nullptr) //caso ainda tenha algum filho a esquerda
            Busca(SUP->esq, valor);
        else                  //insere novo filho
            return false;
    }
}
bool inserirnodo(nodo*SUP, double valor)
{
    //if(busca(raiz,valor))return false; //para não inserir valores iguais
    cout << "PAI" << SUP->info << endl;
    if (valor >= SUP->info) //caso o valor seja maior que o nodo vai para direita
    {
        if (SUP->dir != nullptr) //caso ainda tenha algum filho a esquerda
            inserirnodo(SUP->dir, valor);
        else                  //insere novo filho
        {
            nodo *novo = new(nothrow) nodo;
            novo->esq = novo->dir = nullptr;
            novo->info = valor;
            novo->pai = SUP;
            SUP->dir = novo;
            return true;
        }
    }
    else if (valor < SUP->info) //caso o valor seja maior que o nodo vai para direita
    {
        if (SUP->esq != nullptr) //caso ainda tenha algum filho a esquerda
            inserirnodo(SUP->esq, valor);
        else                  //insere novo filho
        {
            nodo *novo = new(nothrow) nodo;
            novo->esq = novo->dir = nullptr;
            novo->info = valor;
            novo->pai = SUP;
            SUP->esq = novo;
            return true;
        }
    }
    else
        return false;
}
nodo* locprox(nodo*SUP)
{
    if (SUP->esq != nullptr) //caso ele ainda tenha um filho a esquerda
        locprox(SUP->esq);
    else return SUP;
}
bool retirarnodo(nodo* SUP, double valor)
{
    if (valor == SUP->info)
    {
        if (SUP->esq == nullptr && SUP->dir == nullptr) //caso o nodo a ser excluido (eu) for um nodo folha...
        {
            if (SUP == raiz) //se eu for a raiz
                raiz = nullptr;
            else if (SUP == SUP->pai->esq)//se eu for um filho a esquerda
                SUP->pai->esq = nullptr;
            else if (SUP == SUP->pai->dir)//se eu for um filho a direita
                SUP->pai->dir = nullptr;
        }
        if (SUP->esq == nullptr && SUP->dir != nullptr) //caso o nodo a ser excluido (eu) tenha um filho a direita mas não a esquerda...
        {
            if (SUP == raiz) //se eu sou uma raiz
            {
                raiz = SUP->dir; //a raiz passa a ser meu filho a direita
                SUP->dir->pai = nullptr; //meu filho passa a nao ter pai
            }
            else if (SUP == SUP->pai->esq) //se eu sou um filho a esquerda
            {
                SUP->pai->esq = SUP->dir; //meu pai aponta para o meu filho a direita
                SUP->dir->pai = SUP->pai; //meu filho a direita (único) aponta para o meu pai
            }
            else if (SUP == SUP->pai->dir) //se eu sou um filho a direita
            {
                SUP->pai->dir = SUP->dir; //meu pai passa a apontar para o meu filho a direita
                SUP->dir->pai = SUP->pai; //meu filho direita passa a apontar para o meu pai
            }
        }
        if (SUP->esq != nullptr && SUP->dir == nullptr) //caso o nodo a ser excluido tenha um filho a esquerda mas não a direita...
        {
            if (SUP == raiz) //se eu sou uma raiz
            {
                SUP->dir->pai = nullptr; // meu filho passa a nao ter pai
                raiz = SUP->esq; // a raiz passa a ser meu filho a esquerda
            }
            else if (SUP == SUP->pai->esq) //se eu sou um filho a esquerda
            {
                SUP->pai->esq = SUP->esq; //meu pai passa a apontar para o meu filho a esquerda
                SUP->esq->pai = SUP->pai; //meu filho a esquerda passa a apontar para o meu pai
            }
            else if (SUP == SUP->pai->dir)//se eu sou um filho a direita
            {
                SUP->pai->dir = SUP->esq; //meu pai passa a apontar para o meu filho a esquerda
                SUP->esq->pai = SUP->pai; //meu filho a esquerda passa a apontar para o meu pai
            }
        }
        if (SUP->esq != nullptr && SUP->dir != nullptr) //caso eu tenha um filho a direita e a esquerda
        {
            auto aux = locprox(SUP->dir);
            /*para a substituição pelo anterior altera-se a linha de cima por:
            auto aux = locprox(SUP->esq);
            e dentro da função 'locprox' por:
            	if (SUP->dir != nullptr)
            locprox(SUP->dir);
            else return SUP;
            */
            SUP->info = aux->info; // o nodo posterior ao meu passa a assumir meu lugar.
            retirarnodo(aux, aux->info); //retira o nodo encontrado.
            return true;
        }
        delete SUP;
        return true;
    }
    else if (valor > SUP->info) //se o valor for maior que o nodo SUPerior continua a busca a direita
    {
        if (SUP->dir != nullptr) //caso ainda tenha filhos a direita
            retirarnodo(SUP->dir, valor);
        else                  //Valor não encontrado
            return false;
    }
    else if (valor < SUP->info) //caso o valor seja maior que o nodo vai para direita
    {
        if (SUP->esq != nullptr) //caso ainda tenha algum filho a esquerda
            retirarnodo(SUP->esq, valor);
        else                  //insere novo filho
            return false;
    }
}
void pre_esq(nodo*it)
{
    cout << it->info << " "; //R
    if (it->esq != nullptr) //E
        pre_esq(it->esq);
    if (it->dir != nullptr) //D
        pre_esq(it->dir);
}
void pre_dir(nodo*it)
{
    cout << it->info << " "; //R
    if (it->dir != nullptr) //D
        pre_dir(it->dir);
    if (it->esq != nullptr) //E
        pre_dir(it->esq);
}
void infix_esq(nodo*it)
{
    if (it->esq != nullptr) //E
        infix_esq(it->esq);
    cout << it->info << " "; //R
    if (it->dir != nullptr) //D
        infix_esq(it->dir);
}
void infix_dir(nodo*it)
{
    if (it->dir != nullptr) //D
        infix_dir(it->dir);
    cout << it->info << " "; //R
    if (it->esq != nullptr) //E
        infix_dir(it->esq);
}
void pos_esq(nodo*it)
{
    if (it->esq != nullptr) //E
        pos_esq(it->esq);
    if (it->dir != nullptr) //D
        pos_esq(it->dir);
    cout << it->info << " "; //R
}
void pos_dir(nodo*it)
{
    if (it->dir != nullptr) //D
        pos_dir(it->dir);
    if (it->esq != nullptr) //E
        pos_dir(it->esq);
    cout << it->info << " "; //R
}
int main()
{
    int n;
    cout<<"Bruno de Almeida Zampirom - 158788@upf.br\n"<<endl;
    while (1)
    {
        cout << "0 - Para sair" << endl;
        cout << "1 - Para inserir um novo nodo" << endl;
        cout << "2 - Para buscar um valor" << endl;
        cout << "3 - Para retirar um nodo" << endl;
        cout << "4 - Para mostrar percurso com diferentes caminhamentos" << endl;
        cin >> n;
        switch (n)
        {
        case 0:
            return 0;
        case 1:
            if (raiz == nullptr)
            {
                double valor;
                cout << "  Digite o valor a ser inserido na Raiz: ";
                cin >> valor;
                if (alocarRaiz(raiz, valor))
                    cout << "   Raiz incluida com sucesso!" << endl;
                else
                    cout << "   Erro na inclusao" << endl;
            }
            else
            {
                int valor;
                cout << "  Digite o valor a ser inserido: ";
                cin >> valor;
                if (inserirnodo(raiz, valor))
                    cout << "Filho incluido com sucesso!" << endl;
                else
                    cout << "Erro na inclusao" << endl;
            }
            break;
        case 2:
            if (raiz == false)
            {
                cout << "  A Arvore Binaria de pesquisa esta vazia" << endl;
                break;
            }
            double valor;
            cout << "  Digite o valor a ser consultado: ";
            cin >> valor;
            if (Busca(raiz, valor))
                cout << "   Valor encontrado!" << endl;
            else
                cout << "   Valor nao encontrado!" << endl;
            break;
        case 3:
            if (raiz == false)
            {
                cout << "  A Arvore Binaria de pesquisa esta vazia" << endl;
                break;
            }
            cout << "  Digite o valor a ser retirado: ";
            cin >> valor;
            if (retirarnodo(raiz, valor))
                cout << "   Valor retirado!" << endl;
            else
                cout << "   Valor nao encontrado!" << endl;
            break;
        case 4:
            cout << "   1 - Para caminhamento Pre-fixado a esquerda" << endl;
            cout << "   2 - Para caminhamento Pre-fixado a direita" << endl;
            cout << "   3 - Para caminhamento Infixado a esquerda" << endl;
            cout << "   4 - Para caminhamento Infixado a direita" << endl;
            cout << "   5 - Para caminhamento Pos-fixado a esquerda" << endl;
            cout << "   6 - Para caminhamento Pos-fixado a direita" << endl;
            cout << endl;
            cout << "    Digite o numero da opcao (0 para sair) ";
            int a;
            cin >> a;
            if (a == 0 || raiz == nullptr);
            else if (a == 1)pre_esq(raiz);
            else if (a == 2)pre_dir(raiz);
            else if (a == 3)infix_esq(raiz);
            else if (a == 4)infix_dir(raiz);
            else if (a == 5)pos_esq(raiz);
            else if (a == 6)pos_dir(raiz);
            cout << endl;
            break;
        }
    }
}
