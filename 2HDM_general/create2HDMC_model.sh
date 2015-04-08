#!/bin/bash
#
# Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
# 21-Mar-2014
# changes: 
#     28-Oct-2014 Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
#           Add input for H production and mH
#
# script to create a datacard to be fed to SuShi and 2HDMC and produce sigma and BR

## Constant
mh=125.03 # Higgs mass
pi=3.14159265359
epsilon=0.001
pihalf=$(echo "scale=10; ${pi}/2"| bc)
##

# Create the datacard for SuShi
function createDatacard() {
what=$1 # Produce A(==1) or H(==2) 
Type=$2 # 2HDM type
mA=$3 # A mass
mH=$4 # H mass
xtanbeta=$5 # tan beta
xsinba=$6 # sin (beta-alpha)
m12=$7 # M_12
mHC=$((mA))
#mHC=100

fname=$8

rm -f ${fname}
cat >> ${fname} << EOF
Block SUSHI
  1   2		# model: 0 = SM, 1 = MSSM, 2 = 2HDM
  2   ${what}     # 0 = light Higgs (h), 1 = pseudoscalar (A), 2 = heavy Higgs (H)
  3   0		# collider: 0 = p-p, 1 = p-pbar
  4   8000.d0	# center-of-mass energy in GeV
  5   2		# order ggh: -1 = off, 0 = LO, 1 = NLO, 2 = NNLO
  6   2	      # order bbh: -1 = off, 0 = LO, 1 = NLO, 2 = NNLO
  7   1 	      # electroweak cont. for ggh:
                  # 0 = no, 1 = light quarks at NLO, 2 = SM EW factor
 19   1		# 0 = silent mode of SusHi, 1 = normal output
 20   0           # ggh@nnlo subprocesses: 0=all, 10=listing individual contributions
Block 2HDMC 	      # 2HDMC arXiv:0902.0851
  1   2 	            # 2HDMC key, 1=lambda basis, 2=physical basis, 3=H2 basis
  2   ${Type} 	      # 2HDM version type according to arxiv:1106.0034
  3   ${xtanbeta} 	# tan(beta)
  4   ${m12} 		# m12
  21  ${mh} 	      # mh
  22  ${mH} 		 	# mH
  23  ${mA} 		 	# mA
  24  ${mHC} 		 	# mC
  25  ${xsinba}	 		# sin(beta-alpha)
  26  0.d0 		      # lambda6
  27  0.d0 		      # lambda7
Block SMINPUTS		# Standard Model inputs
  1   1.27934000e+02	# alpha_em^(-1)(MZ) SM MSbar
  2   1.16637000e-05	# G_Fermi
  3   1.17200000e-01	# alpha_s(MZ) SM MSbar
  4   9.11876000e+01	# m_Z(pole)
  5   4.20000000e+00	# m_b(m_b)
  6   1.73300000e+02	# m_t(pole)
  8   1.27500000e+00	# m_c(m_c)
Block DISTRIB
  1   0		# distribution : 0 = sigma_total, 1 = dsigma/dpt,
		      #                2 = dsigma/dy,   3 = d^2sigma/dy/dpt
		      #                (values for pt and y: 22 and 32)
  2   0    		# pt-cut: 0 = no, 1 = pt > ptmin, 2 = pt < ptmax,
		      #         3 = ptmin < pt < ptmax
 21   30.d0	      # minimal pt-value ptmin in GeV
 22   100.d0	# maximal pt-value ptmax in GeV
  3   0		# rapidity-cut: 0 = no, 1 = Abs[y] < ymax,
		      #    2 = Abs[y] > ymin, 3 = ymin < Abs[y] < ymax
 31   0.5d0	      # minimal rapidity ymin
 32   1.5d0	      # maximal rapidity ymax
  4   0		# 0 = rapidity, 1 = pseudorapidity
Block SCALES
  1   0.5 	# renormalization scale muR/mh
  2   0.5	# factorization scale muF/mh
 11   1.0 	# renormalization scale muR/mh for bbh
 12   0.25	# factorization scale muF/mh for bbh
  3   0         # 1 = Use (muR,muF)/Sqrt(mh^2+pt^2) for dsigma/dpt and d^2sigma/dy/dpt
Block RENORMBOT # Renormalization of the bottom sector
  1   0 	      # m_b used for bottom Yukawa:  0 = OS, 1 = MSbar(m_b), 2 = MSbar(muR)
  4   4.75d0      # Fixed value of m_b^OS
Block PDFSPEC
  1   MSTW2008lo90cl.LHgrid		# name of pdf (lo)
  2   MSTW2008nlo90cl.LHgrid		# name of pdf (nlo)
  3   MSTW2008nnlo90cl.LHgrid	      # name of pdf (nnlo)
  4   0		# set number
Block VEGAS
# parameters for NLO SusHi
         1    10000   # Number of points
         2        5   # Number of iterations
         3       10   # Output format of VEGAS integration
# parameters for ggh@nnlo:
         4     2000   # Number of points
         5        5   # Number of iterations
        14     5000   # Number of points in second run
        15        2   # Number of iterations in second run
         6        0   # Output format of VEGAS integration
# parameters for bbh@nnlo:
         7     2000   # Number of points
         8        5   # Number of iterations
        17     5000   # Number of points in second run
        18        2   # Number of iterations in second run
         9        0   # Output format of VEGAS integration
Block FACTORS
  1   0.d0	# factor for yukawa-couplings: c
  2   1.d0	# t
  3   1.d0	# b
EOF
}

