Introduction
============

This page explains how to use the Remote Annotation and Multichannel Boundary Observer in 3D (Rambo3D).  
It can be used for any of the data for which we have build the cutout service,
which includes Bock11 and Kasthuri11.
As more datasets become available, we will update here.


Installation
============


At this point, for prebuilt binaries we only provide a win32 executeable
(VolumeViewer.exe). But we have successfully compiled it on mac and linux boxes.  
If you have any trouble, just email ming@cs.jhu.edu.

Before you run the executable, make sure the driver of your video card is 
up to date (the generic one coming with windows does not work).

The general usage of the executable is:

VolumeViewer.exe --img img.data --ano ano.data --dRes xRes yRes zRes

where img.data and ano.data are the volumes downloaded from the cut-out service,
and xRes/yRes/zRes together specify the data resolution.

Notice that the volume here needs to be a flattened hdf5 cube. For convenience
in the package we provide a python script for doing that. To run the script, you
you will need to have Python installed along with NumPy and h5py (whose win7-64
installers are all included in the package as well). 

For now, the easiest way to get through the whole plumbing process is to use 
the provided batch script (demo.bat):

Demo Script
===========

:: Specify here the minimum coordinate of the bounding box

    SET XSTART=5000
    SET YSTART=8000
    SET ZSTART=968

:: Specify here the size (#voxels) of the data

    SET XRES=512
    SET YRES=512
    SET ZRES=64

:: Leave the rest untouched

    SET /A XEND=%XSTART%+%XRES%
    SET /A YEND=%YSTART%+%YRES%
    SET /A ZEND=%ZSTART%+%ZRES%
    SET ANNO=http://openconnecto.me/annotate/kanno/hdf5/1/%XSTART%,%XEND%/%YSTART%,%YEND%/%ZSTART%,%ZEND%/
    SET IMGS=http://openconnecto.me/cutout/kasthuri11/hdf5/1/%XSTART%,%XEND%/%YSTART%,%YEND%/%ZSTART%,%ZEND%/
    hdf5Flatten.py %ANNO% ano.data
    hdf5Flatten.py %IMGS% img.data
    VolumeViewer.exe --dRes %XRES% %YRES% %ZRES% --img img.data --ano ano.data


User Interface
==============

### Mouse


* Right  mouse button: drawing the zoom-in box
* LEFT   mouse button: translating the camera
* MIDDLE mouse button: rotating the camera

* WHEEL: moving camera backward/forward

* SHIFT + WHEEL: advancing the viewing plane (same as SHIFT+UP/DOWN)
* SHIFT + RIGHT: rotating the viewing plane around the pivot
* SFHIT + LEFT:  translating the pivot


### KEYBOARD

* UP  : moving the camera forward
* DOWN: moving the camera backward
* SHIFT+UP  : moving the viewing plane forward
* SHIFT+DOWN: moving the viewing plane backward

* R: resetting the viewing plane

* Q,W: rotation around Y axis
* A,Z: rotation around X axis
* S,X: rotation around Z axis

* 3: setting the viewing plane to X-Y plane 
* SHIFT+3: resetting the camera to look at X-Y plane from top
(Simiarly for 1 and 2)

* O: toggle orthographics/perspective projection
* Esc: exit the viewer


Notes
=====


If there is any problem, let me know at: ming@cs.jhu.edu

--Ming


PS1. The plumbing is just of the time being and we are working on the improvement 
of the setup interface.

PS2. The webpage for this project is http://openconnectome.github.com/Rambo3D/

For COMPILATION ON A MAC
==================

The below procedure works well on my Air running Mac-OS 10.7.4

1. Download and install Xcode if you don't have it yet: 
https://developer.apple.com/xcode/
Note that the latest Xcode seems not to come with GCC anymore (!!!). So you will need to do the following manually:
Go to "Xcode->preference->downloads" and then click to install "Command Line Tools"
After it's done, do "which gcc" to make sure it is there.

2. Download and install Qt SDK 1.1.2 (selecting "Mac 64" option, of course):
http://www.developer.nokia.com/info/sw.nokia.com/id/84801bfe-8517-4287-9829-014c6f572127/Qt_SDK_1_1_2.html
Yes, this is an older version. You could try the latest release instead (http://qt-project.org/downloads) but I haven't tested it out, so no guarantee...

3. Download and install GLEW as following:
    1) download and extract the package from https://sourceforge.net/projects/glew/files/glew/1.9.0/glew-1.9.0.tgz/download
    2) cd into the directory (doesn't matter where you extract btw)
    3) do "make install" (you may need to be a sudoer to do this)

4. Download and compile Rambo3D as following:
    1) download and extract the source code (attached as "Source_2.zip" with this mail)
    2) fire up "VolumeViewer.pro" by double-clicking
    3) click "Done" (you should see that the default selects the "Desktop" configuration)
    4) Compile the code by "Build->Build Project VolumeViewer" (or simply "Command+B")

FOR EXECUTION ON A MAC
==================

1. cd into the directory where the binary was created
(starting for the source code directory, usually it should be at: ../VolumeViewer-build-desktop/VolumeViewer.app/Contents/MacOS/)

2. Download and extract the attached "Supplementary.zip"

3. Copy everything to the binary directory

4. Run "./VolumeViewer --dRes 256 256 128 --img myImg.data --ano myAno.data"

5. Ta-da!!


--Ming

