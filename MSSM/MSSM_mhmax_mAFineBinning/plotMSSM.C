void plotMSSM(const TString& what="(ggA+bbA)*BRAZh*BRhbb"){
  const double BRZll=0.06726;
  const double fb2pb=1000;
  TString scale(Form("*%f*%f",BRZll,fb2pb));
  TString scale("");

  TString cname(what);
  cname.ReplaceAll("*","x");
  cname.ReplaceAll("(","U");
  cname.ReplaceAll(")","U");
  cname+="_MSSM_mhmax";
  //
  TString goodName(what);
  goodName.ReplaceAll("mh","m_{h}");
  goodName.ReplaceAll("ggA","#sigma_{gg#rightarrowA}");
  goodName.ReplaceAll("bbA","#sigma_{bb#rightarrowA}");
  goodName.ReplaceAll("BRAZh","B(A#rightarrowZh)");
  goodName.ReplaceAll("BRhbb","B(h#rightarrowbb)");
  //goodName+=("*B(Z#rightarrowll)");
  //goodName+=("[fb] ");
  goodName+=("[pb] ");
  //goodName+=("[GeV] ");
  TString goodType("MSSM m_{h}^{max}");
  //goodName=("#sigma*B(pp#rightarrowA#rightarrowZh#rightarrowllbb) [fb]");
  //goodName=("#sigma*B(pp#rightarrowA) [fb]");
  //goodName=("BR(A#rightarrowZh)");
  //goodName=("BR(h#rightarrowbb)");

  //if (m>0) mass=(Form(" * (mA==%d)",m));
  //TString ok(" * validity * stability * perturbativity * unitarity ");
  //TString ok(" * unitarity");
  TString ok("");


  TChain* ch=new TChain("TreeMSSM");

  ch->Add("Run_M225/parameter_MSSM.root");
  ch->Add("Run_M230/parameter_MSSM.root");
  ch->Add("Run_M235/parameter_MSSM.root");
  ch->Add("Run_M240/parameter_MSSM.root");
  ch->Add("Run_M245/parameter_MSSM.root");
  ch->Add("Run_M250/parameter_MSSM.root");
  ch->Add("Run_M255/parameter_MSSM.root");
  ch->Add("Run_M260/parameter_MSSM.root");
  ch->Add("Run_M265/parameter_MSSM.root");
  ch->Add("Run_M270/parameter_MSSM.root");
  ch->Add("Run_M275/parameter_MSSM.root");
  ch->Add("Run_M280/parameter_MSSM.root");
  ch->Add("Run_M285/parameter_MSSM.root");
  ch->Add("Run_M290/parameter_MSSM.root");
  ch->Add("Run_M295/parameter_MSSM.root");
  ch->Add("Run_M300/parameter_MSSM.root");
  ch->Add("Run_M305/parameter_MSSM.root");
  ch->Add("Run_M310/parameter_MSSM.root");
  ch->Add("Run_M315/parameter_MSSM.root");
  ch->Add("Run_M320/parameter_MSSM.root");
  ch->Add("Run_M325/parameter_MSSM.root");
  ch->Add("Run_M330/parameter_MSSM.root");
  ch->Add("Run_M335/parameter_MSSM.root");
  ch->Add("Run_M340/parameter_MSSM.root");
  ch->Add("Run_M345/parameter_MSSM.root");
  ch->Add("Run_M350/parameter_MSSM.root");
  ch->Add("Run_M360/parameter_MSSM.root");
  ch->Add("Run_M370/parameter_MSSM.root");
  ch->Add("Run_M380/parameter_MSSM.root");
  ch->Add("Run_M390/parameter_MSSM.root");
  ch->Add("Run_M400/parameter_MSSM.root");
  ch->Add("Run_M410/parameter_MSSM.root");
  ch->Add("Run_M420/parameter_MSSM.root");
  ch->Add("Run_M430/parameter_MSSM.root");
  ch->Add("Run_M440/parameter_MSSM.root");
  ch->Add("Run_M450/parameter_MSSM.root");
  ch->Add("Run_M460/parameter_MSSM.root");
  ch->Add("Run_M470/parameter_MSSM.root");
  ch->Add("Run_M480/parameter_MSSM.root");
  ch->Add("Run_M490/parameter_MSSM.root");
  ch->Add("Run_M500/parameter_MSSM.root");
  ch->Add("Run_M510/parameter_MSSM.root");
  ch->Add("Run_M520/parameter_MSSM.root");
  ch->Add("Run_M530/parameter_MSSM.root");
  ch->Add("Run_M540/parameter_MSSM.root");
  ch->Add("Run_M550/parameter_MSSM.root");
  ch->Add("Run_M560/parameter_MSSM.root");
  ch->Add("Run_M570/parameter_MSSM.root");
  ch->Add("Run_M580/parameter_MSSM.root");
  ch->Add("Run_M590/parameter_MSSM.root");
  ch->Add("Run_M600/parameter_MSSM.root");


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
  for (unsigned int i=0; i<50; ++i) {
    bin_mA[i]=0.5*(mA[i]+mA[i+1]);
    //cout << "bin_mA["<<i<<"]="  << bin_mA[i] << endl;
  }
  bin_mA[50]=605;
  
  TH2F* hggA=new TH2F("hggA","ggA cross section vs tan#beta,m_{A}; m_{A} GeV; tan#beta",sizeof(bin_mA)/sizeof(Double_t)-1,bin_mA,sizeof(bin_tb)/sizeof(Double_t)-1,bin_tb);
  hggA->Sumw2();
  //hggA->Draw();
  TString cut=what+scale+ok;
  cout << "CUT: " << cut << endl;
  ch->Project("hggA","tb:mA",cut);

  TStyle *tdrStyle = gROOT->GetStyle("tdrStyle");
  // Double_t level[15]={.01,.02,.05,.1,.2,.5,1.,2.,5.,10.,20.,50.,100.,200.,500.};
  // hggA->SetContour(14,level);
  // hggA->SetMinimum(level[0]);
  //
  Double_t level[10]={1.,5.,10.,20.,50.,100.,200.,500.,800.,1000.}; // for x-section
  //Double_t level[10]={100,105,110.,115.,120.,123,125.7,127,130.,135.}; // for mh
  //Double_t level[10]={1,2,3.,4.,120.,123,125.7,127,130.,135.}; // for mh
  //Double_t level[10]={.01,.1,.2,0.5,0.6,0.65,0.7,0.75,0.8,0.9}; // for BR
  //Double_t level[10]={.01,.02,.05,.07,.1,.15,0.2,0.5,0.75,1.}; // for BR
  hggA->SetContour(9,level);
  hggA->SetMinimum(level[0]);
  
  // Double_t level[7]={122.7.,123.7,125.4,126.0,127.7,128.7.,150}; // for mh
  // hggA->SetContour(6,level);
  // hggA->SetMinimum(90);
  // Int_t colors[7] = {kWhite,kGreen,kGreen+2,kBlack,kGreen+2,kGreen,kWhite};
  // tdrStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);

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

  cout << "Creating canvas " << cname << endl;
  TCanvas* c1=new TCanvas(cname,goodName,1200,600);
  cout << " done " << c1->GetName() << endl;
  c1->Divide(2);

  c1->cd(1);
  hggA->DrawCopy("lego2");
  gPad->SetLogz();
  gPad->SetLogy();
  //gPad->SetPhi(120);
  gPad->SetPhi(-150);
  //gPad->SetTheta(30);
  gPad->UseCurrentStyle();
  gPad->Update();

  TLatex tl;
  tl.SetTextSize(0.04);
  tl.SetNDC();
  tl.SetTextAlign(11);
  tl.DrawLatex(0.1,0.95,goodName);
  tl.DrawLatex(0.1,0.89,goodType);

  c1->cd(2);
 // tdrStyle->SetPadLeftMargin(0.25);

  gPad->UseCurrentStyle();
  gPad->Update();
  hggA->GetXaxis()->SetTitleOffset(1.1);
  hggA->GetYaxis()->SetTitleOffset(1.1);
  hggA->GetZaxis()->SetTitleOffset(100);
  //hggA->Smooth();
  gPad->SetLogy(kFALSE);
  hggA->DrawCopy("zcont1");
  tl.DrawLatex(0.5,0.97,goodName);
  tl.SetTextAlign(11);
  tl.DrawLatex(0.2,0.9,goodType);

  TCanvas* ctmp=new TCanvas(cname,goodName,600,600);
  hggA->GetYaxis()->SetRangeUser(0.1,100.);
  hggA->DrawCopy("zcont1");
  tl.DrawLatex(0.83,0.97,goodName);
  tl.SetTextAlign(11);
  tl.DrawLatex(0.2,0.9,goodType);
  pCan(ctmp,cname+"_Lin");

  // TH1F* test=new TH1F("test","ggA cross section vs tan#beta; tan#beta",27,bin_tb);
  // ch->Project("test","tb",what);
  // test->Draw();


  TCanvas* c2=new TCanvas(cname+"Obs",goodName,800,800);
  gPad->UseCurrentStyle();
  gPad->Update();
  hggA->GetXaxis()->SetTitleOffset(1.1);
  hggA->GetYaxis()->SetTitleOffset(1.1);
  hggA->DrawCopy("cont list");
  gPad->Update();

  //return;
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

   TH2F *hr = new TH2F("hr", ";m_{A};tan#beta", 2, 225, 600, 2, 0.1, 100);

   hr->GetXaxis()->SetTitleOffset(1.1);
   hr->GetXaxis()->SetRangeUser(200,650);
   hr->GetYaxis()->SetTitleOffset(1.2);
   hr->GetYaxis()->SetNdivisions(110,kFALSE);
   hr->GetXaxis()->SetNdivisions(20205,kFALSE);
   hr->Draw();
   Double_t x0, y0, z0;
   TLatex l;
   l.SetTextSize(0.03);
   l.SetTextAlign(32);
   char val[20];

   int jjj=2;
   for(i = 0; i < TotalConts; i++){
      contLevel = (TList*)conts->At(i);
      z0 = level[i];
      printf("Z-Level Passed in as:  Z = %f\n", z0);

      // Get first graph from list on curves on this level
      curv = (TGraph*)contLevel->First();
      for(j = 0; j < contLevel->GetSize(); j++){
        // last point
         //curv->GetPoint(curv->GetN()-1, x0, y0);
        // first point
         curv->GetPoint(jjj++, x0, y0);

         // if (z0<0) curv->SetLineColor(kRed);
         // if (z0>0) curv->SetLineColor(kBlue);
         nGraphs ++;
         printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());

	 // Draw clones of the graphs to avoid deletions in case the 1st
	 // pad is redrawn.
         gc = (TGraph*)curv->Clone();
         gc->Draw("C");

         if (z0>=.01) sprintf(val,"%0.2f",z0);
         if (z0>=.1) sprintf(val,"%0.2f",z0);
         if (z0>=1) sprintf(val,"%0.0f",z0);
         l.DrawLatex(x0*0.99,y0,val);
         curv = (TGraph*)contLevel->After(curv); // Get Next graph
      }
   }
   gPad->SetLogy();
   gPad->SetGridx();
   gPad->SetGridy();
   gPad->SetRightMargin(0.05);
   gPad->SetTopMargin(0.10);
   c2->Update();
   printf("\n\n\tExtracted %d Contours and %d Graphs \n", TotalConts, nGraphs );



  tl.SetTextAlign(31);
  tl.DrawLatex(0.93,0.85,goodName);

  tl.SetTextAlign(31);
  tl.DrawLatex(0.93,0.77,goodType);


  pCan(c2,cname+"_BW");

   c1->cd(1);
   gPad->SetLogy();
   gPad->SetLogz();
   c1->cd(2);
   gPad->SetLogy();
   c1->Update();
  pCan(c1,cname);
}

