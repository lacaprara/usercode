#!/bin/bash

for M in 225 250 275 300 325 350 400 500 600
do
  bsub -o M$M.log -J M$M /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/create2HDMC_model.sh $M
done
  

