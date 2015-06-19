/*****************************************************************************
* Copyright (c) xxxxxxxx. All Rights Reserved.
*
*
*  File: main.cpp
*  Date: February 2015
*  Author(s): 	Cedric de Cesare <cedric.decesare.edinburgh@gmail.com>
*
*  Description: Main file. Used to test the broken/valid frames.
*
*
*****************************************************************************/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <cstdio>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <vector>

#include "BrokenFrameFilter.h"

using namespace cv;
using namespace std;
namespace fs = boost::filesystem;

void ProcessFolder(const string& folderName);


//************************************
// Method:    main
// FullName:  main
// Access:    public 
// Returns:   void
// Description: Main method 
//************************************
void main()
{
	// Parse all images from folder
	ProcessFolder("Images/broken");
	//ProcessFolder("Images/valid");


}

//************************************
// Method:    ProcessFolder
// FullName:  ProcessFolder
// Access:    public 
// Returns:   void
// Description: Reads a folder containing several images
// Parameter: const string & folderName : Folder containing the images
//************************************
void ProcessFolder(const string& folderName)
{
	// Initialize folder name and image filename
	fs::path aFolder(folderName);
	std::string aImageFilename("");

	// Create report file
	ofstream aReport;
	aReport.open("Report.txt");
	
	// Check folder exists and is actually a folder
	if (fs::exists(aFolder) && fs::is_directory(aFolder))
	{
		fs::directory_iterator it(aFolder);
		fs::directory_iterator endit;
			
		// Browse the folder
		while (it != endit)
		{
			if (it->path().extension() == ".png")
			{
				
				// Extract filename
				// /!\ The whole filename must be composed of the folder name + image name.
				aImageFilename = folderName + "/" +  boost::lexical_cast<string>(it->path().filename());
				boost::algorithm::erase_all(aImageFilename, "\""); // TODO: remove the quotes ""
						
				// Filter frame
				// Result = True if the image is smudged, False otherwise.
				BrokenFrameFilter aFrameFilter;
				const bool isFrameValid = aFrameFilter.filter(aImageFilename);
					
				// Populate report file 
				cout << "Image : " << aImageFilename << "----Result : " << isFrameValid << endl;
				aReport << "--- Image: " << aImageFilename << "----Result : " << isFrameValid << endl;
					
			}
			++it;
		}
	}
	else
	{
		cout << "Folder does not exist." << endl << endl;
	}
	cvWaitKey(0);
	cvWaitKey(0); // /!\ Add a 2nd cvWaitKey(0) to make the console output stay on screen (otherwise it disappears after completion)

	// Close report file
	aReport.close();

}


