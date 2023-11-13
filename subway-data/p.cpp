#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

#define LINE_FILE "../line.txt"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::set;

int edges_num = 0;
int stations_num = 0;

int main() {

    std::ifstream fp;
    std::ofstream of, of1;

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

    set< pair<int, int> > edges;

    // read edges and write edges and write lines
    of.open("../edges.txt", std::ios::out);
    if (!of.is_open()) {
        std::cout << "Error: edges.txt not found" << std::endl;
        return 1;
    }
    of1.open("../lines.txt", std::ios::out);
    if (!of1.is_open()) {
        std::cout << "Error: lines.txt not found" << std::endl;
        return 1;
    }
    map<string, int> station_to_id;
    for (int i = 0; i < num_lines; i++) {
        fp.open("../" + lines[i] + ".txt", std::ios::in);
        if (!fp.is_open()) {
            std::cout << "Error: " << lines[i] << ".txt not found" << std::endl;
            return 1;
        }
        string from, to;
        int weight;
        set<int> stations_in_line;
        while (fp >> from >> to >> weight) {
            if (station_to_id.find(from) == station_to_id.end()) {
                station_to_id[from] = stations_num++;
            }
            if (station_to_id.find(to) == station_to_id.end()) {
                station_to_id[to] = stations_num++;
            }
            stations_in_line.insert(station_to_id[from]);
            stations_in_line.insert(station_to_id[to]);
            if (edges.find(std::make_pair(station_to_id[from], station_to_id[to])) == edges.end()) {
                edges.insert(std::make_pair(station_to_id[from], station_to_id[to]));
                of << edges_num << ' ' << i << ' ' << station_to_id[from] << ' ' << station_to_id[to] << ' ' << 0 << ' ' << weight << "\n";
                edges_num++;
            }
            if (edges.find(std::make_pair(station_to_id[to], station_to_id[from])) == edges.end()) {
                edges.insert(std::make_pair(station_to_id[to], station_to_id[from]));
                of << edges_num << ' ' << i << ' ' << station_to_id[to] << ' ' << station_to_id[from] << ' ' << 0 << ' ' << weight << "\n";
                edges_num++;
            }
        }
        fp.close();
        of1 << i << ' ' << lines[i] << ' ' << stations_in_line.size() << "\n";
        for (auto it = stations_in_line.begin(); it != stations_in_line.end(); it++) {
            of1 << *it << ' ';
        }
        of1 << "\n";
    }
    of.close();
    of1.close();

    map< string, pair<int, int> > station_positions;
    fp.open("../xy.txt", std::ios::in);
    if (!fp.is_open()) {
        std::cout << "Error: xy.txt not found" << std::endl;
        return 1;
    }
    while (!fp.eof()) {
        string station;
        int x, y;
        fp >> station >> x >> y;
        station_positions.insert(std::make_pair(station, std::make_pair(x, y)));
    }

    // write stations
    of.open("../data.station", std::ios::out);

    map<int, string> id_to_station;
    for (auto it = station_to_id.begin(); it != station_to_id.end(); it++) {
        id_to_station.insert(std::make_pair(it->second, it->first));
    }
    for (auto it = id_to_station.begin(); it != id_to_station.end(); it++) {
        of << it->first << ' ' << it->second;
        if (station_positions.find(it->second) != station_positions.end()) {
            of << ' ' << station_positions[it->second].first << ' ' << station_positions[it->second].second;
        }
        else {
            of << ' ' << 0 << ' ' << 0;
        }
        of << "\n";
    }
    of.close();

}