/*
Implementação de Métodos Numéricos
@author Thomás Augusto Gouveia Chaves
@version 03/04/2020
Métodos:
  Interpolação polinomial: Método de Lagrange
  Interpolação polinomial: Método de Newton
  Interpolação polinomial inversa
  Método dos mínimos quadrados
  Integração numérica: Regra dos Trapézios
  Integração numérica: Regra 1/3 de Simpson
*/

#include "metodosnumericos.h"

int main(){
	string entrada = "0";
	int opcao;
	cout << "\n..:: Metodos Numericos ::..\nThomas Augusto Gouveia Chaves\n\n1-Intepolacao Polinomial\n2-Metodo dos Minimos Quadrados\n3-Integracao Numerica\nEscolha uma opcao: ";
	getline(cin, entrada);
	opcao = atoi(entrada.c_str());
	menu(opcao);
	cout << "\nObrigado. Programa encerrado!";
}

void menu(int opcao){
		string entrada = "0";
		if(opcao != 1 && opcao != 2 && opcao != 3){
			cout << "\nErro: Opcao Invalida! (escolha entre 1, 2 e 3)";
			return;
		}

		if(opcao == 1){
			cout << "\nInterpolacao Polinomial:\n1-Metodo de Lagrange\n2-Metodo de Newton\n3-Interpolacao Inversa\nEscolha um dos metodos: ";

			int opcao2;
			getline(cin, entrada);
			opcao2 = atoi(entrada.c_str());


			if(opcao2 != 1 && opcao2 != 2 && opcao2 != 3){
				cout << "\nErro: Opcao Invalida! (escolha entre 1, 2 e 3)";
				return;
			}

			if(opcao2 == 1)
				lagrange();
			if(opcao2 == 2)
				newton();
			if(opcao2 == 3)
				inversa();
		}

		if(opcao == 2){
			cout << "\nMetodo dos Minimos Quadrados";
			minimos_quadrados();
		}

		if(opcao == 3){
			cout << "\nIntegracao Numerica:\n1-Regra dos Trapezios\n2-Regra 1/3 de Simpson\nEscolha um dos metodos: ";
			int opcao2;
			getline(cin, entrada);
			opcao2 = atoi(entrada.c_str());
			if(opcao2 != 1 && opcao2 != 2){
				cout << "\nErro: Opcao Invalida! (escolha entre 1, 2)";
				return;
			}
			if(opcao2 == 1){
				cout << "\nRegra dos Trapezios para funcao g(x) = x*e^(x^2)\n";
				regra_dos_trapezios();
			}
			if(opcao2 == 2){
				cout << "\nRegra 1/3 de Simpson para as funcoes:\n    h(x) = e^(x^2)\n    j(x) = sen(x^2)\n    k(x) = cos(x^2)\n    l(x) = x/(1+x^2)\n";
				regra_1_3_simpson();
			}

		}
}

void lagrange(){
	/* LEITURA DA TABELA */
	cout << "\n" << "Insira os valores de X(ou Y para inversa) da tabela, um a um.";
	cout << "\n" << "Para finalizar, entre com '/'.\n";

	string entrada = "0";
	vector<float> x;
	while(entrada != "/"){
		getline(cin, entrada);
		if(entrada != "/"){
			x.push_back(atof(entrada.c_str()));
		}
	}
	cout << "\n" << "Insira os valores de Y da tabela, um a um:\n";
	vector<float> y;
	for(int i = 0; i < x.size(); i++){
		getline(cin, entrada);
		y.push_back(atof(entrada.c_str()));
	}
	/* IMPRIMINDO A TABELA*/
	cout << "\nTABELA:\n__________\nX\tY\n";
	for(int i = 0; i < x.size(); i++)
		cout << "" << x[i] << "\t" << y[i] << "\n";
	cout << "__________";
	/*        */

	/* LEITURA DOS INDICES DESEJADOS PELO USUARIO */
	cout << "\n" << "Insira tres indices para construir o polinomio\ninterpolador quadratico:\n";
	vector<float> indices;
	for(int i = 0; i < 3; i++){
		getline(cin, entrada);
		indices.push_back(atof(entrada.c_str()));
	}

	cout << "\n" << "Insira o valor de Y(ou X para inversa) que voce deseja encontrar:\n";
	float valor_desejado;
	getline(cin, entrada);
	valor_desejado = atof(entrada.c_str());

	float resultado = calcula_lagrange(valor_desejado, x[indices[0]], x[indices[1]], x[indices[2]], y[indices[0]], y[indices[1]], y[indices[2]]);
	cout << "\n" << "Resultado pelo polinomio construido com x" << indices[0] << ", x" << indices[1] << ", x" << indices[2] << " = " << resultado;

	#define f(X) exp(3*X)
	cout << "\n" << "Comparando resultados com a funcao f(x) = exp(3x):";
	float resultado_real = f(valor_desejado);
	cout << "\n" << "Resultado por interpolacao: " << resultado << "\n" << "Resultado real: " << resultado_real << "\nErro estimado: " << abs(resultado_real-resultado);
	return;
}

