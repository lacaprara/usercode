#!/bin/bash

export LSF_WORKING_DIR=$PWD

for T in 1 2
do
  #for M in {200..350..10}
  #for M in {400..1200..100}
  #for MA in {200..350..10} {400..1200..100}
  for MA in 300
  do
    #for MH in {200..350..10} {400..1200..100}
    for MH in 300
    do
      bsub -o MA${MA}_MH${MH}_Type$T.log -J MA${MA}_MH${MH}_Type$T /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/create2HDMC_model.sh $MA $MH $T
    done
  done
done
  

