#include "distances.h"

namespace simbase::cpu
{

Distances::Distances() {}

double Distances::euclidean(VectorXd a, VectorXd b) const
{
    assert(a.size() == b.size());
    double sum = 0;
    for(int i = 0; i < a.size(); ++i)
    {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

double Distances::manhattan(VectorXd a, VectorXd b) const
{
    assert(a.size() == b.size());
    double sum = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        sum += abs(a[i] - b[i]);
    }
}

double Distances::cosine(VectorXd a, VectorXd b) const
{
    assert(a.size() == b.size());
    double dot = a.dot(b);
    double norm_a = a.norm();
    double norm_b = b.norm();
    return 1 - (dot / (norm_a * norm_b));
}

double Distances::minkowski(VectorXd a, VectorXd b, double p) const
{
    assert(a.size() == b.size());
    double sum = 0;
    for(int i = 0; i < a.size(); ++i)
    {
        sum += pow(abs(a[i] - b[i]), p);
    }
    return pow(sum, 1/p);
}

double Distances::hamming(VectorXd a, VectorXd b) const 
{
    assert(a.size() == b.size());
    double sum = 0;
    for(int i = 0; i < a.size(); ++i)
    {
        sum += (a[i] != b[i]);
    }
    return sum;
}

} // namespace simbase::cpu
