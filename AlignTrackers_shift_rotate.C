#include <vector>
#include "doubleGausFit_withHistParameter.C"
#include <iostream>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

void tracking(string Thestring){
 string thestring = "Hit_Position_Info";
  string txtfilename = thestring + std::string(".txt");
  string shiftHead = "RotationBack_shiftParameters_";
  string rotateHead = "RotationBack_angles_";
  string residualHead = "RotationBack_residuals_";
  string ResidualRHead="RotationBack_Residual_";
  string chi2Head = "ResolutionChi2Angle_";
  string foutname = shiftHead+thestring+"_exclusive.txt";
  string fout1name = residualHead+thestring+"_exclusive.txt";
  string foutchi2name = chi2Head + thestring + "_exclusive.txt";
  string foutRotationName = rotateHead + thestring + "_exclusive.txt";
  fstream fin(txtfilename.c_str(),ios::in);
  if(!fin){cout<<"file not read"<<endl; return;}
  else cout<<"processing "<<txtfilename<<endl;
  fstream fout(foutname.c_str(),ios::out);
  fstream fout1(fout1name.c_str(),ios::out);
  fstream fout2(foutRotationName.c_str(),ios::out);
  fstream fout3(foutchi2name.c_str(),ios::out|ios::app);
  double Pos_g2xcl=0.0, Pos_g2ycl=0.0;
  double Pos_g3xcl=0.0, Pos_g3ycl=0.0;
  //double pUVA3X=0.0, pUVA3Y=0.0;
  double Pos_g1xcl=0.0, Pos_g1ycl=0.0;
  //double pZZ1=0.0, pZZ2=0.0;
  //double pEta5=0.0;
  vector<double> vPos_g2xcl; vector<double> vPos_g2ycl;
  vector<double> vPos_g3xcl; vector<double> vPos_g3ycl;
 double CalculateCosTheta1(double x, double y, double x1,double y1); 
// vector<double> vpUVA3X; vector<double> vpUVA3Y;
  vector<double> vPos_g1xcl; vector<double> vPos_g1ycl;
  //vector<double> vpZZ1; vector<double> vpZZ2;
  //vector<double> vpEta5;
  Int_t nbLines=0;
  while(fin>>Pos_g2xcl>>Pos_g2ycl>>Pos_g3xcl>>Pos_g3ycl>>/*pUVA3X>>pUVA3Y>>*/Pos_g1xcl>>Pos_g1ycl/*>>pEta5*/){
    vPos_g2xcl.push_back(Pos_g2xcl); vPos_g2ycl.push_back(Pos_g2ycl); vPos_g3xcl.push_back(Pos_g3xcl); vPos_g3ycl.push_back(Pos_g3ycl);
   /* vpUVA3X.push_back(pUVA3X); vpUVA3Y.push_back(pUVA3Y);*/ vPos_g1xcl.push_back(Pos_g1xcl); vPos_g1ycl.push_back(Pos_g1ycl);
    //vpZZ1.push_back(pZZ1); vpZZ2.push_back(pZZ2);
    //vpEta5.push_back(pEta5);
    nbLines++;
  }
  fin.close();
  /*
  g2xcl:
      [-30,-20]: -22.98, 1.089, -28.29, -3.209, -37.22, 14.88, -46.62, -2.411, 29.84
      [-20,-15]: -17.07, 0.4154, -22.27, -3.92, -31.12, 14.55, -40.55, -2.637, 29.48
  */
  /* coarse alignment parameters
  double shig2xcl=10.72, shig2ycl=1.048;
  double shig3xcl=6.162, shig3ycl=-3.395;
 // double shiUVA3X=-1.489, shiUVA3Y=15.05;
  double shig1xcl=-10.46, shig1ycl=-1.496;
  //double shiZZ1=0,   shiZZ2=0;
  double shiEta5=29.5
 */
 //fine alignment parameters
  double shig2xcl=3.656, shig2ycl=1.865;
  double shig3xcl=-1.781, shig3ycl=-2.415;
 // double shiUVA3X=-8.389, shiUVA3Y=15.779;
  double shig1xcl=-17.504, shig1ycl=-0.844;
  double ag3clg2cl=0.009499;
 // double aUVA3g2cl=-0.004731;
  double ag1clg2cl=-0.02473;

  
//  double shig2xcl=12.26791212, shig2ycl=2.02708225;
//  double shig3xcl=7.4824985, shig3ycl=-2.35562;
 // double shiUVA3X=-0.7097, shiUVA3Y=15.75778;
 // double shig1xcl=-9.92822, shig1ycl=-0.68756;
 // double shiEta5=29.47;
//  double ag3clg2cl=0;//0.0037;//0.01254602;//start angle: 0.01197;
 // double aUVA3g2cl=0;//-0.017;//0.00203396;//0.02807;//start angle: 0.01102
//  double ag1clg2cl=0;//-0.0486;//-0.0171;//start angle: 0.008273;
  
  //double aEta5g2cl;
  double temPos_g2xcl, temPos_g2ycl, temPos_g3xcl, temPos_g3ycl,/* tempUVA3X, tempUVA3Y,*/ temPos_g1xcl, temPos_g1ycl, tempEta5;

  double meang2xcl=0.0, meang2ycl=0.0;
  double meang3xcl=0.0, meang3ycl=0.0;
//  double meanUVA3X=0.0, meanUVA3Y=0.0;
  double meang1xcl=0.0, meang1ycl=0.0;
  //double meanZZ1=0.0, meanZZ2=0.0;
  //double meanEta5=0;
  double meanAngleg3cl=0.0;
 // double meanAngleUVA3=0.0;
  double meanAngleg1cl=0.0;
  //double meanAngleEta5=0.0;
  double sigmag2xcl=0.0,sigmag2ycl=0.0,sigmag3xcl=0.0,sigmag3ycl=0.0,/*sigmaUVA3X=0.0,sigmaUVA3Y=0.0,*/sigmag1xcl=0.0,sigmag1ycl=0.0;
  double totalAngleg3cl=0.0,/* totalAngleUVA3=0.0,*/ totalAngleg1cl=0.0;
  double meanXChi2=0.0,meanYChi2=0.0; // chi square for tracks.

  Int_t iterNb=0;
  while(1){
    char rootfile[50]; sprintf(rootfile,"_iter%i_exclusive.root",iterNb);
    string outputrootname=ResidualRHead+thestring+rootfile;
    TFile* f = new TFile(outputrootname.c_str(),"recreate");
    iterNb++;
    char name2X[15];sprintf(name2X,"posg2xcl_%i",iterNb); char name2Y[15];sprintf(name2Y,"posg2ycl_%i",iterNb);
    char name3X[15];sprintf(name3X,"posg3xcl_%i",iterNb); char name3Y[15];sprintf(name3Y,"posg3ycl_%i",iterNb);
  //  char nameu3X[15];sprintf(nameu3X,"posUVA3X_%i",iterNb);char nameu3Y[15];sprintf(nameu3Y,"posUVA3Y_%i",iterNb);
    char name1X[15];sprintf(name1X,"posg1xcl_%i",iterNb); char name1Y[15];sprintf(name1Y,"posg1ycl_%i",iterNb);
    //char nameZZ1[15];sprintf(nameZZ1,"pos10cmZZ1_%i",iterNb); char nameZZ2[15];sprintf(nameZZ2,"pos10cmZZ2_%i",iterNb);
    //char nameEta5[15];sprintf(nameEta5,"posEta5_%i",iterNb); 
    TH1F* hPos_g2xcl = new TH1F(name2X,"",500,-50,50); hPos_g2xcl->SetXTitle("mm"); hPos_g2xcl->SetYTitle("Frequency");hPos_g2xcl->SetLabelSize(0.045,"XY");hPos_g2xcl->SetTitleSize(0.045,"XY");
    TH1F* hPos_g2ycl = new TH1F(name2Y,"",500,-50,50); hPos_g2ycl->SetXTitle("mm"); hPos_g2ycl->SetYTitle("Frequency");hPos_g2ycl->SetLabelSize(0.045,"XY");hPos_g2ycl->SetTitleSize(0.045,"XY");  
    TH1F* hPos_g3xcl = new TH1F(name3X,"",500,-50,50); hPos_g3xcl->SetXTitle("mm"); hPos_g3xcl->SetYTitle("Frequency");hPos_g3xcl->SetLabelSize(0.045,"XY");hPos_g3xcl->SetTitleSize(0.045,"XY");
    TH1F* hPos_g3ycl = new TH1F(name3Y,"",500,-50,50); hPos_g3ycl->SetXTitle("mm"); hPos_g3ycl->SetYTitle("Frequency");hPos_g3ycl->SetLabelSize(0.045,"XY");hPos_g3ycl->SetTitleSize(0.045,"XY");  
   // TH1F* hpUVA3X = new TH1F(nameu3X,"",500,-50,50); hpUVA3X->SetXTitle("mm"); hpUVA3X->SetYTitle("Frequency");hpUVA3X->SetLabelSize(0.045,"XY");hpUVA3X->SetTitleSize(0.045,"XY");
   // TH1F* hpUVA3Y = new TH1F(nameu3Y,"",500,-50,50); hpUVA3Y->SetXTitle("mm"); hpUVA3Y->SetYTitle("Frequency");hpUVA3Y->SetLabelSize(0.045,"XY");hpUVA3Y->SetTitleSize(0.045,"XY");  
    TH1F *hPos_g1xcl = new TH1F(name1X,"",500,-50,50); hPos_g1xcl->SetXTitle("mm"); hPos_g1xcl->SetYTitle("Frequency");hPos_g1xcl->SetLabelSize(0.045,"XY");hPos_g1xcl->SetTitleSize(0.045,"XY");
    TH1F *hPos_g1ycl = new TH1F(name1Y,"",500,-50,50); hPos_g1ycl->SetXTitle("mm"); hPos_g1ycl->SetYTitle("Frequency");hPos_g1ycl->SetLabelSize(0.045,"XY");hPos_g1ycl->SetTitleSize(0.045,"XY");  
    //TH1F* hpZZ1 = new TH1F(nameZZ1,"",600,-150,150); hpZZ1->SetXTitle("mm"); hpZZ1->SetYTitle("Frequency"); hpZZ1->SetLabelSize(0.045,"XY");hpZZ1->SetTitleSize(0.045,"XY");
    //TH1F* hpZZ2 = new TH1F(nameZZ2,"",600,-150,150); hpZZ2->SetXTitle("mm"); hpZZ2->SetYTitle("Frequency"); hpZZ2->SetLabelSize(0.045,"XY");hpZZ2->SetTitleSize(0.045,"XY");
    //TH1F* hpEta5 = new TH1F(nameEta5,"",600,-150,150); hpEta5->SetXTitle("mm"); hpEta5->SetYTitle("Frequency"); hpEta5->SetLabelSize(0.045,"XY");hpEta5->SetTitleSize(0.045,"XY");
    char nameRes2X[20];sprintf(nameRes2X,"residualg2xcl_%i",iterNb);char nameRes2Y[20];sprintf(nameRes2Y,"residualg2ycl_%i",iterNb);
    char nameRes3X[20];sprintf(nameRes3X,"residualg3xcl_%i",iterNb);char nameRes3Y[20];sprintf(nameRes3Y,"residualg3ycl_%i",iterNb);
  //  char nameResu3X[20];sprintf(nameResu3X,"residualUVA3X_%i",iterNb);char nameResu3Y[20];sprintf(nameResu3Y,"residualUVA3Y_%i",iterNb);
    char nameRes1X[20];sprintf(nameRes1X,"residualg1xcl_%i",iterNb);char nameRes1Y[20];sprintf(nameRes1Y,"residualg1ycl_%i",iterNb);
    //char nameResZZ1[20];sprintf(nameResZZ1,"residualZZ1_%i",iterNb);char nameResZZ2[20];sprintf(nameResZZ2,"residualZZ2_%i",iterNb);
    //char nameResEta5[20];sprintf(nameResEta5,"residualEta5_%i",iterNb);
    TH1F* residualg2xcl = new TH1F(nameRes2X,"",200,-2,2); residualg2xcl->SetXTitle("Residual [mm]"); residualg2xcl->SetYTitle("Frequency");residualg2xcl->SetLabelSize(0.045,"XY");residualg2xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg2ycl = new TH1F(nameRes2Y,"",200,-2,2); residualg2ycl->SetXTitle("Residual [mm]"); residualg2ycl->SetYTitle("Frequency");residualg2ycl->SetLabelSize(0.045,"XY");residualg2ycl->SetTitleSize(0.045,"XY");
    TH1F* residualg3xcl = new TH1F(nameRes3X,"",200,-2,2); residualg3xcl->SetXTitle("Residual [mm]"); residualg3xcl->SetYTitle("Frequency");residualg3xcl->SetLabelSize(0.045,"XY");residualg3xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg3ycl = new TH1F(nameRes3Y,"",200,-2,2); residualg3ycl->SetXTitle("Residual [mm]"); residualg3ycl->SetYTitle("Frequency");residualg3ycl->SetLabelSize(0.045,"XY");residualg3ycl->SetTitleSize(0.045,"XY");
   // TH1F* residualUVA3X = new TH1F(nameResu3X,"",200,-2,2); residualUVA3X->SetXTitle("Residual [mm]"); residualUVA3X->SetYTitle("Frequency");residualUVA3X->SetLabelSize(0.045,"XY");residualUVA3X->SetTitleSize(0.045,"XY");
   // TH1F* residualUVA3Y = new TH1F(nameResu3Y,"",200,-2,2); residualUVA3Y->SetXTitle("Residual [mm]"); residualUVA3Y->SetYTitle("Frequency");residualUVA3Y->SetLabelSize(0.045,"XY");residualUVA3Y->SetTitleSize(0.045,"XY");
    TH1F* residualg1xcl = new TH1F(nameRes1X,"",200,-2,2); residualg1xcl->SetXTitle("mm"); residualg1xcl->SetYTitle("Frequency");residualg1xcl->SetLabelSize(0.045,"XY");residualg1xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg1ycl = new TH1F(nameRes1Y,"",200,-2,2); residualg1ycl->SetXTitle("mm"); residualg1ycl->SetYTitle("Frequency");residualg1ycl->SetLabelSize(0.045,"XY");residualg1ycl->SetTitleSize(0.045,"XY");
    //TH1F* residualZZ1 = new TH1F(nameResZZ1,"",320,-16,16); residualZZ1->SetXTitle("Residual [mm]"); residualZZ1->SetYTitle("Frequency");residualZZ1->SetLabelSize(0.045,"XY");residualZZ1->SetTitleSize(0.045,"XY");
    ////TH1F* residualZZ2 = new TH1F(nameResZZ2,"",320,-16,16); residualZZ2->SetXTitle("Residual [mm]"); residualZZ2->SetYTitle("Frequency");residualZZ2->SetLabelSize(0.045,"XY");residualZZ2->SetTitleSize(0.045,"XY");
    //TH1F* residualEta5 = new TH1F(nameResEta5,"",320,-16,16); residualEta5->SetXTitle("Residual [mm]"); residualEta5->SetYTitle("Frequency");residualEta5->SetLabelSize(0.045,"XY");residualEta5->SetTitleSize(0.045,"XY");
    /*
    char nameDxg3xcl[20]; sprintf(nameDxg3xcl,"g3xcl_g2xcl_%i",iterNb); char nameDyg3ycl[20]; sprintf(nameDyg3ycl,"g3ycl_g2ycl_%i",iterNb); 
    char nameDxUVA3X[20]; sprintf(nameDxUVA3X,"UVA3X_g2xcl_%i",iterNb); char nameDyUVA3Y[20]; sprintf(nameDyUVA3Y,"UVA3Y_g2ycl_%i",iterNb); 
    char nameDxg1xcl[20]; sprintf(nameDxg1xcl,"g1xcl_g2xcl_%i",iterNb); char nameDyg1ycl[20]; sprintf(nameDyg1ycl,"g1ycl_g2ycl_%i",iterNb); 
    TH1F* dxg3xcl = new TH1F(nameDxg3xcl,"",400,-4,4); dxg3xcl->SetXTitle("Delta_X_g3xcl_g2xcl [mm]"); dxg3xcl->SetYTitle("Frequency");dxg3xcl->SetLabelSize(0.045,"XY"); dxg3xcl->SetTitleSize(0.045,"XY");
    TH1F* dxUVA3X = new TH1F(nameDxUVA3X,"",400,-4,4); dxUVA3X->SetXTitle("Delta_X_UVA3X_g2xcl [mm]"); dxUVA3X->SetYTitle("Frequency");dxUVA3X->SetLabelSize(0.045,"XY"); dxUVA3X->SetTitleSize(0.045,"XY");
    TH1F* dxg1xcl = new TH1F(nameDxg1xcl,"",400,-4,4); dxg1xcl->SetXTitle("Delta_X_g1xcl_g2xcl [mm]"); dxg1xcl->SetYTitle("Frequency");dxg1xcl->SetLabelSize(0.045,"XY"); dxg1xcl->SetTitleSize(0.045,"XY");
    TH1F* dyg3ycl = new TH1F(nameDyg3ycl,"",400,-4,4); dyg3ycl->SetXTitle("Delta_Y_g3ycl_g2ycl [mm]"); dyg3ycl->SetYTitle("Frequency");dyg3ycl->SetLabelSize(0.045,"XY"); dyg3ycl->SetTitleSize(0.045,"XY");
    TH1F* dyUVA3Y = new TH1F(nameDyUVA3Y,"",400,-4,4); dyUVA3Y->SetXTitle("Delta_Y_UVA3Y_g2ycl [mm]"); dyUVA3Y->SetYTitle("Frequency");dyUVA3Y->SetLabelSize(0.045,"XY"); dyUVA3Y->SetTitleSize(0.045,"XY");
    TH1F* dyg1ycl = new TH1F(nameDyg1ycl,"",400,-4,4); dyg1ycl->SetXTitle("Delta_Y_g1ycl_g2ycl [mm]"); dyg1ycl->SetYTitle("Frequency");dyg1ycl->SetLabelSize(0.045,"XY"); dyg1ycl->SetTitleSize(0.045,"XY");
    
    char nameDxUVA3g3cl[20]; sprintf(nameDxUVA3g3cl,"UVA3X_g3xcl_%i",iterNb);
    char nameDxg1clUVA3[20]; sprintf(nameDxg1clUVA3,"g1xcl_UVA3X_%i",iterNb);
    char nameDxg1clg3cl[20]; sprintf(nameDxg1clg3cl,"g1xcl_g3xcl_%i",iterNb);
    char nameDyUVA3g3cl[20]; sprintf(nameDyUVA3g3cl,"UVA3Y_g3ycl_%i",iterNb);
    char nameDyg1clUVA3[20]; sprintf(nameDyg1clUVA3,"g1ycl_UVA3Y_%i",iterNb);
    char nameDyg1clg3cl[20]; sprintf(nameDyg1clg3cl,"g1ycl_g3ycl_%i",iterNb);
    TH1F* dxUVA3g3cl = new TH1F(nameDxUVA3g3cl,"",400,-4,4); dxUVA3g3cl->SetXTitle("Delta_X_UVA3X_g3xcl [mm]"); dxUVA3g3cl->SetYTitle("Frequency"); dxUVA3g3cl->SetLabelSize(0.045,"XY"); dxUVA3g3cl->SetTitleSize(0.045,"XY");
    TH1F* dxg1clUVA3 = new TH1F(nameDxg1clUVA3,"",400,-4,4); dxg1clUVA3->SetXTitle("Delta_X_g1xcl_UVA3X [mm]"); dxg1clUVA3->SetYTitle("Frequency"); dxg1clUVA3->SetLabelSize(0.045,"XY"); dxUVA3g3cl->SetTitleSize(0.045,"XY");
    TH1F* dxg1clg3cl = new TH1F(nameDxg1clg3cl,"",400,-4,4); dxg1clg3cl->SetXTitle("Delta_X_g1xcl_g3xcl [mm]"); dxg1clg3cl->SetYTitle("Frequency"); dxg1clg3cl->SetLabelSize(0.045,"XY"); dxg1clg3cl->SetTitleSize(0.045,"XY");
    TH1F* dyUVA3g3cl = new TH1F(nameDyUVA3g3cl,"",400,-4,4); dyUVA3g3cl->SetXTitle("Delta_Y_UVA3Y_g3ycl [mm]"); dyUVA3g3cl->SetYTitle("Frequency"); dyUVA3g3cl->SetLabelSize(0.045,"XY"); dyUVA3g3cl->SetTitleSize(0.045,"XY");
    TH1F* dyg1clUVA3 = new TH1F(nameDyg1clUVA3,"",400,-4,4); dyg1clUVA3->SetXTitle("Delta_Y_g1ycl_UVA3Y [mm]"); dyg1clUVA3->SetYTitle("Frequency"); dyg1clUVA3->SetLabelSize(0.045,"XY"); dyg1clUVA3->SetTitleSize(0.045,"XY");
    TH1F* dyg1clg3cl = new TH1F(nameDyg1clg3cl,"",400,-4,4); dyg1clg3cl->SetXTitle("Delta_Y_g1ycl_g3ycl [mm]"); dyg1clg3cl->SetYTitle("Frequency"); dyg1clg3cl->SetLabelSize(0.045,"XY"); dyg1clg3cl->SetTitleSize(0.045,"XY");
    */
    TH1F* angleg3cl = new TH1F("angleg3cl","Rotation angle distribution of g3cl and g2cl",1000,-0.5,0.5); angleg3cl->SetXTitle("Angle [radian]"); angleg3cl->SetYTitle("Frequency");
    //TH1F* angleg3cl_2 = new TH1F("angleg3cl","Get From Delta_y",2000,-0.5,3.5); angleg3cl_2->SetXTitle("Rotation angle of ERF3 and g2cl [radian]"); angleg3cl_2->SetYTitle("Frequency");
   // TH1F* angleUVA3 = new TH1F("angleUVA3","Rotation angle distribution of UVA3 and g2cl",1000,-0.5,0.5); angleUVA3->SetXTitle("Angle [radian]"); angleUVA3->SetYTitle("Frequency");
    //TH1F* angleUVA3_2 = new TH1F("angleUVA3_2","Get From Delta_y",2000,-0.5,3.5); angleUVA3_2->SetXTitle("Rotation angle of UVA3 and g2cl [radian]"); angleUVA3_2->SetYTitle("Frequency");
    TH1F* angleg1cl = new TH1F("angleg1cl","Rotation angle distribution of g1cl and g2cl",1000,-0.5,0.5); angleg1cl->SetXTitle("Angle [radian]"); angleg1cl->SetYTitle("Frequency");
    //TH1F* angleg1cl_2 = new TH1F("angleg1cl_2","Get From Delta_y",2000,-0.5,3.5); angleg1cl_2->SetXTitle("Rotation angle of ERF1 and g2cl [radian]"); angleg1cl_2->SetYTitle("Frequency");
    //TH1F* angleEta5 = new TH1F("angleEta5","Rotation Eta5 and g2cl",1000,-0.5,0.5);
    //delta-y up: 200,-4,4
    //TH1F* deltayZZ = new TH1F("deltaY","",200,-4,4); deltayZZ->SetXTitle("Position difference [mm]");deltayZZ->SetYTitle("Frequency");
    //deltayZZ->SetLabelSize(0.045,"XY");deltayZZ->SetTitleSize(0.045,"XY");
    //cout<<"shift: "<<shig2xcl<<"\t"<<shig2ycl<<"\t"<<shig3xcl<<"\t"<<shig3ycl<<"\t"<<shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<shig1xcl<<"\t"<<shig1ycl<<endl;
    
    TH1F* xTrackChi2 = new TH1F("XTrackChi2","Chi square of tracks in X projection",1000,0,0.2); xTrackChi2->SetXTitle("#chi^{2} of track in X"); xTrackChi2->SetYTitle("Frequency");
    xTrackChi2->SetTitleSize(0.04,"XY"); xTrackChi2->SetLabelSize(0.04,"XY");
    TH1F* yTrackChi2 = new TH1F("YTrackChi2","Chi square of tracks in Y projection",1000,0,0.2); yTrackChi2->SetXTitle("#chi^{2} of track in Y"); yTrackChi2->SetYTitle("Frequency");
    yTrackChi2->SetTitleSize(0.04,"XY"); yTrackChi2->SetLabelSize(0.04,"XY");
    
    fout<<"shift: "<<shig2xcl<<"\t"<<shig2ycl<<"\t"<<shig3xcl<<"\t"<<shig3ycl<<"\t"<</*shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<*/shig1xcl<<"\t"<<shig1ycl<<endl;
    fout2<<"rotation: "<<ag3clg2cl<<"\t"<</*aUVA3g2cl<<"\t"<<*/ag1clg2cl<<endl;
    int nnnn=0;
    for(Int_t i=0;i<vPos_g2xcl.size();i++){
    	//shift
      vPos_g2xcl[i] = vPos_g2xcl[i] - shig2xcl; vPos_g2ycl[i] = vPos_g2ycl[i] - shig2ycl;      
      vPos_g3xcl[i] = vPos_g3xcl[i] - shig3xcl; vPos_g3ycl[i] = vPos_g3ycl[i] - shig3ycl;
   //   vpUVA3X[i] = vpUVA3X[i] - shiUVA3X; vpUVA3Y[i] = vpUVA3Y[i] - shiUVA3Y;
      vPos_g1xcl[i] = vPos_g1xcl[i] - shig1xcl; vPos_g1ycl[i] = vPos_g1ycl[i] - shig1ycl;
     // vpZZ1[i] = vpZZ1[i] - shiZZ1; vpZZ2[i] = vpZZ2[i] - shiZZ2;
      //vpEta5[i] = vpEta5[i] - shiEta5; 
      temPos_g2xcl=vPos_g2xcl[i]; temPos_g2ycl=vPos_g2ycl[i]; temPos_g3xcl=vPos_g3xcl[i]; temPos_g3ycl=vPos_g3ycl[i]; 
     // tempUVA3X=vpUVA3X[i]; tempUVA3Y=vpUVA3Y[i]; temPos_g1xcl=vPos_g1xcl[i]; tempg1ycl=vPos_g1ycl[i]; 
      //tempEta5=vpEta5[i];
      //rotate back
      vPos_g3xcl[i]=temPos_g3xcl*cos(ag3clg2cl)-temPos_g3ycl*sin(ag3clg2cl);
      vPos_g3ycl[i]=temPos_g3xcl*sin(ag3clg2cl)+temPos_g3ycl*cos(ag3clg2cl);
     // vpUVA3X[i]=tempUVA3X*cos(aUVA3g2cl)-tempUVA3Y*sin(aUVA3g2cl);
    //  vpUVA3Y[i]=tempUVA3X*sin(aUVA3g2cl)+tempUVA3Y*cos(aUVA3g2cl);//
      vPos_g1xcl[i]=temPos_g1xcl*cos(ag1clg2cl)-temPos_g1ycl*sin(ag1clg2cl);
      vPos_g1ycl[i]=temPos_g1xcl*sin(ag1clg2cl)+temPos_g1ycl*cos(ag1clg2cl);
      //vpEta5[i]=temPos_g2xcl*sin(aEta5g2cl)+tempEta5*cos(aEta5g2cl);
      
      hPos_g2xcl->Fill(vPos_g2xcl[i]); hPos_g2ycl->Fill(vPos_g2ycl[i]);
      hPos_g3xcl->Fill(vPos_g3xcl[i]); hPos_g3ycl->Fill(vPos_g3ycl[i]);
     // hpUVA3X->Fill(vpUVA3X[i]); hpUVA3Y->Fill(vpUVA3Y[i]);
      hPos_g1xcl->Fill(vPos_g1xcl[i]); hPos_g1ycl->Fill(vPos_g1ycl[i]);
      //hpZZ1->Fill(vpZZ1[i]); hpZZ2->Fill(vpZZ2[i]);
      //hpEta5->Fill(vpEta5[i]); //cout<<vpEta5[i]<<endl;
      /*
      dxg3xcl->Fill(vPos_g3xcl[i]-vPos_g2xcl[i]); dyg3ycl->Fill(vPos_g3ycl[i]-vPos_g2ycl[i]);
      dxUVA3X->Fill(vpUVA3X[i]-vPos_g2xcl[i]); dyUVA3Y->Fill(vpUVA3Y[i]-vPos_g2ycl[i]);
      dxg1xcl->Fill(vPos_g1xcl[i]-vPos_g2xcl[i]); dyg1ycl->Fill(vPos_g1ycl[i]-vPos_g2ycl[i]);
      dxUVA3g3cl->Fill(vpUVA3X[i]-vPos_g3xcl[i]); dyUVA3g3cl->Fill(vpUVA3Y[i]-vPos_g3ycl[i]);
      dxg1clUVA3->Fill(vPos_g1xcl[i]-vpUVA3X[i]); dyg1clUVA3->Fill(vPos_g1ycl[i]-vpUVA3Y[i]);
      dxg1clg3cl->Fill(vPos_g1xcl[i]-vPos_g3xcl[i]); dyg1clg3cl->Fill(vPos_g1ycl[i]-vPos_g3ycl[i]);
      */
      TGraph* g1 = new TGraph();
      g1->SetPoint(0,0,     vPos_g2xcl[i]);
      g1->SetPoint(1,1143.5,vPos_g3xcl[i]);
 //     g1->SetPoint(2,2686.5,vpUVA3X[i]);
     // g1->SetPoint(3,3169.5,vPos_g1xcl[i]);
      TF1* f1 = new TF1("line1","[0]+[1]*x",0,3200);
      g1->Fit("line1","Q");
      double intercept1 = f1->GetParameter(0);
      double slope1     = f1->GetParameter(1);
      double Measuredg2xcl = intercept1 + slope1*0.0;
      double Measuredg3xcl = intercept1 + slope1*1143.5;
     // double MeasuredUVA3X = intercept1 + slope1*2686.5;
      double Measuredg1xcl = intercept1 + slope1*3169.5;
      residualg2xcl->Fill(Measuredg2xcl-vPos_g2xcl[i]);
      residualg3xcl->Fill(Measuredg3xcl-vPos_g3xcl[i]);
     // residualUVA3X->Fill(MeasuredUVA3X-vpUVA3X[i]);
      residualg1xcl->Fill(Measuredg1xcl-vPos_g1xcl[i]);
      xTrackChi2->Fill(f1->GetChisquare());
      //cout<<f1->GetChisquare()<<"\t";
      delete f1; delete g1;

      TGraph* g2 = new TGraph();
      g2->SetPoint(0,0,     vPos_g2ycl[i]);
      g2->SetPoint(1,1143.5,vPos_g3ycl[i]);
      // exclusive
    //  g2->SetPoint(2,2686.5,vpUVA3Y[i]);
      g2->SetPoint(3,3169.5,vPos_g1ycl[i]);
      // inclusive
      //g2->SetPoint(2,2305.5,vpZZ2[i]); //inclusive 1
      //g2->SetPoint(2,2327.5,vpZZ1[i]);  //inclusive 2
      //g2->SetPoint(3,2686.5,vpUVA3Y[i]);


      //g2->SetPoint(4,3169.5,vPos_g1ycl[i]);
      //g2->SetPoint(3,3169.5,vPos_g1ycl[i]);    
      TF1* f2 = new TF1("line2","[0]+[1]*x",0,3200);
      g2->Fit("line2","Q");
      double intercept2 = f2->GetParameter(0);
      double slope2     = f2->GetParameter(1);
      double Measuredg2ycl = intercept2 + slope2*0.0;
      double Measuredg3ycl = intercept2 + slope2*1143.5;
     // double MeasuredUVA3Y = intercept2 + slope2*2686.5;
      double Measuredg1ycl = intercept2 + slope2*3169.5;
      //double MeasuredZZ1  = intercept2 + slope2*2327.5;
      //double MeasuredZZ2  = intercept2 + slope2*2305.5;
      //double MeasuredEta5 = intercept2 + slope2*2011.5;
      residualg2ycl->Fill(Measuredg2ycl-vPos_g2ycl[i]);
      residualg3ycl->Fill(Measuredg3ycl-vPos_g3ycl[i]);
     // residualUVA3Y->Fill(MeasuredUVA3Y-vpUVA3Y[i]);
      residualg1ycl->Fill(Measuredg1ycl-vPos_g1ycl[i]);
      //residualZZ1->Fill(MeasuredZZ1-vpZZ1[i]);
      //residualZZ2->Fill(MeasuredZZ2-vpZZ2[i]);
      //residualEta5->Fill(MeasuredEta5-vpEta5[i]);
      //deltayZZ->Fill(vpZZ1[i]-vpZZ2[i]);
      yTrackChi2->Fill(f2->GetChisquare());
      //cout<<f2->GetChisquare()<<endl;
      delete f2; delete g2;
      
      double cosineg3cl = CalculateCosTheta1(vPos_g2xcl[i],vPos_g2ycl[i],vPos_g3xcl[i],vPos_g3ycl[i]);
     // double cosineUVA3 = CalculateCosTheta1(vPos_g2xcl[i],vPos_g2ycl[i],vpUVA3X[i],vPos_g3ycl[i]);
    double cosineg1cl = CalculateCosTheta1(vPos_g2xcl[i],vPos_g2ycl[i],vPos_g1xcl[i],vPos_g1ycl[i]);
     // double cosineEta5 = CalculateCosTheta1(vPos_g2xcl[i],vPos_g2ycl[i],vPos_g2xcl[i],vpEta5[i]);
    angleg3cl->Fill(cosineg3cl);   //angleg3cl_2->Fill(cosineg3cl_2);
     // angleUVA3->Fill(cosineUVA3); //angleUVA3_2->Fill(cosineUVA3_2);
  angleg1cl->Fill(cosineg1cl); //angleg1cl_2->Fill(cosineg1cl_2);
      //angleEta5->Fill(cosineEta5);
      
      nnnn++;
      //if(nnnn%1000==0) cout<<nnnn<<"......"<<endl;
      //if(nnnn>1000) break;
    } //for loop
    //cout<<"after for loop"<<endl;
    gStyle->SetOptFit(1111);

    I2GFvalues myValues;
    myValues = I2GFmainLoop(residualg2xcl, 1, 10 , 1);
    meang2xcl = myValues.mean; sigmag2xcl=myValues.sigma;
    myValues = I2GFmainLoop(residualg2ycl, 1, 10 , 1);
    meang2ycl = myValues.mean; sigmag2ycl=myValues.sigma;
    myValues = I2GFmainLoop(residualg3xcl, 1, 10 , 1);
    meang3xcl = myValues.mean; sigmag3xcl=myValues.sigma;
    myValues = I2GFmainLoop(residualg3ycl, 1, 10 , 1);
    meang3ycl = myValues.mean; sigmag3ycl=myValues.sigma;
   /* myValues = I2GFmainLoop(residualUVA3X, 1, 10 , 1);
    meanUVA3X = myValues.mean; sigmaUVA3X=myValues.sigma;
    myValues = I2GFmainLoop(residualUVA3Y, 1, 10 , 1);
    meanUVA3Y = myValues.mean; sigmaUVA3Y=myValues.sigma;*/
    myValues = I2GFmainLoop(residualg1xcl, 1, 10 , 1);
    meang1xcl = myValues.mean; sigmag1xcl=myValues.sigma;
    myValues = I2GFmainLoop(residualg1ycl, 1, 10 , 1);
    meang1ycl = myValues.mean; sigmag1ycl=myValues.sigma;

    cout<<"residual mean: "<<meang2xcl<<"\t"<<meang2ycl<<"\t"<<meang3xcl<<"\t"<<meang3ycl<<"\t"<</*meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<*/meang1xcl<<"\t"<<meang1ycl<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    fout1<<"residual mean: "<<meang2xcl<<"\t"<<meang2ycl<<"\t"<<meang3xcl<<"\t"<<meang3ycl<<"\t"<</*meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<*/meang1xcl<<"\t"<<meang1ycl<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    /*
    myValues = I2GFmainLoop(dxg3xcl, 1, 10 , 1);
    myValues = I2GFmainLoop(dxUVA3X, 1, 10 , 1);
    myValues = I2GFmainLoop(dxg1xcl, 1, 10 , 1);
    myValues = I2GFmainLoop(dyg3ycl, 1, 10 , 1);
    myValues = I2GFmainLoop(dyUVA3Y, 1, 10 , 1);
    myValues = I2GFmainLoop(dyg1ycl, 1, 10 , 1);
    myValues = I2GFmainLoop(dxUVA3g3cl, 1, 10 , 1);
    myValues = I2GFmainLoop(dxg1clUVA3, 1, 10 , 1);
    myValues = I2GFmainLoop(dxg1clg3cl, 1, 10 , 1);
    myValues = I2GFmainLoop(dyUVA3g3cl, 1, 10 , 1);
    myValues = I2GFmainLoop(dyg1clUVA3, 1, 10 , 1);
    myValues = I2GFmainLoop(dyg1clg3cl, 1, 10 , 1);
    */
    myValues = I2GFmainLoop(angleg3cl, 1, 10 , 1);
    meanAngleg3cl=myValues.mean;
   // myValues = I2GFmainLoop(angleUVA3, 1, 10 , 1);
   // meanAngleUVA3=myValues.mean;
    myValues = I2GFmainLoop(angleg1cl, 1, 10 , 1);
    meanAngleg1cl=myValues.mean;
    //maximum=angleEta5->GetMean(); rms=angleEta5->GetRMS(1); lRange=maximum-rms*0.7; hRange=maximum+rms*0.7;
    //TF1* funAngleEta5=new TF1("funAngleEta5","gaus",lRange,hRange); angleEta5->Fit("funAngleEta5","RQ");
    //meanAngleEta5=funAngleEta5->GetParameter(1);
    //maximum=xTrackChi2->GetMean(); rms=xTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funXTrackChi2=new TF1("funXTrackChi2","gaus",lRange,hRange); xTrackChi2->Fit("funXTrackChi2","RQ");
    meanXChi2=xTrackChi2->GetMean();
    //maximum=yTrackChi2->GetMean(); rms=yTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funYTrackChi2=new TF1("funYTrackChi2","gaus",lRange,hRange); yTrackChi2->Fit("funYTrackChi2","RQ");
    meanYChi2=yTrackChi2->GetMean();
    
    totalAngleg3cl += ag3clg2cl;
   // totalAngleUVA3 += aUVA3g2cl;
    totalAngleg1cl += ag1clg2cl;
    fout3<<sigmag2xcl<<"\t"<<sigmag2ycl<<"\t"<<sigmag3xcl<<"\t"<<sigmag3ycl<<"\t"<</*sigmaUVA3X<<"\t"<<sigmaUVA3Y<<*/"\t"<<sigmag1xcl<<"\t"<<sigmag1ycl<<"\t"<<totalAngleg3cl<<"\t"<</*totalAngleUVA3<<*/"\t"<<totalAngleg1cl<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
    
    f->Write();
    f->Close();
    //delete funPosEta5; delete funPosg1ycl; delete funPosUVA3Y; delete funPosg3ycl; delete funPosg2ycl;
    
    double factor = -0.2;
    //shig2xcl = meang2xcl*factor; shig2ycl = meang2ycl*factor; 
    //shig3xcl = meang3xcl*factor; shig3ycl = meang3ycl*factor; 
    //shiUVA3X = meanUVA3X*factor; shiUVA3Y = meanUVA3Y*factor; 
    //shig1xcl = meang1xcl*factor; shig1ycl = meang1ycl*factor; 
    //shiZZ1 = meanZZ1*factor; shiZZ2 = meanZZ2*factor; 
    //shiEta5 = meanEta5*factor;
    factor=0.2;
    shig2xcl=0.0; shig2ycl=0.0;
    shig3xcl=0.0; shig3ycl=0.0;
//    shiUVA3X=0.0; shiUVA3Y=0.0;
    shig1xcl=0.0; shig1ycl=0.0;
    
    ag3clg2cl = 0.0 ;
  //  aUVA3g2cl = 0.0;
    ag1clg2cl = 0.0;
    //aUVA3g2cl = meanAngleUVA3*factor;
    //ag1clg2cl = meanAngleg1cl*factor;
   // aEta5g2cl = meanAngleEta5*factor;
   // if(iterNb>0) break; // only cylce once.
    //if((meang2xcl>=-0.001 && meang2xcl<=0.001) && (meang2ycl>=-0.001 && meang2ycl<=0.001))
    //  if((meang3xcl>=-0.001 && meang3xcl<=0.001) && (meang3ycl>=-0.001 && meang3ycl<=0.001))
    //    if((meanUVA3X>=-0.001 && meanUVA3X<=0.001) && (meanUVA3Y>=-0.001 && meanUVA3Y<=0.001))
    //    	if((meang1xcl>=-0.001 && meang1xcl<=0.001) && (meang1ycl>=-0.001 && meang1ycl<=0.001) && meanEta5<=0.005)
    //if(meanAngleg3cl>=-0.001 && meanAngleg3cl<=0.001 && meanAngleUVA3>=-0.001 && meanAngleUVA3<=0.001 && meanAngleg1cl>=-0.001 && meanAngleg1cl<=0.001)
    //      {
    //        cout<<"find it...iterating "<<iterNb<<" times."<<endl;
    //        break;
    //      }
  // break;
    if(iterNb==1) break;
 }//while(1)
 fout.close();
 fout1.close();
 fout2.close();
} // entire script

int AlignTrackers_shift_rotate(){
	
  string name[1]={
  	"Position" 
 }; 
{
return false;
}
  for(int i=0;i<1;i++) tracking(name[i]);  
}

double CalculateCosTheta1(double x, double y, double x1,double y1){
	//double cosineTheta = ( x*x1 + y*y1 )/(x*x+y*y);
	double sineTheta = (x1*y - x*y1)/(x*x + y*y);
	//if(cosineTheta>1) cosineTheta=2-cosineTheta;
	//cout<<sineTheta<<endl;
	return asin(sineTheta);
}


