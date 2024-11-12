#include "../index.h"
#include "../distances.h"
#include <string>
#include <set>
#include <unordered_map>
#include <bitset>
#include <queue>

using Eigen::VectorXd;
using std::string;
using std::set;

namespace simbase::cpu
{

// LSH Implementation using random projection
class LSHIndex: public Index 
{
private:
    // creates 2^numHyperplane buckets
    int numHyperplanes;
    int size;

    std::unordered_map<string, std::vector<int>> hashTables;
    std::vector<VectorXd> hyperplanes;
    string hash(VectorXd point) const;
    
public:
    LSHIndex(int dimensions);
    std::vector<VectorXd> search(VectorXd query, int k) const override;
    void Add(VectorXd point);
    void Add(std::vector<VectorXd> pts);

private:

};

} // namespace simbase::cpu
