#!/bin/sh
BASEDIR="../"   # root of translatable sources
PROJECT="simonmanual"  # project name
BUGADDR="http://sourceforge.net/tracker/?atid=935103&group_id=190872"      # MSGID-Bugs
WDIR=`pwd`          # working dir
 
echo "Extracting messages"
cd ${WDIR}
xml2pot ${BASEDIR}/index.docbook > ${PROJECT}.pot
echo "Done extracting messages"
 
 
echo "Merging translations"
catalogs=`find . -name '*.po'`
for cat in $catalogs; do
  echo $cat
  msgmerge -o $cat.new $cat ${PROJECT}.pot
  mv $cat.new $cat
done
echo "Done merging translations"
 
 
echo "Done"
