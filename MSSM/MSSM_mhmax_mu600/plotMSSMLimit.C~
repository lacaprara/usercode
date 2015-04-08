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
  TString goodMu("#mu=600 GeV");


  TString ok(""); // possible additional selection


  // Read trees with results from SuShi and 2HDMC
  TChain* ch=new TChain("TreeMSSM");

  ch->Add("lsf_working_dir_M225_23295340/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M230_23295341/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M235_23295342/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M240_23295343/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M245_23295344/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M250_23295345/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M255_23295346/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M260_23295347/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M265_23295348/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M270_23295349/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M275_23295350/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M280_23295351/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M285_23295352/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M290_23295353/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M295_23295354/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M300_23295355/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M305_23295356/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M310_23295357/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M315_23295358/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M320_23295359/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M325_23295360/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M330_23295361/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M335_23295362/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M340_23295363/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M345_23295364/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M350_23295365/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M360_23295366/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M370_23295367/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M380_23295368/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M390_23295369/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M400_23295370/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M410_23295371/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M420_23295372/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M430_23295373/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M440_23295374/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M450_23295375/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M460_23295376/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M470_23295377/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M480_23295378/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M490_23295379/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M500_23295380/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M510_23295381/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M520_23295382/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M530_23295383/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M540_23295384/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M550_23295385/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M560_23295386/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M570_23295387/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M580_23295388/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M590_23295389/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M600_23295390/parameter_MSSM.root");




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
  double mA[52];
  mA[0]=220;
  for (unsigned int i=0; i<=24; ++i) mA[i+1]=(225+i*5);
  for (unsigned int i=0; i<=25; ++i) mA[i+25]=(350+i*10);
  mA[51]=610;

  Double_t bin_mA[51];
  for (unsigned int i=0; i<51; ++i) {
    //cout << "mA["<<i<<"]="  << mA[i] << endl;
    bin_mA[i]=0.5*(mA[i]+mA[i+1]);
    //cout << "bin_mA["<<i<<"]="  << bin_mA[i] << endl;
  }
  bin_mA[50]=605;

  // This is the variable bin histogram tanbeta vs mA (to be used)
  TH2F* hggA=new TH2F("hggA","ggA cross section vs tan#beta,m_{A}; m_{A} GeV; tan#beta",sizeof(bin_mA)/sizeof(Double_t)-1,bin_mA,sizeof(bin_tb)/sizeof(Double_t)-1,bin_tb);
  hggA->Sumw2();
  hggA->GetYaxis()->SetRangeUser(0.1,100.);
  hggA->GetXaxis()->SetRangeUser(225.,600.);
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

  double mAlimits[51];
  TString limitFname[51];
  for (unsigned int i=1; i<51; ++i) {
    mAlimits[i-1]=mA[i];
    cout << "mA " << mA[i] << " " << Form("Low2D_M%.0f.txt",mA[i]) << endl;
    if (mA[i]<=285) limitFname[i-1]=Form("Low2D_M%.0f.txt",mA[i]);
    else if (mA[i]<=370) limitFname[i-1]=Form("Int2D_M%.0f.txt",mA[i]);
    else limitFname[i-1]=Form("High2D_M%.0f.txt",mA[i]);
  }

  lim limits[51];
  for (unsigned int i=0; i<50; ++i) {
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
  double expTb[50],expTbM1s[50],expTbM2s[50],expTbP1s[50],expTbP2s[50],obsLimTb[50];

  for (unsigned int i=0; i<50; ++i) {
    findTB(hggA, limits[i]);
    expTb[i]=limits[i].expTb;
    expTbM1s[i]=limits[i].expM1sTb-expTb[i];
    expTbM2s[i]=limits[i].expM2sTb-expTb[i];
    expTbP1s[i]=expTb[i]-limits[i].expP1sTb;
    expTbP2s[i]=expTb[i]-limits[i].expP2sTb;
    obsLimTb[i]=limits[i].obsLimTb;
  }

  // I need to create a TGraph with the values I found
  

  TGraph* expG=new TGraph(50,mAlimits,expTb);
  expG->SetLineWidth(2);
  expG->SetLineStyle(2);
  TGraphAsymmErrors* exp1sG=new TGraphAsymmErrors(50,mAlimits,expTb,0,0,expTbP1s,expTbM1s);
  exp1sG->SetLineWidth(2);
  exp1sG->SetLineStyle(2);
  exp1sG->SetFillColor(kGreen);
  TGraphAsymmErrors* exp2sG=new TGraphAsymmErrors(50,mAlimits,expTb,0,0,expTbP2s,expTbM2s);
  exp2sG->SetLineWidth(2);
  exp2sG->SetLineStyle(2);
  exp2sG->SetFillColor(kYellow);
  TGraph* obsG=new TGraph(50,mAlimits,obsLimTb);
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
  TH2F *hr = new TH2F("hr", ";m_{A} [GeV] ;tan#beta", 2, 200., 620., 2, 0.1, 10);
  hr->GetYaxis()->SetTitleOffset(1.0);
  hr->GetXaxis()->SetTitleOffset(1.0);
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
  tl.SetTextSize(0.05); // 
  tl.DrawLatex(0.15,0.84,goodName);
  tl.DrawLatex(0.15,0.77,goodType);
  tl.SetTextSize(0.04); // 
  tl.DrawLatex(0.20,0.70,goodMu);
  Leg->Draw();
  cms(19.7);

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
  cout << "Calculating limit on tb for mA = " << limit.mA << endl;
  limit.obsLimTb=findTB(hggA, limit.mA, limit.obsLim);
  limit.expTb=findTB(hggA, limit.mA, limit.exp);
  limit.expM2sTb=findTB(hggA, limit.mA, limit.expM2s);
  limit.expM1sTb=findTB(hggA, limit.mA, limit.expM1s);
  limit.expP1sTb=findTB(hggA, limit.mA, limit.expP1s);
  limit.expP2sTb=findTB(hggA, limit.mA, limit.expP2s);
  if (limit.expM1sTb> limit.expP1sTb) {
    double tmp=limit.expM1sTb;
    limit.expM1sTb=limit.expP1sTb;
    limit.expP1sTb=tmp;
  }
  if (limit.expM2sTb> limit.expP2sTb) {
    double tmp=limit.expM2sTb;
    limit.expM2sTb=limit.expP2sTb;
    limit.expP2sTb=tmp;
  }
  cout << " exp: " << limit.exp << " => " << limit.expTb << " obs: " << limit.obsLim << " => " << limit.obsLimTb << endl;
  cout << " exp1s: " << limit.expM1s << " => " << limit.expM1sTb << " , " << limit.expP1s << " => " << limit.expP1sTb << endl;
  cout << " exp2s: " << limit.expM2s << " => " << limit.expM2sTb << " , " << limit.expP2s << " => " << limit.expP2sTb << endl;
}

