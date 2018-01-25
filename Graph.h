#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>



namespace gdwg {

	template <typename N, typename E> 
	class Graph {
		class Edge;
	private:

		class Node {

		public:
			Node(const N& val): data(val) {};
			const N& get_data() const{ return data; };
			//getter and setter function of the memebers
			std::vector<std::shared_ptr<Edge>>& getOutEdges() { return outEdges; };
			void setData(const N& newData) { data = newData; };
			//manual comparison function for sorting nodes 
			bool operator<(const Node& n) const{ 
				if (n.outEdges.size() == outEdges.size()) return data < n.data;
				return outEdges.size() < n.outEdges.size(); 
			}; 
		private:
			N data;
			std::vector<std::shared_ptr<Edge>> outEdges;
		};

		class Edge {

		public:
			Edge(const E val, std::weak_ptr<Node> f, std::weak_ptr<Node> t): weight{val}, from{f}, to{t} {};
			//getter and setter of members
			std::weak_ptr<Node> getFrom() { return from; };
			std::weak_ptr<Node> getTo() { return to; };
			const E& get_weight() { return weight; };
			void set_toNode(std::shared_ptr<Node> n) { to = n; };
			//manual comparison functions for sorting edges
			bool operator<(const Edge& e) const{ 
				if (weight == e.weight) {
					auto to_node = to.lock();
					auto e_to_node = e.to.lock();
					return to_node->get_data() < e_to_node->get_data();
				}
				return weight < e.weight;
			};

		private:
		    E weight;
			std::weak_ptr<Node> from;
			std::weak_ptr<Node> to;

		};
		

		std::vector<std::shared_ptr<Node>> nodes;
		mutable typename std::vector<std::shared_ptr<Node>>::const_iterator niterator;
	

	public:

		//constructor
		Graph() {};
		Graph(const Graph& g);
		Graph(Graph&& g): nodes{std::move(g.nodes)} {
			g.clear();
		};

		//~destructor
		~Graph() {
			for(auto node: nodes) {
				for (auto e: node->getOutEdges()) e.reset();
				node.reset();
			}
		}

		//assignment operation
		Graph& operator=(const Graph& g);
		Graph& operator=(Graph&& g);

		//operation of the graph
		bool addNode(const N& val);		
		bool addEdge(const N& src, const N& dst, const E& w);
		void printNodes() const;
		bool isNode(const N& val) const;
		void printEdges(const N& val) const; 
		bool isConnected(const N& src, const N& dst) const;
		bool replace(const N& oldData, const N& newData);
		void mergeReplace(const N& oldData, const N& newData);
		void deleteNode(const N&) noexcept;
		void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
		std::vector<std::shared_ptr<Node>> getNodes() const{ return nodes; };		
		
		//methods for traversing the graph
		void begin() const{ niterator = nodes.begin(); };
		bool end() const{ return niterator == nodes.end(); };
		void next() const{ ++niterator; };
		const N& value() const{ return (*niterator)->get_data(); };
		void clear() noexcept {
			for (auto n: nodes) {
				for (auto e: n->getOutEdges()) e.reset();
				n.reset();
			}
			nodes.clear();
		};
	};
	#include "Graph.tem"
};

#endif