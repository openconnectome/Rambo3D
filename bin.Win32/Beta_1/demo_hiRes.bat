SET XRES=1024
SET YRES=1024
SET ZRES=128
SET ANNO=http://openconnecto.me/~randal/cutout/annotate/kanno/hdf5/5000,6024/8000,9024/900,1028/
SET IMGS=http://openconnecto.me/~randal/cutout/kasthuri11/hdf5/1/5000,6024/8000,9024/900,1028/

( @ECHO %ANNO% & @ECHO %IMGS% ) | VolumeViewer.exe --dRes %XRES% %YRES% %ZRES% --url



