#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>

using namespace std;

void dijkstra(map<char, map<char, int>> &graph, char source, char dest) {
    map<char, int> dist;
    map<char, char> prev;
    vector<char> unvisited;

    // setup dist and prev
    for (const auto &pair : graph) {
        char vertex = pair.first;
        dist[vertex] = numeric_limits<int>::max(); // current closest is infin
        prev[vertex] = ' ';
        unvisited.push_back(vertex);
    }

    // distance from source to source is 0
    dist[source] = 0;

    for (int i = 0; i < unvisited.size(); i++) {
        char current = ' ';
        int min_distance = numeric_limits<int>::max();

        for (int j = 0; j < unvisited.size(); j++) {
            char vertex = unvisited[j];
            if (dist[vertex] < min_distance) {
                current = vertex;
                min_distance = dist[vertex];
            }
        }

        if (current == ' ' || current == dest) {
            break;
        }

        unvisited.erase(unvisited.begin() + i);

        for (const auto &nexto : graph[current]) {
            char n_vert = nexto.first;
            int weight = nexto.second;
            int alt_dist = dist[current] + weight;

            // if shorter path update
            if (alt_dist < dist[n_vert]) {
                dist[n_vert] = alt_dist;
                prev[n_vert] = current;
            }
        }
    }

    cout << "Shortest distance is " << dist[dest] << endl;
}

int main() {
    map<char, map<char, int>> grp;
    grp['A'] = {{'B', 1}, {'C', 4}};
    grp['B'] = {{'A', 1}, {'C', 25}};
    grp['C'] = {{'B', 25}, {'A', 4}};
    char sou = 'A';
    char destination = 'C';
    dijkstra(grp, sou, destination);
    return 0;
}