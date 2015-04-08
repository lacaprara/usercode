#!/bin/bash
#
# Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
# 21-Mar-2014
#
# script to create a datacard to be fed to SuShi and 2HDMC and produce sigma and BR for A->ZH
#

function createDatacard() {
mA=$1 # A mass
xtanbeta=$2 # tan beta
xmu=$3 # \mu
xA_x=$4 # A_{t,b,\tau}

fname=$5

rm -f ${fname}
cat >> ${fname} << EOF
Block SUSHI
  1   1		# model: 0 = SM, 1 = MSSM
  2   1           # 0 = light Higgs (h), 1 = pseudoscalar (A), 2 = heavy Higgs (H)
  3   0		# collider: 0 = p-p, 1 = p-pbar
  4   8000.d0	# center-of-mass energy in GeV
  5   3		# order ggh: -1 = off, 0 = LO, 1 = NLO, 2 = NNLO, 3 = ~NNLO stop for h
  6   2		# order bbh: -1 = off, 0 = LO, 1 = NLO, 2 = NNLO
  7   1 	# electroweak cont. for ggh:
                # 0 = no, 1 = light quarks at NLO, 2 = SM EW factor
 19   1		# 0 = silent mode of SusHi, 1 = normal output
 20   0         # ggh@nnlo subprocesses: 0=all, 10=ind. contributions
Block SMINPUTS		# Standard Model inputs
  1   1.27670000e+02    # alpha_em^(-1)(MZ) SM MSbar
  2   1.16637000e-05    # G_Fermi
  3   1.19000000e-01    # alpha_s(MZ) SM MSbar
  4   9.11876000e+01    # m_Z(pole)
  5   4.16000000e+00    # m_b(m_b)
  6   1.73200000e+02    # m_t(pole)
  8   1.40000000e+00    # m_c(m_c)
Block MINPAR
  3   ${xtanbeta}d0 	# tan(beta)
Block EXTPAR
  3   1500.d0		# M_3
 11   ${xA_x}.d0		# A_T   # ADJUST WHEN CHANGING mu OR tanb
 12   ${xA_x}.d0		# A_B   # ADJUST WHEN CHANGING mu OR tanb
 23   ${xmu}.d0		# mu in GeV
 26   ${mA}.d0 		# M_A0
 43   1000.d0		# M_Q3
 46   1000.d0		# M_U3
 49   1000.d0		# M_D3
Block FEYNHIGGS # FeynHiggs specific input
  1   0.d0		# M_1
  2   200.d0	# M_2
 13   ${xA_x}.d0   # A_TAU   # ADJUST WHEN CHANGING mu OR tanb
 14   0.d0  	# A_C
 15   0.d0 		# A_S
 16   0.d0 		# A_MU
 17   0.d0 		# A_U
 18   0.d0 		# A_D
 19   0.d0 		# A_E
 31   500.d0    	# M_L1
 32   500.d0    	# M_L2
 33   1000.d0    	# M_L3
 34   500.d0    	# M_E1
 35   500.d0    	# M_E2
 36   1000.d0    	# M_E3
 41   1500.d0    	# M_Q1
 42   1500.d0    	# M_Q2
 44   1500.d0    	# M_U1
 45   1500.d0    	# M_U2
 47   1500.d0    	# M_D1
 48   1500.d0    	# M_D2
Block DISTRIB
  1   0		# distribution : 0 = sigma_total, 1 = dsigma/dpt,
		#                2 = dsigma/dy,   3 = d^2sigma/dy/dpt
		#                (values for pt and y: 22 and 32)
  2   0		# pt-cut: 0 = no, 1 = pt > ptmin, 2 = pt < ptmax,
		#         3 = ptmin < pt < ptmax
 21   30.d0	# minimal pt-value ptmin in GeV
 22   100.d0	# maximal pt-value ptmax in GeV
  3   0		# rapidity-cut: 0 = no, 1 = Abs[y] < ymax,
		#    2 = Abs[y] > ymin, 3 = ymin < Abs[y] < ymax
 31   0.5d0	# minimal rapidity ymin
 32   1.5d0	# maximal rapidity ymax
  4   0		# 0 = rapidity, 1 = pseudorapidity
Block SCALES
  1   0.5 	# renormalization scale muR/mh
  2   0.5	# factorization scale muF/mh
 11   1.0 	# renormalization scale muR/mh for bbh
 12   0.25	# factorization scale muF/mh for bbh
  3   0         # 1 = Use (muR,muF)/Sqrt(mh^2+pt^2) for dsigma/dpt and d^2sigma/dy/dpt
Block RENORMBOT # Renormalization of the bottom sector
  1   0 	# m_b used for bottom Yukawa:  0 = OS, 1 = MSbar(m_b), 2 = MSbar(muR)
  2   2 	# tan(beta)-res. of Y_b: 0 = no, 1 = naive, 2 = full (for OS only)
  3   1 	# Delta_b: Take Delta_b from FeynHiggs: 0 = no, 1 = yes
Block RENORMSBOT # Renormalization of the sbottom sector
  1   2  	# m_b:     0 = OS, 1 = DRbar, 2 = dep; recommended: 2
  2   0  	# A_b:     0 = OS, 1 = DRbar, 2 = dep; recommended: 0
  3   0  	# theta_b: 0 = OS, 1 = DRbar         ; recommended: 0
Block PDFSPEC
  1   MSTW2008lo90cl.LHgrid		# name of pdf (lo)
  2   MSTW2008nlo90cl.LHgrid		# name of pdf (nlo)
  3   MSTW2008nnlo90cl.LHgrid	# name of pdf (nnlo)
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
  4   1.d0	# st
  5   1.d0	# sb
EOF
}

