#include "RNA.h"

RNA::RNA()
{
	//Inicialización de las variables
	Tasa_aprendizaje = 1.414213562;
	momento = 0.25;
	h1 = 0;
	h2 = 0;
	sesgo = 1;
	RMSE_ERROR = 1;
	epoch = 0;
	salida_neuron = 0;
	derivada_O1 = 0;
	derivada_h1 = 0;
	derivada_h2 = 0;
	sum_salida = 0;
	sum_h1 = 0;
	sum_h2 = 0;
	RMSE_array_error[19999] = {};
	band = false;
	for (size_t i = 0; i < 9; i++)
	{
		pesos_previos[i] = 0;
		pesos_nuevos[i] = 0;
		gradiente[i] = 0;
	}
	for (size_t i = 0; i < 4; i++)
	{
		error[i] = 0;
	}
	
}
//Activación de tipo sigmoide
float RNA::FunAct_Sigmoid(float x)
{
	float sigmoid = 1 / (1 + exp(-x));
	return sigmoid;
}





void RNA::CalNeuronasEscondidas(int x)
{
	//Sumatoria de cada una de las neuronas y su salida
	sum_h1 = (entradas[x][0] * pesos[0]) + (entradas[x][1] * pesos[2]) + (sesgo * pesos[4]);
	sum_h2 = (entradas[x][0] * pesos[1]) + (entradas[x][1] * pesos[3]) + (sesgo * pesos[5]);
	h1 = FunAct_Sigmoid(sum_h1);
	h2 = FunAct_Sigmoid(sum_h2);
}

void RNA::CalNeruonaSalida()
{
	//Calculo de la neruona de salida
	sum_salida = (h1 * pesos[6]) + (h2 * pesos[7]) + (sesgo * pesos[8]);
	salida_neuron = FunAct_Sigmoid(sum_salida);
}
void RNA::CalcError(int x) {
	//Error salida obtenida - salida esperada
	error[x] = salida_neuron - salidas[x];
}
void RNA::CalcDeriva(int x) {
	//Calculo de la derivada para cada una de las neuronas
	derivada_O1 = -error[x] * (exp(salida_neuron) / pow((1 + exp(salida_neuron)), 2));
	derivada_h1 = (exp(sum_h1) / pow((1 + exp(sum_h1)), 2)) * pesos[6] * derivada_O1;
	derivada_h2 = (exp(sum_h2) / pow((1 + exp(sum_h2)), 2)) * pesos[7] * derivada_O1;
}
void RNA::CalcGradiente(int x) {
	//Calculo del gradiente en cada una de las conexiones de la neurona usando el sesgo
	gradiente[0] = FunAct_Sigmoid(entradas[x][0]) * derivada_h1;
	gradiente[1] = FunAct_Sigmoid(entradas[x][0]) * derivada_h2;
	gradiente[2] = FunAct_Sigmoid(entradas[x][1]) * derivada_h1;
	gradiente[3] = FunAct_Sigmoid(entradas[x][1]) * derivada_h2;
	gradiente[4] = FunAct_Sigmoid(sesgo) * derivada_h1;
	gradiente[5] = FunAct_Sigmoid(sesgo) * derivada_h2;
	gradiente[6] = h1 * derivada_O1;
	gradiente[7] = h2 * derivada_O1;
	gradiente[8] = FunAct_Sigmoid(sesgo) * derivada_O1;
}

void RNA::CalcActua() {
//Calculo de los pesos de la RNA teniendo en cuenta la epoca, momento y su tasa de aprendizaje
	for (int i = 0; i < 9; i++)
	{
		pesos_nuevos[i] = (Tasa_aprendizaje * gradiente[i]) + (momento * pesos_previos[i]);
		pesos_previos[i] = pesos_nuevos[i];
	}
}

