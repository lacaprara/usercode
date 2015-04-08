// 30-Apr-2014
// Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
// 
// a Macro to plot the limit on tanbeta vs cos(alpha-beta) plane
//



void plot2HDMCLimit(int m=300, int type=1, const TString& fileLimit="Int2D_M300.txt") {

  // What to plot (sigma*BR)
  const TString what="(ggA+0.797*bbA)*BRAZh*BRhbb";
  const double BRZll=0.06726;
  const double fb2pb=1000;
  TString scale(Form("*%f*%f",BRZll,fb2pb));
  // Add also BR of Z->ll and move to fb
  what+=scale;

  TString mass(Form("_M%d",m));
  TString ttype(Form("_T%d",type));

  TString cname("Limit"+mass+ttype);
  //
  TString goodName=("A#rightarrowZh#rightarrowllbb");
  TString goodMass(Form("m_{A}=%d GeV",m));
  TString goodType(Form("Type %s 2HDM ",(type==1?"I":"II")));

  TString ok(""); // possible additional selection


  // Read trees with results from SuShi and 2HDMC
  TChain* ch=new TChain("Tree2HDM");

  if (type==1) { // 2HDM type 1
    switch (m) {
      case 225:
        ch->Add("lsf_working_dir_M225_Type1_20759756//parameter_2HDM.root");
        break;
      case 250:
        ch->Add("lsf_working_dir_M250_Type1_20759757//parameter_2HDM.root");
        break;
      case 275:
        ch->Add("lsf_working_dir_M275_Type1_20759758//parameter_2HDM.root");
        break;
      case 300:
        ch->Add("lsf_working_dir_M300_Type1_20759759//parameter_2HDM.root");
        break;
      case 325:
        ch->Add("lsf_working_dir_M325_Type1_20759760//parameter_2HDM.root");
        break;
      case 350:
        ch->Add("lsf_working_dir_M350_Type1_20759761///parameter_2HDM.root");
        break;
      case 400:
        ch->Add("backup2/lsf_working_dir_M400_Type1_20759762///parameter_2HDM.root");
        break;
      case 500:
        ch->Add("backup2/lsf_working_dir_M500_Type1_20759763///parameter_2HDM.root");
        break;
      case 600:
        ch->Add("backup2/lsf_working_dir_M600_Type1_20759764///parameter_2HDM.root");
        break;
      default:
        cout << "No mass defined!" << endl;
    }
  }
  if (type==2) { // type 2
    switch (m) {
      case 225:
        ch->Add("lsf_working_dir_M225_Type2_20759765/parameter_2HDM.root");
        break;
      case 250:
        ch->Add("lsf_working_dir_M250_Type2_20759766/parameter_2HDM.root");
        break;
      case 275:
        ch->Add("lsf_working_dir_M275_Type2_20759767/parameter_2HDM.root");
        break;
      case 300:
        ch->Add("lsf_working_dir_M300_Type2_20759768/parameter_2HDM.root");
        break;
      case 325:
        ch->Add("lsf_working_dir_M325_Type2_20759769/parameter_2HDM.root");
        break;
      case 350:
        ch->Add("lsf_working_dir_M350_Type2_20759770/parameter_2HDM.root");
        break;
      case 400:
        ch->Add("backup2/lsf_working_dir_M400_Type2_20759771/parameter_2HDM.root");
        break;
      case 500:
        ch->Add("backup2/lsf_working_dir_M500_Type2_20759772/parameter_2HDM.root");
        break;
      case 600:
        ch->Add("backup2/lsf_working_dir_M600_Type2_20759773/parameter_2HDM.root");
        break;
      default:
        cout << "No mass defined!" << endl;
    }
  }


  // Create a variable binning histogram following the granularity used in the MC generation
  //
  // for tanBeta
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

  // for cos(beta-alpha)
  // Double_t bin_cba[102];
  // bin_cba[0]=-1.01;
  // for (unsigned int i=1; i<=100; ++i) {
  //    bin_cba[i]=-1.01+1.*i/50;
  //    //cout << "bin_cba["<<i<<"]="  << bin_cba[i] << endl;
  // }
  // bin_cba[101]=1.01;
  Double_t bin_cba[102];
  bin_cba[0]=-1.;
  for (unsigned int i=0; i<=100; ++i) {
     bin_cba[i]=-0.99+1.*i/50;
     //cout << "bin_cba["<<i<<"]="  << bin_cba[i] << endl;
  }
  bin_cba[101]=1.3;


  // This is the variable bin histogram beta vs cos(#beta-#alpha) (to compare with th papaer)
  TH2F* hbetacba=new TH2F("hbetacba","ggA cross section vs #beta,cos(#beta-#alpha); cos(#beta-#alpha); #beta",101,bin_cba,37,bin_b);
  //TH2F* hggA=new TH2F("hbetacba","ggA cross section vs #beta,cos(#beta-#alpha); cos(#beta-#alpha); #beta",51,bin_cba,28,bin_b);

  // This is the variable bin histogram tanbeta vs cos(#beta-#alpha) (to be used)
  TH2F* hggA=new TH2F("hggA","ggA cross section vs tan#beta,cos(#beta-#alpha); cos(#beta-#alpha); tan#beta",101,bin_cba,37,bin_tb);
  hggA->Sumw2();
  hggA->GetYaxis()->SetRangeUser(0.1,100.);
  TString cut=what+ok;
  cout << "CUT: " << cut << " Mass " << m << endl;

  // Here I project the tree into the histograms
  ch->Project("hggA","tb:cba",cut);
  ch->Project("hbetacba","atan(tb):cba",cut);



  // Set style to draw
  TStyle *tdrStyle = gROOT->GetStyle("tdrStyle");
  tdrStyle->SetOptStat(0);
  // tdrStyle->SetPadGridX(true);
  // tdrStyle->SetPadGridY(true);
  // tdrStyle->SetPadTopMargin(0.05);
  // tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetTitleYOffset(1.1);
  tdrStyle->SetTitleXOffset(1.3);
  tdrStyle->SetTitleOffset(1.3,"Z");
  //tdrStyle->SetPadRightMargin(0.14);
  //tdrStyle->SetPalette(1);


  tdrStyle->cd();
  gROOT->ForceStyle();

  // set countour levels
  // I read the expected and observed limit from a set of external files, provided by Alberto
  cout << "opening " << fileLimit << endl;
  std::ifstream infile(fileLimit.Data());

  double obsLim , expM2s ,   expM1s , exp , expP1s , expP2s , sign , pValue , bestFitR , bestFitRUp , bestFitRDow ;
  infile >> obsLim >> expM2s >>   expM1s >> exp >> expP1s >> expP2s >> sign >> pValue >> bestFitR >> bestFitRUp >> bestFitRDow ;
  cout 
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

  infile.close();


  // Now it is time to plot.
  //
  // First 2D (lego and contour)
  TCanvas* c1=new TCanvas(cname+"_2D",goodName+goodMass+goodType+"_2D",1200,800);

  c1->Divide(2);

  // these levels are the expected limits ones
  Double_t level[7]={0,expM2s, expM1s, exp, expP1s, expP2s,100000};
  hggA->SetContour((sizeof(level)/sizeof(Double_t)),level);
  Int_t colors[7] = {kWhite,kYellow,kGreen,kBlack,kGreen,kYellow,kWhite};
  tdrStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);

  c1->cd(1);
  hggA->DrawCopy("lego2");
  gPad->SetPhi(120);
  gPad->SetTheta(30);
  gPad->UseCurrentStyle();
  gPad->Update();
  gPad->SetLogz();
  gPad->SetLogy();

  TLatex tl;
  tl.SetNDC();
  tl.SetTextAlign(11); // align left
  tl.SetTextSize(0.05); // 
  //tl.SetTextFont(51); // 
  tl.DrawLatex(0.1,0.95,goodName);
  tl.DrawLatex(0.1,0.90,goodMass);
  tl.DrawLatex(0.1,0.85,goodType);

  c1->cd(2);
  // tdrStyle->SetPadLeftMargin(0.25);

  gPad->UseCurrentStyle();
  gPad->SetLogy();
  gPad->Update();
  hggA->GetXaxis()->SetTitleOffset(1.1);
  hggA->GetZaxis()->SetTitleOffset(100);
  //hggA->Smooth();
  hggA->DrawCopy("cont1");

  tl.DrawLatex(0.2,0.2,goodType);
  tl.DrawLatex(0.2,0.15,goodMass);
  tl.DrawLatex(0.16,0.96,goodName);
  cmsPrel(19.7);
