// 30-Apr-2014
// Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
// 
// a Macro to plot the limit on tanbeta vs cos(alpha-beta) plane
//

struct lim {
  double mA;
  double obsLim , expM2s ,   expM1s , exp , expP1s , expP2s;
  double obsLimTb , expM2sTb ,   expM1sTb , expTb , expP1sTb , expP2sTb;
};

void  findTB(TH2* hggA, lim& limit);

void plotMSSMLimit(int m=300, int type=1, const TString& fileLimit="Int2D_M300.txt") {
  // What to plot (sigma*BR)
  const TString what="(ggA+bbA)*BRAZh*BRhbb";
  const double BRZll=0.06726;
  const double fb2pb=1000;
  TString scale(Form("*%f*%f",BRZll,fb2pb));
  // Add also BR of Z->ll and move to fb
  what+=scale;

  TString ttype("_MSSM_mhmax");

  TString cname("Limit"+ttype);
  //
  TString goodName=("A#rightarrowZh#rightarrowllbb");
  TString goodType("MSSM m_{h}^{max}");


  TString ok(""); // possible additional selection


  // Read trees with results from SuShi and 2HDMC
  TChain* ch=new TChain("TreeMSSM");

  ch->Add("lsf_working_dir_M225_20636539/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M250_20636540/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M275_20636541/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M300_20636542/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M325_20636543/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M350_20636544/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M400_20636545/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M500_20636546/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M600_20636547/parameter_MSSM.root");


  // Create a variable binning histogram following the granularity used in the MC generation
  //
  // for tanBeta
  //double tanbeta[51]={0,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1500,2000,3000,4000,5000,6000};
  double tanbeta[51]={0,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,500,550,580,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1500,2000,3000,4000,5000,6000};
  Double_t bin_tb[50];
  for (unsigned int i=0; i<50; i++) {
    bin_tb[i]=0.005*(tanbeta[i]+tanbeta[i+1]);
    //cout << "bin_tb[" << i << "]=" << bin_tb[i] << " " << tanbeta[i+1]/100. << endl;
  }

  

  // for mA
  double mA[11]={200,225,250,275,300,325,350,400,500,600,700};
  Double_t bin_mA[10];
  for (unsigned int i=0; i<=10; ++i) {
    bin_mA[i]=0.5*(mA[i]+mA[i+1]);
    //cout << "bin_mA["<<i<<"]="  << bin_mA[i] << endl;
  }
  bin_mA[10]=650;
  Double_t bin_cba[52];
  bin_cba[0]=-0.01;
  for (unsigned int i=1; i<=50; ++i) {
    bin_cba[i]=-0.01+1.*i/50;
    //cout << "bin_cba["<<i<<"]="  << bin_cba[i] << endl;
  }
  bin_cba[51]=1.01;

  // This is the variable bin histogram tanbeta vs mA (to be used)
  TH2F* hggA=new TH2F("hggA","ggA cross section vs tan#beta,m_{A}; m_{A} GeV; tan#beta",9,bin_mA,49,bin_tb);
  hggA->Sumw2();
  hggA->GetYaxis()->SetRangeUser(0.1,100.);
  TString cut=what+ok;
  cout << "CUT: " << cut << " Mass " << m << endl;

  // Here I project the tree into the histograms
  ch->Project("hggA","tb:mA",cut);


  // Set style to draw
  TStyle *tdrStyle = gROOT->GetStyle("tdrStyle");
  tdrStyle->SetOptStat(0);
  // tdrStyle->SetPadGridX(true);
  // tdrStyle->SetPadGridY(true);
  // tdrStyle->SetPadTopMargin(0.05);
  // tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetTitleXOffset(1.6);
  tdrStyle->SetTitleOffset(1.3,"Z");
  //tdrStyle->SetPadRightMargin(0.14);
  //tdrStyle->SetPalette(1);


  tdrStyle->cd();
  gROOT->ForceStyle();

  // set countour levels
  // I read the expected and observed limit from a set of external files, provided by Alberto

  double mAlimits[9]={225,250,275,300,325,350,400,500,600};
  TString limitFname[9]={
    "Low2D_M225.txt",
    "Low2D_M250.txt",
    "Low2D_M275.txt",
    "Int2D_M300.txt",
    "Int2D_M325.txt",
    "Int2D_M350.txt",
    "High2D_M400.txt",
    "High2D_M500.txt",
    "High2D_M600.txt"};

  lim limits[9];
  for (unsigned int i=0; i<9; ++i) {
    cout << "opening " << limitFname[i] << endl;
    std::ifstream infile(limitFname[i].Data());

    double obsLim , expM2s ,   expM1s , exp , expP1s , expP2s , sign , pValue , bestFitR , bestFitRUp , bestFitRDow ;
    infile >> obsLim >> expM2s >>   expM1s >> exp >> expP1s >> expP2s >> sign >> pValue >> bestFitR >> bestFitRUp >> bestFitRDow ;
    cout << " mA: " << mAlimits[i]
      << " obsLim: " << obsLim 
      << " expM2s: " << expM2s 
      << " expM1s: " << expM1s 
      << " exp: " << exp 
      << " expP1s: " << expP1s 
      << " expP2s: " << expP2s 
      << " sign: " << sign 
      << " pValue: " << pValue 
      << " bestFitR: " << bestFitR 
      << " bestFitRUp: " << bestFitRUp
      << " bestFitRDow: " << bestFitRDow 
      << endl;

    limits[i].mA=mAlimits[i];
    limits[i].obsLim=obsLim;
    limits[i].expM2s=expM2s;
    limits[i].expM1s=expM1s;
    limits[i].exp=exp;
    limits[i].expP1s=expP1s;
    limits[i].expP2s=expP2s;
    infile.close();
  }


  // for each mass point, I have to find the values of tanbeta which correspond to the value of sigma*BR (namely z)
  double expTb[9],expTbM1s[9],expTbM2s[9],expTbP1s[9],expTbP2s[9],obsLimTb[9];

  for (unsigned int i=0; i<9; ++i) {
    findTB(hggA, limits[i]);
    expTb[i]=limits[i].expTb;
    expTbM1s[i]=limits[i].expM1sTb-expTb[i];
    expTbM2s[i]=limits[i].expM2sTb-expTb[i];
    expTbP1s[i]=expTb[i]-limits[i].expP1sTb;
    expTbP2s[i]=expTb[i]-limits[i].expP2sTb;
    obsLimTb[i]=limits[i].obsLimTb;
  }

  // I need to create a TGraph with the values I found
  

  TGraph* expG=new TGraph(9,mAlimits,expTb);
  expG->SetLineWidth(2);
  expG->SetLineStyle(2);
  TGraphAsymmErrors* exp1sG=new TGraphAsymmErrors(9,mAlimits,expTb,0,0,expTbP1s,expTbM1s);
  exp1sG->SetLineWidth(2);
  exp1sG->SetLineStyle(2);
  exp1sG->SetFillColor(kGreen);
  TGraphAsymmErrors* exp2sG=new TGraphAsymmErrors(9,mAlimits,expTb,0,0,expTbP2s,expTbM2s);
  exp2sG->SetLineWidth(2);
  exp2sG->SetLineStyle(2);
  exp2sG->SetFillColor(kYellow);
  TGraph* obsG=new TGraph(9,mAlimits,obsLimTb);
  obsG->SetLineWidth(2);
  obsG->SetLineWidth(-1002);
  obsG->SetFillStyle(3004);


  // The limit plot
  TCanvas* clin = new TCanvas("clin","Contour List",610,0,600,600);

  //clin->SetTopMargin(0.15);
  clin->SetGridx();
  clin->SetGridy();
  //clin->SetLogy();

  // a dummy histo to set the x and y scale
  TH2F *hr = new TH2F("hr", ";m_{A} [GeV] ;tan#beta", 2, 200., 650., 2, 0.1, 10);
  hr->GetXaxis()->SetTitleOffset(1.1);
  hr->Draw();
  exp2sG->Draw("3");
  exp1sG->Draw("3");
  expG->Draw("");
  obsG->Draw("");

  TLegend* Leg=new TLegend(0.6, 0.6, 0.995, 0.92,"95\% C.L. CLs Limits");
  Leg->SetBorderSize(0); Leg->SetFillStyle(0); Leg->SetFillColor(0);

  Leg->AddEntry(obsG, "Observed", "lf");
  Leg->AddEntry(expG, "Expected", "l");
  Leg->AddEntry(exp1sG, "Expected #pm1#sigma", "lf");
  Leg->AddEntry(exp2sG, "Expected #pm2#sigma", "lf");

  //mg->Draw("F");
  TLatex tl;
  tl.SetNDC();
  tl.DrawLatex(0.15,0.89,goodName);
  tl.DrawLatex(0.15,0.79,goodType);
  Leg->Draw();
  cmsPrel(19.7);

  clin->Update();

  // save the canvas
  pCan(clin,cname+"_Lin");

  TCanvas* clog = clin->Clone();

  clog->SetLogy();
  clog->Update();

  // save the canvas
  pCan(clog,cname+"_Log");
}

