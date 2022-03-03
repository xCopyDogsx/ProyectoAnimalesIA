/*|-----------------------------------|*/
/*|           Proyecto Zoologico      |  
  |Diseñado por:                      |
  |  Maria L. Regino Salgado          | 
  |  Brian S. Cañon Rojas             |
  |  Códigos:-20182578014             |
  |  -20191578110                     |
  |              UDFJC                |
  |              2021                 | */
/*|-----------------------------------|*/


/*---------Recomendaciones: ------------------------------------------------------------
  1. No usar DEV-C++ dado a que este usa un compilador desactualizado.
  2. Usar un compilador GCC u otro que este al día, además de usar VS Code como IDE o VS Community.
  3. Si usa un compilador desactualizado, lo más probable es que el código no compile. 
  4. Algunos métodos presentados acá fueron recuperados de diferentes autores y bibliografias
  creditos a sus respectivos autores. 
-----------------------------------------------------------------------------------------*/

/*Llamado al la libreria que contiene los procedimientos 
necesarios para ejecutar la red neuronal
*/
#include "RNA.h"
//Metodo para poder pasar una cadena minuscula a mayusucla
string aMayuscula(string cadena);

int main()
{
    //Instancia de la red Neuronal 
	RNA* rna = new RNA();
    //Variables necesarias para la ejecución del menu de usuario
    float x, y;
    string nombreA="";
    string tipoA = "";
    int opc,opcion = 0;
   
    do {
        system("cls");
        cout << "Zoologico " << endl;
        cout << "1. Entrenar RNA " << endl;
        cout << "2. Cargar RNA desde archivo" << endl;
        cout << "3. Mostrar Pesos y Umbrales " << endl;
        cout << "4. Probar red neuronal " << endl;
        cout << "5. Salir " << endl;
        cout << "Ingrese opcion: "; cin >> opc;
        cout << endl;
        switch (opc)
        {
        case 1:
            system("cls");
            rna->Entrenar();//Se llama a la red neuronal para que se entrene 
            system("pause");
            break;
        case 2:
            system("cls");
            if (rna->Cargar()) {
                cout << "Red neuronal cargada con exito...." << endl;
            }
            else {
                cout << "Entrene la red primero...." << endl;
            }
            system("pause");
            break;
        case 3:
            system("cls");
            if (rna->Cargar()) {
                cout << "Red neuronal cargada con exito...." << endl;
                rna->Desplegar();
            }
            else {
                cout << "Entrene la red primero...." << endl;
            }
            
            system("pause");
            break;
        case 4:
            system("cls");
            if (rna->Cargar()) {
                cout << "Red neuronal cargada con exito...." << endl;
                cout << " De la siguiente lista ingrese el animal a probar " << endl;
                cout << "\t | # | Animal    | Tipo de Animal | \t" << endl;
                cout << "\t | 1 | Perro     | Vertebrado     | \t" << endl;
                cout << "\t | 2 | Gato      | Vertebrado     | \t" << endl;
                cout << "\t | 3 | Gallina   | Ave            | \t" << endl;
                cout << "\t | 4 | Serpiente | Invertebrado   | \t" << endl;
                cout << "\t | 5 | Mojarra   | Pez            | \t" << endl;
                cout << "\t | 6 | Otro                       | \t" << endl;
                cout << " Ingrese opcion:  ";  cin >> opcion; cout << endl;
               //Asignacion de pesos dependiendo del tipo de animal y su clasificación
                switch (opcion)
                {
                case 1:
                    rna->Probar(0, 1);
                    break;
                case 2:
                    rna->Probar(1, 0);
                    break;
                case 3:
                    rna->Probar(0, 1);
                    break;
                case 4:
                    rna->Probar(1, 1);
                    break;
                case 5:
                    rna->Probar(0, 0);
                    break;
                case 6:
                //En caso de que sea un animal nuevo, la red preguntara por otras caracteristicas
                    system("cls");
                    cin.ignore();
                    cout << "Ingrese el nombre del animal:  " << endl;
                    getline(cin, nombreA);
                    cout << "Ingrese el tipo del animal (Vertebrado,Invertebrado,Etc):  " << endl;
                    getline(cin, tipoA);
                    tipoA = aMayuscula(tipoA);
                    if (strcmp(tipoA.c_str(), "VERTEBRADO") == 0) {
                        rna->Probar(0, 1);
                    }
                    if (strcmp(tipoA.c_str(), "INVERTEBRADO") == 0) {
                        rna->Probar(1, 1);
                    }
                    if (strcmp(tipoA.c_str(), "PEZ") == 0) {
                        rna->Probar(0, 0);
                    }
                    if (strcmp(tipoA.c_str(), "AVE") == 0) {
                        rna->Probar(1, 0);
                    }
                    if (~strcmp(tipoA.c_str(), "VERTEBRADO") == 0 || ~strcmp(tipoA.c_str(), "INVERTEBRADO") == 0 || ~strcmp(tipoA.c_str(), "PEZ") == 0 || ~strcmp(tipoA.c_str(), "AVE") == 0) {
                        cout << "Ingrese la capacidad del animal (0 muy capaz o 1 poco capaz) " << endl;
                        cin >> x;
                        cout << "Ingrese si tiene patas el animal (0 SI o 1 NO) " << endl;
                        cin >> y;
                        rna->Probar(x, y);
                    }
                    system("pause");
                    break;
                default:
                    break;
                }

               
            }
            else {
                cout << "Entrene la red primero...." << endl;
            }
            system("pause");
            break;
        case 5:
            break;
        default:
            system("cls");
            cout << "Opcion invalida" << endl;
            system("pause");
            break;
        }
    } while (opc == 0 || opc != 5);
}


//Metodo para el parseo de minusculas a mayusculas
string aMayuscula(string cadena) {
    for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
    return cadena;
}