//
  pCan(c1,cname+"_2D");

  // 
  // I need to replot it becaouse I want a lin scale on y
  TCanvas* c2=new TCanvas(cname,goodName+goodMass+goodType,800,800);
  gPad->UseCurrentStyle();
  //gPad->SetLogy();
  gPad->Update();
  hggA->GetXaxis()->SetTitleOffset(1.1);
  hggA->GetYaxis()->SetTitleOffset(1.1);
  //hggA->Smooth();
  hggA->Draw("cont Z list");
  gPad->Update();

  // Get Contours as plot by root
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

  //printf("TotalConts = %d\n", TotalConts);

  // The issue is that each contour is made of different graph, because "island" are always possible
  for(i = 0; i < TotalConts; i++){
     contLevel = (TList*)conts->At(i);
     //printf("Contour %d has %d Graphs\n", i, contLevel->GetSize());
     nGraphs += contLevel->GetSize();
  }

  nGraphs = 0;

  // The limit plot
  //  QUELLO GIUSTO
  TCanvas* c3 = new TCanvas("c3","Good Plot",610,0,600,600);
  TMultiGraph *mg = new TMultiGraph();

  //c3->SetTopMargin(0.15);
  c3->SetGridx();
  c3->SetGridy();
  c3->SetLogy();

  // a dummy histo to set the x and y scale
  TH2F *hr = new TH2F("hr", ";cos(#beta-#alpha);tan#beta", 2, -1., 1., 2, 0.1, 100);
  //TH2F *hr = new TH2F("hr", ";cos(#beta-#alpha);#beta", 2, 0., .2, 2, 0, TMath::PiOver2());
  hr->GetXaxis()->SetTitleOffset(1.0);
  hr->GetXaxis()->SetNdivisions(504,kFALSE);
  hr->Draw();

  TLegend* Leg=0;
  if(type==1) Leg=new TLegend(0.65, 0.70, 0.98, 0.90,"95\% CL Limits");
  else if (type==2) Leg=new TLegend(0.15, 0.25, 0.48, 0.45,"95\% CL Limits");
  Leg->SetBorderSize(0); Leg->SetFillStyle(1001); Leg->SetFillColor(kWhite);
  Leg->SetTextSize(0.035);

  Color_t col[5]={kYellow,kGreen, kBlack, kGreen, kYellow };
  Int_t lstyle[5]={1,1,2,1,1};
  Int_t lwidth[5]={+102,+102,2,+102,+102};
  Int_t fstyle[5]={1,1,1,1,1};

  // Loop over the countours
  for(i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);

    // Get first graph from list on curves on this level
    curv = (TGraph*)contLevel->First();

    for(int j = 0; j < contLevel->GetSize(); j++){
      curv->SetLineColor(col[i]);
      curv->SetLineStyle(lstyle[i]);
      curv->SetLineWidth(lwidth[i]);
//      curv->SetFillColor(col[i]);
//      curv->SetFillStyle(fstyle[i]);
      nGraphs ++;
      //printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());

      // Draw clones of the graphs to avoid deletions in case the 1st
      // pad is redrawn.
      gc = (TGraph*)curv->Clone();
      
      // Alberto's modifications
      if(i==3) gc->SetFillColor(kYellow);
      if(i==4) gc->SetFillColor(0);
      // Type 2 and not for expected limit
      if(type==2 && i!=2) { // complete the area polygons with points at the plot edges
        if(gc->GetX()[0]<0.) { // Left side
          gc->SetPoint(gc->GetN(), -1., 0.1);
          gc->SetPoint(gc->GetN(), -1., 100.);
        }
        else { // Right side
          gc->SetPoint(gc->GetN(), 1., 100.);
          gc->SetPoint(gc->GetN(), 1., 0.1);
        }
      }
      mg->Add(gc, (i!=2?"F":""));
      curv = (TGraph*)contLevel->After(curv); // Get Next graph
    }
  }

  // Dummy graph to draw a proper legend
  TGraph* gobs=new TGraph();
  gobs->SetLineColor(kBlack);
  gobs->SetLineStyle(1);
  gobs->SetLineWidth(2);
  Leg->AddEntry(gobs, "Observed", "l");
  // do we like this?
