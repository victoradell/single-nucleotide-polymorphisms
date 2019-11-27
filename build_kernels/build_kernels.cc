#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
using Matrix = vector<vector<int>>;

const int N = 389;
const int D = 27183;

Matrix load_dataframe(string filepath) {
    Matrix K(N, vector<int>(N, 0));
    ifstream data(filepath);
    if (data.is_open()) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < D; ++j) {

            }
        }
    } else {
        cout << "Could not load " << filepath << endl;
    }
    return K;
}



int main() {
    Matrix X = load_dataframe("../data/snp.csv");
}