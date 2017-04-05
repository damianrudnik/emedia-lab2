#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>
#include <map>

using namespace std;
string getErrorMessage(int);
string encodewithkey(string, string, int **);
string decodewithkey(string, string, int **);
string ReadFile(string);
string ReadFileSW(string);
bool WriteToFile(string, string);

int main(){
    char ccase=0;
    string phrase, line, filename, crypted, decrypted, key="\0";
    int **Tab = new int*[95];
    for(int i = 0; i < 95; ++i) {
        Tab[i] = new int[95];
    }
    do{
        cout << " \nMenu:\n";
        cout << " a - pokaz tablce znakow\n";
        cout << " 1. Szyfrowanie pliku\n";
        cout << " 2. Deszyfrowanie pliku\n";
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
                        cout<< char(Tab[i][j]) << " ";
                    }
                    k++;
                    cout << endl;
                }
                break;
            }
            case '1': {
                //odczyt frazy
                filename = "in.txt";
                phrase = ReadFile(filename);
                //odczyta klucza
                filename = "key.txt";
                key = ReadFileSW(filename);
                crypted = encodewithkey(phrase, key,Tab);
                cout << endl << crypted << endl;
                
                //zapis do pliku
                filename = "out.txt";
                WriteToFile(filename,crypted);
                break;
            }
            case '2':{
                //odczyt frazy
                filename = "out.txt";
                phrase = ReadFile(filename);
                //odczyta klucza
                filename = "key.txt";
                key = ReadFileSW(filename);
                crypted = decodewithkey(phrase, key,Tab);
                cout << endl << crypted << endl;
                
                //zapis do pliku
                filename = "out2.txt";
                WriteToFile(filename,crypted);
                break;
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
    cout << "Rozmiar frazy: " << PhraseSize <<endl;
    uint KeySize = Key.length();
    cout << "Rozmiar klucza: " << KeySize <<endl;
    int Tabbyte[PhraseSize], Tabkey[KeySize],j ;
    unsigned int tmplength = Phrase.length();
    for (uint i = 0; i < KeySize; i++){
        Tabkey[i]=Key[i] - '\0';
        cout << char(Tabkey[i])<<" ";
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

string decodewithkey(string Phrase, string Key, int **Tab){
    string Crypted = Phrase;
    uint PhraseSize = Phrase.length();
    cout << "Rozmiar frazy: " << PhraseSize <<endl;
    uint KeySize = Key.length();
    cout << "Rozmiar klucza: " << KeySize <<endl;
    int Tabbyte[PhraseSize], Tabkey[KeySize],j ;
    unsigned int tmplength = Phrase.length();
    for (uint i = 0; i < KeySize; i++){
        Tabkey[i]=Key[i] - '\0';
        Tabkey[i]=(127-Tabkey[i])%95 + 32;
        cout << char(Tabkey[i]);
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

string ReadFile(string filename){
    int length;
    string phrase;
    ifstream file (filename);
    if (file.is_open()){
        file.seekg(0,file.end);
        length = file.tellg();
        file.seekg (0,file.beg);
        char * buffer = new char [length];
        cout << "Zczytano " << length << " znakow.\n";
        file.read(buffer,length);
        phrase = buffer;
        delete[] buffer;
        file.close();
        return phrase;
    }else {
        cerr << "Nie moge otworzyc pliku " << filename << endl; 
        return getErrorMessage(10); 
    }
}
string ReadFileSW(string filename){
    string phrase, line;
    ifstream file (filename);
    if (file.is_open()){
        /*while (*/getline (file,line);// ){
            istringstream dane(line);
            dane >> phrase;//}
        file.close();
        return phrase;
    }else {
        cerr << "Nie moge otworzyc pliku " << filename << endl;
        return getErrorMessage(10); 
    }
}
bool WriteToFile(string filename, string phrase){
    int length = phrase.length();
    ofstream encodefile (filename);
    if (encodefile.is_open()){
        char * buffer = new char [length];
        strcpy(buffer,phrase.c_str());
        encodefile.write(buffer,length);
        delete[] buffer;
        encodefile.close();
        cout << "Zapisano do pliku " << filename<<endl;
        return true;
    }else {
        cerr << "Nie moge otworzyc pliku " << filename << endl; 
        return false;
    }
}

string getErrorMessage(int errorCode)
{
    static map<int, string> codes;
    static bool initialized = false;
    if (!initialized) {
        codes[0]    = "No error.";
        codes[10]   = "Read error.";
        codes[40]   = "Network or protocol error.";
        initialized = true;
    }
    if (codes.count(errorCode) > 0)
        return codes[errorCode];
    return "Unknown error.";
}