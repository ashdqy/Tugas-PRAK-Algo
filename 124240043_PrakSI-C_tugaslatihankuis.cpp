#include <iostream>
using namespace std;

struct datapnddk
{
    int nik;
    char nama[40];
    char alamat[50];
    char jenis_kelamin;
};

datapnddk penduduk[100];
int Pilihan;
int jumlah = 0;

void bubbleSort(datapnddk *penduduk, int jumlah)
{
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = 0; j < jumlah - i - 1; j++)
        {
            if (penduduk[j].nik > penduduk[j + 1].nik)
            {
                
                // datapnddk temp = penduduk[j];
                // penduduk[j] = penduduk[j + 1];
                // penduduk[j + 1] = temp;
                swap(penduduk[j], penduduk[j + 1]);
            }
        }
    }
}

void tampilkanData(datapnddk *penduduk, int jumlah)
{

    for (int i = 0; i < jumlah; i++)
    {
        cout << "Datapenduduk ke-" << (i + 1) << endl;
        cout << "NIK: " << penduduk[i].nik << endl;
        cout << "Nama: " << penduduk[i].nama << endl;
        cout << "alamat: " << penduduk[i].alamat << endl;
        cout << "Jenis Kelamin: " << penduduk[i].jenis_kelamin << endl;
    }
}

void bacaDataDariFile()
{
    FILE *datapenduduk = fopen("datapenduduk.txt", "r");
    if (datapenduduk == NULL)
    {
        cout << "Gagal membuka file" << endl;
        return;
    }

    while (fscanf(datapenduduk, "%d %s %s %c", &penduduk[jumlah].nik, penduduk[jumlah].nama, penduduk[jumlah].alamat, &penduduk[jumlah].jenis_kelamin) != EOF)
    {
        jumlah++;
    }
    fclose(datapenduduk);
}

void caridata()
{
    int cari;
    cout << "Masukkan NIK yang dicari : ";
    cin >> cari;
    int i = 0;
    while (penduduk[i].nik != cari)
    {
        i++;
    }
    if (i >= jumlah)
    {
        cout << cari << " tidak ditemukan" << endl;
    }
    else
    {
        cout << "Data ditemukan" << endl;
        cout << "NIK : " << penduduk[i].nik << endl;
        cout << "Nama : " << penduduk[i].nama << endl;
        cout << "Alamat : " << penduduk[i].alamat << endl;
        cout << "Jenis Kelamin : " << penduduk[i].jenis_kelamin << endl;
    }
}

void editdata()
{
    int cari;
    cout << "Masukkan NIK yang ingin diedit : ";
    cin >> cari;

    int i = 0;
    while (penduduk[i].nik != cari)
    {
        i++;
    }
    if (i >= jumlah)
    {
        cout << cari << " tidak ditemukan" << endl;
    }
    else
    {
        cout << "Data ditemukan" << endl;
        cout << "NIK : " << penduduk[i].nik << endl;
        cout << "Nama : " << penduduk[i].nama << endl;
        cout << "Alamat : " << penduduk[i].alamat << endl;
        cout << "Jenis Kelamin : " << penduduk[i].jenis_kelamin << endl;

        cout << "Masukkan alamat baru : ";
        cin.ignore();
        cin.getline(penduduk[i].alamat, 50);
    }
}

