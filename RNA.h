#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;
class RNA
{
private:
	double Tasa_aprendizaje; //Tasa de aprendizaje ~sqrt(2)
	double momento; //Usado para controlar el aprendizaje

	//Pesos de la RNA
	double pesos[9] = {};

	//Datos para el entrenamiento
	double entradas[4][2] = { {1, 0},
				   { 1, 1 },
				   { 0, 1 },
				   { 0, 0 } };
	int salidas[4]={ 1, 0, 1, 0 };;

	int sesgo;
	float h1;
	float h2;
	float error[4];
	float salida_neuron;
	float gradiente[9];
	float derivada_O1;
	double derivada_h1;
	float derivada_h2;
	float sum_salida;
	float sum_h1;
	float sum_h2;
	float pesos_nuevos[9];
	float pesos_previos[9];
	float RMSE_ERROR;
	int epoch;
	float RMSE_array_error[20000];
	bool band;
public:
	RNA();
	float FunAct_Sigmoid(float x);
	void CalNeuronasEscondidas(int x);
	void CalNeruonaSalida();
	void CalcError(int x);
	void CalcDeriva(int x);
	void CalcGradiente(int x);
	void CalcActua();
	void Camb_Pesos();
	void CalRMSE();
	void GenerarPesos();
	void Entrenar();
	void Probar(float i1, float i2);
	void GuardarInfo();
	void CargarData();
	bool Cargar();
	void Desplegar();

};