double  findTB(TH2* hggA, const double& mA, const double& zGood) {
  // loop trough all bin of a given mA
  //
  //
  // cout << " Z: " << zGood ;
  int nBinsY=hggA->GetNbinsY();
  int ibx=hggA->GetXaxis()->FindBin(mA);
  double zlow=10000;
  double zhigh=0;
  double tblow, tbhigh;
  for (unsigned int iby=1; iby<nBinsY; ++iby) {
    double z=hggA->GetBinContent(ibx,iby);
    // cout << " z "  << z << endl;
    if (z>0) {
      // cout << "XS*BR(" << mA << ","<< hggA->GetYaxis()->GetBinCenter(iby)<< ")=" << z << " " << zGood << endl;
      if (z>zGood && z<=zlow) {
        zlow=z; 
        tblow=hggA->GetYaxis()->GetBinCenter(iby);
        // cout << " zlow " << zlow << " tblow " << tblow << endl;
      }
      if (z<zGood && z>=zhigh) {
        zhigh=z; 
        tbhigh=hggA->GetYaxis()->GetBinCenter(iby);
        // cout << " zhigh " << zhigh << " tbhigh " << tbhigh << endl;
      }
    }
  }
  double tb=tblow+(tbhigh-tblow)/(zhigh-zlow)*(zGood-zlow);
  // cout << " tb " << tb << endl;
  return tb;
}


// void  findTB(TH2* hggA, lim& limit) {
//   cout << "Calculating limit on tb for mA = " << limit.mA ;
//   limit.obsLimTb=findTB(hggA, limit.mA, limit.obsLim);
//   limit.expTb=findTB(hggA, limit.mA, limit.exp);
//   limit.expM2sTb=findTB(hggA, limit.mA, limit.expM2s);
//   limit.expM1sTb=findTB(hggA, limit.mA, limit.expM1s);
//   limit.expP1sTb=findTB(hggA, limit.mA, limit.expP1s);
//   limit.expP2sTb=findTB(hggA, limit.mA, limit.expP2s);
//   cout << " exp: " << limit.expTb << " obs: " << limit.obsLimTb << endl;
//   cout << " exp1s: " << limit.expM1sTb << " , " << limit.expP1sTb << endl;
//   cout << " exp2s: " << limit.expM2sTb << " , " << limit.expP2sTb << endl;
// }

// double  findTB(TH2* hggA, const double& mA, const double& zGood) {
//   // loop trough all bin of a given mA
//   //
//   //
//   int nBinsY=hggA->GetNbinsY();
//   int ibx=hggA->GetXaxis()->FindBin(mA);
//   double zlow=10000;
//   double zhigh=0;
//   double tblow, tbhigh;
//   for (unsigned int iby=1; iby<nBinsY; ++iby) {
//     double z=hggA->GetBinContent(ibx,iby);
//     // cout << "XS*BR(" << limit.mA << ","<< hggA->GetYaxis()->GetBinCenter(iby)<< ")=" << z << " " << limit.exp << endl;
//     if (z>zGood && z<=zlow) {
//       zlow=z; 
//       tblow=hggA->GetYaxis()->GetBinCenter(iby);
//     }
//     if (z<zGood && z>=zhigh) {
//       zhigh=z; 
//       tbhigh=hggA->GetYaxis()->GetBinCenter(iby);
//     }
//   }
//   // cout << "zlow " << zlow << " zhigh " << zhigh << endl;
//   // cout << "tblow " << tblow << " tbhigh " << tbhigh << endl;
//   double tb=tblow+(tbhigh-tblow)/(zhigh-zlow)*(zGood-zlow);
//   //cout << "tb " << tb << endl;
//   return tb;
// }
