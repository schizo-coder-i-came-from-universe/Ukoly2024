#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int> > stavVezi;
};


void provedTah(vector<vector<int> >& veze, Tah tah) {
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);

}


void hanoi(int n, char z, char pomocny, char cil, vector<vector<int> >& veze, vector<Tah>& tahy,int& pocetkroku) {
    if (n == 1) {
        Tah tah = {1, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);
        pocetkroku++;
    } else {
        hanoi(n - 1, z, cil, pomocny, veze, tahy,pocetkroku);
        Tah tah = {n, z, cil, veze};
        provedTah(veze, tah);
        tahy.push_back(tah);
        hanoi(n - 1, pomocny, z, cil, veze, tahy,pocetkroku);
        pocetkroku++;
    }
}


void zobrazVeze(const vector<vector<int> >& veze,int vyska) {
int totalWidth = vyska * 2 +1; // sirka vezi

    for (int i = vyska - 1; i >= 0; --i) {
        for (int j = 0; j < 3; ++j) {
            if (i < veze[j].size()) {
                int disk = veze[j][i];
                int diskWidth = disk * 2+1;
                int padding = (totalWidth - diskWidth) / 2; // Pocet mezer pred a za diskem
                cout << string(padding, ' ') << string(diskWidth, '=') << string(padding, ' ');
            } else {
                cout << string(totalWidth / 2, ' ') << "|" << string(totalWidth / 2, ' ');
            }
            cout << "   "; // mezera mezi vezemi
        }
        cout << endl;
    }

    // zakladna vezi
    for (int j = 0; j < 3; ++j) {
        cout << string(totalWidth, '-') << "   ";
    }
    cout << endl;
}

#ifndef __TEST__
int main()
{
    int n;
    cout << "Zadejte pocet disku: ";
    cin >> n;
    cin.ignore();

    vector<vector<int> > veze(3);
    for (int i = n; i > 0; i--)
    {
        veze[0].push_back(i);
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    int pocetkroku=0;
    hanoi(n, 'A', 'B', 'C', veze, tahy,pocetkroku);
    
    // Zobrazení tahů a stavů věží
    for (Tah tah: tahy)
    {   
        provedTah(tah.stavVezi, tah); // Provedení tahu
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi,n); // Zobrazení stavu věží po tahu
    }
    cout << "Celkem kroku: " << pocetkroku << endl;
    return 0;
}
#endif // __TEST__