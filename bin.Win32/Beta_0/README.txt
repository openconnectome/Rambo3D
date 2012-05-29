////////////////////////////////////////
// VolumeViewer Beta 0.1 Release Note //
////////////////////////////////////////

Command Format:
VolumeViewer.exe --[param#1] [value#1] --[param#2] [value#2] ...


Parameters:

--aHeader : the header of annotations (the path before sequence#)
--aSuffix : the suffix of annotations (the rest path after sequence#)
--{xMin,yMin,zMin} : the min {x,y,z} coordinate of the bounding box that bounds the annotations.
--{xMax,yMax,zMax} : the max {x,y,z} coordinate of the bounding box that bounds the annotations.
--image : the input image data obtained from the cut-out service.
--{xRes,yRes,zRes} : the {x,y,z} resolution of the image (actual #pixels)


Example:
VolumeViewer.exe --aHeader ".\two-cubes\contour-s" --aSuffix "-4.xml" --bMin 10000 10000 400 --bMax 20000 20000 900  --image foo.dat --dRes 512 512 90

This will:
1. parse annotations exist in from slice #400 to #900, i.e., ".\two-cubes\contour-s17-400.xml" to ".\two-cubes\contour-s17-900.xml",
2. ignore points outside [10000,2000]x[10000,20000], and
3. use the image "foo.dat" that has a resolution of 512 x 512 x 90.

The current implementation only accepts Bobby's annotation format (the only I have). 
However, it is easy to rewrite the "Window::parseAnnotation()" function in Window.cpp if one wants to extend this.

Note that the viewer does not assume any correlation between the resolution of the image and the annotation bounding-box.
(The viewer simply fits the image into a unit cube for later texture look-up. The bounding-box is used to normalize each annotated point's global coordinate to find its texture coordinate.)
This gives us more flexibility feeding in data. For example, one could sample different dimensions using different stride numbers.



==================== KEYBOARD ==========================

UP  : moving the camera forward
DOWN: moving the camera backward

SHIFT+UP  : moving the viewing plane forward
SHIFT+DOWN: moving the viewing plane backward

R: resetting the viewing plane

Q,W: rotation around Y axis
A,Z: rotation around X axis
S,x: rotation around Z axis

3: setting the viewing plane to X-Y plane 
SHIFT+3: resetting the camera to look at X-Y plane from top
(Simiarly for 1 and 2)

O: toggle orthographics/perspective projection
Esc: exit the viewer



==================== MOUSE ===========================

Right  mouse button: drawing the zoom-in box
LEFT   mouse button: translating the camera
MIDDLE mouse button: rotating the camera

WHEEL: moving camera backward/forward

SHIFT + WHEEL: advancing the viewing plane (same as SHIFT+UP/DOWN)
SHIFT + RIGHT: rotating the viewing plane around the pivot
SFHIT + LEFT:  translating the pivot
