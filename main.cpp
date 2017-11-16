//
//  main.cpp
//  Gaus Jordan partial pivot
//
//  Created by Eris  Llangos on 7/13/17.
//  Copyright © 2017 Eris  Llangos. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

void print(vector< vector<double> > mat) {
    size_t size = mat.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size + 1; j++) {
            cout << mat[i][j] << " ";
            if (j == size - 1) {
                cout << "| ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

vector<double> gauss(vector< vector<double> > mat) {
    size_t size = mat.size();
    
    for (int i = 0; i < size; i++) {
        double maxElement = 0.0;
        int maxRow = i;
        for (int k = i + 1; k < size; k++) {
            if (abs (mat[k][i]) > maxElement) {
                maxElement = abs(mat[k][i]);
                maxRow = k;
            }
        }
        // partial pivot
        for (int j = i; j < size + 1; j++) {
            swap(mat[i][j], mat[maxRow][j]);
        }
        // perfor Gaussian and make everything before pivot 0
        for (int j = i + 1; j < size; j++) {
            double factor = -mat[j][i] / mat[i][i];
            for (int k = i; k < size + 1; k++) {
                if (i == k) {
                    mat[j][k] = 0;
                }
                else {
                    mat[j][k] += factor * mat[i][k];
                }
            }
        }
    }
    vector<double> result(size);
    for (int i = size - 1; i >= 0; i--) {
        result[i] = mat[i][size] / mat[i][i];
        for (int j = i - 1;j >= 0; j--) {
            mat[j][size] -= mat[j][i] * result[i];
        }
    }
    return result;
}

int main() {
    cout << 'A' + 'B' << endl;
    cout << "Enter size of square matrix: ";
    int size;
    cin >> size;
    cout << endl;
    vector<double> oneLine(size + 1, 0);
    vector< vector<double> > mat(size, oneLine);
    
    string filename;
    cout << "Enter filename: " << endl;
    cin >> filename;
    cout << "Reading from " << filename << endl << endl;

    ifstream in;
    in.open(filename);
    
    //read matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            in >> mat[i][j];
        }
    }
    //read result vector
    for (int i = 0; i < size; i++) {
        in >> mat[i][size];
    }
    in.close();
    
    print(mat);
    //create solution vector
    vector<double> x(size);
    x = gauss(mat);
    // Print solution
    cout << "Result(transposed): ";
    for (int i = 0; i < size; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

