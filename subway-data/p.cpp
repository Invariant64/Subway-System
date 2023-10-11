#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define LINE_FILE "../line.txt"

using std::string;
using std::cout;
using std::endl;
using std::map;

// struct Edge {
//     string from;
//     string to;
//     string line;
//     int weight;
// } edges[1000];

int edges_num = 0;
int stations_num = 0; 

int main() {
    // FILE *fp = fopen(LINE_FILE, "r");
    // if (fp == NULL) {
    //     std::cout << "Error: " << LINE_FILE << " not found" << std::endl;
    //     return 1;
    // }

    std::ifstream fp;
    std::ofstream of;

    // read lines
    fp.open(LINE_FILE, std::ios::in);
    if (!fp.is_open()) {
        std::cout << "Error: " << LINE_FILE << " not found" << std::endl;
        return 1;
    }
    string lines[50];
    int num_lines = 0;
    while (!fp.eof()) {
        getline(fp, lines[num_lines]);
        num_lines++;
    }
    fp.close();

    // write lines
    of.open("../lines.txt", std::ios::out);
    if (!of.is_open()) {
        std::cout << "Error: lines.txt not found" << std::endl;
        return 1;
    }
    for (int i = 0; i < num_lines; i++) {
        of << i << ' ' << lines[i] << "\n";
    }
    of.close();

    // read edges and write edges
    of.open("../edges.txt", std::ios::out);
    map<string, int> m;
    for (int i = 0; i < num_lines; i++) {
        fp.open("../" + lines[i] + ".txt", std::ios::in);
        if (!fp.is_open()) {
            std::cout << "Error: " << lines[i] << ".txt not found" << std::endl;
            return 1;
        }
        string from, to;
        int weight;
        while (fp >> from >> to >> weight) {
            if (m.find(from) == m.end()) {
                m[from] = stations_num++;
            }
            if (m.find(to) == m.end()) {
                m[to] = stations_num++;
            }
            of << edges_num << ' ' << i << ' ' << m[from] << ' ' << m[to] << ' ' << 0 << ' ' << weight << "\n";
            edges_num++;
            of << edges_num<< ' ' << i << ' ' << m[to] << ' ' << m[from] << ' ' << 0 << ' ' << weight << "\n";
            edges_num++;
        }
        fp.close();
    }
    of.close();
    // for (int i = 0; i < edges_num; i++) {
    //     cout << edges[i].from << " " << edges[i].to << " " << edges[i].weight << endl;
    // }

    // write stations
    of.open("../stations.txt", std::ios::out);
    for (auto it = m.begin(); it != m.end(); it++) {
        of << it->second << ' ' << it->first << "\n";
    }
    of.close();
    
}