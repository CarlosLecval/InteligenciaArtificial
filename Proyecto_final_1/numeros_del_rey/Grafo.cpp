#include "Grafo.h"


Grafo::Grafo()
{
}

unordered_map<char, int> Grafo::devuelve_vecinos_numeros_del_rey(int digito_actual, int total_actual)
{
    int siguiente_digito = digito_actual + 1;
    unordered_map<char, int> vecinos;
    if (siguiente_digito > 9) return vecinos;
    string operaciones = "+-*/";
    int resultado = 0;
    for (int i = 0; i < operaciones.length(); i++)
    {
        switch (operaciones[i])
        {
            case '+':
                resultado = total_actual + siguiente_digito;
                break;
            case '-':
                resultado = total_actual - siguiente_digito;
                break;
            case '*':
                resultado = total_actual * siguiente_digito;
                break;
            case '/':
                resultado = total_actual / siguiente_digito;
                break;
        }
        vecinos[operaciones[i]] = resultado;
    }
    return vecinos;
}