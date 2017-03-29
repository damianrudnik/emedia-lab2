#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>

using namespace std;
string encodewithkey(string, string, int **);

int main(){
    char ccase=0;
    string phrase, line, filename, crypted, decrypted, key;
    int length;
    int **Tab = new int*[95];
    for(int i = 0; i < 95; ++i) {
        Tab[i] = new int[95];
    }
    do{
        cout << " \nMenu:\n";
        cout << " a - pokaz tablce znakow\n";
        cout << " 1. Szyfrowanie pliku\n";
        cout << " 2. Deszyfrowanie pliku\n";
        //cout << " 3. Szyfrowanie pliku\n";
        //cout << " 4. Deszyfrowanie pliku\n";
        cout << " --- \n";
        cin >> ccase;
        switch (ccase){
            case 'a': {
                int k=0, sum =0, modulo=0;
                for (int i = 0; i<95;i++){
                    for (int j = 0; j<95;j++){
                        sum = 32 + j + k;
                        modulo = sum%127;
                        if (modulo < 33) {
                            Tab[i][j] = modulo + 32;
                        }else{
                            Tab[i][j] = modulo;
                        }
                        //cout<< Tab[i][j] << " ";
                    }
                    k++;
                    cout << endl;
                }
                break;
            }
            case '1': {
                //odczyt frazy
                filename = "in.txt";
                ifstream phrasefile (filename);
                if (phrasefile.is_open()){
                    phrasefile.seekg(0,phrasefile.end);
                    length = phrasefile.tellg();
                    phrasefile.seekg (0,phrasefile.beg);

                    char * buffer = new char [length];
                    cout << "Zczytano " << length << " znakow.\n";
                    phrasefile.read(buffer,length);
                    phrase = buffer;
                    delete[] buffer;
                    phrasefile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                //odczyta klucza
                filename = "key.txt";
                ifstream keyfile(filename);
                if (keyfile.is_open()){
                    keyfile.seekg(0,keyfile.end);
                    length = keyfile.tellg();
                    keyfile.seekg (0,keyfile.beg);

                    char * buffer = new char [length];
                    cout << "Zczytano " << length << " znakow.\n";
                    keyfile.read(buffer,length);
                    key = buffer;
                    delete[] buffer;
                    keyfile.close();
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }

                crypted = encodewithkey(phrase, key ,Tab);
                cout << endl << crypted << endl;
                
                //zapis do pliku
                filename = "out.txt";
                ofstream encodefile (filename);
                if (encodefile.is_open()){
                    char * buffer = new char [length];
                    strcpy(buffer,crypted.c_str());
                    encodefile.write(buffer,length);
                    delete[] buffer;
                    encodefile.close();
                    cout << "Zapisano do pliku " << filename<<endl;
                }else {
                    cout << "Nie moge otworzyc pliku " << filename << endl; 
                    break;
                }
                break;
            }
            case '2':{
                
            }
            default :
                cout << "Niewlasciwy znak" <<endl;
        }
    }while(ccase != 'x');
    // zwalnianie pamieci
    for(int i = 0; i < 95; ++i) {
        delete [] Tab[i];
    }
    delete [] Tab;

    return 0;
}

string encodewithkey(string Phrase, string Key, int **Tab){
    string Crypted = Phrase;
    uint PhraseSize = Phrase.length();
    uint KeySize = Key.length();
    //cout << "Rozmiar slowa: " << PhraseSize <<endl;
    int Tabbyte[PhraseSize], Tabkey[KeySize],j ;
    int tmplength = Phrase.length();
    for (uint i = 0; i < KeySize; i++){
        Tabkey[i] - '\0';
    }
    for(uint i = 0; i < tmplength; i++){
        Tabbyte[i] = Crypted[i] - '\0';
        //cout << "Bajt: " << Tab[i] << " Litera: " << Crypted[i];
        j = i%KeySize;
        Tabbyte[i] = Tab[Tabbyte[i]-32][Tabkey[j]-32];
        
        //cout << " Bajt przesuniety: " << Tab[i] << " literka: "<< char(Tab[i]) <<endl;
        Crypted[i] = '\0'+ Tabbyte[i];
    }
    Crypted[PhraseSize] = '\0';
    return Crypted;
}