if [ "$#" -ne 3 ]; then
  echo "usage:\t $0 <A_mass> <H_mass> <2HDM type>"
  exit 1
fi

export LHAPATH=/lustre/cmswork/lacaprar/AZh/2HDM/local/share/lhapdf/

# cd /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/test
# eval `scram runtime -sh`
# cd -
ln -s /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/Hp_limit_tau .
ln -s /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/Hp_limit_cs .

massA=$1
massH=$2
ty=$3
njob=0
for mA in $massA
#for mA in {200..1200..100}
  do
  for mH in $massH
#  for mH in {200..1200..100}
    do
  #for tanbeta in 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 120 140 160 180 200 220 240 260 280 300 350 400 450 500 550 600 650 700 750 800 850 900 950 1000 5000 10000
  #for tanbeta in 10 20 30 40 50 60 70 80 90 100 120 140 160 180 200 220 240 260 280 300 350 400 450 500 550 600 650 700 750 800 850 900 950 1000 5000 10000
  #for tanbeta in {100..1000..100}
  for tanbeta in {10..90..10}
#  for tanbeta in 150
    do
    for cosba in {-100..100..10}
#    for cosba in 10
    do
      njob=$((njob+1))
      tb=$(echo "scale=1; ${tanbeta}/100." | bc) 
      #beta=$(echo "scale=4; a($tb)" | bc -l)

      cba=$(echo "scale=2; ${cosba}/100." | bc) 
      sba=$(echo "scale=10; sqrt(100.*100.-(${cosba})*(${cosba}))/100." | bc -l)

      if (( $(echo "$cba==1"|bc) == 1 )) ; then
        ba=0
      elif (( $(echo "$cba==-1"|bc) == 1 )) ; then
        #ba=$(echo "$pi"| bc)
        ba=$(echo "scale=10;$pi-$epsilon"| bc)
        sba=$(echo "scale=10;s($ba)"|bc -l)
      elif (( $(echo "$cba==0"|bc) == 1 )) ; then
        ba=$(echo "$pihalf" | bc)
      else
        ba=$( echo "scale=4; a(sqrt(1 - ${cba}*${cba} )/ ${cba})" | bc -l)
        if (( $(echo "${ba} < 0" | bc) )); then
          ba=$(echo "scale=4; ${ba}+${pi}" | bc -l)
        fi
      fi
      #if (( $(echo "scale=10; ${ba} >= ${pi}" | bc) )); then
      if (( $(echo "${ba} > ${pihalf}" | bc) )); then
         sba=$(echo "scale=2; -1*${sba}" | bc)
      fi
      sba=$(echo ${sba} |xargs printf "%1.5f")

      m12=$(echo "scale=1;sqrt(${mA}^2*(${tb}/(1.+${tb}^2)))"  | bc)

      sbaname=${sba/-/M}
      rm -f report.txt
      name=2HDM_prodh_ty${ty}_mA${mA}_mH${mH}_tb${tb/./p}_sba${sbaname/./p}
      echo "creating for h $njob Datacard mA=$mA mH=$mH tanBeta=$tb cos(beta-alpha)=${cba} sin(beta-alpha)=$sba name: ${name}.card"
      createDatacard 0 ${ty} $mA $mH $tb $sba $m12 ${name}.card 
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/bin/sushi.2HDMC ${name}.card ${name}_SuShi.out
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parseSuShiOutput.pl ${name}_SuShi.out

      name=2HDM_prodA_ty${ty}_mA${mA}_mH${mH}_tb${tb/./p}_sba${sbaname/./p}
      echo "creating for A $njob Datacard mA=$mA mH=$mH tanBeta=$tb cos(beta-alpha)=${cba} sin(beta-alpha)=$sba name: ${name}.card"
      createDatacard 1 ${ty} $mA $mH $tb $sba $m12 ${name}.card 
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/bin/sushi.2HDMC ${name}.card ${name}_SuShi.out
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parseSuShiOutput.pl ${name}_SuShi.out

      name=2HDM_prodH_ty${ty}_mA${mA}_mH${mH}_tb${tb/./p}_sba${sbaname/./p}
      echo "creating for H $njob Datacard mA=$mA mH=$mH tanBeta=$tb cos(beta-alpha)=${cba} sin(beta-alpha)=$sba name: ${name}.card"
      createDatacard 2 ${ty} $mA $mH $tb $sba $m12 ${name}.card 
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/bin/sushi.2HDMC ${name}.card ${name}_SuShi.out
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parseSuShiOutput.pl ${name}_SuShi.out

      name=2HDM_ty${ty}_mA${mA}_mH${mH}_tb${tb/./p}_sba${sbaname/./p}
      # CalcPhys.x mh mH mA mHp sin(beta-alpha) lambda_6 lambda_7 m_12^2 tan_beta yukawas_type output_filename
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/CalcPhys $mh $mH $mA $mA $sba 0 0 $(echo "${m12}*${m12}"|bc) $tb ${ty} ${name}_2HDMC.out
      /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parse2HDMCOutput.pl ${name}_2HDMC.out

      name=2HDM_ty${ty}_mA$1_mH$2
      cat report.txt >>  Summary_${name}.out
      rm -f ${name}*
      done
    done
  done
done
echo $njob