float calcula_lagrange(float valor, float x0, float x1, float x2, float y0, float y1, float y2){
	#define L0(X) ((X-(x1))*(X-(x2)))/((x0-(x1))*(x0-(x2)))
	#define L1(X) ((X-(x0))*(X-(x2)))/((x1-(x0))*(x1-(x2)))
	#define L2(X) ((X-(x0))*(X-(x1)))/((x2-(x0))*(x2-(x1)))
	#define Pn(X) y0*L0(X) + y1*L1(X) + y2*L2(X)
	return Pn(valor);
}

void newton(){
	/* LEITURA DA TABELA */
	cout << "\n" << "Insira os valores de X(ou Y para inversa) da tabela, um a um.";
	cout << "\n" << "Para finalizar, entre com '/'.\n";

	string entrada = "0";
	vector<float> x;
	while(entrada != "/"){
		getline(cin, entrada);
		if(entrada != "/"){
			x.push_back(atof(entrada.c_str()));
		}
	}
	cout << "\n" << "Insira os valores de Y(ou X para inversa) da tabela, um a um:\n";
	vector<float> y;
	for(int i = 0; i < x.size(); i++){
		getline(cin, entrada);
		y.push_back(atof(entrada.c_str()));
	}
	/* IMPRIMINDO A TABELA*/
	cout << "\nTABELA:\n__________\nX\tY\n";
	for(int i = 0; i < x.size(); i++)
		cout << "" << x[i] << "\t" << y[i] << "\n";
	cout << "__________";
	/*        */

	cout << "\n" << "Ordem de diferencas divididas: " << x.size() << "\n";
	/* Calcula a matriz de diferencas divididas*/
	int ordem = x.size();
	int aux = 0;
	float fx;
	vector<vector<float>> matriz_dd(ordem,vector<float>(ordem));
	//float matriz_dd[ordem][ordem];

    for(int i = 0; i < ordem; i++){
        matriz_dd[0][i] = y[i];
    }

    for(int i = 1; i < ordem; i++){
        for(int j = 0; j < ordem - i; j++){
	        fx = ((y[j+1] - y[j])/(x[j+aux+1] - x[j]));
	        y[j] = fx;
	        matriz_dd[i][j] = fx;
        }
        aux++;
    }
    /*          */
    /*  Imprime a matriz de diferenças divididas */
    for(int i = 0; i < ordem; i++){
        cout << "Ordem " << i << ":";
        for(int j = 0; j < ordem - i; j++){
            cout << " " << matriz_dd[i][j] << "";
        }
        cout << endl;
    }
    /*  */
	/* LEITURA DOS INDICES DESEJADOS PELO USUARIO */
	cout << "\n" << "Insira tres indices para construir o polinomio\ninterpolador quadratico:\n";
	vector<float> indices;
	for(int i = 0; i < 3; i++){
		getline(cin, entrada);
		indices.push_back(atof(entrada.c_str()));
	}

	cout << "\n" << "Insira o valor de X que voce deseja encontrar:\n";
	float valor_desejado;
	getline(cin, entrada);
	valor_desejado = atof(entrada.c_str());

	float resultado = calcula_newton(valor_desejado, matriz_dd, x[indices[0]], x[indices[1]], x[indices[2]], indices[0], indices[1], indices[2]);
	cout << "\n" << "Resultado pelo polinomio construido com x" << indices[0] << ", x" << indices[1] << ", x" << indices[2] << " = " << resultado;

	#define f(X) exp(3*X)
	cout << "\n" << "Comparando resultados com a funcao f(x) = exp(3x):";
	float resultado_real = f(valor_desejado);
	cout << "\n" << "Resultado por interpolacao: " << resultado << "\n" << "Resultado real: " << resultado_real << "\nErro estimado: " << abs(resultado_real-resultado);
	return;
}

