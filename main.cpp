#include <iostream>
#include <fstream>
#include <string>


using namespace std;


void To_Uppercase(string& text)//budowa funkcji zmieniajacej znak z liter malych na wielkie w wiadomosci
{
    for (unsigned int i = 0;i < text.length();i++)//petla iteracyjna dla kazdego znaku
    {
        if (text.at(i) >= 'a' && text.at(i) <= 'z')//jezeli wiadomosc jest zawiera male litery to funkcja ta zamienia odejmujac 32 od kazdego znaku w ASCII zamienia go na litery duze
        {
            text.at(i) -= 32;
        }
    }
}


string Encrypt(string message, string key)
{
    int keyIndex = 0;//zmienna jest uzywana do tego aby okreslic ktory znak klucza jest uzywany do szyfrowania kolejnego znaku
    string encrypted;

    for (unsigned int i = 0; i < message.length(); i++)//petla ktora idzie po kolei po kazdym znaku w wyrazie
    {
        if (isalpha(message[i]))//sprawdzenie czy znak jest litera
        {
            int shift = tolower(key[keyIndex % key.length()]) - 'a';//jezeli znak jest litera to przesunieciem jest roznica miedzy znakiem klucza ktory jest zamieniany na litere mala, a pierwsza litera alfabetu

            if (isupper(message[i]))//isupper zwraca wartosc gdy litera jest wielka,
            {
                encrypted += (char)(((message[i] - 'A') +shift )%26  + 'A');//+shift % 26 jest to dodanie przesuniecia do znaku i zamienienia go na zakres od A do Z, char rzutuje calosc na znak ktory jest pozniej dodawany do encrypted
            }
            else//zwracanie wartosci dla litery malej
            {
                encrypted += (char)(((message[i] - 'a') + shift)%26 + 'a');//to samo co w 27 linijce dla malej litery
            }
            keyIndex++;//zwi�kszenie indeksu klucza o wartosc 1
        }
        else if (message[i] == ' ')//jezeli znak nie jest litera szyfrowanie go pomija
        {
            encrypted += ' ';
        }
    }
    return encrypted;//funkcja zwraca wartosc zaszyfrowana
}

string Decrypt(string message, string key)
{
    int keyIndex = 0;//zmienna jest uzywana do tego aby okreslic ktory znak klucza jest uzywany do deszyfrowania kolejnego znaku
    string decrypted;

    for (unsigned int i = 0; i < message.length(); i++)//petla ktora idzie po kolei po kazdym znaku w wyrazie zaszyfrowanym
    {
        if (isalpha(message[i]))//sprawdzenie czy znak jest litera
        {
            int shift = tolower(key[keyIndex % key.length()]) - 'a';//jezeli znak jest litera to przesunieciem jest roznica miedzy znakiem klucza ktory jest zamieniany na litere mala, a pierwsza litera alfabetu

            if (isupper(message[i]))//isupper zwraca wartosc gdy litera jest wielka, jezeli jest to jest odszyfrowany przez odjecie przesuniecia od litery "A" a nastepnie dodaje go do "decrypted"
            {
                decrypted += (char)(((message[i] - 'A') - shift + 26) % 26 + 'A');//shift + 26 % 26 jest to przesuniecie z powrotem do zakresu od 0 do 25, z kolei A jest po to zeby przesunac go z oryginalnego zakresu A do Z , char rzutuje calosc na znak ktory jest pozniej dodawany do decrypted
            }
            else//jezeli znak nie jest litera wielka to jest odszyfrowany przez odjecie przesuniecia od litery "a" a nastepnie dodany do "decrypted"
            {
                decrypted += (char)(((message[i] - 'a') - shift + 26) % 26 + 'a');//to samo co w 55 linijce dla malej litery
            }
            keyIndex++;//zwiekszenie indeksu klucza o wartosc 1
        }
        else if (message[i] == ' ')//jezeli znak nie jest litera deszyfrowanie go pomija
        {
            decrypted += ' ';
        }
    }
    return decrypted;//funkcja zwraca wartosc odszyfrowana
}

