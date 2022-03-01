#include "RNA.h"

string aMayuscula(string cadena);

int main()
{
	RNA* rna = new RNA();
	
    int contador = 0;
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
            rna->Entrenar();
            
           
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



string aMayuscula(string cadena) {
    for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
    return cadena;
}