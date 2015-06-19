/*****************************************************************************
* Copyright (c) xxxxxxxxx. All Rights Reserved.
*
*
*  File: BrokenFrameFilter.cpp
*  Date: February 2015
*  Author(s): 	Cedric de Cesare <cedric.decesare.edinburgh@gmail.com>
*
*  Descritpion: File implementing the BrokenFrameFiler class. Handles filter that rejects broken frames.
*
*
*****************************************************************************/
//#include <boost/filesystem.hpp>
#include "BrokenFrameFilter.h"

#include <string>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <vector>
#include <iostream>

using namespace cv;


//************************************
// Method:    BrokenFrameFilter
// Access:    public 
// Returns:   
// Description: default constructor
//************************************
BrokenFrameFilter::BrokenFrameFilter() :_SSDThresh(52), _StripHeightCoeff(0.1)
{
}


//************************************
// Method:    ~BrokenFrameFilter
// Access:    public 
// Returns:   
// Description: destructor
//************************************
BrokenFrameFilter::~BrokenFrameFilter()
{
}


//************************************
// Method:    computeSSD
// Access:    private
// Returns:   float : Sum Squared Difference measure
// Parameter: const cv::Mat& iBlock1 : 1st strip block 
// Parameter: const cv::Mat& iBlock2 : 2nd strip block 
// Description: compute the Sum Squared Difference measure between 2 strip blocks
//************************************
double BrokenFrameFilter::computeSSD(const std::vector<int>& iV1, const std::vector<int>& iV2)
{
	double aSSD = 0;
	for (int ii = 0; ii < iV1.size(); ++ii)
	{
		aSSD += pow(iV1[ii] - iV2[ii], 2);	// SSD
	}
	return aSSD / (double)(iV1.size());
}

//************************************
// Method:    filter
// Access:    public
// Returns:   bool: true is frame is estimated as valid, false otherwise
// Parameter: const std::string& iFramePath : file pathk 
// Description: filter broken frames taht re smudged
//************************************
bool BrokenFrameFilter::filter(const std::string& iFramePath)
{
	// TODO : Improvements: check that the image file exists. 
	/*if (!boost::filesystem::exists(iFramePath))
	{
		return false;
	}*/
	
	/*---------------------------------------------------------------
	*	Aim: Here we detect broken frames that are smudged.
	*	Strategy: To detect smudged regions we divide the test image into 
	*			horizontal strips (with height =10% of test image height),
	*			and check the similarity between consecutive strips.
	*			1) For each iteration: We consider 2 consecutive strips
	*			2) We then measure the similarity between the 2 strips (using the SSD)
	*			3) If the SSD is < SSD threshold it means the strips are similar.
	*				In that case the filter rejects the frame: return true.
	*--------------------------------------------------------------*/
	// Read test image
	const Mat& aTestImage = imread(iFramePath, CV_LOAD_IMAGE_GRAYSCALE);

	//const float aStripHeightCoeff = 0.1; // strip height set in percentage of the input height e.g. 10%
	const int aStripHeight = (int)(_StripHeightCoeff * aTestImage.rows);
	const int aStep = aStripHeight;

	const int aNbRow = aTestImage.rows; // Number of rows of test image
	const int aNbCol = aTestImage.cols; // Number of columns of test image

	// Initialise 1st strip into a vector
	std::vector<int> aStripVec1 = Mat_<int>(aTestImage(cv::Range(0, aStripHeight), cv::Range(0, aNbCol)).reshape(1, 1));
	std::vector<int> aStripVec2;

	for (int ii = aStep; ii < aNbRow - 2 * aStripHeight; ii += aStep)
	{
		// Extract 2nd consecutive strip into a vector
		aStripVec2 = Mat_<int>(aTestImage(cv::Range(ii + aStripHeight, ii + 2 * aStripHeight), cv::Range(0, aNbCol)).reshape(1, 1));

		// Compute the SSD measure between the 2 strips
		// If SSD score < threshold => reject
		if (computeSSD(aStripVec1, aStripVec2) < _SSDThresh)
		{
			return false;
		}
		
		// Prepare strip1 for the next iteration
		aStripVec1 = aStripVec2;
	}

	return true;
}