function createDatacardFH() {
mA=$1 # A mass
xtanbeta=$2 # tan beta
xmu=$3 # \mu
xXt=$4 # \mu

fname=$5

rm -f ${fname}
cat >> ${fname} << EOF
MT           173.2
MSusy        1000
Abs(Xt)      ${xXt}
Abs(M_2)     200
Abs(MUE)     ${xmu}
Abs(M_3)     800
MA0          ${mA}
TB           ${xtanbeta}

# FeynHiggs example/LHBMS/mhmax.in 400202110

EOF
}

export LHAPATH=/lustre/cmswork/lacaprar/AZh/2HDM/local/share/lhapdf/

# cd /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/test
# eval `scram runtime -sh`
# cd -
ln -s /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/Hp_limit_tau .
ln -s /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/2HDMC-1.6.4/Hp_limit_cs .

mA=$1
njob=0
X_t=2000 # formhmax
mu=600 # formhmax
#for mA in 225 250 275 300 325 350 400 500 600
#for mA in 225 
#  do
  for tanbeta in 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 120 140 160 180 200 220 240 260 280 300 320 340 360 380 400 420 440 460 480 500 550 600 650 700 750 800 850 900 950 1000 1100 1200 1300 1400 1500 2000 3000 4000 5000
  #for tanbeta in 75
    do
    njob=$((njob+1))
    tb=$(echo "scale=2; ${tanbeta}/100." | bc  | awk '{printf "%1.2f", $0}') 
    #echo "scale=2; sqrt(100.*100.-(${cosba})*(${cosba})))/100." 

    ## A_t = A_b (= A_tau) = X_t + mu / tan(beta).
    A_x=$(echo "scale=0; $X_t + $mu/$tb" | bc )

    name=MSSM_mhmax_mA${mA}_tb${tb/./p}

    echo "creating $njob Datacard mA=$mA tanBeta=$tb mu=$mu X_t=$X_t A_x=$A_x name: ${name}.card"

    createDatacard ${mA} ${tb} $mu $A_x ${name}.card
    
    /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/SusHi-1.2.0/bin/sushi.FH ${name}.card ${name}_SuShi.out

    createDatacardFH ${mA} ${tb} $mu $X_t ${name}_FH.in

    /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/FeynHiggs-2.10.0/build/FeynHiggs ${name}_FH.in#SLHA > ${name}_FH.log
    mv -f ${name}_FH.in.fh-001 ${name}_FH.slha
    /lustre/cmswork/lacaprar/Ana/CMSSW_5_3_11/src/AZh/2HDM/FeynHiggs-2.10.0/example/demo ${name}_FH.slha > ${name}_FH.out
  done
#done
echo $njob
