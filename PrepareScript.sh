wget https://sourceforge.net/projects/wordlist/files/12Dicts/6.0/12dicts-6.0.2.zip/download?use_mirror=svwh
unzip 'download?use_mirror=svwh'
cd American
tr -d '%' < 2of12inf.txt > temp.txt && mv temp.txt 2of12inf.txt
tr -d '!' < 2of12inf.txt > temp.txt && mv temp.txt 2of12inf.txt
mv 2of12inf.txt BoggleDictionary.txt
cd ..
cp American/BoggleDictionary.txt BoggleDictionary.txt
rm -rf American
rm -rf International
rm -rf Lemmatized
rm -rf Special
rm agid.txt
rm alllists.html
rm 'download?use_mirror=svwh'
rm ReadMe.html
