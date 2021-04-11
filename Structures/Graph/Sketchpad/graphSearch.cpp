#include <iostream>
#include <list>
#include <unordered_map>
#include <set>
#include <string>
#include <queue>
#include <functional>
#include <vector>
#include <climits>

class Graph {
private:

    struct Edge {

        unsigned int weight;
        std::string  to;
        std::string  from;

        Edge() {
            weight = 0;
            to = "";
            from = "";
        }

        Edge(std::string to, std::string from, unsigned int weight) {

            this->from = from;
            this->to = to;
            this->weight = weight;
        }
    };

    struct Node {

        std::list<Edge> neighbors;

        Node() {


        }
    };

    struct Decoration {

        unsigned int cost;
        bool         isVisited; 
        std::string  predecessor;
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

    std::unordered_map<std::string, Node>       graph;
    std::unordered_map<std::string, Decoration> decorations;
public:

    void addNode(std::string name) {

        graph.insert({name, Node()});

        Node& node = graph.at(name);

        decorations.insert({name, Decoration(&node, 0)});
    }

    void addEdge(std::string a, std::string b, int weight) {

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

    void dijkstra(std::list<std::string>& path, std::string start, std::string end) {

        for (auto itr = decorations.begin(); itr != decorations.end(); itr++) {

            itr->second.reset();
            itr->second.cost = INT_MAX;
        }

        decorations[start].cost = 0;

        auto comparator = [this](const std::string& aId, const std::string& bId) -> bool {

            auto& a = this->decorations.at(aId);
            auto& b = this->decorations.at(bId);
            
            return a.cost > b.cost;
        };

        std::priority_queue<std::string, std::vector<std::string>, decltype(comparator)> pq(comparator);        

        pq.push(start);

        while(!pq.empty()) {

            std::string nodeId = pq.top();

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

        std::string pathNode = decorations[end].predecessor;

        path.push_back(end);

        while(pathNode != "") {
            
            path.push_back(pathNode);
            pathNode = decorations[pathNode].predecessor;
        }

        path.reverse();
    }
};

void printPath(std::list<std::string>& path) {

    if(path.size() > 0) {

        auto itr = path.begin();
        int  i   = 0;

        for(i; i < path.size() - 1; i++, itr++) {

            std::cout << *itr << " to "; 
        } 

        std::cout << *itr << std::endl; 
    }
}

int main(int argc, char** argv) {

    Graph graph;

    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
    graph.addNode("E");
    
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

    printPath(path);

}