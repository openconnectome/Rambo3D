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