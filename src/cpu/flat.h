#ifndef SIMBASE_CPU_INDEX_FLAT_H
#define SIMBASE_CPU_INDEX_FLAT_H

#include "../index.h"

using Eigen::VectorXd;

namespace simbase::cpu
{

class IndexFlatIP : public Index
{
public:
	IndexFlatIP(int dimensions);

	std::vector<VectorXd> search(VectorXd query, int k) const override;
};

} // namespace simbase::cpu

#endif