void plotAllMassLimit() {
//    I numeri che ci sono dentro seguono questo schema:
// 0 - Observed Limit
// 1 - Expected  2.5%
// 2 - Expected 16.0%
// 3 - Expected 50.0%
// 4 - Expected 84.0%
// 5 - Expected 97.5%
// 6 - Significance
// 7 - p-value
// 8 - Best fit r
// 9 - Best fit r up
// 9 - Best fit r down
  for (int t=1; t<=2; ++t) {
    plot2HDMCLimit(225,t,"Low2D_M225.txt");
    plot2HDMCLimit(250,t,"Low2D_M250.txt");
    plot2HDMCLimit(275,t,"Low2D_M275.txt");
    plot2HDMCLimit(300,t,"Int2D_M300.txt");
    plot2HDMCLimit(325,t,"Int2D_M325.txt");
    plot2HDMCLimit(350,t,"Int2D_M350.txt");
    plot2HDMCLimit(400,t,"High2D_M400.txt");
    plot2HDMCLimit(500,t,"High2D_M500.txt");
    plot2HDMCLimit(600,t,"High2D_M600.txt");
  }
  
}

void  findTB(TH2* hggA, lim& limit) {
  cout << "Calculating limit on tb for mA = " << limit.mA ;
  limit.obsLimTb=findTB(hggA, limit.mA, limit.obsLim);
  limit.expTb=findTB(hggA, limit.mA, limit.exp);
  limit.expM2sTb=findTB(hggA, limit.mA, limit.expM2s);
  limit.expM1sTb=findTB(hggA, limit.mA, limit.expM1s);
  limit.expP1sTb=findTB(hggA, limit.mA, limit.expP1s);
  limit.expP2sTb=findTB(hggA, limit.mA, limit.expP2s);
  cout << " exp: " << limit.expTb << " obs: " << limit.obsLimTb << endl;
  cout << " exp1s: " << limit.expM1sTb << " , " << limit.expP1sTb << endl;
  cout << " exp2s: " << limit.expM2sTb << " , " << limit.expP2sTb << endl;
}

double  findTB(TH2* hggA, const double& mA, const double& zGood) {
  // loop trough all bin of a given mA
  //
  //
  int nBinsY=hggA->GetNbinsY();
  int ibx=hggA->GetXaxis()->FindBin(mA);
  double zlow=10000;
  double zhigh=0;
  double tblow, tbhigh;
  for (unsigned int iby=1; iby<nBinsY; ++iby) {
    double z=hggA->GetBinContent(ibx,iby);
    // cout << "XS*BR(" << limit.mA << ","<< hggA->GetYaxis()->GetBinCenter(iby)<< ")=" << z << " " << limit.exp << endl;
    if (z>zGood && z<=zlow) {
      zlow=z; 
      tblow=hggA->GetYaxis()->GetBinCenter(iby);
    }
    if (z<zGood && z>=zhigh) {
      zhigh=z; 
      tbhigh=hggA->GetYaxis()->GetBinCenter(iby);
    }
  }
  // cout << "zlow " << zlow << " zhigh " << zhigh << endl;
  // cout << "tblow " << tblow << " tbhigh " << tbhigh << endl;
  double tb=tblow+(tbhigh-tblow)/(zhigh-zlow)*(zGood-zlow);
  //cout << "tb " << tb << endl;
  return tb;
}