float calcula_newton(float valor, vector<vector<float>> &matriz_dd, float x0, float x1, float x2, float ix0, float ix1, float ix2){
	float d0, d1, d2;
	d0 = matriz_dd[0][ix0];
	d1 = matriz_dd[1][ix0];
	d2 = matriz_dd[2][ix0];
	#define PNn(X) d0 + d1*(X-x0) + d2*(X-x0)*(X-x1)
	return PNn(valor);
}

void inversa(){
	/* LEITURA DA TABELA */
	cout << "\n" << "Insira os valores de X da tabela, um a um.";
	cout << "\n" << "Para finalizar, entre com '/'.\n";

	string entrada = "0";
	vector<float> x;
	while(entrada != "/"){
		getline(cin, entrada);
		if(entrada != "/"){
			x.push_back(atof(entrada.c_str()));
		}
	}
	cout << "\n" << "Insira os valores de Y da tabela, um a um:\n";
	vector<float> y;
	for(int i = 0; i < x.size(); i++){
		getline(cin, entrada);
		y.push_back(atof(entrada.c_str()));
	}
	/* IMPRIMINDO A TABELA*/
	cout << "\nTABELA:\n__________\nX\tY\n";
	for(int i = 0; i < x.size(); i++)
		cout << "" << x[i] << "\t" << y[i] << "\n";
	cout << "__________";
	/*        */

	cout << "\n" << "Ordem de diferencas divididas: " << x.size() << "\n";
	/* Calcula a matriz de diferencas divididas*/
	int ordem = x.size();
	int aux = 0;
	float fx;
	vector<vector<float>> matriz_dd(ordem,vector<float>(ordem));
	//float matriz_dd[ordem][ordem];

    for(int i = 0; i < ordem; i++){
        matriz_dd[0][i] = y[i];
    }

    for(int i = 1; i < ordem; i++){
        for(int j = 0; j < ordem - i; j++){
	        fx = ((y[j+1] - y[j])/(x[j+aux+1] - x[j]));
	        y[j] = fx;
	        matriz_dd[i][j] = fx;
        }
        aux++;
    }
    /*          */
    /*  Imprime a matriz de diferenças divididas */
    for(int i = 0; i < ordem; i++){
        cout << "ORDEM " << i;
        for(int j = 0; j < ordem; j++){
            cout << " " << matriz_dd[i][j];
        }
        cout << endl;
    }
    /*  */
	/* LEITURA DOS INDICES DESEJADOS PELO USUARIO */
	cout << "\n" << "Insira tres indices para construir o polinomio\ninterpolador quadratico:\n";
	vector<float> indices;
	for(int i = 0; i < 3; i++){
		getline(cin, entrada);
		indices.push_back(atof(entrada.c_str()));
	}

	cout << "\n" << "Insira o valor de Y que voce deseja encontrar:\n";
	float valor_desejado;
	getline(cin, entrada);
	valor_desejado = atof(entrada.c_str());

	float resultado = calcula_inversa(valor_desejado, matriz_dd, x[indices[0]], x[indices[1]], x[indices[2]], indices[0], indices[1], indices[2]);
	cout << "\n" << "Resultado pelo polinomio construido com x" << indices[0] << ", x" << indices[1] << ", x" << indices[2] << " = " << resultado;
}

