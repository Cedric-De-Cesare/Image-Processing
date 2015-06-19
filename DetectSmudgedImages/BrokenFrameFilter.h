/*****************************************************************************
* Copyright (c) xxxxxxxxx. All Rights Reserved.
*
*
*  File: BrokenFrameFilter.h
*  Date: February 2015
*  Author(s): 	Cedric de Cesare <cedric.decesare.edinburgh@gmail.com>
*
*  Descritpion: Declaration of BrokenFrameFilter class. Handles filter that rejects broken frames.
*
*
*****************************************************************************/

#ifndef BROKENFRAMEFILTER_H_
#define BROKENFRAMEFILTER_H_

#include <string>
#include <opencv\cv.h>
#include "FrameFilter.h"

/**
* An frame filter that rejects broken frames.
*/

class BrokenFrameFilter : public FrameFilter
{
public:
	BrokenFrameFilter();
	virtual ~BrokenFrameFilter();

	// Filter an  image given by path
	bool filter(const std::string& iFramePath);

private:

	// Compute the Sum Squared Difference between 2 strips
	double computeSSD(const std::vector<int>& iBlock1, const std::vector<int>& iBlock2);

	// Threshold on the SSD measure to determine if the filter should reject or not
	double _SSDThresh; 
	// Strip height set in percentage of the input height. Here we consider strips with heigh = 10% of test image height
	double _StripHeightCoeff; 
};

#endif /* BROKENFRAMEFILTER_H_ */