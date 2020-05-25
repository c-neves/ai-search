#include "maze.hpp"

const char maze::PATHWAY = '*';
const char maze::OBSTACLE = '-';
const char maze::SOURCE = '#';
const char maze::TARGET = '$';

maze::maze(std::istream& _is)
{
	unsigned int& m = this->_m;
	unsigned int& n = this->_n;
	char**& matrix = this->_matrix;

	_is >> m;
	_is >> n;

	matrix = new char*[m];
	for (unsigned int i = 0u; i < m; i++)
	{
		matrix[i] = new char[n];
		for (unsigned int j = 0u; j < n; j++)
		{
			_is >> matrix[i][j];
			if (matrix[i][j] == maze::SOURCE)
				this->_source = {i, j};
			else if (matrix[i][j] == maze::TARGET)
				this->_target = {i, j};
		}
	}
}

maze::~maze()
{
	for (unsigned int i = 0u; i < this->_m; i++)
		delete [] this->_matrix[i];
	delete [] this->_matrix;
}

unsigned int maze::m() const
{
	return this->_m;
}

unsigned int maze::n() const
{
	return this->_n;
}

char** maze::matrix() const
{
	return this->_matrix;
}

maze::position maze::source() const
{
	return this->_source;
}

maze::position maze::target() const
{
	return this->_target;
}

std::ostream& operator<<(std::ostream& _os, const maze& _m)
{
	const unsigned int m = _m.m(), n = _m.n();
	char** matrix = _m.matrix();

	for (unsigned int i = 0u; i < m; i++)
	{
		for (unsigned int j = 0u; j < n; j++)
			_os << matrix[i][j];
		if (i < m - 1u)
			_os << "\n";
	}
	return _os;
}
