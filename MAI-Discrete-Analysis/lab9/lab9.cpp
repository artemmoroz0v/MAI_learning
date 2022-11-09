#include <iostream>
#include <vector>
#include <queue>
#include <limits>
bool BreadthFirstSearch (std:: vector<std:: vector<long long int>>& graph, long long int source, long long int sink, std:: vector<long long int>& parent) {
    std:: vector<bool> visited(graph.size(), false); //в самом начале все вершины не посещены
    std:: queue<long long int> q;
    visited[source] = true; //исток мы посетили
    parent[source] = -1; //у стока нет родителя
    q.push(source);
    while (!q.empty()) {
        long long int u = q.front();
        q.pop();
        for (long long int v = 0; v < graph.size(); ++ v) {
            if (visited[v] == false && graph[u][v]) {
                parent[v] = u;
                q.push(v);
                visited[v] = true;
                if (v == sink) {
                    return true; //возвращаем true, так как есть путь до нашего стока
                }
            }
        }
    }
    return false; //иначе возвращаем false, если пути у нас нет
}
long long int FordFulkersonAlgorithm (std:: vector<std:: vector<long long int>>& graph, long long int source, long long int sink) { //source - исток, sink - сток
    std:: vector<long long int> parent(graph.size());
    long long int maximum_flow = 0; //изначально величина потока ноль
    std:: vector<std:: vector<long long int>> result = graph; //изначально наша остаточная сеть совпадает со всем графом
    long long int u, v;
    while (BreadthFirstSearch(result, source, sink, parent)) { //пока у нас есть какой-то путь из истока в сток (потому что пути постепенно сокращаются из-за обратных сетей)
        long long int path_flow = std:: numeric_limits<long long int>::max();
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            path_flow = std:: min(path_flow, result[u][v]); //ищем минимальную остаточную способность (ищем то значение, которое можно пустить по всем ребрам от истока до стока)
        }
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            result[u][v] -= path_flow;
            result[v][u] += path_flow;
        }
        maximum_flow += path_flow;
    }
    return maximum_flow;
}
int main() {
    long long int n, m;
    std:: cin >> n >> m;
    std:: vector<std:: vector<long long int>> graph(n, std:: vector<long long int>(n));
    for (long long int i = 0; i < m; ++i) {
        long long int from, to, capacity;
        std:: cin >> from >> to >> capacity;
        graph[from - 1][to - 1] = capacity;
    }
    std:: cout << FordFulkersonAlgorithm(graph, 0, n - 1) << "\n";
    return 0;
}
