SET XRES=512
SET YRES=512
SET ZRES=64
SET ANNO=http://openconnecto.me/annotate/kanno/hdf5/1/5000,5512/8000,8512/968,1032/
SET IMGS=http://openconnecto.me/cutout/kasthuri11/hdf5/1/5000,5512/8000,8512/968,1032/
hdf5Flatten.py %ANNO% ano.data
hdf5Flatten.py %IMGS% img.data
VolumeViewer.exe --dRes %XRES% %YRES% %ZRES% --img img.data --ano ano.data



