void plotMSSM_mA() {
  TFile *_file0 = TFile::Open("Run_M400/parameter_MSSM.root");

  const TString what="(ggA+bbA)*BRAZh*BRhbb";
  const double BRZll=0.06726;
  const double fb2pb=1000;
  TString scale(Form("*%f*%f",BRZll,fb2pb));
  // Add also BR of Z->ll and move to fb
  what+=scale;

  
  //double tanbeta[51]={0,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,500,550,580,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1500,2000,3000,4000,5000,6000};
  double tanbeta[61]={0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1500,2000,3000,4000,5000,6000};
  Double_t bin_tb[60];
  for (unsigned int i=0; i<60; i++) {
    bin_tb[i]=0.005*(tanbeta[i]+tanbeta[i+1]);
    cout << "bin_tb[" << i << "]=" << bin_tb[i] << " " << tanbeta[i+1]/100. << endl;
  }

  TH1F* htb=new TH1F("htb","",sizeof(bin_tb)/sizeof(Double_t)-1,bin_tb);
  //htb->GetXaxis()->SetRangeUser(0.,1.);

  TreeMSSM->Project("htb","tb",what);
  //TreeMSSM->Project("htb","tb");

  htb->Draw();

  for (unsigned int i=1; i<htb->GetNbinsX(); ++i) {
    cout << "bin " << htb->GetBinCenter(i) << " : " << htb->GetBinContent(i) << endl;
  }

}
