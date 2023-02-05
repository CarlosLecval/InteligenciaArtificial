rm $1/a.out
rm CarlosLecona_JyaruHernandez.zip
mkdir CarlosLecona_JyaruHernandez
mkdir CarlosLecona_JyaruHernandez/$1
cp $1/* CarlosLecona_JyaruHernandez/$1
zip -r CarlosLecona_JyaruHernandez.zip CarlosLecona_JyaruHernandez
rm -rf CarlosLecona_JyaruHernandez