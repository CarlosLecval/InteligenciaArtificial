#Argumento: nombre del directorio que se va a crear
mkdir $1
cd $1
touch Source.cpp
echo "#include <iostream>" >> Source.cpp
echo "using namespace std;" >> Source.cpp
echo "int main()" >> Source.cpp
echo "{" >> Source.cpp
echo "  return 0;" >> Source.cpp
echo "}" >> Source.cpp