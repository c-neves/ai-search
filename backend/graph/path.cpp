#include "graph.hpp"

graph::path::path(graph::node _initial_node)
{
	this->_nodes.push_back(_initial_node);
}

graph::path::path(const graph::path& _p)
{
	for (graph::node x : _p.nodes())
		this->_nodes.push_back(x);
}

const std::vector<graph::node>& graph::path::nodes() const
{
	return this->_nodes;
}

graph::node graph::path::last_node() const
{
	return this->_nodes.back();
}

void graph::path::add_node(graph::node& _n)
{
	this->_nodes.push_back(_n);
}

bool operator<(const graph::path& _r, const graph::path& _l)
{
	graph::node l = _l.last_node();
	graph::node r = _r.last_node();
	double fl = g(l) + h(l);
	double fr = g(r) + h(r);
	return fl < fr;
}

std::ostream& operator<<(std::ostream& _os, const graph::path& _p)
{
	const std::vector<graph::node>& path = _p.nodes();
	_os << "[";
	uint path_length = path.size();
	for (uint i = 0u; i < path_length; i++)
		_os << path[i] << (i < path_length - 1u ? ", " : "");
	return _os << "]";
}