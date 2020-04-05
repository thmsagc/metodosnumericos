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

#ifndef METODOSNUMERICOS_H
#define METODOSNUMERICOS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

float calcula_lagrange(float valor, float x0, float x1, float x2, float y0, float y1, float y2);
void lagrange();
void newton();
void inversa();
void minimos_quadrados();
void regra_dos_trapezios();
void regra_1_3_simpson();
float calcula_newton(float valor, vector<vector<float>> &matriz_dd, float x0, float x1, float x2, float ix0, float ix1, float ix2);
float calcula_inversa(float valor, vector<vector<float>> &matriz_dd, float x0, float x1, float x2, float ix0, float ix1, float ix2);
void menu(int opcao);

#endif