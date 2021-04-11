#include <iostream>
#include <list>
#include <unordered_map>
#include <set>
#include <string>
#include <queue>
#include <functional>
#include <vector>
#include <climits>

template<typename T_KEY, typename T_NODE_DATA>
class Graph {
private:

    struct Edge {

        unsigned int weight;
        T_KEY  to;
        T_KEY  from;

        Edge() {
            weight = 0;
            to = "";
            from = "";
        }

        Edge(T_KEY to, T_KEY from, unsigned int weight) {

            this->from = from;
            this->to = to;
            this->weight = weight;
        }
    };

    struct Node {

        T_NODE_DATA     data;
        std::list<Edge> neighbors;

        Node() {


        }
    };

    struct Decoration {

        unsigned int cost;
        bool         isVisited; 
        T_KEY        predecessor;
        Node*        node;

        Decoration() {
            isVisited = false;
            node      = nullptr;
            predecessor = "";
            cost = 0;
        }

        Decoration(Node* node, unsigned int cost) {

            this->cost = cost;
            this->node = node;
            isVisited = false;
            predecessor = "";
        }

        void reset() {
            
            cost = 0;
            isVisited = false;
            predecessor = "";
        }

    };

    std::unordered_map<T_KEY, Node>       graph;
    std::unordered_map<T_KEY, Decoration> decorations;
public:

    void addNode(T_KEY name, T_NODE_DATA data) {

        graph.insert({name, Node()});

        Node& node = graph.at(name);
        node.data = data;

        decorations.insert({name, Decoration(&node, 0)});
    }

    void addEdge(T_KEY a, T_KEY b, int weight) {

        if(graph.find(a) == graph.end()) {

            std::cout << "Graph: addEdge: Unknown node " << a << std::endl;

            return;
        }

        if(graph.find(b) == graph.end()) {

            std::cout << "Graph: addEdge: Unknown node " << b << std::endl;

            return;
        }

        Node& node = graph.at(a);
        node.neighbors.emplace_back(b, a, weight);
    }

    void dijkstra(std::list<T_KEY>& path, T_KEY start, T_KEY end) {

        for (auto itr = decorations.begin(); itr != decorations.end(); itr++) {

            itr->second.reset();
            itr->second.cost = INT_MAX;
        }

        decorations[start].cost = 0;

        auto comparator = [this](const T_KEY& aId, const T_KEY& bId) -> bool {

            auto& a = this->decorations.at(aId);
            auto& b = this->decorations.at(bId);
            
            return a.cost > b.cost;
        };

        std::priority_queue<T_KEY, std::vector<T_KEY>, decltype(comparator)> pq(comparator);        

        pq.push(start);

        while(!pq.empty()) {

            T_KEY nodeId = pq.top();

            pq.pop();

            Decoration& dec    = decorations.at(nodeId);
            dec.isVisited      = true;
            
            auto& neighbors = dec.node->neighbors;

            for(auto itr = neighbors.begin(); itr != neighbors.end(); itr++) {

                Edge& e = *itr;
                
                Decoration& nDec = decorations.at(e.to);

                if(!nDec.isVisited) {

                    int newCost = e.weight + dec.cost;

                    if(nDec.cost > newCost) {

                        nDec.cost        = newCost;
                        nDec.predecessor = nodeId; 

                        pq.push(e.to);
                    }
                }
            }
        }

        T_KEY pathNode = decorations[end].predecessor;

        path.push_back(end);

        while(pathNode != "") {
            
            path.push_back(pathNode);
            pathNode = decorations[pathNode].predecessor;
        }

        path.reverse();
    }

    bool getNodeData(T_KEY nodeId, T_NODE_DATA& data) {

        if(graph.find(nodeId) == graph.end()) {

            return false;
        }

        data = graph.at(nodeId).data;

        return true;
    }

    static void printPath(std::list<T_KEY>& path) {

        if(path.size() > 0) {

            auto itr = path.begin();
            int  i   = 0;

            std::cout << "Shortest path: "; 

            for(i; i < path.size() - 1; i++, itr++) {

                std::cout << *itr << " to "; 
            } 

            std::cout << *itr << std::endl; 
        }
    }
};

using SGraph = Graph<std::string, int>;

int main(int argc, char** argv) {

    SGraph graph;

    graph.addNode("A", 111);
    graph.addNode("B", 222);
    graph.addNode("C", 333);
    graph.addNode("D", 444);
    graph.addNode("E", 555);
    
    graph.addEdge("A", "B", 3);
    graph.addEdge("B", "A", 3);

    graph.addEdge("B", "D", 1);
    graph.addEdge("D", "B", 1);

    graph.addEdge("D", "E", 1);
    graph.addEdge("E", "D", 1);

    graph.addEdge("A", "C", 4);
    graph.addEdge("C", "A", 4);

    graph.addEdge("C", "E", 22);
    graph.addEdge("E", "C", 22);
    
    std::list<std::string> path;

    graph.dijkstra(path, "C", "D");

    SGraph::printPath(path);
}