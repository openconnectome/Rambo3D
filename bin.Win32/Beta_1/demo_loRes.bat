SET XRES=512
SET YRES=512
SET ZRES=64
SET ANNO=http://openconnecto.me/~randal/cutout/annotate/kanno/hdf5/5000,5512/8000,8512/968,1032/
SET IMGS=http://openconnecto.me/~randal/cutout/kasthuri11/hdf5/1/5000,5512/8000,8512/968,1032/

( @ECHO %ANNO% & @ECHO %IMGS% ) | VolumeViewer.exe --dRes %XRES% %YRES% %ZRES% --url



