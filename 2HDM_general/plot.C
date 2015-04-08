TFile *_file0 = 0;
TGraph2D* plot2d(const TString& what,
                 const TString& cut="",
                 const TString& opt="") {
  if (!_file0)
    _file0 = TFile::Open("./parameter_2HDM_ty1_mA1200_mH1200.root");
  Tree2HDM->Draw(what,cut,"goff");
  TGraph2D *gr2=new TGraph2D(Tree2HDM->GetSelectedRows(),
                             Tree2HDM->GetV2(),
                             Tree2HDM->GetV3(),
                             Tree2HDM->GetV1());
  gr2->SetTitle(what);
  gr2->Draw(opt);

  gPad->Print(what+".pdf");
  return gr2;
}
TGraph* plot(const TString& what,
             const TString& cut="",
             const TString& opt="") {
  if (!_file0)
    _file0 = TFile::Open("./parameter_2HDM_ty1_mA1200_mH1200.root");
  Tree2HDM->Draw(what,cut,"goff");
  TGraph *gr=new TGraph(Tree2HDM->GetSelectedRows(),
                        Tree2HDM->GetV2(),
                        Tree2HDM->GetV1());
  gr->SetTitle(what);
  gr->Draw(opt);

  gPad->Print(what+".pdf");
  return gr;
}
