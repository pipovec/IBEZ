#include <iostream>
#include <fstream> 
#include <map>

using namespace std;

class ZiskajText
{
    public:
        string tmp;

        string SetString(int argc, char *argv[])
        {
            int i;
            for(i=1; i<argc; i++)
            {
                tmp += argv[i];
                tmp += " ";
            }
            return tmp;
        }

        // Pre jednoduchost je subor pevne dany a ma len jeden riadok
        string FileToString()
        {
            ifstream file("vstup.txt");
            
            getline(file,tmp);
            
            file.close();
            return tmp;
        }
};

class Ntice
{
    public:
        map<string,int> mymap;
        map<string,int>::iterator it;
        
        void SpracujTo(string Text, int ntic)
        {
            string tmp;
            int dlzka,i,medzera;
            i = 0;
            dlzka = Text.length();
            while(i < dlzka)
            {
                tmp = Text.substr(i, ntic);
                                
                /* 
                *  Nevedel som ci pri analyzovani iba vyskytu jedneho pismena
                *  mam do medzery medzi slovami dat x alebo nie, tak som to 
                *  osetril tak ze sa tam X doplni
                */

                // Najdenie " " a nahradenie X
                medzera = tmp.find(" ");
                if(medzera != -1)
                {
                    tmp.replace(medzera,1,"X");
                }
  
                
                
                // Ukladanie do mapy a pocitanie
                if(mymap.count(tmp) > 0)
                {
                    mymap[tmp] += 1;
                }
                else
                {
                    mymap[tmp] = 1 ;
                }

                i = i+ntic;

                tmp.clear();
                
            }
            
            for(it = mymap.begin(); it != mymap.end(); ++it)
            {
                cout << it->first << " => " << it->second << endl;
            }
            
        }

};

int main(int argc, char *argv[])
{
    string Text;
    
    // Zistenie ci ide o command line alebo subor
    if(argc == 1)
    {
       ZiskajText file;
       Text  = file.FileToString();
       cout << "Nacitany text zo suboru: " << endl << Text << endl; 
    }  
    else
    {
        ZiskajText cmd;
        Text = cmd.SetString(argc,argv);
        cout << "Text nacitany z riadka: " << endl << Text << endl;
    }

    // Rozparsovanie textu na n-gramy
    int ntic;

    cout << endl << "=============================" << endl;
    cout << "Zadaj kolko chces n-gramov: " ; 
    cin >> ntic;
    
    Ntice doit;
    doit.SpracujTo(Text,ntic);

    return 0;
}
