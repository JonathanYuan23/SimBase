#ifndef SIMBASE_CPU_DISTANCES_H
#define SIMBASE_CPU_DISTANCES_H

#include <Eigen/Dense>
#include <cmath>

using Eigen::VectorXd;

namespace simbase::cpu
{

class Distances 
{
public: 
    Distances();

    double euclidean(VectorXd a, VectorXd b) const;
    double manhattan(VectorXd a, VectorXd b) const;
    double cosine(VectorXd a, VectorXd b) const;
    double minkowski(VectorXd a, VectorXd b, double p) const;
    double hamming(VectorXd a, VectorXd b) const;
    double hamming(std::string a, std::string b) const;

};

} // namaespace simbase::cpu
#endif