//  TGraph* gobs2=new TGraph();
//  gobs2->SetLineColor(0);
//  gobs2->SetLineWidth(-1002);
//  gobs2->SetFillStyle(3004);
//  Leg->AddEntry(gobs2, "Excluded region", "f");
  TGraph* gexp=new TGraph();
  gexp->SetLineColor(kBlack);
  gexp->SetLineStyle(2);
  gexp->SetLineWidth(2);
  Leg->AddEntry(gexp, "Expected", "l");
  TGraph* gexp1=new TGraph();
  gexp1->SetLineColor(kBlack);
  //gexp1->SetLineStyle(2);
  gexp1->SetLineWidth(2);
  gexp1->SetFillColor(kGreen);
  Leg->AddEntry(gexp1, "Expected #pm1#sigma", "f");
  TGraph* gexp2=new TGraph();
  gexp2->SetLineColor(kBlack);
  //gexp2->SetLineStyle(2);
  gexp2->SetLineWidth(2);
  gexp2->SetFillColor(kYellow);
  Leg->AddEntry(gexp2, "Expected #pm2#sigma", "f");
  
  Leg->SetFillColor(0);

  mg->Draw("C");
  //mg->Draw("F");
  tl.DrawLatex(0.15,0.15,goodType);
  tl.DrawLatex(0.65,0.15,goodMass);
  tl.DrawLatex(0.15,0.96,goodName);
  Leg->Draw();
  cmsPrel(19.7);
  c3->RedrawAxis();

  c3->Update();
  //pCan(c3,cname);


  // Now get Observed limit, same as before
  TCanvas* c4=new TCanvas(cname+"Obs",goodName+goodMass+goodType,800,800);
  c4->cd();

  Double_t levelObs[2]={obsLim,100000};
  TH2* hggAObs=hggA->Clone();
  hggAObs->SetContour((sizeof(levelObs)/sizeof(Double_t)),levelObs);
  // Int_t colors[2] = {kBlack,kWhite};
  // tdrStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);

  gPad->UseCurrentStyle();
  gPad->Update();
  hggAObs->GetXaxis()->SetTitleOffset(1.1);
  hggAObs->GetYaxis()->SetTitleOffset(1.1);
  hggAObs->Draw("cont Z list");
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
     //printf("Contour %d has %d Graphs\n", i, contLevel->GetSize());
     nGraphs += contLevel->GetSize();
  }

  nGraphs = 0;

  for(i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);

    // Get first graph from list on curves on this level
    curv = (TGraph*)contLevel->First();
    for(j = 0; j < contLevel->GetSize(); j++){
      curv->SetLineColor(1);
      curv->SetLineStyle(1);
      curv->SetLineWidth(-1002);
      curv->SetFillStyle(3004);
      curv->SetFillColor(kBlack);
      nGraphs ++;
      //printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());

      // Draw clones of the graphs to avoid deletions in case the 1st
      // pad is redrawn.
      gc = (TGraph*)curv->Clone();
      //cout << "gc " << gc<< endl;
      mg->Add(gc);

      //l.DrawLatex(x0,y0,val);
      curv = (TGraph*)contLevel->After(curv); // Get Next graph
    }
  }
  c4->cd();

  mg->Draw("CS");
  //mg->Draw("F");
  //
  //some text
  tl.DrawLatex(0.16,0.22,goodType);
  tl.DrawLatex(0.16,0.15,goodMass);
  tl.DrawLatex(0.16,0.96,goodName);
  Leg->Draw();
  cmsPrel(19.7);
  c3->Update();

  // save the canvas
  pCan(c3,cname);
}

void plot2HDMCLimit() {
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
