//Librerias necesarias para el funcionamiento
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
	//Salidas esperadas para el programa
	int salidas[4]={ 1, 0, 1, 0 };;

	int sesgo;//Bias o sesgo a tener en cuenta
	float h1;//Calculo de las salidas de cada neurona
	float h2;//Calculo de las salidas de cada neurona
	float error[4];//Error calculado en cada salida
	float salida_neuron; //Neurona de salida
	float gradiente[9];
	float derivada_O1;//Derivadas parciales de las salidas
	double derivada_h1;
	float derivada_h2;
	float sum_salida;
	float sum_h1;
	float sum_h2;
	float pesos_nuevos[9];
	float pesos_previos[9];
	float RMSE_ERROR;//Error cuadratico medio
	int epoch;//Epocas o vueltas para el sistema
	float RMSE_array_error[20000]; //Lugar para almacenar el error cuadratico medio 
	bool band;//Variable de estado del sistema
public:
	RNA();
	float FunAct_Sigmoid(float x);
	void CalNeuronasEscondidas(int x); //Calculo de salida de la capa oculta
	void CalNeruonaSalida();//Calculo capa externa 
	void CalcError(int x);//Calculo del error
	void CalcDeriva(int x);//Calculo de la derivada 
	void CalcGradiente(int x);//Calculo del gradiente capa oculta
	void CalcActua();//Calcular pesos nuevos
	void Camb_Pesos();//Cambiar pesos en la RNA
	void CalRMSE();//Error cuadratico medio
	void GenerarPesos();//Inicializador de la RNAs
	void Entrenar();//Entrenador
	void Probar(float i1, float i2);//Evaluador
	//Metodos para mostrar pesos y guaradar la información en archivos así como cargarla
	void GuardarInfo();
	void CargarData();
	bool Cargar();
	void Desplegar();

};