float calcula_inversa(float valor, vector<vector<float>> &matriz_dd, float x0, float x1, float x2, float ix0, float ix1, float ix2){
	float d0, d1, d2;
	d0 = matriz_dd[0][ix0];
	d1 = matriz_dd[1][ix0];
	d2 = matriz_dd[2][ix0];

	float a, b, c, delta, raiz_um, raiz_dois;
	a = d2;
	b = d2*(-x1)+d2*(-x0)+d1;
	c = d2*x0*x1+d1*(-x0)+d0;
	c -= valor;

	delta = pow(b, 2)-(4*a*c);

	cout << "\nCoeficientes: [" << a << "," << b << "," << c << "] | Delta: " << delta << "";

	raiz_um = ((-b)+sqrt(delta))/(2*a);
	raiz_dois = ((-b)-sqrt(delta))/(2*a);

	cout << "\nRaizes: [" << raiz_um << "," << raiz_dois << "]";

	if(raiz_um >= 0 && raiz_dois < 0)
		return raiz_um;
	if(raiz_dois >= 0 && raiz_um < 0)
		return raiz_dois;	
	return 0.0;
}

void minimos_quadrados(){
	/* LEITURA DA TABELA */
	cout << "\n" << "Insira os valores de X da tabela, um a um.";
	cout << "\n" << "Para finalizar, entre com '/'.\n";

	string entrada = "0";
	vector<float> x;
	while(entrada != "/"){
		getline(cin, entrada);
		if(entrada != "/"){
			x.push_back(atof(entrada.c_str()));
		}
	}
	cout << "\n" << "Insira os valores de Y da tabela, um a um:\n";
	vector<float> y;
	for(int i = 0; i < x.size(); i++){
		getline(cin, entrada);
		y.push_back(atof(entrada.c_str()));
	}
	/* IMPRIMINDO A TABELA*/
	cout << "\nTABELA DE ENTRADA:\n__________\nX\tY\n";
	for(int i = 0; i < x.size(); i++)
		cout << "" << x[i] << "\t" << y[i] << "\n";
	cout << "__________\n\n";
	/*        */

	int num_valores = x.size();
	float somatorio_x = 0, somatorio_y = 0, somatorio_xy = 0, somatorio_x_quadrado = 0;

	for(int i = 0; i < num_valores; i++){
		somatorio_x += x[i];
	}
	for(int i = 0; i < num_valores; i++){
		somatorio_y += y[i];
	}
	for(int i = 0; i < num_valores; i++){
		somatorio_xy += x[i]*y[i];
	}
	for(int i = 0; i < num_valores; i++){
		somatorio_x_quadrado += pow(x[i],2);
	}
	cout << "Valores de entrada:\n";
	cout << "Somatorio de X: " << somatorio_x << "\n"
		 << "Somatorio de Y: " << somatorio_y << "\n"
		 << "Somatorio de X*Y: " << somatorio_xy << "\n"
		 << "Somatorio de X^2: " << somatorio_x_quadrado;

    float somatorio_y_ajustado = 0, somatorio_xy_ajustado = 0;

	for(int i = 0; i < num_valores; i++){
		somatorio_y_ajustado += log(y[i]);
	}
	for(int i = 0; i < num_valores; i++){
		somatorio_xy_ajustado += x[i]*log(y[i]);
	}

	cout << "\n\nValores ajustados ao problema:\n";
	cout << "Somatorio de X: " << somatorio_x << "\n"
		 << "Somatorio de ln(Y): " << somatorio_y_ajustado << "\n"
		 << "Somatorio de X*ln(Y): " << somatorio_xy_ajustado << "\n"
		 << "Somatorio de X^2: " << somatorio_x_quadrado;

	float a = (num_valores*somatorio_xy_ajustado-somatorio_x*somatorio_y_ajustado)
	         /(num_valores*somatorio_x_quadrado-pow(somatorio_x,2));
	float b = (somatorio_x*somatorio_xy_ajustado-somatorio_y_ajustado*somatorio_x_quadrado)
			 /(pow(somatorio_x,2)-num_valores*somatorio_x_quadrado);

	cout << "\n\nEquacao da reta: \n   y = " << exp(b) << " * e^(" << a << "x)";
	cout << "\nPara Y = 2000, X = 11.6176";
}

