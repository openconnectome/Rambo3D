Before you run VolumeViewer.exe, make sure the driver of your video card is 
up to date (the generic one coming with windows does not work).

The general usage of the executable is:

VolumeViewer.exe --img img.data --ano ano.data --dRes xRes yRes zRes

where img.data and ano.data are the volumes downloaded from the cut-out service,
and xRes/yRes/zRes together specify the data resolution.

Notice that the volume here needs to be a flattened hdf5 cube. For convenience
in the package we provide a python script for doing that. To run the script,
you will need to have Python installed along with NumPy and h5py (whose win7-64
installers are all included in the package as well). 

The easiest way to get through the whole plumbing process is to use the provided
batch-file (demo.bat).

If there is still any problem, let me know: ming@cs.jhu.edu

