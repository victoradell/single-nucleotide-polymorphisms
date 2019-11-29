#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

using MatrixInt = vector<vector<int> >;
using MatrixDouble = vector<vector<double> >;

const int N = 500;
const int D = 39108;
const int dictionary_length = 3; // All SNP's are codified as {0, 1, 2}


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


MatrixInt n_gram_features(const MatrixInt& X, int n) {
    int features_dimension = (int)pow(dictionary_length, n);
    cout << "Feature space has dimension " << features_dimension << endl;
    MatrixInt features(N, vector<int>(features_dimension, 0));
    for (int individual = 0; individual < N; ++individual) {
        for (int starting_index = 0; starting_index <= D-n; ++starting_index) {
            // We take advantage of the representation in base 3 (dictionary length).
            int value = 0;
            for (int it = 0; it < n; ++it) {
                value += X[individual][starting_index + it] * (int)pow(dictionary_length, n-it-1);
            }
            ++features[individual][value];
        }
    }
    return features;
}


MatrixInt n_gram_kernel(const MatrixInt& X, int n) {
    MatrixInt features = n_gram_features(X, n);
    int n_features = features[0].size();
    cout << "Features finished: " << features.size() << " " << features[0].size() << endl;
    
    MatrixInt K(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        if (i % 20 == 0) {
            cout << "Building row " << i << "..." << endl;
        }
        for (int j = i; j < N; ++j) {
            int total = 0;
            for (int it = 0; it < n_features; ++it) {
                total += features[i][it] * features[j][it];
            }
            K[i][j] = total;
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


void write_kernel_matrix(const MatrixInt& K, string filepath) {
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
    cout << "Finished loading the dataset" << endl;

    // MatrixInt F = n_gram_features(X, 3);

    MatrixInt K = n_gram_kernel(X, 11);
    cout << "Finished building K" << endl;
    
    filepath = "../kernel_matrices/11_gram.txt";
    write_kernel_matrix(K, filepath);
    cout << "Kernel matrix written at " << filepath << endl;


    // MatrixDouble K = dirac_kernel(X);
    // cout << "Finished building K" << endl;

    // filepath = "../kernel_matrices/dirac.txt";
    // write_kernel_matrix(K, filepath);
    // cout << "Kernel matrix written at " << filepath << endl;
}