void regra_dos_trapezios(){

	#define g(x) x*exp(pow(x, 2))
	string entrada = "0";
	float a, b, passo, x0, x1, resultado = 0;
	int subintervalos;

	cout << "\n" << "Insira o valor inicial do intervalo:\n";
	getline(cin, entrada);
	a = atof(entrada.c_str());

	cout << "\n" << "Insira o valor final do intervalo:\n";
	getline(cin, entrada);
	b = atof(entrada.c_str());

	cout << "\n" << "Insira o numero de subintervalos desejado:\n";
	getline(cin, entrada);
	subintervalos = atoi(entrada.c_str());
	
	passo = (b-a)/subintervalos;
	cout << "\n" << "Passo: " << passo;

	for(int i = 0; i < subintervalos; i++){
		x1 = a+passo*(i+1);
		x0 = a+passo*(i);
		resultado += ((g(x1)+g(x0))*passo)/2;
	}

	cout << "\n" << "Resultado da integracao: " << resultado;

	#define gdx2(x) 2*exp(pow(x, 2))*x*(2*pow(x, 2)+3)

	float m0, m1, mmax, erro, erro_real;
	m0 = abs(gdx2(0));
	m1 = abs(gdx2(1));
	if(m0 > m1)	mmax = m0;
	else mmax = m1;
	erro = (mmax*(b-a)*pow(passo,2))/12;

	
	erro_real = abs(5.10877-resultado);
	cout << "\n" << "	- M = [" << m0 << "," << m1 << "]   Mmax: " << mmax;
	cout << "\n" << "	- Esr <= " << erro;
	cout << "\n" << "	Resultado por primitiva(Wolfram): 5.10877";
	cout << "\n" << "	Erro real: " << erro_real;
	cout << "\n" << "	Comparacao entre os erros: " << abs(erro-erro_real);

}

