#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

using MatrixInt = vector<vector<int>>;
using MatrixDouble = vector<vector<double>>;

const int N = 500;
const int D = 39108;


MatrixInt load_dataframe(string filepath) {
    MatrixInt X(N, vector<int>(D, 0));
    ifstream data(filepath);
    if (data.is_open()) {
        string s;
        getline(data, s); // Omit header line

        for (int i = 0; i < N; ++i) {
            getline(data, s);
            istringstream iss(s);

            string val;
            getline(iss, val, ','); // Omit row index
            for (int j = 0; j < D; ++j) {
                getline(iss, val, ',');
                X[i][j] = stoi(val);
            }
        }
    } else {
        cout << "Could not load " << filepath << endl;
    }
    return X;
}


MatrixDouble dirac_kernel(const MatrixInt& X) {
    MatrixDouble K(N, vector<double>(N));
    for (int i = 0; i < N; ++i) {
        if (i % 20 == 0) {
            cout << "Building row " << i << "..." << endl;
        }
        for (int j = i; j < N; ++j) {
            int total = 0;
            for (int it = 0; it < D; ++it) {
                if (X[i][it] == X[j][it]) ++total;
            }
            K[i][j] = double(total) / D;
            K[j][i] = K[i][j];
        }
    }
    return K;
}


void write_kernel_matrix(const MatrixDouble& K, string filepath) {
    ofstream outfile(filepath);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j != 0) outfile << " ";
            outfile << K[i][j];
        }
        outfile << endl;
    }
    outfile.close();
}


int main() {
    string filepath = "../data/snp.csv";
    MatrixInt X = load_dataframe(filepath);

    MatrixDouble K = dirac_kernel(X);
    cout << "Finished building K" << endl;

    filepath = "../kernel_matrices/dirac.txt";
    write_kernel_matrix(K, filepath);
    cout << "Kernel matrix written at " << filepath << endl;
}