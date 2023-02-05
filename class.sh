#Primer argumento: nombre de la clase
#Segundo argumento: nombre del directorio
cd $2
touch $1.cpp $1.h
echo "#pragma once" >> $1.h
echo "#include <iostream>" >> $1.h
echo "using namespace std;" >> $1.h
echo "class" $1 >> $1.h
echo "{" >> $1.h
echo "};" >> $1.h
echo "#include" "\"$1.h\"" >> $1.cpp