void RNA::Camb_Pesos() {
	//Cambio de pesos 
	for (int i = 0; i < 9; i++)
	{
		pesos[i] = pesos[i] + pesos_nuevos[i];
	}
}
void RNA::CalRMSE() {
	//Error cuadratico medio usado para tener una mejor exactitud en cada conexión
	RMSE_ERROR = sqrt((pow(error[0], 2) + pow(error[1], 2) + pow(error[2], 2) + pow(error[3], 2) / 4));
	cout << "Error cuadratico: " << RMSE_ERROR << endl;
	cout << "" << endl;
}
void RNA::GenerarPesos() {
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		int randNum = rand() % 2;
		if (randNum == 1)
			pesos[i] = -1 * (double(rand()) / (double(RAND_MAX) + 1.0)); 
		else
			pesos[i] = double(rand()) / (double(RAND_MAX) + 1.0); 

		cout << "Pesos " << i << " = " << pesos[i] << endl;
	}
	cout << "" << endl;

}
void RNA::Entrenar() {
	//CargarData();
	while (epoch < 20000)
	{
		for (int i = 0; i < 4; i++)
		{
			CalNeuronasEscondidas(i); 
			CalNeruonaSalida();
			CalcError(i);
			CalcDeriva(i);
			CalcGradiente(i); 
			CalcActua();
			Camb_Pesos();
		}
		CalRMSE();
		RMSE_array_error[epoch] = RMSE_ERROR;
		cout << "Vuelta (Epoca): " << epoch << endl;
		epoch = epoch + 1;

		
		if (epoch > 4000 && RMSE_ERROR > 0.5)
		{
			band = true;
			for (int i = 0; i < 9; i++)
			{
				pesos_previos[i] = 0;
				pesos_nuevos[i] = 0;
				gradiente[i] = 0;
			}
			for (int i = 0; i < 4; i++)
				error[i] = 0;
			for (int i = 0; i < epoch; i++)
				RMSE_array_error[i] = 0;
			epoch = 0;
			GenerarPesos();
		}
	}
	GuardarInfo();
}
void RNA::Probar(float i1, float i2) {
	sum_h1 = (i1 * pesos[0]) + (i2 * pesos[2]) + (sesgo * pesos[4]);
	sum_h2 = (i1 * pesos[1]) + (i2 * pesos[3]) + (sesgo * pesos[5]);
	h1 = FunAct_Sigmoid(sum_h1);
	h2 = FunAct_Sigmoid(sum_h2);
	sum_salida = (h1 * pesos[6]) + (h2 * pesos[7]) + (sesgo * pesos[8]);
	salida_neuron = FunAct_Sigmoid(sum_salida);
	if (round(salida_neuron) == 0) {
		cout << "Prediccion: No puede correr" << endl;
	}
	else {
		cout << "Prediccion: Si puede correr" << endl;
	}
	cout<< endl;
}
void RNA::GuardarInfo() {
	ofstream salida("datosNeuronas.txt", ios::out);
	for (size_t i = 0; i < 9; i++)
	{
		salida << pesos[i] << endl;
	}
}
void RNA::CargarData() {
	ifstream entrada("Entradas.txt");
	ifstream entrada2("Salidas.txt");
	if(!entrada.good()|| !entrada2.good()){ 
		cout << "Los archivos de entrenamiento no existen " << endl;
		exit(1); 
	}
	double i1, i2;
	int x;
	int contador = 0;
	int contador2 = 0;
	while (!entrada.eof() && entrada.good() && entrada >> i1 >> i2 ) {
		entradas[contador][contador] = i1;
		entradas[contador][contador] = i2;
		contador++;
	}
	while (!entrada2.eof() && entrada2.good() && entrada2 >>x) {
		salidas[contador2] = x;
		contador2++;
	}
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			cout << entradas[i][j] << " ";
		}
		cout << endl;
	}
}

bool RNA::Cargar() {
	ifstream entrada("datosNeuronas.txt");
	int contador = 0;
	if (!entrada.good()) {
		cout << "Los archivos de las neuronas no existen " << endl;
		return false;
	}
	double peso;
	while (!entrada.eof() && entrada.good() && entrada >> peso) {
		pesos[contador] = peso;
		contador++;
	}
}

void RNA::Desplegar()
{
	for (size_t i = 0; i < 9; i++)
	{
		
		if (i % 3 == 0) {
			if(i==0){
				cout << "-----------------------" << endl; cout << "Neurona " << i+1 << endl; cout << "-----------------------" << endl;
			}
			if(i==3){
				cout << "-----------------------" << endl; cout << "Neurona " << (i - 1) << endl; cout << "-----------------------" << endl;
			}
			if(i == 6){
				cout << "-----------------------" << endl; cout << "Neurona " << (i/2) << endl; cout << "-----------------------" << endl;
			}

		}
		cout << pesos[i] << endl;
		
	}
}
