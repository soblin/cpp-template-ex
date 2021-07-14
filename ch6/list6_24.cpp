#include <cassert>
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>

using namespace boost;

struct City {
  std::string name;
  int population;
};

struct Highway {
  std::string name;
  double distance;
};

typedef boost::adjacency_list<vecS,
                              vecS,
                              bidirectionalS,
                              City,   // node property
                              Highway // edge property
                              >
    Map;

int main() {
  Map m;

  // add two nodes
  Map::vertex_descriptor n1 = add_vertex(m);
  Map::vertex_descriptor n2 = add_vertex(m);

  m[n1].name = "Tokyo";
  m[n1].population = 13221169;

  m[n2].name = "Nagoya";
  m[n2].population = 2267048;

  // add edge
  bool inserted = false;
  Map::edge_descriptor e;
  tie(e, inserted) = add_edge(n1, n2, m);

  assert(inserted);
  m[e].name = "Tomei Express";
  m[e].distance = 325.5;

  // find the shortest path from Tokyo(n1) to the others
  std::vector<Map::vertex_descriptor> parents(num_vertices(m));
  std::vector<double> distance(num_vertices(m));
  dijkstra_shortest_paths(m,
                          n1,
                          weight_map(get(&Highway::distance, m))
                              .predecessor_map(&parents[0])
                              .distance_map(&distance[0]));

  // the shortest path to Nagoya(n2)
  double result = distance[boost::get(boost::vertex_index, m, n2)];
  std::cout << "Tokyo-Nagoya : " << result << "km" << std::endl;
}
