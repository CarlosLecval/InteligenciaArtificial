/*#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Función para encontrar la ubicación de un número en el rompecabezas
void find_location(string puzzle, int& row, int& col)
{
    int numero_espacios = 0;
    for(int i = 0; i < puzzle.length(); i++)
    {
        if(puzzle[i] == ' '){
            numero_espacios++;
        }
        if(puzzle[i] == '0'){
            break;
        }
    }
    row = (numero_espacios - 1) / 3;
    col = (numero_espacios - 1) % 3;
}

// Función para intercambiar dos caracteres en una cadena
void swap(string& puzzle, int i, int j)
{
    char temp = puzzle[i];
    puzzle[i] = puzzle[j];
    puzzle[j] = temp;
}
// Función para obtener los vecinos del rompecabezas
vector<string> devuelve_vecinos_de_un_nodo(string puzzle)
{
    vector<string> neighbors;
    int row, col;
    find_location(puzzle, row, col);

    // Si el espacio vacío no está en la primera fila, podemos mover la pieza superior
    if (row > 0) {
        string neighbor = puzzle;
        swap(neighbor, 3 * (row - 1) + col, 3 * row + col);
        neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la última fila, podemos mover la pieza inferior
    if (row < 2) {
        string neighbor = puzzle;
        swap(neighbor, 3 * (row + 1) + col, 3 * row + col);
        neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la primera columna, podemos mover la pieza izquierda
    if (col > 0) {
        string neighbor = puzzle;
        swap(neighbor, 3 * row + col - 1, 3 * row + col);
        neighbors.push_back(neighbor);
    }

    // Si el espacio vacío no está en la última columna, podemos mover la pieza derecha
    if (col < 2) {
        string neighbor = puzzle;
        swap(neighbor, 3 * row + col + 1, 3 * row + col);
        neighbors.push_back(neighbor);
    }

    return neighbors;
}

int main(){
    string puzzle = "1 2 3 4 5 6 7 8 0";
    cout << "El puzzle es: " << puzzle << endl;
    vector<string> vecinos = devuelve_vecinos_de_un_nodo(puzzle);
    for (int i = 0; i < vecinos.size(); i++){
        cout << vecinos[i] << endl;
    }
    return 0;
}


123456789abcdefghijklmn00
123456789abcdefghi00lmnjk
254316790BA0DEFGHIJKLMNC8

123456789ABCDEFGHIJKLMN00

239A50647F10H8CGDJEIBLMNK
1237A098456HDEFB0IJCLGMNK

*/