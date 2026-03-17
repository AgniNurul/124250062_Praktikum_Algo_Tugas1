#include <iostream>
#include <cstring>
using namespace std;

struct Karyawan {
	int id;
	char nama[50];
};

struct Barang {
	char nama[50];
	int harga;
	int stok;
};

void tambahKaryawan() {
	FILE *fp = fopen("karyawan.txt", "a");
	if(fp == NULL) {
		cout << "File gagal dibuka!\n";
		return;
	}
	
	int jumlah;
    cout << "Masukkan jumlah karyawan: ";
    cin >> jumlah;

    Karyawan k[100];

    for(int i = 0; i < jumlah; i++){
        cout << "\nData ke-" << i + 1 << endl;

        cout << "ID Karyawan: ";
        cin >> k[i].id;
        cin.ignore();

        cout << "Nama Karyawan: ";
        cin.getline(k[i].nama, 50);
    }

    for(int i = 0; i < jumlah; i++){
        fprintf(fp, "%d %s\n", k[i].id, k[i].nama);
    }
    fclose(fp);

    cout<<"Semua data berhasil ditambahkan!\n";
}

void lihatKaryawan() {
	FILE *fp = fopen("karyawan.txt", "r");
	if(fp == NULL) {
		cout << "File tidak ditemukan!\n";
		return;
	}
	
	Karyawan k;
	while(fscanf(fp, "%d %[^\n]\n", &k.id, k.nama) != EOF) {
		cout << "ID karyawan: " << k.id << "\nNama karyawan: " << k.nama << "\n\n";
	}
	fclose(fp);
}

void cariKaryawan() {
	FILE *fp = fopen("karyawan.txt", "r");
	if(fp == NULL) {
		cout << "File tidak ditemukan!\n";
		return;
	}
	
	int cari;
	bool ketemu = false;
	Karyawan k;
	
	cout << "Masukkan ID: ";
	cin >> cari;
	
	while(fscanf(fp, "%d %[^\n]\n", &k.id, k.nama) != EOF) {
		if(k.id == cari) {
			cout << "Ditemukan!\n";
			cout << "ID: " << k.id << "\nNama: " << k.nama << "\n";
			ketemu = true;
		}
	}
	
	if(!ketemu) cout << "Data tidak ditemukan!\n";
	fclose(fp);
}

