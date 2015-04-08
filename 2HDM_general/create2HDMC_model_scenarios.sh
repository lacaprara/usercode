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
mHC=$8
#mHC=100

fname=$9

echo $fname
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
 21   00.d0	      # minimal pt-value ptmin in GeV
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

if [ "$#" -ne 1 ]; then
  echo "usage:\t $0 <Scenario> "
  exit 1
fi

export LHAPATH=/lustre/cmswork/lacaprar/AZh/2HDM/local/share/lhapdf/

# cd /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/test
# eval `scram runtime -sh`
# cd -
ln -s /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/Hp_limit_tau .
ln -s /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/Hp_limit_cs .

if [ "$1" = "A" ]; then
  # Scenario A
  ty=1
  mH=300
  mA=330
  mHC=230
  M12square=25600
  tanbeta=1.5
  sinba=0.901314
elif [ "$1" = "B" ]; then
  # Scenario B
  ty=2
  mH=300
  mA=270
  mHC=335
  M12square=1798
  tanbeta=50
  sinba=0.999001
elif [ "$1" = "C" ]; then
  # Scenario C
  ty=2
  mH=400
  mA=500
  mHC=550
  M12square=15800
  tanbeta=10
  sinba=0.999
else
  echo "Scenario A B C"
  exit 1
fi

m12=$(echo "scale=4; sqrt(${M12square})" | bc)

tb=$(echo "scale=3; ${tanbeta}" | bc) 

sba=$(echo "scale=6; ${sinba}" | bc) 
cba=$(echo "scale=10; sqrt(1-(${sba})*(${sba}))" | bc -l)


sbaname=${sba/-/M}
rm -f report.txt
name=2HDM_prodh_Scenario$1
echo "creating for h $njob Datacard mA=$mA mH=$mH tanBeta=$tb cos(beta-alpha)=${cba} sin(beta-alpha)=$sba name: ${name}.card"
createDatacard 0 ${ty} $mA $mH $tb $sba $m12 $mHC ${name}.card 
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/bin/sushi.2HDMC ${name}.card ${name}_SuShi.out
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parseSuShiOutput.pl ${name}_SuShi.out

name=2HDM_prodA_Scenario$1
echo "creating for A $njob Datacard mA=$mA mH=$mH tanBeta=$tb cos(beta-alpha)=${cba} sin(beta-alpha)=$sba name: ${name}.card"
createDatacard 1 ${ty} $mA $mH $tb $sba $m12 $mHC ${name}.card 
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/bin/sushi.2HDMC ${name}.card ${name}_SuShi.out
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parseSuShiOutput.pl ${name}_SuShi.out

name=2HDM_prodH_Scenario$1
echo "creating for H $njob Datacard mA=$mA mH=$mH tanBeta=$tb cos(beta-alpha)=${cba} sin(beta-alpha)=$sba name: ${name}.card"
createDatacard 2 ${ty} $mA $mH $tb $sba $m12 $mHC ${name}.card 
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/bin/sushi.2HDMC ${name}.card ${name}_SuShi.out
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parseSuShiOutput.pl ${name}_SuShi.out

name=2HDM_Scenario$1
# CalcPhys.x mh mH mA mHp sin(beta-alpha) lambda_6 lambda_7 m_12^2 tan_beta yukawas_type output_filename
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/CalcPhys $mh $mH $mA $mHC $sba 0 0 $M12square $tb ${ty} ${name}_2HDMC.out
/lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/test/2HDM_general/parse2HDMCOutput.pl ${name}_2HDMC.out

name=2HDM_Scenario$1
cat report.txt >>  Summary_${name}.out
#rm -f ${name}*

echo $njob
