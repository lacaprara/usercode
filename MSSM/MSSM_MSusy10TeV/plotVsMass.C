void plotVsMass(int type=1) {
  const TString what="ggA";
  TStyle *tdrStyle = gROOT->GetStyle("tdrStyle");
  tdrStyle->SetOptStat(0);
  tdrStyle->cd();
  gROOT->ForceStyle();

  TChain* ch=new TChain("Tree2HDM");

  TString ttype(Form("_T%d",type));
  TString cname(what+ttype);
  cname.ReplaceAll("*","x");
  cname.ReplaceAll("(","#");
  cname.ReplaceAll(")","#");

  //TString scale(Form("*%f*%f",BRZll,fb2pb));
  TString scale("");
  //TString ok("* (cba==0.5) ");
  //TString ok("");

  if (type==1) {
    ch->Add("Old/lsf_working_dir_M225_20304694//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M250_20304695//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M275_20304696//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M300_20304697//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M325_20304698//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M350_20304699//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M400_20304700//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M500_20304701//parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M600_20304702//parameter_2HDM.root");
  }
  if (type==2) {
    ch->Add("Old/lsf_working_dir_M225_20285950/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M250_20285951/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M275_20285952/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M300_20285953/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M325_20285954/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M350_20285955/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M400_20285956/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M500_20285957/parameter_2HDM.root");
    ch->Add("Old/lsf_working_dir_M600_20285958/parameter_2HDM.root");
  }


  double ma[11]={200,225,250,275,300,325,350,400,500,600,700};
  Double_t bin_ma[10];
  for (unsigned int i=0; i<10; i++) {
    bin_ma[i]=0.5*(ma[i]+ma[i+1]);
    //cout << "bin_ma[" << i << "]=" << bin_ma[i] << " " << ma[i+1] << endl;
    //cout << "bin_tb[" << i << "]=" << bin_tb[i] << " " << bin_b[i] << endl;
  }


  //TH2F* hggA=new TH2F("hggA","ggA cross section vs tan#beta,cos(#beta-#alpha);  tan#beta; #sigma("+what+")",9,bin_ma,100,0,100);

  TCanvas* c1=new TCanvas(cname,cname,1200,800);
  gPad->SetLogy();


  TLegend* Leg=new TLegend(0.83, 0.6, 0.995, 0.99,"#sigma(gg#rightarrowA) [pb]");
  Leg->SetBorderSize(1);
  //Leg->SetFillStyle(0);
  Leg->SetFillColor(0);

  bool first=true;

  Double_t x0, y0, z0;
  TLatex ll;
  ll.SetTextSize(0.02);
  ll.SetTextAlign(11);

  double tanbeta[8]={0.1,0.2,0.3, 0.5, 1.0, 2.0, 4.0, 10.};
  double color[8]={kRed+1,kOrange+8,kOrange,kGreen+1,kGreen+2,kAzure+6,kBlue,kBlue+3};
  for (int itb=0; itb<8; ++itb) {
    TString hname=Form("hggA_%.0f",(tanbeta[itb]*100.));
    TString hnameBB=Form("hbbA_%.0f",(tanbeta[itb]*100.));
    //cout << "hname " << hname << " " << tanbeta[itb]*100.<< endl;
    TH1F* hggA=new TH1F(hname,"ggA cross section vs tan#beta,cos(#beta-#alpha);  m_{A} [GeV]; #sigma("+what+") [pb]",9,bin_ma);
    hggA->GetXaxis()->SetTitleOffset(1.1);
    hggA->GetYaxis()->SetTitleOffset(1.2);
    hggA->SetLineColor(color[itb]);
    hggA->SetLineWidth(3);
    hggA->SetMinimum(0.01);
    Leg->AddEntry(hggA, Form("tan#beta=%.1f",tanbeta[itb]), "l");


    TH1F* hbbA=new TH1F(hnameBB,"ggA cross section vs tan#beta,cos(#beta-#alpha);  m_{A} [GeV]; #sigma("+what+") [pb]",9,bin_ma);
    hbbA->SetLineColor(color[itb]);
    hbbA->SetLineWidth(3);
    hbbA->SetLineStyle(2);
    //Leg->AddEntry(hggA, Form("tan#beta=%.1f",tanbeta[itb]), "l");

    TString ok(Form("* (cba==0.5) * (abs(tb-%.2f)<0.05)",tanbeta[itb]));
    TString cut=what+scale+ok;
    //cout << "cut " << cut << endl;
    ch->Project(hname,"mA",cut);

    TString cutBB="bbA"+scale+ok;
    //cout << "cut " << cutBB << endl;
    ch->Project(hnameBB,"mA",cutBB);

    if (first) hggA->DrawCopy("L");
    else hggA->DrawCopy("L same");
    hbbA->DrawCopy("L same");

    // x0=hggA->GetBinLowEdge(7);
    // y0=hggA->GetBinContent(7);
    // cout << "x0 " << x0 << " y0 " << y0 << endl;
    // ll.DrawLatex(x0,y0,Form("ggA tan#beta=%.1f",tanbeta[itb]));

    // x0=hbbA->GetBinLowEdge(1);
    // y0=hbbA->GetBinContent(1);
    // cout << "x0 " << x0 << " y0 " << y0 << endl;
    // ll.DrawLatex(x0,y0,Form("bbA tan#beta=%.1f",tanbeta[itb]));
    first=false;

  }
  TH1* dummy=new TH1F("dummy","",1,0,1);
  dummy->SetLineStyle(2);
  dummy->SetLineWidth(3);
  Leg->AddEntry(dummy, "#sigma(gg#rightarrowbbA)", "l");
  TLatex tl;
  tl.SetNDC();
  TString goodType(Form("Type %d 2HDM ",type));
  tl.DrawLatex(0.5,0.9,goodType);

  Leg->Draw();
  pCan(c1,cname);
}
