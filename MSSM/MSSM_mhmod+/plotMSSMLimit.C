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

  TString ttype("_MSSM_mhmod+");

  TString cname("Limit"+ttype);
  //
  TString goodName=("A#rightarrowZh#rightarrowllbb");
  TString goodType("MSSM m^{h}_{mod+}");


  TString ok(""); // possible additional selection


  // Read trees with results from SuShi and 2HDMC
  TChain* ch=new TChain("TreeMSSM");

  ch->Add("lsf_working_dir_M225_20952785/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M230_20952786/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M235_20952787/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M240_20952788/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M245_20952789/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M250_20952790/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M255_20952791/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M260_20952792/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M265_20952793/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M270_20952794/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M275_20952795/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M280_20952796/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M285_20952797/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M290_20952798/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M295_20952799/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M300_20952800/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M305_20952801/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M310_20952802/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M315_20952803/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M320_20952804/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M325_20952805/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M330_20952806/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M335_20952807/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M340_20952808/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M345_20952809/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M350_20952810/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M360_20952811/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M370_20952812/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M380_20952813/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M390_20952814/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M400_20952815/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M410_20952816/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M420_20952817/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M430_20952818/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M440_20952819/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M450_20952820/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M460_20952821/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M470_20952822/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M480_20952823/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M490_20952824/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M500_20952825/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M510_20952826/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M520_20952827/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M530_20952828/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M540_20952829/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M550_20952830/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M560_20952831/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M570_20952832/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M580_20952833/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M590_20952834/parameter_MSSM.root");
  ch->Add("lsf_working_dir_M600_20952835/parameter_MSSM.root");


  // Create a variable binning histogram following the granularity used in the MC generation
  //
  // for tanBeta
  double tanbeta[61]={0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1500,2000,3000,4000,5000,6000};
  Double_t bin_tb[60];
  for (unsigned int i=0; i<60; i++) {
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

  Double_t bin_cba[52];
  bin_cba[0]=-0.01;
  for (unsigned int i=1; i<=50; ++i) {
    bin_cba[i]=-0.01+1.*i/50;
    //cout << "bin_cba["<<i<<"]="  << bin_cba[i] << endl;
  }
  bin_cba[51]=1.01;

  // for (unsigned int i=0; i<52; ++i) {
  //   cout << "bin_mA["<<i<<"]="  << bin_mA[i] << endl;
  // }
  // This is the variable bin histogram tanbeta vs mA (to be used)
  TH2F* hggA=new TH2F("hggA","ggA cross section vs tan#beta,m_{A}; m_{A} GeV; tan#beta",sizeof(bin_mA)/sizeof(Double_t)-1,bin_mA,sizeof(bin_tb)/sizeof(Double_t)-1,bin_tb);
  hggA->Sumw2();
  hggA->GetYaxis()->SetRangeUser(0.15,100.);
  hggA->GetXaxis()->SetRangeUser(225.,600.);
  TString cut=what+ok;
  cout << "CUT: " << cut << endl;

  // Here I project the tree into the histograms
  ch->Project("hggA","tb:mA",cut);


  // Set style to draw
  TStyle *tdrStyle = gROOT->GetStyle("tdrStyle");
  tdrStyle->SetOptStat(0);
  // tdrStyle->SetPadGridX(true);
  // tdrStyle->SetPadGridY(true);
  // tdrStyle->SetPadTopMargin(0.05);
  // tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetTitleYOffset(1.);
  tdrStyle->SetTitleXOffset(1.2);
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
    //cout << "opening " << limitFname[i] << endl;
    std::ifstream infile(limitFname[i].Data());

    double obsLim , expM2s ,   expM1s , exp , expP1s , expP2s , sign , pValue , bestFitR , bestFitRUp , bestFitRDow ;
    infile >> obsLim >> expM2s >>   expM1s >> exp >> expP1s >> expP2s >> sign >> pValue >> bestFitR >> bestFitRUp >> bestFitRDow ;
    // cout << " mA: " << mAlimits[i]
    //   << " obsLim: " << obsLim 
    //   << " expM2s: " << expM2s 
    //   << " expM1s: " << expM1s 
    //   << " exp: " << exp 
    //   << " expP1s: " << expP1s 
    //   << " expP2s: " << expP2s 
    //   << " sign: " << sign 
    //   << " pValue: " << pValue 
    //   << " bestFitR: " << bestFitR 
    //   << " bestFitRUp: " << bestFitRUp
    //   << " bestFitRDow: " << bestFitRDow 
    //   << endl;

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
    //if (mA[i]!=400) continue;
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
  //TH2F *hr = new TH2F("hr", ";m_{A} [GeV] ;tan#beta", 2, 200., 620., 2, 0.1, 10);
  TH2F *hr = new TH2F("hr", ";m_{A} [GeV] ;tan#beta", 2, 200., 620., 2, 0.1, 5.);
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
  tl.DrawLatex(0.62,0.54,goodName);
  tl.DrawLatex(0.62,0.45,goodType);
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
  //cout << " Z: " << zGood ;
  int nBinsY=hggA->GetNbinsY();
  int ibx=hggA->GetXaxis()->FindBin(mA);
  double zlow=10000;
  double zhigh=0;
  double tblow, tbhigh;
  for (unsigned int iby=1; iby<nBinsY; ++iby) {
    double z=hggA->GetBinContent(ibx,iby);
    if (z>0) {
      //cout << "XS*BR(" << mA << ","<< hggA->GetYaxis()->GetBinCenter(iby)<< ")=" << z << " " << zGood << endl;
      if (z>zGood && z<=zlow) {
        zlow=z; 
        tblow=hggA->GetYaxis()->GetBinCenter(iby);
        //cout << " zlow " << zlow << " tblow " << tblow << endl;
      }
      if (z<zGood && z>=zhigh) {
        zhigh=z; 
        tbhigh=hggA->GetYaxis()->GetBinCenter(iby);
        //cout << " zhigh " << zhigh << " tbhigh " << tbhigh << endl;
      }
    }
  }
  double tb=tblow+(tbhigh-tblow)/(zhigh-zlow)*(zGood-zlow);
  //cout << " tb " << tb << endl;
  return tb;
}
