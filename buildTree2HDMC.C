#include <fstream>
   
void buildTree2HDMC(const string& fname="./report.out", const string& dir="./") {

  bool stab,pert,unit,valid;
  float mA,mH,tanbeta,alpha,mHC,m12,ggh,bbh,ggA,bbA,ggH,bbH;
  float gammah, gammaA, gammaH, gammaHC;
  float sba, cba;

  TString part,what;

  struct BRh {
      float ss;
      float cc;
      float bb;
      float ee;
      float mumu;
      float tautau;
      float gamgam;
      float ZZ;
      float WW;
      float Zgam;
      float gluglu;
      BRh() {};

      ClassDef(BRh,0);
  };

  struct BRA {
      float ss;
      float cc;
      float bb;
      float tt;
      float ee;
      float mumu;
      float tautau;
      float gamgam;
      float Zgam;
      float gluglu;
      float Zh;
      BRA() {};

      ClassDef(BRA,0);
  };

  struct BRH {
      float ss;
      float cc;
      float bb;
      float tt;
      float ee;
      float mumu;
      float tautau;
      float gamgam;
      float Zgam;
      float ZZ;
      float WW;
      float gluglu;
      float hh;
      float AA;
      float HCHC;
      float ZA;
      float WHC;
      float HCW;
      BRH() {};

      ClassDef(BRH,0);
  };

  struct BRHC {
      float us;
      float ub;
      float cd;
      float cs;
      float cb;
      float td;
      float ts;
      float tb;
      float enue;
      float munumu;
      float taunutau;
      float Wh;
      BRHC() {};

      ClassDef(BRHC,0);
  };
  BRh aBRh;
  BRA aBRA;
  BRH aBRH;
  BRHC aBRHC;

  TString filename (dir+fname);
  filename.ReplaceAll(".out",".root");
  //cout << "filename " << filename << endl;

  TFile *hfile = TFile::Open(filename,"RECREATE");
  TTree *tree = new TTree("Tree2HDM","2HDM parameter space");
  tree->Branch("validity",&valid,"valid/O");
  tree->Branch("stability",&stab,"stab/O");
  tree->Branch("perturbativity",&pert,"pert/O");
  tree->Branch("unitarity",&unit,"unit/O");
  tree->Branch("gammah",&gammah,"gammah/F");
  tree->Branch("mA",&mA,"mA/F");
  tree->Branch("gammaA",&gammaA,"gammaA/F");
  tree->Branch("mH",&mH,"mH/F");
  tree->Branch("gammaH",&gammaH,"gammaH/F");
  tree->Branch("mHC",&mHC,"mHC/F");
  tree->Branch("gammaHC",&gammaHC,"gammaHC/F");
  tree->Branch("m12",&m12,"m12/F");
  tree->Branch("tanbeta",&tanbeta,"tanbeta/F");
  tree->Branch("alpha",&alpha,"alpha/F");
  tree->Branch("sinba",&sba,"sba/F");
  tree->Branch("cosba",&cba,"cba/F");
  tree->Branch("ggh",&ggh,"ggh/F");
  tree->Branch("bbh",&bbh,"bbh/F");
  tree->Branch("ggA",&ggA,"ggA/F");
  tree->Branch("bbA",&bbA,"bbA/F");
  tree->Branch("ggH",&ggH,"ggH/F");
  tree->Branch("bbH",&bbH,"bbH/F");
  tree->Branch("BRh",&aBRh,"ss/F:cc/F:bb/F:ee/F:mumu/F:tautau/F:gamgam/F:ZZ/F:WW/F:Zgam/F:gluglu/F");
  tree->Branch("BRA",&aBRA,"ss/F:cc/F:bb/F:tt/F:ee/F:mumu/F:tautau/F:gamgam/F:Zgam/F:gluglu/F:Zh/F");
  tree->Branch("BRH",&aBRH,"ss/F:cc/F:bb/F:tt/F:ee/F:mumu/F:tautau/F:gamgam/F:ZZ/F:WW/F:Zgam/F:gluglu/F:hh/F:AA/F:HCHC/F:ZA/F:WHC/F");
  tree->Branch("BRHC",&aBRH,"us/F:ub/F:cd/F:cs/F:cb/F:td/F:ts/F:tb/F:enue/F:munumu/F:taunutau/F:Wh/F");

  TString infilename(dir+fname);
  cout << "opening " << infilename << endl;
  std::ifstream infile(infilename.Data());
  TString file1, file2;
  //while (!infile.eof()) {}
  int line=0;
  while (true) {
    line++;

    infile >>
      part ;
    if (infile.eof()) break;
    cout << "Line " << line << endl;

    // h x-section
    infile >>
      ggh >>
      bbh >>
      stab >>
      pert >>
      unit >>
      alpha >>
      tanbeta >>
      mA >>
      mH;
    if (part != "h") {
      cout << "ERROR: part must be h, while is " << part << endl;
      break;
    }
    // A x-section
    infile >>
      part >>
      ggA >>
      bbA >>
      stab >>
      pert >>
      unit >>
      alpha >>
      tanbeta >>
      mA >>
      mH;
    if (part != "A") {
      cout << "ERROR: part must be A, while is " << part << endl;
      break;
    }


    // H x-section
    infile >>
      part >>
      ggH >>
      bbH >>
      stab >>
      pert >>
      unit >>
      alpha >>
      tanbeta >>
      mA >>
      mH;
    if (part != "H") {
      cout << "ERROR: part must be H, while is " << part  << endl;
      break;
    }


    // 2HDMC generalities
    infile >>
      what >>
      valid >>
      unit >>
      pert >>
      stab >>
      mHC >>
      tanbeta >>
      sba >>
      cba >>
      m12 >>
      gammah >>
      gammaH >>
      gammaA >>
      gammaHC;
    if ( what!="2HDMC") {
      cout << "ERROR: what must be 2HDMC, while is " << what << endl;
      break;
    }
    // cout << " " << 
    //   "what: " << what << " " << 
    //   "valid: " << valid << " " << 
    //   "unit: " << unit << " " << 
    //   "pert: " << pert << " " << 
    //   "stab: " << stab << " " << 
    //   "mHC: " << mHC << " " << 
    //   "tanbeta: " << tanbeta << " " << 
    //   "sba: " << sba << " " << 
    //   "cba: " << cba << " " << 
    //   "m12: " << m12 << " " << 
    //   "gammah: " << gammah << " " << 
    //   "gammaH: " << gammaH << " " << 
    //   "gammaA: " << gammaA << " " << 
    //   "gammaHC: " << gammaHC << endl;

    // BR h
    infile >>
      what >>
      aBRh.ss >>
      aBRh.cc >>
      aBRh.bb >>
      aBRh.ee >>
      aBRh.mumu >>
      aBRh.tautau >>
      aBRh.gamgam >>
      aBRh.ZZ >>
      aBRh.WW >>
      aBRh.Zgam >>
      aBRh.gluglu;
    if ( what!="BRh") {
      cout << "ERROR: what must be BRh, while is " << what << endl;
      break;
    }
    // cout  << " " << 
    //   "what: " << what << " " << 
    //   "ss: " << aBRh.ss << " " << 
    //   "cc: " << aBRh.cc << " " << 
    //   "bb: " << aBRh.bb << " " << 
    //   "ee: " << aBRh.ee << " " << 
    //   "mumu: " << aBRh.mumu << " " << 
    //   "tautau: " << aBRh.tautau << " " << 
    //   "gamgam: " << aBRh.gamgam << " " << 
    //   "ZZ: " << aBRh.ZZ << " " << 
    //   "WW: " << aBRh.WW << " " << 
    //   "Zgam: " << aBRh.Zgam << " " << 
    //   "gluglu: " << aBRh.gluglu << endl;

    // BR H
    infile >>
      what >>
      aBRH.ss >>
      aBRH.cc >>
      aBRH.bb >>
      aBRH.tt >>
      aBRH.ee >>
      aBRH.mumu >>
      aBRH.tautau >>
      aBRH.gamgam >>
      aBRH.ZZ >>
      aBRH.WW >>
      aBRH.Zgam >>
      aBRH.gluglu >>
      aBRH.hh>>
      aBRH.AA>>
      aBRH.HCHC>>
      aBRH.ZA>>
      aBRH.WHC>>
      aBRH.HCW;

    if ( what!="BRH") {
      cout << "ERROR: what must be BRH, while is " << what  << endl;
      break;
    }
    // cout << " " << 
    //   what << " " << 
    //   "ss: " << aBRH.ss << " " << 
    //   "cc: " << aBRH.cc << " " << 
    //   "bb: " << aBRH.bb << " " << 
    //   "tt: " << aBRH.tt << " " << 
    //   "ee: " << aBRH.ee << " " << 
    //   "mumu: " << aBRH.mumu << " " << 
    //   "tautau: " << aBRH.tautau << " " << 
    //   "gamgam: " << aBRH.gamgam << " " << 
    //   "ZZ: " << aBRH.ZZ << " " << 
    //   "WW: " << aBRH.WW << " " << 
    //   "Zgam: " << aBRH.Zgam << " " << 
    //   "gluglu: " << aBRH.gluglu << " " << 
    //   "hh: " << aBRH.hh;

    // BR A
    infile >>
      what >>
      aBRA.ss >>
      aBRA.cc >>
      aBRA.bb >>
      aBRA.tt >>
      aBRA.ee >>
      aBRA.mumu >>
      aBRA.tautau >>
      aBRA.gamgam >>
      aBRA.Zgam >>
      aBRA.gluglu >>
      aBRA.Zh;

    if ( what!="BRA") {
      cout << "ERROR: what must be BRA, while is " << what  << endl;
      break;
    }
    // cout << " " << 
    //   what << " " << 
    //   "ss: " << aBRA.ss << " " << 
    //   "cc: " << aBRA.cc << " " << 
    //   "bb: " << aBRA.bb << " " << 
    //   "tt: " << aBRA.tt << " " << 
    //   "ee: " << aBRA.ee << " " << 
    //   "mumu: " << aBRA.mumu << " " << 
    //   "tautau: " << aBRA.tautau << " " << 
    //   "gamgam: " << aBRA.gamgam << " " << 
    //   "Zgam: " << aBRA.Zgam << " " << 
    //   "gluglu: " << aBRA.gluglu << " " << 
    //   "Zh: " << aBRA.Zh;

    // BR HC
    infile >>
      what >>
      aBRHC.us >>
      aBRHC.ub >>
      aBRHC.cd >>
      aBRHC.cs >>
      aBRHC.cb >>
      aBRHC.td >>
      aBRHC.ts >>
      aBRHC.tb >>
      aBRHC.enue >>
      aBRHC.munumu >>
      aBRHC.taunutau >>
      aBRHC.Wh;
    aBRHC.Wh*=2.; // To take into account h.c.

    if ( what!="BRHC") {
      cout << "ERROR: what must be BRHC, while is " << what << endl;
      break;
    }
    // cout << " " << 
    //   what << " " << 
    //   "us: " << aBRHC.us << " " << 
    //   "ub: " << aBRHC.ub << " " << 
    //   "cd: " << aBRHC.cd << " " << 
    //   "cs: " << aBRHC.cs << " " << 
    //   "cb: " << aBRHC.cb << " " << 
    //   "td: " << aBRHC.td << " " << 
    //   "td: " << aBRHC.ts << " " << 
    //   "td: " << aBRHC.tb << " " << 
    //   "enue: " << aBRHC.enue << " " << 
    //   "munumu: " << aBRHC.munumu << " " << 
    //   "taunutau: " << aBRHC.taunutau << " " << 
    //   "Wh: " << aBRHC.Wh;
    //break;

    // compute cos(beta-alpha) and sin(beta-alpha) in the range
    // 0<b-a<pi
    // 0<sin(b-a)<1
    // -1<cos(b-a)<1
    //cout << "sba= " << sba << " cba " << cba << " tanbeta= " << tanbeta << endl;
    float beta=atan(tanbeta);
    float ba=beta-alpha;
    //cout << "alpha " << alpha << " beta " << beta << " b-a "<< ba << endl;
    if (ba<0) {
      sba=-sba;
      cba=-cba;
    }
    //cout << "sba_2HDMC= " << sba_2HDMC << " cba_2HDMC " << cba_2HDMC << endl;
   // cout << "sba= " << sba << " cba " << cba << endl;

    tree->Fill();
  }
  tree->Write();

  infile.close();
  hfile->Close();
  cout << "Output filename: " << filename << endl;
}
