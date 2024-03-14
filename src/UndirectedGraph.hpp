#pragma once
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <set>

template<typename Vertex>
class UndirectedGraph
{
public:
    using Edge = std::pair<Vertex, Vertex>; //<fromVertex, toVertex>
    using EdgeList = std::set<Vertex>;

    UndirectedGraph() = default;
    UndirectedGraph(const std::vector<Edge>& edges);

    /* Checks */
    bool vertexExists(const Vertex&) const;
    bool edgeExists(const Vertex& end1, const Vertex& end2) const;
    bool edgeExists(const Edge&) const;
    bool verticesEmpty() const;
    bool edgesEmpty() const;

    /* Getters */
    std::set<Vertex> getVertices() const;
    const std::map<Vertex, EdgeList>& getEdgeLists() const;
    const EdgeList& getEdgeList(const Vertex&) const;

    /* Adders */
    void addVertex(const Vertex&);
    void addEdge(const Vertex& end1, const Vertex& end2);
    void addEdge(const Edge&);

    /* Removers */
    void removeVertex(const Vertex&);
    void removeEdge(const Vertex& end1, const Vertex& end2);
    void removeEdge(const Edge&);

private:
    std::map<Vertex, EdgeList> m_edges;
};

template<typename Vertex>
UndirectedGraph<Vertex>::UndirectedGraph(const std::vector<Edge>& edges)
{
    for(const Edge& edge : edges)
        addEdge(edge);
}

template<typename Vertex>
bool UndirectedGraph<Vertex>::vertexExists(const Vertex& vertex) const
{
    return m_edges.count(vertex) != 0;
}

template<typename Vertex>
bool UndirectedGraph<Vertex>::edgeExists(const Vertex& end1, const Vertex& end2) const
{
    /* Check if the vertices exist */
    if(!vertexExists(end1) || !vertexExists(end2))
        return false;

    /* Get the edges of both end vertices */
    const EdgeList& edgeList1 = getEdgeList(end1);
    const EdgeList& edgeList2 = getEdgeList(end2);

    //See if the vertices exist in at least one of the edge lists
    return edgeList1.count(end2) != 0 || edgeList2.count(end1) != 0;
}

template<typename Vertex>
bool UndirectedGraph<Vertex>::edgeExists(const Edge& edge) const
{
    /* Extract vertices and weight */
    const Vertex& end1 = std::get<0>(edge);
    const Vertex& end2 = std::get<1>(edge);

    return edgeExists(end1, end2);
}

template<typename Vertex>
bool UndirectedGraph<Vertex>::verticesEmpty() const
{
    return m_edges.empty();
}

template<typename Vertex>
bool UndirectedGraph<Vertex>::edgesEmpty() const
{
    for(const std::pair<Vertex, EdgeList>& pair : m_edges)
    {
        const EdgeList& edgeList = pair.second;

        /* If at least one vertex's edges isn't empty, then there are edges in the graph */
        if(!edgeList.empty())
            return false;
    }

    return true;
}

template<typename Vertex>
std::set<Vertex> UndirectedGraph<Vertex>::getVertices() const
{
    std::set<Vertex> vertices;

    for(const std::pair<Vertex, EdgeList>& pair : m_edges)
        vertices.insert(pair.first);

    return vertices;
}

template<typename Vertex>
const typename UndirectedGraph<Vertex>::EdgeList&                //return type
UndirectedGraph<Vertex>::getEdgeList(const Vertex& vertex) const //function name and params
{
    static EdgeList error;
    
    /* Return the edge list if vertex exists; otherwise, return an empty one */
    auto it = m_edges.find(vertex);
    return it != m_edges.cend() ? it->second : error;
}

template<typename Vertex>
const std::map<Vertex, typename UndirectedGraph<Vertex>::EdgeList>& //return type
UndirectedGraph<Vertex>::getEdgeLists() const                       //function name and params
{
    return m_edges;
}

template<typename Vertex>
void UndirectedGraph<Vertex>::addVertex(const Vertex& vertex)
{
    if(!vertexExists(vertex))
        m_edges[vertex];
}

template<typename Vertex>
void UndirectedGraph<Vertex>::addEdge(const Vertex& end1, const Vertex& end2)
{
    /* Make sure vertices exist */
    addVertex(end1);
    addVertex(end2);

    EdgeList& edgeList1 = m_edges[end1];
    edgeList1.insert(end2);

    EdgeList& edgeList2 = m_edges[end2];
    edgeList2.insert(end1);
}

template<typename Vertex>
void UndirectedGraph<Vertex>::addEdge(const Edge& edge)
{
    const Vertex& end1 = std::get<0>(edge);
    const Vertex& end2 = std::get<1>(edge);

    addEdge(end1, end2);
}

template<typename Vertex>
void UndirectedGraph<Vertex>::removeVertex(const Vertex& vertex)
{
    /* Remove each edge of the vertex */
    for(const Edge& edge : getEdgeList(vertex))
        removeEdge(Edge(vertex, edge.second));

    //Remove entry in edges
    m_edges.erase(vertex);
}

template<typename Vertex>
void UndirectedGraph<Vertex>::removeEdge(const Vertex& end1, const Vertex& end2)
{
    EdgeList& edgeList1 = getEdgeList(end1);
    std::remove(edgeList1.begin(), edgeList1.end(), end2);

    EdgeList& edgeList2 = getEdgeList(end2);
    std::remove(edgeList2.begin(), edgeList2.end(), end1);
}

template<typename Vertex>
void UndirectedGraph<Vertex>::removeEdge(const Edge& edge)
{
    const Vertex& end1 = std::get<0>(edge);
    const Vertex& end2 = std::get<1>(edge);

    removeEdge(end1, end2);
}