Detecting Broken Frames in Live Video Streams
=============================================

Nowadays applications ingest live video streams which often have a variable quality. The video resolution might vary based on available bandwidth and the video might show compression or streaming artifacts. One type of live video streams, RTSP streams over UDP, often exhibits two pretty distinctive kinds of artifacts:

- A large part of the frame is tinted gray (e.g. Images/broken/frame3.png)
- The bottom part of the frame is smudged (e.g. Images/broken/frame10.png)

This small project aims to detect broken frames with those artifacts so we can skip them during processing.

*** The code currently implemented ONLY shows a way to detect the smudged images! (not the gray ones) ***


## Resources
In the `Images` folder you'll find frames (PNG images) extracted from RTSP/UDP streams. Some of them are broken (in the `Images/broken` folder) and some of them are valid (in the `Images/valid` folder). 


## Conventions used as Coding Standards
* private class attributes name start with a "_"
* local variable names start with an "a"
* method input parameter names start with an "i"
* method output parameter names start with an "o"
