#include "lsh.h"

namespace simbase::cpu
{
LSHIndex::LSHIndex(int dimensions): 
	// TODO: find better way of deciding on numHyperplanes
	numHyperplanes(dimensions / 10), size(0),
	Index(dimensions), hyperplanes(), 
	hashTables()
{
	// generate random hyperplanes
	for (int i = 0; i < numHyperplanes; i++)
	{
		hyperplanes.push_back(VectorXd::Random(dimensions) - (0.5 * VectorXd::Ones(dimensions)));
	}
}

void LSHIndex::Add(VectorXd point)
{
	// TODO: use something better to store hash values, bitset (?)
	string hash = "";
	// calculate the hash value for each hash function
	for (int i = 0; i < numHyperplanes; i++)
	{
		hash += (hyperplanes[i].dot(point) > 0) ? "1" : "0";
	}

	// if no hash bucket exists for the hash value, create one
	if (hashTables.find(hash) == hashTables.end())
	{
		hashTables[hash] = std::vector<int>();
	}

	// add the point index to the hash bucket
	hashTables[hash].push_back(size++);
	points.push_back(point);
}

std::vector<VectorXd> LSHIndex::search(VectorXd query, int k) const
{
	// TODO

} // namespace simbase
