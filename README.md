7zip-and-p7zip
==============

For reasons I cannot fathom, the developer of 7zip and the porters/developers of p7zip do not maintain a public version control system with their source code. (I sure hope for their sanity they use one privately)

This repository contains a properly tagged and branched recent history of 7zip and p7zip source code to help with debugging and porting, starting with version 9.20 released in 2010.

The master_7zip branch ( https://github.com/pombredanne/7zip-and-p7zip/tree/master_7zip ) contains the 7zip code history assembled from the downloadable archives at https://sourceforge.net/projects/sevenzip/

The master_p7zip branch ( https://github.com/pombredanne/7zip-and-p7zip/tree/master_p7zip ) contains the 7pzip code history, branched from the corresponding ported version of 7zip and assembled from the  downloadable archives at https://sourceforge.net/projects/p7zip/

Each released version is tagged with vXXXX-7zip for 7zip versions and vXXXX-p7zip for p7zip versions.

The code is --as originally-- available under a combination of the LGPL 2.1 and the unRar restricted license. See the LICENSE file  and the DOCS directory in each branch for details.
