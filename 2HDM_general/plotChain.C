TChain* ch=0;

void loadChain() {
  if (ch) return;
  ch=new TChain("Tree2HDM");
  std::ifstream filelist("list_ty1_afs.txt");

  char line[100];
  while (!(filelist.eof())) {
    filelist.getline(line, sizeof(line));
    if (strcmp(line, "") == 0) continue;
    ch->Add(line);
  }
}

TGraph2D* plot2d(const TString& what,
                 const TString& cut="",
                 const TString& opt="") {
  loadChain();
  ch->Draw(what,cut,"goff");
  TGraph2D *gr2=new TGraph2D(Tree2HDM->GetSelectedRows(),
                             Tree2HDM->GetV2(),
                             Tree2HDM->GetV3(),
                             Tree2HDM->GetV1());
  gr2->SetTitle(what);
  gr2->Draw(opt);

  //gPad->Print(what+".pdf");
  return gr2;
}

TGraph* plot(const TString& what,
             const TString& cut="",
             const TString& opt="") {

  loadChain();
  ch->Draw(what,cut,"goff");
  TGraph *gr=new TGraph(Tree2HDM->GetSelectedRows(),
                        Tree2HDM->GetV2(),
                        Tree2HDM->GetV1());
  gr->SetTitle(what);
  gr->Draw(opt);

  //gPad->Print(what+".pdf");
  return gr;
}
