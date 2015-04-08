#!/bin/bash

dir="./"
if [ "$#" -eq 1 ]; then
  dir=$1
fi

function extractParameterSushi() {
  file=$1
  mA=$(grep -A8 MASSOUT ${file}| grep "MA in GeV" | awk '{print $2}')
  tb=$(grep -A8 MINPAR ${file}| grep "tan(beta)" | awk '{print $2}')
  alpha=$(grep -A1 "Block ALPHA " ${file}| grep "# alpha" | awk '{print $1}')

  # mH=$(grep -A8 2HDMCOUT ${file}| grep MH | awk '{print $2}')
  # mHC=$(grep -A8 2HDMC ${file}| grep mC | awk '{print $2}')
  # m12=$(grep -A8 2HDMC ${file}| grep m12 | awk '{print $2}')

  ggA=$(grep -A1 SUSHIggh ${file}| grep "ggh XS" | awk '{print $2}')
  bbA=$(grep -A1 SUSHIbbh ${file}| grep "bbh XS" | awk '{print $2}')

  #echo stability $stability perturbativity $perturbativity unitarity $unitarity mA $mA  mH $mH tanbeta $tb alpha $a mHC $mHC m12 $m12 ggA $ggA bbA $bbA
  echo $file $mA $tb $alpha $ggA $bbA
}

function extractParameterFH() {
  file=$1

  mA=$(grep  Mh3 ${file} | awk '{print $3}')
  mh=$(grep  Mh1 ${file} | awk '{print $3}')
  mH=$(grep  Mh2 ${file} | awk '{print $3}')
  mHC=$(grep MHp ${file}| awk '{print $3}')

  tb=$(grep TB ${file} | awk '{print $2}')

  BRhbb=$(grep "BRhbb" ${file} | awk '{print $2}')
  [[ -z $BRhbb ]] && BRhbb=0.0
  BRAZh=$(grep "BRAZh" ${file} | awk '{print $2}')
  [[ -z $BRAZh ]] && BRAZh=0.0

  #echo validity $validity stability $stability perturbativity $perturbativity unitarity $unitarity mA $mA  mH $mH tanbeta $tb "sin(beta-alpha)" $sba "cos(beta-alpha)" $cba mHC $mHC "m12^2" $m12_sq BRhbb $BRhbb BRAZh $BRAZh
  echo $file $mA $mh $mH $tb $mHC $BRhbb $BRAZh
}

function createOneTree() {
  dir=$1

  allJobs=$((`ls $dir/MSSM_MSusy10TeV*_SuShi.out | wc -l `))
  echo Working on dir $dir on $allJobs points
  outFile=$dir/parameters_MSSM.data
  mv -f ${outFile} ${outFile}_save
  touch ${outFile}
  njob=0
  for f in `ls ${dir}/MSSM_MSusy10TeV*_SuShi.out`
  do
    njob=$((njob+1))
    extractParameterSushi ${f} >> ${outFile}
    extractParameterFH ${f/SuShi/FH} >> ${outFile}
    echo -ne "Done ${njob} jobs of $allJobs\r"
  done
  echo Done $njob jobs

  root -q -l buildTreeMSSM.C\(\"$dir\"\)
}

#createOneTree test1
#for ddir in lsf_working_dir_M225_Type1_20598531/
#for ddir in `ls -d lsf*`
for ddir in "."
do
  echo "$ddir"
  createOneTree $ddir &
done