int main()
{
    char choice= '0';//znak wyboru
    string key, message;
    cout << "Welcome to the program which is encrypting and decrypting a text with vigenere cipher." << endl;
    cout << "Before making choices you need to create a file named message.txt in a folder where the program is located."<<endl;
    //for (;;)
    //{
    for (;;)
    {
        cout << "Make your choice: "<< endl;
        cout << "1. Encryption from file\n2. Decryption from file\n3. Encryption from user message\n4. Decryption from user message\n5. Close the program" << endl;
        cin >> choice;
        //remove ("encrypted.txt");
        //remove ("decrypted.txt");
        //ofstream encrypted1("encrypted.txt", ios::trunc);
        //ofstream decrypted1("decrypted.txt", ios::trunc);
        cin.ignore();

        message.clear();

        switch (choice)//menu wyboru
        {
            case '1'://wczytywanie wiadomosci z pliku(szyfrowanie)
            {
                ifstream ifhandle("message.txt", ios::in); //czytanie z pliku
                if (!ifhandle)
                {
                    cout << "Cannot open file " <<"message.txt"<< "." << endl;//blad przy odczytywaniu z pliku

                    return 0;
                }
                string input_line;
                while (getline(ifhandle, input_line))//czytanie tekstu do zaszyfrowania z pliku
                {
                    message += input_line;//czytanie calej lini tekstu z wiadomosci
                    message += '\n';
                }
                ifhandle.close();
                cout<<"enter key (key must be typed by alphabet letters only)"<<endl;
                cin>>key;
                To_Uppercase(key);//implementowanie funkcji zmieniajacej litery male na wielkie w kluczu
                cout << "Encryption has been uploaded to text file." << endl;
                ofstream encryptedfile("encrypted.txt", ios::out);//zapis tekstu po szyfrowaniu do pliku
                encryptedfile << "Message from the file: " << message << endl;
                To_Uppercase(message);//implementowanie funkcji zmieniajacej litery male na wielkie w wiadomosci
                encryptedfile << "Message after encryption: " << Encrypt(message,key)<< endl;////implementowanie funkcji szyfrujacej
                encryptedfile.close();
                break;
            }
            case '2'://wczytywanie wiadomosci z pliku(deszyfrowanie)
            {
                ifstream ifhandle("message.txt", ios::in); //czytanie z pliku
                if (!ifhandle)
                {
                    cout << "Cannot open file " <<"message.txt"<< "." << endl;
                    return 0;
                }
                string input_line;
                while (getline(ifhandle, input_line))//czytanie tekstu do zaszyfrowania z pliku
                {
                    message += input_line;
                    message += '\n';
                }
                ifhandle.close();
                cout << "enter key(key must be typed by alphabet letters only)"<< endl;
                cin >> key;
                To_Uppercase(key);
                cout << "Decryption has been uploaded to text file." << endl;
                ofstream decryptedfile ("decrypted.txt", ios::out);//zapis tekstu po odszyfrowaniu do pliku
                decryptedfile << "Message from the file: "<< message << endl;
                To_Uppercase(message);
                decryptedfile << "Message after decryption: " << Decrypt(message,key) << endl;
                decryptedfile.close();
                break;
            }
            case '3'://podanie wiadomosci z klawiatury(szyfrowanie)
            {
                cout << "Enter message(message must be typed by alphabet letters only): " << endl;
                getline(cin,message);
                cout << "Enter key(key must be typed by alphabet letters only): " << endl;
                getline(cin,key);
                To_Uppercase(key);//implementacja funkcji zmieniajacej litery male na wielkie w wiadomosci
                To_Uppercase(message);//implementacja funkcji zmieniajacej litery male na wielkie w wiadomosci
                cout << "Your message after encryption: " << Encrypt(message, key) << endl;//implementacja szyfrowania
                break;
            }
            case '4'://podanie wiadomosci z klawiatury(deszyfrowanie)
            {
                cout << "Enter encrypted message(message must be typed by alphabet letters only): " << endl;
                getline(cin,message);
                cout << "Enter key(key must be typed by alphabet letters only): " << endl;
                getline(cin,key);
                To_Uppercase(key);//implementacja funkcji zmieniajacej litery male na wielkie w wiadomosci
                To_Uppercase(message);//implementacja funkcji zmieniajacej litery male na wielkie w wiadomosci
                cout << "Your message after decryption: " << Decrypt(message, key) << endl;//implementacja deszyfrowania
                break;
            }
            case '5'://wylaczenie programu
            {
                cout << "Closing the program" << endl;
                return 0;
            }
            default://przy podaniu nieodpowiedniego przycisku program przekazuje wiadomosc aby wybrac odpowiednia cyfre wyboru.
            {
                cout << "Make valid choice." << endl;
                // break;
                continue;
            }
        }
        //}
    }


}