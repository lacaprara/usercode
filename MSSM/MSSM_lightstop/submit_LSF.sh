#!/bin/bash

export LSF_WORKING_DIR=${PWD}

#for M in 225 250 275 300 325 350 400 500 600
#for M in `seq 225 5 345` # 25 mass points
#for M in `seq 350 10 600` # 26 mass points
for M in `seq 225 5 345; seq 350 10 600` # all mass points
do
  bsub -o M$M.log -J M$M /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/MSSM/MSSM_lightstop/createMSSM_model.sh $M
  # mkdir Run_M$M
  # cd Run_M$M
  # /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/MSSM/MSSM_lightstop/createMSSM_model.sh $M > Log$M.log 2>&1 &
  # cd -
done