int main()
{
    bacaDataDariFile();

    do
    {
        cout << "==============================" << endl;
        cout << "  PROGRAM PENDATAAN PENDUDUK  " << endl;
        cout << "==============================" << endl;
        cout << "1. Input data penduduk" << endl;
        cout << "2. Tampilkan Data" << endl;
        cout << "3. cari data penduduk" << endl;
        cout << "4  Edit Data penduduk (alamat) " << endl;
        cout << "5. Hapus data penduduk" << endl;
        cout << "6. exit" << endl;
        cout << "Pilihan : ";
        cin >> Pilihan;

        switch (Pilihan)
        {
        case 1:
        {
            cout << "========================================" << endl;
            cout << "        MENU INPUT DATA PENDUDUK        " << endl;
            cout << "========================================" << endl;
            cout << "Masukkan Jumlah yang ingin diinput : ";
            cin >> jumlah;

            datapnddk penduduk[jumlah];

            for (int i = 0; i < jumlah; i++)
            {
                cout << "Data ke-" << i + 1 << endl;
                cout << "NIK : ";
                cin >> penduduk[i].nik;
                cout << "Nama : ";
                cin >> penduduk[i].nama;
                cout << "Alamat : ";
                cin >> penduduk[i].alamat;
                cout << "Jenis Kelamin : ";
                cin >> penduduk[i].jenis_kelamin;
            }

            FILE *datapenduduk = fopen("datapenduduk.txt", "a");
            if (datapenduduk == NULL)
            {
                cout << "gagal membuka" << endl;
            }
            else
            {
                cout << "Berhasil" << endl;
            }

            for (int i = 0; i < jumlah; i++)
            {
                fprintf(datapenduduk, "%d %s %s %c\n", penduduk[i].nik, penduduk[i].nama, penduduk[i].alamat, penduduk[i].jenis_kelamin);
            }
            fclose(datapenduduk);

            cout << "Data berhasil diinput" << endl;

            break;
        }

        case 2:
        {
            cout << "========================================" << endl;
            cout << "        MENU TAMPIL DATA PENDUDUK       " << endl;
            cout << "========================================" << endl;
            FILE *datapenduduk = fopen("datapenduduk.txt", "r");
            if (datapenduduk == NULL)
            {
                cout << "gagal membuka" << endl;
            }
            else
            {
                cout << "Berhasil" << endl;
            }
            // fscanf ;

            bubbleSort(penduduk, jumlah);
            tampilkanData(penduduk, jumlah);
            fclose(datapenduduk);

            break;
        }

        case 3:
        {
            cout << "========================================" << endl;
            cout << "        MENU CARI DATA PENDUDUK         " << endl;
            cout << "========================================" << endl;
            caridata();

            break;
        }

        case 4:
        {
            cout << "========================================" << endl;
            cout << "     MENU EDIT DATA PENDUDUK(alamat)    " << endl;
            cout << "========================================" << endl;

            editdata();
            FILE *datapenduduk = fopen("datapenduduk.txt", "w");
            if (datapenduduk == NULL)
            {
                cout << "gagal membuka" << endl;
            }
            else
            {
                cout << "Berhasil" << endl;
            }
                for (int i = 0; i < jumlah; i++)
                {
                    fprintf(datapenduduk, "%d %s %s %c\n", penduduk[i].nik, penduduk[i].nama, penduduk[i].alamat, penduduk[i].jenis_kelamin);
                }
                
            fclose(datapenduduk);

            break;
        }

            case 5: {

                cout << "========================================" << endl;
                cout << "        MENU HAPUS DATA PENDUDUK        " << endl;
                cout << "========================================" << endl;

                int hapus;
                cout << "Masukkan NIK yang ingin dihapus : ";
                cin >> hapus;

                int i = 0;
                while (penduduk[i].nik != hapus)
                {
                    i++;
                }
                if (i >= jumlah)
                {
                    cout << hapus << "data tidak ditemukan" << endl;
                }
                else
                {
                    cout << "Data ditemukan" << endl;
                    cout << "Data yang dihapus" << endl;
                    cout << "NIK : " << penduduk[i].nik << endl;
                    cout << "Nama : " << penduduk[i].nama << endl;
                    cout << "Alamat : " << penduduk[i].alamat << endl;
                    cout << "Jenis Kelamin : " << penduduk[i].jenis_kelamin << endl;
                    for (int j = i; j < jumlah-1; j++)
                    {
                        penduduk[j] = penduduk[j + 1];
                    }
                    jumlah--;
                    cout << "Data berhasil dihapus" << endl;
                }
                
                    FILE *datapenduduk = fopen("datapenduduk.txt", "w");
                    if (datapenduduk == NULL)
                    {
                        cout << "gagal membuka" << endl;
                    }
                    else
                    {
                        cout << "Berhasil" << endl;
                    }
                    for (int i = 0; i < jumlah; i++)
                    {
                        fprintf(datapenduduk, "%d %s %s %c\n", penduduk[i].nik, penduduk[i].nama, penduduk[i].alamat, penduduk[i].jenis_kelamin);
                    }

                        fclose(datapenduduk);



               break; 
            }
                case 6:
                {
                    cout << "Terima kasih" << endl;
                    break;
                }


        }
    } while (Pilihan != 6);

    return 0;
}
