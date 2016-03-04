#include <iostream>
#include <fstream> // abrir fluxo de entrada/saida

using namespace std;

typedef struct{

    char aux[3];
    int ponto;

    }ficha;

int main ( void ) {

    //ficha vet[3];
    ficha novo, compara;
    char letra;
    int qtd;
    int cont = 0;

    char *ranking = "C:\\Users\\pedro.fcsgaldino\\Desktop\\PastaDeHoje\\Ranking.txt";

    fstream arquivo("Ranking.txt");

    //if( !arquivo )
    if( arquivo == 0){//erro
		// erro no processo
		cout << "O arquivo nгo pode ser aberto!";
		return 1;
	}
    cout <<"-----------------------------------------------------------------\n";
    cout <<"|             R A N K I N G   D E   V I T O R I A S             |\n";
    cout <<"-----------------------------------------------------------------\n\n";
    // lendo o arquivo por tipos


        cout << "NICK ATE 3 LETRAS: \n";

        cout <<"Insira o nick name do Player 1: ";
        cin >> novo.aux;

        cout <<"Pontos: ";
        cin >> novo.ponto;
        cout<<endl;

        cout <<"Insira o nick name do Player 2: ";
        cin >> compara.aux;

        cout <<"Pontos: ";
        cin >> compara.ponto;
        cout<<endl;

        if (compara.ponto == novo.ponto){
            arquivo << "Player 1 e Player 2 empataram!" <<endl;
            arquivo.close();
        }

        if (compara.ponto > novo.ponto){
            arquivo << "Nick Name: " << compara.aux <<" - Pontos "<< compara.ponto<< '\0' <<endl;
            arquivo.close();
        }
        else{
            arquivo << "Nick Name: " << novo.aux <<" - Pontos "<< novo.ponto<< '\0' <<endl;
            arquivo.close();
            }

    ifstream in (ranking);

    if( !in ){
        // erro no processo
		cout << "O arquivo nгo pode ser aberto!\n";
        return 1; //erro
    }//a funзгo good checa se o estado da stream estah bom  para operacao de E/S

    if (novo.ponto < compara.ponto){
        compara.ponto = novo.ponto;
        //compara.aux = novo.aux;
    }

    while( in.good() ){
        // in serб zero quando eof (fim do arquivo) for encontrado
        letra = in.get();
        cout << letra;
    }
    // fecha o arquivo
    in.close();

    return 0; // retorno sucesso
}

