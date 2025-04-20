// INF110 - Trabalho pratico 3
//
// programa para ler, modificar e gravar uma imagem no formato PNM
//
// Autores: Andre Gustavo dos Santos			(criado em 16/06/14)
//          Andre Gustavo dos Santos			(modificado em 22/05/18)
//					Andre Gustavo dos Santos			(modificado em 13/09/21)
//					Andre Gustavo dos Santos			(modificado em 15/07/24)


#include <iostream>
#include <fstream>
#include <cstring>

const int MAXALTURA  = 500;				//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 500;

using namespace std;

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA][3];	//a imagem propriamente dita
	int largura, altura;						//dimensoes da imagem
	char tipo[4];										//tipo da imagem
	ifstream arqentrada;						//arquivo que contem a imagem original
	ofstream arqsaida;							//arquivo que contera a imagem modificada
	char comentario[200], c;				//auxiliares
	int i, j, valor[3], k;								//auxiliares

//*** LEITURA DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

	//*** Abertura do arquivo ***//
	arqentrada.open("C:\\Users\\Sousa\\Desktop\\output\\pasto.pnm", ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo imagem.pnm" << endl;
		return 0;
	}
//***************************//


//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();		//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
	} 
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
													//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le as dimensoes da imagem, numero de pixels da horizontal e da vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura > MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura > MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor[0];	//Valor maximo do pixel (temos que ler, mas nao sera usado, assumimos 255)
//****************************//


//*** Leitura dos pixels da imagem ***//
if (strcmp(tipo, "P3") == 0) {
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			for (k=0;k<3;k++){
				arqentrada >> valor[k];
				imagem[i][j][k] = (unsigned char)valor[k];
			}
		}
}
else if (strcmp(tipo, "P2") == 0) { // Imagem em tons de cinza
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            arqentrada >> valor[0]; // Lê o valor de cinza
            for (int k = 0; k < 3; k++) {
                imagem[i][j][k] = (unsigned char)valor[0]; // Define o mesmo valor para R, G e B
            }
        }
    }
}
else if (strcmp(tipo, "P1") == 0) {
    cout << "Imagem preto e branco\n";
    cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
    arqentrada.close();
    return 0;
}


//************************************//
	arqentrada.close();  //Fecha arquivo apos a leitura

//*** FIM DA LEITURA DA IMAGEM ***//


//*** TRATAMENTO DA IMAGEM ***//
//inicialmente sera nesta parte do codigo que voce vai trabalhar

	int opcao;
    cout << "o que deseja fazer? \n";
	cout << "clarear/escurecer (1)\n";
	cout << "negativo (2)\n";
	cout << "espelhar (3)\n";
	cout << "filtro de prewitt (4)\n";
	cout << "outro filtro (5)\n";
	cout << "tons de cinza (6)\n";
	cout << "gravar (7)\n";
	cout << "outra operacao (8)\n";
    cin >> opcao;
    
    if (opcao == 1){   //clareia ou escurece
		int ce;
		cout << "clarear(1) ou escurecer(2)? \n";
		cin >> ce;
		if (ce == 2){      //escurece o pixel
			int fator;
			cout << "Qual o fator de escurecimento (1-100)? ";
			cin >> fator;
			for(i=0;i<altura;i++){
				for(j=0;j<largura;j++) {
					for (int k=0;k<3;k++){
						valor[k] = (int)imagem[i][j][k];			//pega o valor do pixel
						valor[k] -= fator;									//escurece o pixel
						if (valor[k] < 0)									//se der negativo
							valor[k] = 0;										//  deixa preto
						imagem[i][j][k] = (unsigned char)valor[k];	//modifica o pixel
					}
				}
			}
		}
		
		else {     //clareia o pixel
			int fator;
			cout << "Qual o fator de clareamento (1-100)? ";
			cin >> fator;
			for(i=0;i<altura;i++){
				for(j=0;j<largura;j++) {
					for (int k=0;k<3;k++){
						valor[k] = (int)imagem[i][j][k];			//pega o valor do pixel
						valor[k] += fator;									//clareia o pixel
						if (valor[k] > 255)									//se passar do limite
							valor[k] = 255;										//  deixa branco
						imagem[i][j][k] = (unsigned char)valor[k];	//modifica o pixel
					}
				}
			}
		}
    }
    
    else if (opcao == 2){   //negativo
        //255 - pixel
        for (int i=0;i<altura;i++){
            for (int j=0;j<largura;j++){
				for (k=0;k<3;k++){
					valor[k] = (int)imagem[i][j][k];
                	valor[k] = 255 - valor[k];
                	imagem[i][j][k] = (unsigned char)valor[k];
				}
                
            }
        }
    }
	
	else if (opcao == 3) {   // espelhar a imagem
		for (i = 0; i < altura; i++) {       //troca linha por coluna
			for (j = 0; j < largura / 2; j++) {  
				for (int k=0;k<3;k++){
					unsigned char temp = imagem[i][j][k];
					imagem[i][j][k] = imagem[i][largura - 1 - j][k];
					imagem[i][largura - 1 - j][k] = temp;
				}
			}
		}
	}

	else if (opcao == 4) {

	}
	

    //*************************//

//*** FIM DO TRATAMENTO DA IMAGEM ***//


//*** GRAVACAO DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

	//*** Grava a nova imagem ***//
	cout << "Qual sera o nome do arquivo? \n";
	string nome;
	cin >> nome;
	arqsaida.open(nome.c_str(),ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar " << nome << ".pnm\n";
		return 0;
	}

	arqsaida << tipo << endl;							//tipo
	arqsaida << "# TP3-INF110, by AGS\n";	//comentario
	arqsaida << largura << " " << altura;	//dimensoes
	arqsaida << " " << 255 << endl;				//maior valor
	if (strcmp(tipo, "P2") == 0) { // Imagem em tons de cinza
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            arqsaida << (int)imagem[i][j][0] << endl; // Grava apenas o valor do canal de cinza
        }
    }
	} else {
		for (i = 0; i < altura; i++) {
			for (j = 0; j < largura; j++) {
				for (int k = 0; k < 3; k++) {
					arqsaida << (int)imagem[i][j][k] << endl;    // pixels
				}
			}
		}
	}


	

	arqsaida.close();		//fecha o arquivo
	//***************************//

//*** FIM DA GRAVACAO DA IMAGEM ***//

	return 0;
}
