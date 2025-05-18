#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
#define M 2000

struct Company {
    string name;
    string profit_tax;
    string address;
};
typedef Company* HashTable; // HashTable thực chất là Company*

vector<Company> readCompanyList(string file_name) {
    vector<Company> companies;
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Can not open " << file_name << endl;
        return companies;
    }

    string line;
    getline(file, line); // Skip dong dau tien
    while (getline(file, line)) {
        Company cur_company;
        stringstream tok(line); 
        getline(tok, cur_company.name, '|');
        getline(tok, cur_company.profit_tax, '|');
        getline(tok, cur_company.address);
        companies.push_back(cur_company);
    }
    file.close();
    return companies;
}
long long hashString(string company_name) {
    string s = company_name;
    if (s.length() > 20) {
        s = s.substr(s.length() - 20);
    }

    const int p = 31;
    const int m = M;
    long long hash = 0;
    long long p_pow = 1; // p^i.

    for (char c : s) {
        // hash = (hash + (char * p^i) % m) % m
        hash = (hash + (c * p_pow) % m) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash;
}
void insert(HashTable* hash_table, Company company) {

    long long hash_idx = hashString(company.name);
    int first_idx = hash_idx;

    while (hash_table[hash_idx] != nullptr) {
        if (hash_table[hash_idx]->name == company.name) {
            cout << company.name << " is existed" << endl;
            return;
        }
        hash_idx = (hash_idx + 1) % M;
        if (hash_idx == first_idx) {
            cout << "The table is full" << endl;
            return;
        }
    }
    hash_table[hash_idx] = new Company(company);
}
HashTable* createHashTable(vector<Company> list_company) {
    HashTable* table = new HashTable[M];
    for (int i = 0; i < M; i++) {
        table[i] = nullptr;
    }
    for (int i = 0; i < list_company.size(); ++i) {
        Company company_data = list_company[i];
        insert(table, company_data);
    }
    return table;
}
Company* search(HashTable* hash_table, string company_name) {
    long long hash_idx = hashString(company_name);
    int first_idx = hash_idx;

    while (hash_table[hash_idx] != nullptr) {
        if (hash_table[hash_idx]->name == company_name) {
            return hash_table[hash_idx];
        }
        hash_idx = (hash_idx + 1) % M;
        if (hash_idx == first_idx) {
            cout << "Can not find" << company_name << endl;
            break;
        }
    }
    return nullptr;
}

void inandout(HashTable* hash_table, string input_file, string output_file) {
    ifstream input(input_file);
    ofstream output(output_file);
    if (!input.is_open()) {
        cout << "can not open " << input_file << endl;
        return;
    }
    if (!output.is_open()) {
        cout << "can not open" << output_file << endl;
        return;
    }
    string company_name;
    while (getline(input, company_name)) {
        Company* cur_company = search(hash_table, company_name);
        if (cur_company != nullptr) {
            output << cur_company->name << "|" << cur_company->profit_tax << "|" << cur_company->address << endl;
        } else {
            output << company_name << "|NOT FOUND" << endl;
        }
    }
    input.close();
    output.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./main.exe <MST.txt> <input.txt> <output.txt>" << endl;
        return 1;
    }
    vector<Company> companies_list = readCompanyList(argv[1]);
    if (companies_list.empty()){
        cout << "Can not find data or " << argv[1] << " error" << endl;
        return 1;
    }
    HashTable* hash_table = createHashTable(companies_list);
    inandout(hash_table, argv[2], argv[3]);
    return 0;
}