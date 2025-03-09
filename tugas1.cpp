#include <iostream>
#include <iomanip>
using namespace std;


struct roti
            {
                string nama_roti;
                float harga;
                int koderoti;
            };

            roti rotianjay[5] = {
    {"RotiTawar", 5000, 1},
    {"Roti Susu", 7000, 2},
    {"Roti Coklat", 9000, 3},
    {"Roti Keju", 10000, 4},
    {"Roti Kacang", 8000, 5}
};


void quicksortroti(roti rotianjay[], int awal, int akhir) {

    int low = awal, high = akhir;

    float pivot = rotianjay[(awal + akhir) / 2].harga;

    int temp;

    do {

        while (rotianjay[low].harga > pivot)

            low++;

        while (rotianjay[high].harga < pivot)

            high--;

        if (low <= high) {

            swap(rotianjay[low], rotianjay[high]);

            low++;

            high--;

        }

    } while (low <= high);

    if (awal < high)

        quicksortroti(rotianjay, awal, high);

    if (low < akhir)

        quicksortroti(rotianjay, low, akhir);

}





int main()
{
    int pilihan ;
    roti *ptr = rotianjay;
    cout << "==============================" << endl;
    cout << "     TOKO ROTI ANGJAYANOI     " << endl;
    cout << "==============================" << endl;
    int n = sizeof(rotianjay) / sizeof(rotianjay[0]);


    do
    {
    
        cout << "1. Daftar Roti" << endl;
        cout << "2. Cari berdasar nama" << endl;
        cout << "3. cari berdasar harga" << endl;
        cout << "4. Sort Harga (ascending)" << endl;
        cout << "5. sort harga (descending)" << endl;
        cout << "6. EXIT" << endl;
        cout << "Pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {

        case 1:

           

            cout << "==============================" << endl;
            cout << "Nama Roti   |Kode    |Harga   " << endl;
            cout << "==============================" << endl;
            for (int i = 0; i < n; i++)
            {
                cout << setw(13) << left << ptr[i].nama_roti
                     << setw(9) << ptr[i].koderoti
                     << setw(10) << ptr[i].harga << endl;
            }
            cout << "==============================" << endl;

        
            break;

            case 2: 
            {
                string cari;
                cout << "MENU CARI BERDASAR NAMA" << endl;
                cout << "Masukkan nama roti yang dicari : ";
                cin.ignore();
                getline(cin, cari);
                
                for (int i = 0; i < n; i++)
                {
                    if (ptr[i].nama_roti == cari)
                    {   cout << "==============================" << endl;
                        cout << "Nama Roti   |Kode    |Harga   " << endl;
                        cout << "==============================" << endl;
                        cout << setw(13) << left << ptr[i].nama_roti
                             << setw(9) << ptr[i].koderoti
                             << setw(10) << ptr[i].harga << endl;
                    }
                }
            }
            
            break;

            case 3:
            {
                float cari;
                cout << "MENU CARI BERDASAR HARGA" << endl;
                cout << "Masukkan harga roti yang dicari : ";
                cin >> cari;
                cin.ignore();
                
                for (int i = 0; i < n; i++)
                {
                    if (ptr[i].harga == cari)
                    {
                        cout << "===============================" << endl;
                        cout << "Nama Roti   |Kode    |Harga   " << endl;
                        cout << "===============================" << endl;
                        cout << setw(13) << left << ptr[i].nama_roti
                             << setw(9) << ptr[i].koderoti
                             << setw(10) << ptr[i].harga << endl;
                    }
                }
            }
            break;

            case 4:
            {
                cout << "MENU SORT HARGA (ASCENDING)" << endl;
                for (int i = 0; i < n-1; i++)
                {
                    for (int j = i + 1; j < n-1-i; j++)
                    {
                        if (ptr[j].harga > ptr[j+1].harga)
                        {
                            // roti temp = ptr[i];
                            // ptr[i] = ptr[j];
                            // ptr[j] = temp;
                            swap(ptr[j], ptr[j + 1]);
                        }
                    }
                }
                cout << "Nama Roti   |Kode    |Harga   " << endl;
                cout << "==============================" << endl;
                for (int i = 0; i < n; i++)
                {
                    cout << setw(13) << left << ptr[i].nama_roti
                         << setw(9) << ptr[i].koderoti
                         << setw(10) << ptr[i].harga << endl;
                }
                cout << "==============================" << endl;
            }
            break;

            case 5:
                {
                cout << "MENU SORT ROTI BERDASAR HARGA (DESCENDING) quicksort" << endl;
                roti valueroti[5];
                 
                for (int i = 0; i < 5; i++) {
                    valueroti[i] = ptr[i];
                }
                quicksortroti(valueroti, 0, 4);
                cout << "==============================" << endl;
                cout << "Nama Roti   |Kode    |Harga   " << endl;
                cout << "==============================" << endl;

             for (int i = 0; i < n; i++)

                {
                      cout << setw(13) << left << valueroti[i].nama_roti;
                      cout << setw(9) << valueroti[i].koderoti;
                      cout << setw(10) << valueroti[i].harga << endl;
                         

                }
                cout << "==============================" << endl;
                }

                break;

        default:
            cout << "Salah input" << endl;
        }
    } while (pilihan != 6);

    return 0;
}