void regra_1_3_simpson(){
	#define h(x) exp(pow(x, 2))
	#define j(x) sin(pow(x, 2))
	#define k(x) cos(pow(x, 2))
	#define l(x) x/(1+pow(x, 2))
	string entrada = "0";
	float a, b, resultado=0, passo, k;
	int subintervalos;

	cout << "\n" << "Insira o valor inicial do intervalo:\n";
	getline(cin, entrada);
	a = atof(entrada.c_str());

	cout << "\n" << "Insira o valor final do intervalo:\n";
	getline(cin, entrada);
	b = atof(entrada.c_str());

	cout << "\n" << "Insira o numero de subintervalos desejado:\n";
	getline(cin, entrada);
	subintervalos = atoi(entrada.c_str());

	passo = (b-a)/subintervalos;

	resultado = h(a) + h(b);

	for(int i=1; i<= subintervalos-1; i++){
		k = a+(passo*i);
		if(i%2 != 0)
			resultado += 4 * (h(k));
		else
			resultado += + 2 * (h(k));
	}
	resultado *= passo/3;
	cout << "\n" << "Resultado da integracao da funcao e^(x^2): " << resultado;


	#define hdx4(x) 4*exp(pow(x, 2))*(3+12*pow(x, 2)+4*pow(x,4))

	float m0, m1, mmax, erro, erro_real;
	m0 = abs(hdx4(0));
	m1 = abs(hdx4(1));
	if(m0 > m1)	mmax = m0;
	else mmax = m1;
	erro = (mmax*(b-a)*pow(passo, 4))/180;

	
	erro_real = abs(3.7109-resultado);
	cout << "\n" << "	- M = [" << m0 << "," << m1 << "]   Mmax: " << mmax;
	cout << "\n" << "	- Esr <= " << erro;
	cout << "\n" << "	Resultado por primitiva(Wolfram): 3.7109";
	cout << "\n" << "	Erro real: " << erro_real;
	cout << "\n" << "	Comparacao entre os erros: " << abs(erro-erro_real);

	resultado=0;
	resultado = h(a) + h(b);

	for(int i=1; i<= subintervalos-1; i++){
		k = a+(passo*i);
		if(i%2 != 0)
			resultado += 4 * (j(k));
		else
			resultado += + 2 * (j(k));
	}

	resultado *= passo/3;
	cout << "\n" << "Resultado da integracao da funcao sin(x^2): " << resultado;

	#define jdx4(x) 4*(4*pow(x,4)-3)*sin(pow(x, 2))-48*pow(x, 2)*cos(pow(x,2))

	m0 = abs(jdx4(0));
	m1 = abs(jdx4(1));
	if(m0 > m1)	mmax = m0;
	else mmax = m1;
	erro = (mmax*(b-a)*pow(passo, 4))/180;

	
	erro_real = abs(0.535001-resultado);
	cout << "\n" << "	- M = [" << m0 << "," << m1 << "]   Mmax: " << mmax;
	cout << "\n" << "	- Esr <= " << erro;
	cout << "\n" << "	Resultado por primitiva(Wolfram): 0.535001";
	cout << "\n" << "	Erro real: " << erro_real;
	cout << "\n" << "	Comparacao entre os erros: " << abs(erro-erro_real);

	resultado=0;
	resultado = h(a) + h(b);

	for(int i=1; i<= subintervalos-1; i++){
		k = a+(passo*i);
		if(i%2 != 0)
			resultado += 4 * (k(k));
		else
			resultado += + 2 * (k(k));
	}
	resultado *= passo/3;

	cout << "\n" << "Resultado da integracao da funcao cos(x^2): " << resultado;

	#define kdx4(x) 4*(-3+4*pow(x, 4))*cos(pow(x, 2))+48*pow(x,2)*sin(pow(x,2))

	m0 = abs(kdx4(0));
	m1 = abs(kdx4(1));
	if(m0 > m1)	mmax = m0;
	else mmax = m1;
	erro = (mmax*(b-a)*pow(passo, 4))/180;

	
	erro_real = abs(-0.0790075-resultado);
	cout << "\n" << "	- M = [" << m0 << "," << m1 << "]   Mmax: " << mmax;
	cout << "\n" << "	- Esr <= " << erro;
	cout << "\n" << "	Resultado por primitiva(Wolfram): -0.0790075";
	cout << "\n" << "	Erro real: " << erro_real;
	cout << "\n" << "	Comparacao entre os erros: " << abs(erro-erro_real);

	resultado=0;
	resultado = h(a) + h(b);

	for(int i=1; i<= subintervalos-1; i++){
		k = a+(passo*i);
		if(i%2 != 0)
			resultado += 4 * (l(k));
		else
			resultado += + 2 * (l(k));
	}
	resultado *= passo/3;
	cout << "\n" << "Resultado da integracao da funcao x/(1+x^2): " << resultado;

	#define ldx4(x) (24*x*(pow(x,4)-10*pow(x,2)+5))/(pow((1+pow(x,2)),5))

	m0 = abs(ldx4(0));
	m1 = abs(ldx4(1));
	if(m0 > m1)	mmax = m0;
	else mmax = m1;
	erro = (mmax*(b-a)*pow(passo, 4))/180;

	erro_real = abs(0.288307-resultado);
	cout << "\n" << "	- M = [" << m0 << "," << m1 << "]   Mmax: " << mmax;
	cout << "\n" << "	- Esr <= " << erro;
	cout << "\n" << "	Resultado por primitiva(Wolfram): 0.288307";
	cout << "\n" << "	Erro real: " << erro_real;
	cout << "\n" << "	Comparacao entre os erros: " << abs(erro-erro_real);
}