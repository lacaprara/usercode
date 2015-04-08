#!/bin/bash

dir="./"
if [ "$#" -eq 1 ]; then
  dir=$1
fi

function createOneTree() {
  dir=$1

  Summary=`basename $dir/Summary*out`

  root -b -q -l buildTree2HDMC.C\(\"$Summary\",\"$dir\"\)
}

#for ddir in lsf_working_dir_M225_Type1_20598531/
for ddir in `ls -d lsf*`
#for ddir in .
do
  echo "$ddir"
  createOneTree $ddir/
done
