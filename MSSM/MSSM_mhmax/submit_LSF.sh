#!/bin/bash

for M in 225 250 275 300 325 350 400 500 600
do
  bsub -o M$M.log -J M$M /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/MSSM/test1/createMSSM_model.sh $M
  # mkdir Run_M$M
  # cd Run_M$M
  # /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/MSSM/test1/createMSSM_model.sh $M > Log$M.log 2>&1 &
  # cd -
done
