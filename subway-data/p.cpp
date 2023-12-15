#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

#define INPUT_LINE_FILE "line.txt"
#define INPUT_POSITION_FILE "position.txt"
#define INPUT_SIGHT_FILE "sight.txt"

#define OUTPUT_STATION_FILE "../net-data/data.station"
#define OUTPUT_EDGE_FILE "../net-data/data.edge"
#define OUTPUT_LINE_FILE "../net-data/data.line"
#define OUTPUT_SIGHT_FILE "../net-data/data.sight"

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
    fp.open(INPUT_LINE_FILE, std::ios::in);
    if (!fp.is_open()) {
        std::cout << "Error: " << INPUT_LINE_FILE << " not found" << std::endl;
        return 1;
    }

    string lines[50];
    string color[50];
    int num_lines = 0;
    while (!fp.eof()) {
        fp >> lines[num_lines] >> color[num_lines];
        num_lines++;
    }
    fp.close();

    set< pair<int, int> > edges;

    // read edges and write edges and write lines
    of.open(OUTPUT_EDGE_FILE, std::ios::out);
    of1.open(OUTPUT_LINE_FILE, std::ios::out);

    map<string, int> station_to_id;
    for (int i = 0; i < num_lines; i++) {
        fp.open(lines[i] + ".txt", std::ios::in);
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
        of1 << i << ' ' << lines[i] << ' ' << stations_in_line.size() << ' ' << color[i] << "\n";
        for (auto it = stations_in_line.begin(); it != stations_in_line.end(); it++) {
            of1 << *it << ' ';
        }
        of1 << "\n";
    }
    of.close();
    of1.close();

    map< string, pair<int, int> > station_positions;
    fp.open(INPUT_POSITION_FILE, std::ios::in);
    if (!fp.is_open()) {
        std::cout << "Error: " << INPUT_POSITION_FILE << "not found" << std::endl;
        return 1;
    }
    while (!fp.eof()) {
        string station;
        int x, y;
        fp >> station >> x >> y;
        station_positions.insert(std::make_pair(station, std::make_pair(x, y)));
    }
    fp.close();

    // write stations
    of.open(OUTPUT_STATION_FILE, std::ios::out);
    
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

    // write sights
    of.open(OUTPUT_SIGHT_FILE, std::ios::out);
    fp.open(INPUT_SIGHT_FILE, std::ios::in);
    if (!fp.is_open()) {
        std::cout << "Error: " << INPUT_SIGHT_FILE << "not found" << std::endl;
        return 1;
    }
    int sight_id = 0;
    while (!fp.eof()) {
        string sight_name, sight_description, sight_station_name;
        double sight_price;
        fp >> sight_name >> sight_description >> sight_price >> sight_station_name;
        if (station_to_id.find(sight_station_name) == station_to_id.end()) {
            std::cout << "Error: " << sight_name << " not found" << endl;
            return 1;
        }
        of << sight_id << ' ' << sight_name << ' ' << sight_description << ' ' << sight_price << ' ' << station_to_id[sight_station_name] << "\n";
        sight_id++;
    }
    of.close();
    fp.close();
}