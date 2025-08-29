#  Copyright (C) 2022 - 2025 Open Risk (www.openriskmanagement.com)
#
#  This file is part of the matrix2json project.
#
#  Licensed under the GPL;
#  you may not use this file except in compliance with the License.


import pymrio

data_path = '../data/'

#
# Download EXIOBASE Data
#
# exio_downloadlog = pymrio.download_exiobase3(
#     storage_folder=data_path, system="pxp", years=[2012]
# )
# print(exio_downloadlog)

#
# Parse and print metadata
#

exio3 = pymrio.parse_exiobase3(path=data_path + "/IOT_2012_pxp.zip")
print(exio3.meta)
# MRIO Name: exio382_ntnu
# System: pxp
# Version: v3.81
# File: None
# History:
# 20231003 18:41:02 - MODIFICATION -  Changed country names
# 20231003 18:41:02 - FILEIO -  Added satellite account from IOT_2012_pxp/satellite
# 20231003 18:40:34 - FILEIO -  Added satellite account from IOT_2012_pxp
# 20231003 18:39:10 - FILEIO -  Added satellite account from IOT_2012_pxp/impacts
# 20231003 18:37:38 - FILEIO -  Loaded IO system from ../data/IOT_2012_pxp.zip - IOT_2012_pxp
# 20210907 23:36:27 - FILEIO -  Saved exio382_ntnu to /home/konstans/Xdrive/indecol/Projects/EXIOBASE_dev/EXIOBASE_3_8_2/upload_to_Box/public/IOT_txt/pxp/IOT_2012_pxp
# 20210907 23:31:42 - MODIFICATION -  Calculating accounts for extension impacts
#     20210907 23:31:35 - MODIFICATION -  Calculating accounts for extension satellite
#     20210907 23:31:35 - MODIFICATION -  Flow matrix Z calculated
# 20210907 23:31:35 - MODIFICATION -  Industry Output x calculated
exio3.Z


# wiod_meta = pymrio.download_wiod2013(storage_folder=raw_wiod_path)
# print(wiod_meta)
# wiod = pymrio.parse_wiod(raw_wiod_path, year=2010)


