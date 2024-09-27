#include "index.h"

namespace simbase
{

Index::Index(int dimensions)
	: dimensions(dimensions)
{}

void Index::Add(VectorXd point)
{
	assert(dimensions == point.size());

	points.push_back(point);
	++n_total;
}

} // namespace simbase
