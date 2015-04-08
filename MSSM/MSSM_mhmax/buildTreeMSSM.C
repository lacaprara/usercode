#include <fstream>
   
void buildTreeMSSM(const string& dir="./") {

  float mA,tb,alpha,ggA,bbA;

  float mA_FH,mh_FH,mH_FH,tb_FH,mHC_FH,BRhbb_FH,BRAZh_FH;

  TString filename (TString(dir.c_str())+("/parameter_MSSM.root"));

  TFile *hfile = TFile::Open(filename,"RECREATE");
  TTree *tree = new TTree("TreeMSSM","2HDM parameter space");
  tree->Branch("mA",&mA,"mA/F");
  tree->Branch("mh",&mh_FH,"mh/F");
  tree->Branch("mH",&mH_FH,"mH/F");
  tree->Branch("mHC",&mHC_FH,"mHC/F");
  tree->Branch("tb",&tb,"tb/F");
  tree->Branch("alpha",&alpha,"alpha/F");
  tree->Branch("ggA",&ggA,"ggA/F");
  tree->Branch("bbA",&bbA,"bbA/F");
  tree->Branch("BRhbb",&BRhbb_FH,"BRhbb/F");
  tree->Branch("BRAZh",&BRAZh_FH,"BRAZh/F");

  TString infilename(TString(dir.c_str())+("/parameters_MSSM.data"));
  cout << "opening " << infilename << endl;
  std::ifstream infile(infilename.Data());
  TString file1, file2;
  //while (!infile.eof()) {}
  while (true) {
    infile >>
      file1 >>
      mA  >>
      tb >>
      alpha >>
      ggA >>
      bbA ;
    infile >>
      file2 >>
      mA_FH  >>
      mh_FH >>
      mH_FH >>
      tb_FH >>
      mHC_FH >>
      BRhbb_FH >>
      BRAZh_FH; 

      // cout << file1 << " " << mA << " " << tb << " " << alpha << " " << ggA << " " <<bbA << endl;
      // cout << file2 << " " << mA_FH  << " " << mh_FH << " " << mH_FH << " " << tb_FH << " " << mHC_FH << " " << BRhbb_FH << " " << BRAZh_FH << " " <<  endl;

    if ( (mA!=mA_FH) ||
         (tb!=tb_FH) ) {
      cout << "ERROR!!! " << 
        (mA!=mA_FH) <<
        (tb!=tb_FH) << endl;
      cout << file1 << " " << mA << " " << tb << " " << alpha << " " << ggA << " " <<bbA << endl;
      cout << file2 << " " << mA_FH  << " " << mh_FH << " " << mH_FH << " " << tb_FH << " " << mHC_FH << " " << BRhbb_FH << " " << BRAZh_FH << " " <<  endl;
      return;
    }
    if (infile.eof()) break;
    tree->Fill();
    //cout << "Done" << endl;
  } //while (infile.eof());
  //tree->Print();
  tree->Write();

  infile.close();
  cout << "Saved " << filename << endl;
}
