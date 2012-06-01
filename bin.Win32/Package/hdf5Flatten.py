##############################################################################
#
#    Randal C. Burns
#    Department of Computer Science
#    Johns Hopkins University
#
################################################################################

import numpy as np
import h5py
import sys
import urllib
import tempfile

if len(sys.argv) != 3:
    print 'USAGE: hdf5Flatten.py <url> <output filename>'
    exit(0)

myTemp = tempfile.NamedTemporaryFile( delete=False )

try:
  print 'Downloading....'  
  urllib.urlretrieve ( sys.argv[1] , myTemp.name )
except URLError:
  print 'Failed to download the cutout image.'
  assert 0

h5f = h5py.File ( myTemp.name , driver='core' , backing_store=False )

try:
  cube = h5f['cube']
except KeyError:
  print 'Failed to retrieved the atrribute cube.'
  assert 0

rawData = cube[:,:,:].flatten()
rawData.tofile( sys.argv[2] )

print 'Dumped to: ' + sys.argv[2]
