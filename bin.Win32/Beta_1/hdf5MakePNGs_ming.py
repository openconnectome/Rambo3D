##############################################################################
#
#    Randal C. Burns
#    Department of Computer Science
#    Johns Hopkins University
#
################################################################################

import numpy as np
from PIL import Image
import urllib
import urllib2
import tempfile
import h5py
import os
import sys

if len(sys.argv) != 3:
    print 'USAGE: hdf5MakeRaw.py <url> <output filename>'
    exit(0)

###### stupid windows has permission issues creating temp files =(
# myTempFile = tempfile.TemporaryFile()

try:
  #urllib.urlretrieve( sys.argv[1] , myTempFile.name )
  #urllib.urlretrieve( sys.argv[1] , sys.argv[2] )
  os.system( "wget " + sys.argv[1] + " -O " + sys.argv[2] )
except EXCEPTION:
  print 'Failed to retrieve URL: ' + sys.argv[1]
  exit(0)
  # urlretrieve is dumb silent...leave it for now
  
#h5f = h5py.File ( tempfile.name , driver='core' , backing_store=False )
h5f = h5py.File ( sys.argv[2] , driver='core' , backing_store=False )

try:
  cube = h5f['cube']
except KeyError:
  print 'Failed to retrieved the atrribute cube....URL was wrong?'
  exit(0)

rawData = cube[:,:,:].flatten()
rawData.tofile( sys.argv[2] )

print 'Retrieved: ' + sys.argv[1]
print 'Dumped to: ' + sys.argv[2]
print ' ---------- END ---------- '







