#ifndef SIMBASE_INDEX_H
#define SIMBASE_INDEX_H

#include <Eigen/Dense>
#include <vector>

using Eigen::VectorXd;

namespace simbase
{

// simbase index interface
class Index
{
public:
	Index(int dimensions);
	
	// add an entry to the index
	void Add(VectorXd point);

	// knn search
	virtual std::vector<VectorXd> search(VectorXd query, int k) const = 0;

protected:
	int dimensions;
	int n_total = 0;
	std::vector<VectorXd> points;
};

} // namespace simbase

#endif