//SORTING
//Bubble Sort
void bubbleSort(Barang arr[], int n) {
	for(int i = 0; i < n-1; i++) {
		for(int j = 0; j < n-i-1; j++) {
			if(arr[j].harga > arr[j+1].harga) {
				Barang temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

//Quick Sort
void quickSort(Barang arr[], int low, int high) {
	int i = low, j = high;
	int pivot = arr[(low + high)/2].harga;
	
	while(i <= j) {
		while(arr[i].harga > pivot) i++;
		while(arr[j].harga < pivot) j--;
		
		if(i <= j) {
			Barang temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	
	if(low < j) quickSort(arr, low, j);
	if(i < high) quickSort(arr, i, high);
}

//BARANG
void tambahBarang() {
	FILE *fp = fopen("barang.txt", "a");
	if(fp == NULL) {
		cout << "File gagal dibuka!\n";
		return;
	}
	
	int jumlah;
    cout << "Masukkan jumlah barang: ";
    cin >> jumlah;
    cin.ignore();
	
	Barang b;
	for(int i = 0; i < jumlah; i++) {
        cout << "\nData ke-" << i + 1 << endl;

        cout << "Nama Barang: ";
        cin.getline(b.nama, 50);

        cout << "Harga Barang: ";
        cin >> b.harga;

        cout << "Stok Barang: ";
        cin >> b.stok;
        cin.ignore();

        fprintf(fp, "%s | %d | %d\n", b.nama, b.harga, b.stok);
    }
	fclose(fp);
	
	cout << "Barang ditambahkan!\n";
}

void lihatBarang() {
	FILE *fp = fopen("barang.txt", "r");
	if(fp == NULL) {
		cout << "File tidak ditemukan!\n";
		return;
	}
	
	Barang arr[100];
	int n = 0;
	
	while(fscanf(fp, "%[^|] | %d | %d\n", arr[n].nama, &arr[n].harga, &arr[n].stok) != EOF) {
		n++;
	}
	fclose(fp);
	
	int pilih;
	cout << "1. Ascending (Bubble)\n";
	cout << "2. Descending (Quick)\n";
	cout << "Pilih: \n";
	cin >> pilih;
	
	if(pilih == 1) bubbleSort(arr, n);
	else quickSort(arr, 0, n-1);
	
	for(int i = 0; i < n; i++) {
		cout << arr[i].nama << " | " << arr[i].harga << " | " << arr[i].stok << "\n";
	}
}

//Binary Search
int binarySearch(Barang arr[], int n, char cari[]) {
    int left = 0, right = n-1;

    while(left <= right) {
        int mid = (left + right)/2;

        int hasil = strcmp(arr[mid].nama, cari);

        if(hasil == 0) return mid;
        else if(hasil < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void cariBarang() {
	FILE *fp = fopen("barang.txt", "r");
	if(fp == NULL) {
		cout << "File tidak ditemukan!\n";
		return;
	}
	
	Barang arr[100];
	int n = 0;
	
	while(fscanf(fp, "%[^|] | %d | %d\n", arr[n].nama, &arr[n].harga, &arr[n].stok) != EOF) {
		n++;
	}
	fclose(fp);
	
	int metode;
    cout << "1. Sequential Search\n2. Binary Search\nPilih metode: ";
    cin >> metode;

    char cari[50];
    cin.ignore();
    cout << "Masukkan nama barang: ";
    cin.getline(cari, 50);

    bool ketemu = false;
    
    //Sequential
    if(metode == 1) {
        for(int i = 0; i < n; i++) {
            if(strcmp(arr[i].nama, cari) == 0) {
                cout << "Barang ditemukan!\n";
                cout << "Nama Barang: " << arr[i].nama << endl;
                cout << "Harga Barang: " << arr[i].harga << endl;
                cout << "Stok Barang: " << arr[i].stok << endl;
                ketemu = true;
            }
        }
    }

    //Binary
    else if(metode == 2) {
        bubbleSort(arr, n);

        int idx = binarySearch(arr, n, cari);

        if(idx != -1) {
            cout << "Barang ditemukan!\n";
            cout << "Nama : " <<arr[idx].nama << endl;
            cout << "Harga : " <<arr[idx].harga << endl;
            cout << "Stok : " <<arr[idx].stok << endl;
            ketemu = true;
		}
	}
	if(!ketemu) cout << "Tidak ditemukan!\n";
}

void editBarang() {
	FILE *fp = fopen("barang.txt","r");
    if(fp == NULL){
        cout << "File tidak ditemukan!\n";
        return;
    }

    Barang arr[100];
    int n = 0;

    while(fscanf(fp, "%[^|] | %d | %d\n", arr[n].nama, &arr[n].harga, &arr[n].stok) != EOF) {
        n++;
    }
    fclose(fp);

    char cari[50];
    cin.ignore();
    cout << "Masukkan nama barang yang ingin diedit: ";
    cin.getline(cari,50);

    bool ketemu = false;

    for(int i = 0; i < n; i++) {
        if(strcmp(arr[i].nama, cari)==0) {
            ketemu = true;

            cout << "\nData ditemukan!\n";
            cout << "Nama Barang: " << arr[i].nama << endl;
            cout << "Harga Barang: " << arr[i].harga << endl;
            cout << "Stok Barang: " << arr[i].stok << endl;

            cout << "\nMasukkan data baru\n";
            cout << "Nama Barang: ";
            cin.getline(arr[i].nama, 50);
            cout << "Harga Barang: ";
            cin >> arr[i].harga;
            cout << "Stok Barang: ";
            cin >> arr[i].stok;
        }
    }

    if(!ketemu) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    fp = fopen("barang.txt","w");
    for(int i = 0; i < n; i++) {
        fprintf(fp, "%s %d %d\n", arr[i].nama, arr[i].harga, arr[i].stok);
    }
    fclose(fp);

    cout << "Data berhasil diupdate!\n";
}

int main() {
	int pilihan;
	
	do {
		cout << "\n=== WELCOME TO COCOA HEAVEN ===\n";
		cout << "1. Login Admin\n";
		cout << "2. Karyawan\n";
		cout << "3. Keluar\n";
		cout << "Masukkan pilihan menu: ";
		cin >> pilihan;
		cout << "==================================\n";
		
		if(pilihan == 1) {
			string user, pass;
			cout << "Username: ";
			cin >> user;
			cout << "Password: ";
			cin >> pass;
			cout << "==================================\n";
			
			if(user == "admin" && pass == "123") {
				int p;
				do {
					cout << "\n=== HALO ADMIN!====\n";
					cout << "1. Tambah data karyawan\n";
					cout << "2. Lihat data karyawan\n";
					cout << "3. Searching data karyawan\n";
					cout << "4. Logout\n";
					cout << "Pilih menu: ";
					cin >> p;
					cout << "==================================\n";
					
					if(p == 1) tambahKaryawan();
					else if(p == 2) lihatKaryawan();
					else if(p == 3) cariKaryawan();
				} while(p != 4);
			} else {
				cout << "Login gagal!\n";
			}
		}
		
		else if(pilihan == 2) {
			int p;
			
			do {
				cout << "\n=== HALO KARYAWAN! ===\n";
				cout << "1. Tambah data barang\n";
				cout << "2. Lihat data barang\n";
				cout << "3. Edit data barang\n";
				cout << "4. Cari data barang\n";
				cout << "5. Logout\n";
				cout << "Pilih: ";
				cin >> p;
				cout << "==================================\n";
				
				if(p == 1) tambahBarang();
				else if(p == 2) lihatBarang();
				else if(p == 3) editBarang();
				else if(p == 4) cariBarang();
			} while(p != 5);
		}
	} while(pilihan != 3);
	return 0;
}
