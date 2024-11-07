#include "../index.h"
#include <string>
#include <set>
#include <unordered_map>
#include <bitset>

using Eigen::VectorXd;
using std::string;
using std::set;

namespace simbase::cpu
{

// LSH Implementation using random projection
class LSHIndex: public Index 
{
private:
    // creates numHyperplane^2 buckets
    int numHyperplanes;
    int size;

    std::unordered_map<string, std::vector<int>> hashTables;
    std::vector<VectorXd> hyperplanes;
    
public:
    LSHIndex(int dimensions);
    std::vector<VectorXd> search(VectorXd query, int k) const override;
    void Add(VectorXd point);
    void Add(std::vector<VectorXd> pts);

private:

};

} // namespace simbase::cpu
