/*****************************************************************************
* Copyright (c) xxxxxxxxxx. All Rights Reserved.
*
*
*  File: FrameFilter.h
*  Date: February 2015
*  Author(s): 	Cedric de Cesare <cedric.decesare.edinburgh@gmail.com>
*
*  Descritpion: Declaration of FrameFilter class.
*
*
*****************************************************************************/

#ifndef FRAMEFILTER_H_
#define FRAMEFILTER_H_

#include <string>

class FrameFilter
{
public:
	virtual ~FrameFilter();

	/**
	* @return true if the frame at the given path (a JPEG image) passes this filter test,
	*    false otherwise
	*/
	virtual bool filter(const std::string& framePath) = 0;
};

#endif /* FRAMEFILTER_H_ */