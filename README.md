Introduction
============

This page explains how to use our VolumeViewer.  
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

PS2. The webpage for this project is http://openconnectome.github.com/VolumeViewer/

