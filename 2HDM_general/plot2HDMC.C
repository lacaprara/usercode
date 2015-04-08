//void plot2HDMC(const TString& what="(bbA+ggA)*BRAZh*BRhbb", int m=300, int type=1){}
void plot2HDMC(const TString& what="(bbA+ggA)*BRAZh", int m=300, int type=2){
  // const double BRZll=0.06726;
  // const double fb2pb=1000;
  // TString scale(Form("*%f*%f",BRZll,fb2pb));
  TString scale("");

  TString mass(Form("_M%d",m));
  TString ttype(Form("_T%d",type));
  TString cname(what+mass+ttype);
  cname.ReplaceAll("*","x");
  cname.ReplaceAll("(","U");
  cname.ReplaceAll(")","U");
  //
  TString goodName(what);
  goodName.ReplaceAll("ggA","#sigma_{gg#rightarrowA}");
  goodName.ReplaceAll("bbA","#sigma_{bb#rightarrowA}");
  goodName.ReplaceAll("BRAZh","B(A#rightarrowZh)");
  goodName.ReplaceAll("BRhbb","B(h#rightarrowbb)");
  goodName+=("*B(Z#rightarrowll)");
  goodName+=("[fb] ");
  TString goodMass(Form("m_{A}=%d GeV",m));
  TString goodType(Form("Type %d 2HDM ",type));
  //goodName=("#sigma*B(pp#rightarrowA#rightarrowZh#rightarrowllbb) [fb]");
  //goodName=("#sigma*B(pp#rightarrowA) [fb]");
  goodName=("#sigma*Br(A#rightarrowZh)");
  //goodName=("BR(h#rightarrowbb)");

  //if (m>0) mass=(Form(" * (mA==%d)",m));
  //TString ok(" * validity * stability * perturbativity * unitarity ");
  //TString ok(" * unitarity");
  TString ok("");

  cout << "Creating canvas " << cname << endl;
  TCanvas* c1=new TCanvas(cname,goodName+goodMass+goodType,1200,600);
  cout << " done " << c1->GetName() << endl;

  c1->Divide(2);

  TChain* ch=new TChain("Tree2HDM");

  if (type==1) { // 2HDM type 1
    switch (m) {
      case 225:
        //ch->Add("Old/lsf_working_dir_M225_Type1_20598725/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M225_Type1_20759756//parameter_2HDM.root");
        break;
      case 250:
        //ch->Add("Old/lsf_working_dir_M250_Type1_20598726/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M250_Type1_20759757//parameter_2HDM.root");
        break;
      case 275:
        //ch->Add("Old/lsf_working_dir_M275_Type1_20598727/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M275_Type1_20759758//parameter_2HDM.root");
        break;
      case 300:
        //ch->Add("Old/lsf_working_dir_M300_Type1_20598728/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M300_Type1_20759759//parameter_2HDM.root");
        break;
      case 325:
        //ch->Add("Old/lsf_working_dir_M325_Type1_20598729/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M325_Type1_20759760//parameter_2HDM.root");
        break;
      case 350:
        //ch->Add("Old/lsf_working_dir_M350_Type1_20598730/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M350_Type1_20759761///parameter_2HDM.root");
        break;
      case 400:
        //ch->Add("Old/lsf_working_dir_M400_Type1_20598731/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M400_Type1_20759762///parameter_2HDM.root");
        break;
      case 500:
        //ch->Add("Old/lsf_working_dir_M500_Type1_20598732/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M500_Type1_20759763///parameter_2HDM.root");
        break;
      case 600:
        //ch->Add("Old/lsf_working_dir_M600_Type1_20598733/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M600_Type1_20759764///parameter_2HDM.root");
        break;
      default:
        cout << "No mass defined!" << endl;
    }
  }
  if (type==2) { // type 2
    switch (m) {
      case 225:
        //ch->Add("Old/lsf_working_dir_M225_Type2_20598734/parameter_2HDM.root");
        ch->Add("lsf_working_dir_M225_Type2_20759765/parameter_2HDM.root");
        break;
      case 250:
        //ch->Add("Old/lsf_working_dir_M250_Type2_20598735//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M250_Type2_20759766/parameter_2HDM.root");
        break;
      case 275:
        //ch->Add("Old/lsf_working_dir_M275_Type2_20598736//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M275_Type2_20759767/parameter_2HDM.root");
        break;
      case 300:
        //ch->Add("Old/lsf_working_dir_M300_Type2_20598737//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M300_Type2_20759768/parameter_2HDM.root");
        break;
      case 325:
        //ch->Add("Old/lsf_working_dir_M325_Type2_20598738//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M325_Type2_20759769/parameter_2HDM.root");
        break;
      case 350:
        //ch->Add("Old/lsf_working_dir_M350_Type2_20598739//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M350_Type2_20759770/parameter_2HDM.root");
        break;
      case 400:
        //ch->Add("Old/lsf_working_dir_M400_Type2_20598740//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M400_Type2_20759771/parameter_2HDM.root");
        break;
      case 500:
        //ch->Add("Old/lsf_working_dir_M500_Type2_20598741//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M500_Type2_20759772/parameter_2HDM.root");
        break;
      case 600:
        //ch->Add("Old/lsf_working_dir_M600_Type2_20598742//parameter_2HDM.root");
        ch->Add("lsf_working_dir_M600_Type2_20759773/parameter_2HDM.root");
        break;
      default:
        cout << "No mass defined!" << endl;
    }
  }

  //double tanbeta[30]={1,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,220,240,260,280,300,400,500,600,700,800,900,1000,1100,10000};
  //double tanbeta[30]={1,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,220,240,260,280,300,400,500,600,700,800,900,1000,10000,100000};
  double tanbeta[39]={1,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,220,240,260,280,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,5000,10000,100000};
  Double_t bin_tb[38];
  Double_t bin_b[38];
  for (unsigned int i=0; i<38; i++) {
    bin_tb[i]=0.005*(tanbeta[i]+tanbeta[i+1]);
    bin_b[i]=atan(bin_tb[i]);
    //cout << "bin_tb[" << i << "]=" << bin_tb[i] << " " << tanbeta[i+1]/100. << endl;
    //cout << "bin_tb[" << i << "]=" << bin_tb[i] << " " << bin_b[i] << endl;
  }
  bin_tb[37]=150;

  Double_t bin_cba[102];
  bin_cba[0]=-1.01;
  for (unsigned int i=1; i<=100; ++i) {
    bin_cba[i]=-1.01+1.*i/50;
    //cout << "bin_cba["<<i<<"]="  << bin_cba[i] << endl;
  }
  bin_cba[101]=1.01;

  TH2F* hbetacba=new TH2F("hbetacba","ggA cross section vs #beta,cos(#beta-#alpha); cos(#beta-#alpha); #beta",101,bin_cba,37,bin_b);

  TH2F* hggA=new TH2F("hggA","ggA cross section vs tan#beta,cos(#beta-#alpha); cos(#beta-#alpha); tan#beta",101,bin_cba,37,bin_tb);
  hggA->Sumw2();
  TString cut=what+scale+ok;
  cout << "CUT: " << cut << " Mass " << m << endl;
  ch->Project("hggA","tb:cba",cut);
  ch->Project("hbetacba","atan(tb):cba",cut+"* (abs(cba)<0.65)");

  TStyle *tdrStyle = gROOT->GetStyle("tdrStyle");
  // Double_t level[15]={.01,.02,.05,.1,.2,.5,1.,2.,5.,10.,20.,50.,100.,200.,500.};
  // hggA->SetContour(14,level);
  // hggA->SetMinimum(level[0]);
  //
  //Double_t level[10]={1.,5.,10.,20.,50.,100.,200.,500.,800.,1000.};
  Double_t level[10]={.01,.1,.2,0.5,0.6,0.65,0.7,0.75,0.8,0.9};
  hggA->SetContour(9,level);
  hggA->SetMinimum(level[0]);

  Double_t levelb[10]={0.005,0.1,0.4,0.5,1,5,10,50,100};
  hbetacba->SetContour(8,levelb);
  hbetacba->SetMinimum(levelb[0]);

  // DRAW
  tdrStyle->SetOptStat(0);
  // tdrStyle->SetPadGridX(true);
  // tdrStyle->SetPadGridY(true);
  // tdrStyle->SetPadTopMargin(0.05);
  // tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetTitleXOffset(1.6);
  tdrStyle->SetTitleOffset(1.3,"Z");
  // tdrStyle->SetOptLogz(1);
  // tdrStyle->SetOptLogy(1);
  tdrStyle->SetPadRightMargin(0.14);
  //tdrStyle->SetPalette(1);


  tdrStyle->cd();
  gROOT->ForceStyle();


  c1->cd(1);
  //hggA->DrawCopy("lego2");
  hbetacba->DrawCopy("lego2");
  //gPad->SetLogz();
  gPad->SetLogy();
  gPad->SetPhi(120);
  //gPad->SetPhi(60);
  gPad->SetTheta(30);
  gPad->UseCurrentStyle();
  gPad->Update();

  TLatex tl;
  tl.SetTextSize(0.04);
  tl.SetNDC();
  tl.DrawLatex(0.1,0.95,goodName);
  tl.DrawLatex(0.1,0.90,goodMass);
  tl.DrawLatex(0.1,0.85,goodType);

  c1->cd(2);
  // tdrStyle->SetPadLeftMargin(0.25);

  gPad->UseCurrentStyle();
  gPad->Update();
  hggA->GetXaxis()->SetTitleOffset(1.1);
  hggA->GetZaxis()->SetTitleOffset(100);
  hggA->Smooth();
  hggA->DrawCopy("zcont1");
  hbetacba->GetXaxis()->SetTitleOffset(1.1);
  hbetacba->GetZaxis()->SetTitleOffset(100);
  //hggA->Smooth();
  hbetacba->DrawCopy("zcont1");

  // TH1F* test=new TH1F("test","ggA cross section vs tan#beta; tan#beta",27,bin_tb);
  // ch->Project("test","tb",what);
  // test->Draw();


  TCanvas* c2=new TCanvas(cname+"Obs",goodName+goodMass+goodType,800,800);
  gPad->UseCurrentStyle();
  gPad->Update();
  // hggA->GetXaxis()->SetTitleOffset(1.1);
  // hggA->GetYaxis()->SetTitleOffset(1.1);
  // hggA->DrawCopy("cont list");
  hbetacba->GetXaxis()->SetTitleOffset(1.1);
  hbetacba->GetYaxis()->SetTitleOffset(1.1);
  hbetacba->DrawCopy("cont list");
  gPad->Update();

  // Get Contours
  TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
  TList* contLevel = NULL;
  TGraph* curv     = NULL;
  TGraph* gc       = NULL;

  Int_t nGraphs    = 0;
  Int_t TotalConts = 0;

  if (conts == NULL){
    printf("*** No Contours Were Extracted!\n");
    TotalConts = 0;
    return;
  } else {
    TotalConts = conts->GetSize();
  }

  printf("TotalConts = %d\n", TotalConts);

  for(i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);
    printf("Contour %d has %d Graphs\n", i, contLevel->GetSize());
    nGraphs += contLevel->GetSize();
  }

  nGraphs = 0;

  //TH2F *hr = new TH2F("hr", ";cos(#beta-#alpha);tan#beta", 2, -1, 1, 2, 0.05, 100);
  // hr->GetXaxis()->SetTitleOffset(1.1);
  // hr->GetYaxis()->SetTitleOffset(1.2);
  // hr->GetYaxis()->SetNdivisions(110,kFALSE);
  // hr->GetXaxis()->SetNdivisions(20205,kFALSE);

  TH2F *hr = new TH2F("hr", ";cos(#beta-#alpha);#beta", 2, -0.6, 0.6, 2, 0, 3.1415/2.);
  hr->GetXaxis()->SetTitleOffset(1.1);
  hr->GetYaxis()->SetTitleOffset(1.2);
  hr->GetYaxis()->SetNdivisions(204,kFALSE);
  hr->GetXaxis()->SetNdivisions(506,kFALSE);
  hr->Draw();
  Double_t x0, y0, z0;
  TLatex l;
  l.SetTextSize(0.03);
  l.SetTextAlign(22);
  char val[20];

  int jjj=5;
  for(i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);
    //z0 = level[i];
    z0 = levelb[i];
    printf("Z-Level Passed in as:  Z = %f\n", z0);

    // Get first graph from list on curves on this level
    curv = (TGraph*)contLevel->First();
    for(j = 0; j < contLevel->GetSize(); j++){
      // last point
      curv->GetPoint(curv->GetN()/3+(jjj++), x0, y0);
      // first point
      //curv->GetPoint((jjj+=2), x0, y0);
      //curv->GetPoint((jjj+=5), x0, y0);

      // if (z0<0) curv->SetLineColor(kRed);
      // if (z0>0) curv->SetLineColor(kBlue);
      nGraphs ++;
      printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());

      // Draw clones of the graphs to avoid deletions in case the 1st
      // pad is redrawn.
      gc = (TGraph*)curv->Clone();
      gc->Draw("C");

      if (z0>=.001) sprintf(val,"%0.3f",z0);
      if (z0>=.01) sprintf(val,"%0.2f",z0);
      if (z0>=.1) sprintf(val,"%0.1f",z0);
      if (z0>=1) sprintf(val,"%0.0f",z0);
      l.DrawLatex(x0*0.99,y0,val);
      curv = (TGraph*)contLevel->After(curv); // Get Next graph
    }
  }
  //gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.10);
  c2->Update();
  printf("\n\n\tExtracted %d Contours and %d Graphs \n", TotalConts, nGraphs );



  tl.SetTextAlign(31);
  tl.DrawLatex(0.8,0.25,goodName);

  tl.SetTextAlign(11);
  tl.DrawLatex(0.13,0.96,goodType+": "+goodMass);


  pCan(c2,cname+"_BW");

  c1->cd(1);
  gPad->SetLogy();
  gPad->SetLogz();
  c1->cd(2);
  gPad->SetLogy();
  c1->Update();
  pCan(c1,cname);
}

void plotAllMass(TString what="ggA*BRAZh") {
  for (int t=1; t<=2; ++t) {
    plot2HDMC(what,225,t);
    plot2HDMC(what,250,t);
    plot2HDMC(what,275,t);
    plot2HDMC(what,300,t);
    plot2HDMC(what,325,t);
    plot2HDMC(what,350,t);
    plot2HDMC(what,400,t);
    plot2HDMC(what,500,t);
    plot2HDMC(what,600,t);
  }
  
}


void plotAllMassLimit(TString what="ggA*BRAZh*0.06726/1000.") {
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
    //plot2HDMC(what,225,t,"Low2D_M225.txt");
    // plot2HDMC(what,250,t);
    // plot2HDMC(what,275,t);
    plot2HDMC(what,300,t);
    // plot2HDMC(what,325,t);
    // plot2HDMC(what,350,t);
    // plot2HDMC(what,400,t);
    // plot2HDMC(what,500,t);
    // plot2HDMC(what,600,t);
  }
  
}
