#ifndef SURFACECOMPLEXITY_H
#define SURFACECOMPLEXITY_H

#include <ModelFile/ModelFile.h>
#include <Geometry/OrientedPoint.h>

#include <ValidType/ValidType.h>

#include "Cluster.h"

/*
Hierarchical clustering builds (agglomerative), or breaks up (divisive), a hierarchy of clusters.
*/

std::vector<unsigned int> KMeans(const std::vector<OrientedPoint> &Points, const double k);
std::vector<vgl_point_3d<double> > EstimateClusterCenters(const std::vector<OrientedPoint> &Points, const std::vector<unsigned int> &Labels);

class Agglomerative
{
	private:
	///////////// Functions ////////////

	void CreateDistanceMatrix(void);
	bool CombineClosestClusters(void);
	bool CombineSingleLinkage(void);
	std::vector<vgl_point_3d<double> > GetClusterPoints(const unsigned int ClusterLabel) const;
	std::vector<unsigned int> GetClusterPointIndices(const unsigned int ClusterLabel) const;
	std::pair<unsigned int, unsigned int> GetMinPair(const std::vector<std::pair<unsigned int, unsigned int> > &Pairs) const;
	
	std::vector<std::pair<unsigned int, unsigned int> > CreatePairs(const std::vector<unsigned int> &V1, const std::vector<unsigned int> &V2) const;
	
	////////// Members Variables ///////////
	std::vector<unsigned int> PointLabels;
	std::vector<ValidType<vgl_point_3d<double> > > ClusterCenters;
	
	std::vector<OrientedPoint> Points;
	double MaxDist;
	
	public:
	Agglomerative(const std::vector<OrientedPoint> &points, const double maxdist);
	
	vbl_array_2d<ValidType<double> > ClusterDistanceMatrix;
	vbl_array_2d<double> PointDistanceMatrix;
	//vbl_array_2d<ValidType<float> > ClusterDistanceMatrix;
	//vbl_array_2d<float> PointDistanceMatrix;
	
	void OutputDistanceMatrix() const;
	
	void PerformClustering();
	std::vector<unsigned int> getPointLabels() {return PointLabels;}
};

#endif