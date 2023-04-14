#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Grafo
{
    public:
        Grafo();
        unordered_map<char, int> devuelve_vecinos_numeros_del_rey(int digito_actual, int total_actual);
    private:
};
