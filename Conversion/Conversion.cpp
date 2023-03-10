#include "Conversion.h"

void Conversion::ConvertirBinario(int num)
{
    int binaryNum[32];
    int i = 0;
    while (num > 0)
    {
        binaryNum[i] = num % 2;
        num = num / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        cout << binaryNum[j];
    }
    cout << endl;
}

void Conversion::ConvertirOctal(int num)
{
    int octalNum[32];
    int i = 0;
    while (num > 0)
    {
        octalNum[i] = num % 8;
        num = num / 8;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        cout << octalNum[j];
    }
    cout << endl;
}

void Conversion::ConvertirHexadecimal(int num)
{
    char hexadecimalNum[32];
    int i = 0;
    while (num > 0)
    {
        int temp = 0;
        temp = num % 16;
        if (temp < 10)
        {
            hexadecimalNum[i] = temp + 48;
            i++;
        }
        else
        {
            hexadecimalNum[i] = temp + 55;
            i++;
        }
        num = num / 16;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        cout << hexadecimalNum[j];
    }
    cout << endl;
}

void Conversion::ConvertirBinarioDecimal(string binario)
{
    int decimal = 0;
    int base = 1;
    int temp = binario.length();
    for (int i = temp - 1; i >= 0; i--)
    {
        if (binario[i] == '1')
        {
            decimal += base;
        }
        base = base * 2;
    }
    cout << "El numero binario " << binario << " en decimal es: " << decimal << endl;
}
