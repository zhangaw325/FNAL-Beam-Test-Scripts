#include <vector>
#include "doubleGausFit_withHistParameter.C"
#include <iostream>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

void tracking(string thestring,double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2Y, double shiREF3X, double shiREF3Y ){

bool verbose = 0;
cout<<"Program Start"<<endl;
  //string thestring = "Hit_Position_Info";
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
  double Pos_g1xcl=0.0, Pos_g1ycl=0.0;
  double Pos_g2xcl=0.0, Pos_g2ycl=0.0;
  double Pos_g3xcl=0.0, Pos_g3ycl=0.0;
  vector<double> vPos_g1xcl; vector<double> vPos_g1ycl;
  vector<double> vPos_g2xcl; vector<double> vPos_g2ycl;
  vector<double> vPos_g3xcl; vector<double> vPos_g3ycl;
 double CalculateCosTheta1(double x, double y, double x1,double y1); 
// vector<double> vpUVA3X; vector<double> vpUVA3Y;
  //vector<double> vpZZ1; vector<double> vpZZ2;
  //vector<double> vpEta5;
  Int_t nbLines=0;
  while(fin>>Pos_g1xcl>>Pos_g1ycl>>Pos_g2xcl>>Pos_g2ycl>>/*pUVA3X>>pUVA3Y>>*/Pos_g3xcl>>Pos_g3ycl/*>>pEta5*/){
	vPos_g1xcl.push_back(Pos_g1xcl); vPos_g1ycl.push_back(Pos_g1ycl);
	vPos_g2xcl.push_back(Pos_g2xcl); vPos_g2ycl.push_back(Pos_g2ycl); vPos_g3xcl.push_back(Pos_g3xcl); vPos_g3ycl.push_back(Pos_g3ycl);
   /* vpUVA3X.push_back(pUVA3X); vpUVA3Y.push_back(pUVA3Y);*/ 
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
  double shiREF2X=10.72, shiREF2Y=1.048;
  double shiREF3X=6.162, shiREF3Y=-3.395;
 // double shiUVA3X=-1.489, shiUVA3Y=15.05;
  double shiREF1X=-10.46, shiREF1Y=-1.496;
  //double shiZZ1=0,   shiZZ2=0;
  double shiEta5=29.5
 */
 //fine alignment parameters
  /* double shiREF1X=61.91, shiREF1Y=55.68;
  double shiREF2X=62.36, shiREF2Y=55.83;
  double shiREF3X=62.72, shiREF3Y=56.06;
  */
  // double shiUVA3X=-8.389, shiUVA3Y=15.779;
  double aREF2REF1=0.00;
  double aREF3REF1=0.00;

  if (verbose)
  	cout<<"ERROR 1 "<<endl;

  
//  double shiREF2X=12.26791212, shiREF2Y=2.02708225;
//  double shiREF3X=7.4824985, shiREF3Y=-2.35562;
 // double shiUVA3X=-0.7097, shiUVA3Y=15.75778;
 // double shiREF1X=-9.92822, shiREF1Y=-0.68756;
 // double shiEta5=29.47;
//  double aREF3REF2=0;//0.0037;//0.01254602;//start angle: 0.01197;
 // double aUVA3REF2=0;//-0.017;//0.00203396;//0.02807;//start angle: 0.01102
//  double aREF1REF2=0;//-0.0486;//-0.0171;//start angle: 0.008273;
  
  //double aEta5REF2;
  double temPos_g2xcl, temPos_g2ycl, temPos_g3xcl, temPos_g3ycl, temPos_g1xcl, temPos_g1ycl;

  double meanREF1X=0.0, meanREF1Y=0.0;
  double meanREF2X=0.0, meanREF2Y=0.0;
  double meanREF3X=0.0, meanREF3Y=0.0;

  double meanAngleREF2=0.0;
  double meanAngleREF3=0.0;

  double sigmag2xcl=0.0,sigmag2ycl=0.0,sigmag3xcl=0.0,sigmag3ycl=0.0,/*sigmaUVA3X=0.0,sigmaUVA3Y=0.0,*/sigmag1xcl=0.0,sigmag1ycl=0.0;
  double totalAngleREF2=0.0,/* totalAngleUVA3=0.0,*/ totalAngleREF3=0.0;
  double meanXChi2=0.0,meanYChi2=0.0; // chi square for tracks.

  Int_t iterNb=0;
  while(1){
    char rootfile[50]; sprintf(rootfile,"_iter%i_exclusive.root",iterNb);
    string outputrootname=ResidualRHead+thestring+rootfile;
    //if (verbose)
  	cout<<"outputroot file name :  "<< outputrootname <<endl;
    TFile* f = new TFile(outputrootname.c_str(),"recreate");
    iterNb++;
    char name1X[15];sprintf(name1X,"posg1xcl_%i",iterNb); char name1Y[15];sprintf(name1Y,"posg1ycl_%i",iterNb);
    char name2X[15];sprintf(name2X,"posg2xcl_%i",iterNb); char name2Y[15];sprintf(name2Y,"posg2ycl_%i",iterNb);
    char name3X[15];sprintf(name3X,"posg3xcl_%i",iterNb); char name3Y[15];sprintf(name3Y,"posg3ycl_%i",iterNb);

    TH1F *hPos_g1xcl = new TH1F(name1X,"",500,-60,60); hPos_g1xcl->SetXTitle("mm"); hPos_g1xcl->SetYTitle("Frequency");hPos_g1xcl->SetLabelSize(0.045,"XY");hPos_g1xcl->SetTitleSize(0.045,"XY");
    TH1F *hPos_g1ycl = new TH1F(name1Y,"",500,-60,60); hPos_g1ycl->SetXTitle("mm"); hPos_g1ycl->SetYTitle("Frequency");hPos_g1ycl->SetLabelSize(0.045,"XY");hPos_g1ycl->SetTitleSize(0.045,"XY");  
    TH1F* hPos_g2xcl = new TH1F(name2X,"",500,-60,60); hPos_g2xcl->SetXTitle("mm"); hPos_g2xcl->SetYTitle("Frequency");hPos_g2xcl->SetLabelSize(0.045,"XY");hPos_g2xcl->SetTitleSize(0.045,"XY");
    TH1F* hPos_g2ycl = new TH1F(name2Y,"",500,-60,60); hPos_g2ycl->SetXTitle("mm"); hPos_g2ycl->SetYTitle("Frequency");hPos_g2ycl->SetLabelSize(0.045,"XY");hPos_g2ycl->SetTitleSize(0.045,"XY");  
    TH1F* hPos_g3xcl = new TH1F(name3X,"",500,-60,60); hPos_g3xcl->SetXTitle("mm"); hPos_g3xcl->SetYTitle("Frequency");hPos_g3xcl->SetLabelSize(0.045,"XY");hPos_g3xcl->SetTitleSize(0.045,"XY");
    TH1F* hPos_g3ycl = new TH1F(name3Y,"",500,-60,60); hPos_g3ycl->SetXTitle("mm"); hPos_g3ycl->SetYTitle("Frequency");hPos_g3ycl->SetLabelSize(0.045,"XY");hPos_g3ycl->SetTitleSize(0.045,"XY");  

    char nameRes1X[20];sprintf(nameRes1X,"residualg1xcl_%i",iterNb);char nameRes1Y[20];sprintf(nameRes1Y,"residualg1ycl_%i",iterNb);
    char nameRes2X[20];sprintf(nameRes2X,"residualg2xcl_%i",iterNb);char nameRes2Y[20];sprintf(nameRes2Y,"residualg2ycl_%i",iterNb);
    char nameRes3X[20];sprintf(nameRes3X,"residualg3xcl_%i",iterNb);char nameRes3Y[20];sprintf(nameRes3Y,"residualg3ycl_%i",iterNb);

    TH1F* residualg1xcl = new TH1F(nameRes1X,"",200,-2,2); residualg1xcl->SetXTitle("mm"); residualg1xcl->SetYTitle("Frequency");residualg1xcl->SetLabelSize(0.045,"XY");residualg1xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg1ycl = new TH1F(nameRes1Y,"",200,-2,2); residualg1ycl->SetXTitle("mm"); residualg1ycl->SetYTitle("Frequency");residualg1ycl->SetLabelSize(0.045,"XY");residualg1ycl->SetTitleSize(0.045,"XY");
    TH1F* residualg2xcl = new TH1F(nameRes2X,"",200,-2,2); residualg2xcl->SetXTitle("Residual [mm]"); residualg2xcl->SetYTitle("Frequency");residualg2xcl->SetLabelSize(0.045,"XY");residualg2xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg2ycl = new TH1F(nameRes2Y,"",200,-2,2); residualg2ycl->SetXTitle("Residual [mm]"); residualg2ycl->SetYTitle("Frequency");residualg2ycl->SetLabelSize(0.045,"XY");residualg2ycl->SetTitleSize(0.045,"XY");
    TH1F* residualg3xcl = new TH1F(nameRes3X,"",200,-2,2); residualg3xcl->SetXTitle("Residual [mm]"); residualg3xcl->SetYTitle("Frequency");residualg3xcl->SetLabelSize(0.045,"XY");residualg3xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg3ycl = new TH1F(nameRes3Y,"",200,-2,2); residualg3ycl->SetXTitle("Residual [mm]"); residualg3ycl->SetYTitle("Frequency");residualg3ycl->SetLabelSize(0.045,"XY");residualg3ycl->SetTitleSize(0.045,"XY");


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
    
    char nameDxUVA3REF3[20]; sprintf(nameDxUVA3REF3,"UVA3X_g3xcl_%i",iterNb);
    char nameDxREF1UVA3[20]; sprintf(nameDxREF1UVA3,"g1xcl_UVA3X_%i",iterNb);
    char nameDxREF1REF3[20]; sprintf(nameDxREF1REF3,"g1xcl_g3xcl_%i",iterNb);
    char nameDyUVA3REF3[20]; sprintf(nameDyUVA3REF3,"UVA3Y_g3ycl_%i",iterNb);
    char nameDyREF1UVA3[20]; sprintf(nameDyREF1UVA3,"g1ycl_UVA3Y_%i",iterNb);
    char nameDyREF1REF3[20]; sprintf(nameDyREF1REF3,"g1ycl_g3ycl_%i",iterNb);
    TH1F* dxUVA3REF3 = new TH1F(nameDxUVA3REF3,"",400,-4,4); dxUVA3REF3->SetXTitle("Delta_X_UVA3X_g3xcl [mm]"); dxUVA3REF3->SetYTitle("Frequency"); dxUVA3REF3->SetLabelSize(0.045,"XY"); dxUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dxREF1UVA3 = new TH1F(nameDxREF1UVA3,"",400,-4,4); dxREF1UVA3->SetXTitle("Delta_X_g1xcl_UVA3X [mm]"); dxREF1UVA3->SetYTitle("Frequency"); dxREF1UVA3->SetLabelSize(0.045,"XY"); dxUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dxREF1REF3 = new TH1F(nameDxREF1REF3,"",400,-4,4); dxREF1REF3->SetXTitle("Delta_X_g1xcl_g3xcl [mm]"); dxREF1REF3->SetYTitle("Frequency"); dxREF1REF3->SetLabelSize(0.045,"XY"); dxREF1REF3->SetTitleSize(0.045,"XY");
    TH1F* dyUVA3REF3 = new TH1F(nameDyUVA3REF3,"",400,-4,4); dyUVA3REF3->SetXTitle("Delta_Y_UVA3Y_g3ycl [mm]"); dyUVA3REF3->SetYTitle("Frequency"); dyUVA3REF3->SetLabelSize(0.045,"XY"); dyUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dyREF1UVA3 = new TH1F(nameDyREF1UVA3,"",400,-4,4); dyREF1UVA3->SetXTitle("Delta_Y_g1ycl_UVA3Y [mm]"); dyREF1UVA3->SetYTitle("Frequency"); dyREF1UVA3->SetLabelSize(0.045,"XY"); dyREF1UVA3->SetTitleSize(0.045,"XY");
    TH1F* dyREF1REF3 = new TH1F(nameDyREF1REF3,"",400,-4,4); dyREF1REF3->SetXTitle("Delta_Y_g1ycl_g3ycl [mm]"); dyREF1REF3->SetYTitle("Frequency"); dyREF1REF3->SetLabelSize(0.045,"XY"); dyREF1REF3->SetTitleSize(0.045,"XY");
    */
    TH1F* angleREF2 = new TH1F("angleREF2","Rotation angle distribution of REF1 and REF2",1000,-0.5,0.5); angleREF2->SetXTitle("Angle [radian]"); angleREF2->SetYTitle("Frequency");
    TH1F* angleREF3 = new TH1F("angleREF3","Rotation angle distribution of REF3 and REF2",1000,-0.5,0.5); angleREF3->SetXTitle("Angle [radian]"); angleREF3->SetYTitle("Frequency");
    //TH1F* angleREF3_2 = new TH1F("angleREF3","Get From Delta_y",2000,-0.5,3.5); angleREF3_2->SetXTitle("Rotation angle of ERF3 and REF2 [radian]"); angleREF3_2->SetYTitle("Frequency");
   // TH1F* angleUVA3 = new TH1F("angleUVA3","Rotation angle distribution of UVA3 and REF2",1000,-0.5,0.5); angleUVA3->SetXTitle("Angle [radian]"); angleUVA3->SetYTitle("Frequency");
    //TH1F* angleUVA3_2 = new TH1F("angleUVA3_2","Get From Delta_y",2000,-0.5,3.5); angleUVA3_2->SetXTitle("Rotation angle of UVA3 and REF2 [radian]"); angleUVA3_2->SetYTitle("Frequency");
    //TH1F* angleREF1_2 = new TH1F("angleREF1_2","Get From Delta_y",2000,-0.5,3.5); angleREF1_2->SetXTitle("Rotation angle of ERF1 and REF2 [radian]"); angleREF1_2->SetYTitle("Frequency");
    //TH1F* angleEta5 = new TH1F("angleEta5","Rotation Eta5 and REF2",1000,-0.5,0.5);
    //delta-y up: 200,-4,4
    //TH1F* deltayZZ = new TH1F("deltaY","",200,-4,4); deltayZZ->SetXTitle("Position difference [mm]");deltayZZ->SetYTitle("Frequency");
    //deltayZZ->SetLabelSize(0.045,"XY");deltayZZ->SetTitleSize(0.045,"XY");
    //cout<<"shift: "<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<"\t"<<shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<shiREF1X<<"\t"<<shiREF1Y<<endl;
    
    TH1F* xTrackChi2 = new TH1F("XTrackChi2","Chi square of tracks in X projection",1000,0,10); xTrackChi2->SetXTitle("#chi^{2} of track in X"); xTrackChi2->SetYTitle("Frequency"); xTrackChi2->SetTitleSize(0.04,"XY"); xTrackChi2->SetLabelSize(0.04,"XY");
    TH1F* yTrackChi2 = new TH1F("YTrackChi2","Chi square of tracks in Y projection",1000,0,10); yTrackChi2->SetXTitle("#chi^{2} of track in Y"); yTrackChi2->SetYTitle("Frequency"); yTrackChi2->SetTitleSize(0.04,"XY"); yTrackChi2->SetLabelSize(0.04,"XY");

    if (verbose)
    	cout<<"Successfully Defined all histogram"<<endl;
    
    fout<<"shift: "<<shiREF1X<<"\t"<<shiREF1Y<<"\t"<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<</*shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<*/shiREF3X<<"\t"<<shiREF3Y<<endl;
    fout2<<"rotation: "<<aREF2REF1<<"\t"<</*aUVA3REF2<<"\t"<<*/aREF3REF1<<endl;
    if (verbose)
    {
    cout<<"shift: "<<shiREF1X<<"\t"<<shiREF1Y<<"\t"<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<</*shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<*/shiREF3X<<"\t"<<shiREF3Y<<endl;
    cout<<"rotation: "<<aREF2REF1<<"\t"<</*aUVA3REF2<<"\t"<<*/aREF3REF1<<endl;
	cout<<"===============================>vPos size = "<< vPos_g1xcl.size() <<endl;
    }
    int nnnn=0;
    for(Int_t i=0;i<vPos_g1xcl.size();i++){
    	//shift
      if (verbose)
      	cout<<"ERROR 2 "<<endl;
      vPos_g1xcl[i] = vPos_g1xcl[i] - shiREF1X; vPos_g1ycl[i] = vPos_g1ycl[i] - shiREF1Y;
      vPos_g2xcl[i] = vPos_g2xcl[i] - shiREF2X; vPos_g2ycl[i] = vPos_g2ycl[i] - shiREF2Y;      
      vPos_g3xcl[i] = vPos_g3xcl[i] - shiREF3X; vPos_g3ycl[i] = vPos_g3ycl[i] - shiREF3Y;
      temPos_g2xcl=vPos_g2xcl[i]; temPos_g2ycl=vPos_g2ycl[i]; temPos_g3xcl=vPos_g3xcl[i]; temPos_g3ycl=vPos_g3ycl[i]; 
      temPos_g1xcl=vPos_g1xcl[i]; temPos_g1ycl=vPos_g1ycl[i]; 

      //rotate back
      vPos_g2xcl[i]=temPos_g2xcl*cos(aREF2REF1)-temPos_g2ycl*sin(aREF2REF1);
      vPos_g2ycl[i]=temPos_g2xcl*sin(aREF2REF1)+temPos_g2ycl*cos(aREF2REF1);
      vPos_g3xcl[i]=temPos_g3xcl*cos(aREF3REF1)-temPos_g3ycl*sin(aREF3REF1);
      vPos_g3ycl[i]=temPos_g3xcl*sin(aREF3REF1)+temPos_g3ycl*cos(aREF3REF1);

      hPos_g1xcl->Fill(vPos_g1xcl[i]); hPos_g1ycl->Fill(vPos_g1ycl[i]);
      hPos_g2xcl->Fill(vPos_g2xcl[i]); hPos_g2ycl->Fill(vPos_g2ycl[i]);
      hPos_g3xcl->Fill(vPos_g3xcl[i]); hPos_g3ycl->Fill(vPos_g3ycl[i]);
      /*
      dxg3xcl->Fill(vPos_g3xcl[i]-vPos_g2xcl[i]); dyg3ycl->Fill(vPos_g3ycl[i]-vPos_g2ycl[i]);
      dxUVA3X->Fill(vpUVA3X[i]-vPos_g2xcl[i]); dyUVA3Y->Fill(vpUVA3Y[i]-vPos_g2ycl[i]);
      dxg1xcl->Fill(vPos_g1xcl[i]-vPos_g2xcl[i]); dyg1ycl->Fill(vPos_g1ycl[i]-vPos_g2ycl[i]);
      dxUVA3REF3->Fill(vpUVA3X[i]-vPos_g3xcl[i]); dyUVA3REF3->Fill(vpUVA3Y[i]-vPos_g3ycl[i]);
      dxREF1UVA3->Fill(vPos_g1xcl[i]-vpUVA3X[i]); dyREF1UVA3->Fill(vPos_g1ycl[i]-vpUVA3Y[i]);
      dxREF1REF3->Fill(vPos_g1xcl[i]-vPos_g3xcl[i]); dyREF1REF3->Fill(vPos_g1ycl[i]-vPos_g3ycl[i]);
      */
      TGraph* g1 = new TGraph();
      g1->SetPoint(0,100, vPos_g1xcl[i]);
      g1->SetPoint(1,380, vPos_g2xcl[i]);
      g1->SetPoint(2,830, vPos_g3xcl[i]);

      TF1* f1 = new TF1("line1","[0]+[1]*x",0,900);
      g1->Fit("line1","Q");
      double intercept1 = f1->GetParameter(0);
      double slope1     = f1->GetParameter(1);
      double Measuredg1xcl = intercept1 + slope1*100.;
      double Measuredg2xcl = intercept1 + slope1*380.;
      double Measuredg3xcl = intercept1 + slope1*830.;
      if (verbose)
      cout<<"measured = "<< Measuredg2xcl <<"\tvPos = "<< vPos_g2xcl[i] <<"\tresidualg2xcl = "<<Measuredg2xcl-vPos_g2xcl[i]<<endl;
      residualg2xcl->Fill(Measuredg2xcl-vPos_g2xcl[i]);
      residualg3xcl->Fill(Measuredg3xcl-vPos_g3xcl[i]);
      residualg1xcl->Fill(Measuredg1xcl-vPos_g1xcl[i]);
      xTrackChi2->Fill(f1->GetChisquare());
  if (verbose)
      cout<<f1->GetChisquare()<<"\t";
      delete f1; delete g1;

      TGraph* g2 = new TGraph();
      g2->SetPoint(0,100, vPos_g1ycl[i]);
      g2->SetPoint(1,380, vPos_g2ycl[i]);
      g2->SetPoint(2,830, vPos_g3ycl[i]);
      // inclusive
      //g2->SetPoint(2,2305.5,vpZZ2[i]); //inclusive 1
      //g2->SetPoint(2,2327.5,vpZZ1[i]);  //inclusive 2
      //g2->SetPoint(3,2686.5,vpUVA3Y[i]);

  if (verbose)
cout<<"test"<<  endl;

      TF1* f2 = new TF1("line2","[0]+[1]*x",0,900);
      g2->Fit("line2","Q");
      double intercept2 = f2->GetParameter(0);
      double slope2     = f2->GetParameter(1);
      double Measuredg1ycl = intercept2 + slope2*100.;
      double Measuredg2ycl = intercept2 + slope2*380.;
      double Measuredg3ycl = intercept2 + slope2*830.;

      residualg2ycl->Fill(Measuredg2ycl-vPos_g2ycl[i]);
      residualg3ycl->Fill(Measuredg3ycl-vPos_g3ycl[i]);
      residualg1ycl->Fill(Measuredg1ycl-vPos_g1ycl[i]);

      yTrackChi2->Fill(f2->GetChisquare());
  if (verbose)
      cout<<f2->GetChisquare()<<endl;
      delete f2; delete g2;
      
      double cosineREF2 = CalculateCosTheta1(vPos_g1xcl[i],vPos_g1ycl[i],vPos_g2xcl[i],vPos_g2ycl[i]);
     // double cosineUVA3 = CalculateCosTheta1(vPos_g2xcl[i],vPos_g2ycl[i],vpUVA3X[i],vPos_g3ycl[i]);
      double cosineREF3 = CalculateCosTheta1(vPos_g1xcl[i],vPos_g1ycl[i],vPos_g3xcl[i],vPos_g3ycl[i]);
     // double cosineEta5 = CalculateCosTheta1(vPos_g2xcl[i],vPos_g2ycl[i],vPos_g2xcl[i],vpEta5[i]);
      angleREF2->Fill(cosineREF2);   //angleREF3_2->Fill(cosineREF3_2);
     // angleUVA3->Fill(cosineUVA3); //angleUVA3_2->Fill(cosineUVA3_2);
      angleREF3->Fill(cosineREF3); //angleREF1_2->Fill(cosineREF1_2);
      //angleEta5->Fill(cosineEta5);
      
      nnnn++;
      //if(nnnn%1000==0) cout<<nnnn<<"......"<<endl;
      //if(nnnn>1000) break;
    } //for loop
    //cout<<"after for loop"<<endl;
    gStyle->SetOptFit(1111);
//
    I2GFvalues myValues;
    if (verbose) cout<<"=========================>Passed 1 "<<endl;
    TH1F *residualg1xcl_tmp = (TH1F*) residualg1xcl->Clone("residualg1xcl_tmp");
    TH1F *residualg1ycl_tmp = (TH1F*) residualg1ycl->Clone("residualg1ycl_tmp");
    TH1F *residualg2xcl_tmp = (TH1F*) residualg2xcl->Clone("residualg2xcl_tmp");
    TH1F *residualg2ycl_tmp = (TH1F*) residualg2ycl->Clone("residualg2ycl_tmp");
    TH1F *residualg3xcl_tmp = (TH1F*) residualg3xcl->Clone("residualg3xcl_tmp");
    TH1F *residualg3ycl_tmp = (TH1F*) residualg3ycl->Clone("residualg3ycl_tmp");
    myValues = I2GFmainLoop(residualg2xcl_tmp, 1, 10 , 1);
    if (verbose) cout<<"=========================>Passed 2 "<<endl;
    meanREF2X = myValues.mean; sigmag2xcl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 2 "<<endl;
    myValues = I2GFmainLoop(residualg2ycl_tmp, 1, 10 , 1);
    meanREF2Y = myValues.mean; sigmag2ycl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 3 "<<endl;
    myValues = I2GFmainLoop(residualg3xcl_tmp, 1, 10 , 1);
    meanREF3X = myValues.mean; sigmag3xcl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 4 "<<endl;
    myValues = I2GFmainLoop(residualg3ycl_tmp, 1, 10 , 1);
    meanREF3Y = myValues.mean; sigmag3ycl=myValues.sigma;
   /* myValues = I2GFmainLoop(residualUVA3X, 1, 10 , 1);
    meanUVA3X = myValues.mean; sigmaUVA3X=myValues.sigma;
    myValues = I2GFmainLoop(residualUVA3Y, 1, 10 , 1);
    meanUVA3Y = myValues.mean; sigmaUVA3Y=myValues.sigma;*/
    if (verbose) cout<<"=========================>Passed 5 "<<endl;
    myValues = I2GFmainLoop(residualg1xcl_tmp, 1, 10 , 1);
    meanREF1X = myValues.mean; sigmag1xcl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 6 "<<endl;
    myValues = I2GFmainLoop(residualg1ycl_tmp, 1, 10 , 1);
    meanREF1Y = myValues.mean; sigmag1ycl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 7 "<<endl;
//
  if (verbose)
    cout<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<</*meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<*/meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    fout1<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<</*meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<*/meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    /*
    myValues = I2GFmainLoop(dxg3xcl, 1, 10 , 1);
    myValues = I2GFmainLoop(dxUVA3X, 1, 10 , 1);
    myValues = I2GFmainLoop(dxg1xcl, 1, 10 , 1);
    myValues = I2GFmainLoop(dyg3ycl, 1, 10 , 1);
    myValues = I2GFmainLoop(dyUVA3Y, 1, 10 , 1);
    myValues = I2GFmainLoop(dyg1ycl, 1, 10 , 1);
    myValues = I2GFmainLoop(dxUVA3REF3, 1, 10 , 1);
    myValues = I2GFmainLoop(dxREF1UVA3, 1, 10 , 1);
    myValues = I2GFmainLoop(dxREF1REF3, 1, 10 , 1);
    myValues = I2GFmainLoop(dyUVA3REF3, 1, 10 , 1);
    myValues = I2GFmainLoop(dyREF1UVA3, 1, 10 , 1);
    myValues = I2GFmainLoop(dyREF1REF3, 1, 10 , 1);
    */
    TH1F *angleREF2_tmp = (TH1F*) angleREF2->Clone("angleREF2_tmp");
    TH1F *angleREF3_tmp = (TH1F*) angleREF3->Clone("angleREF3_tmp");
    myValues = I2GFmainLoop(angleREF2_tmp, 1, 10 , 1);
    if (verbose) cout<<"=========================>Passed 8 "<<endl;
    meanAngleREF2=myValues.mean;
    myValues = I2GFmainLoop(angleREF3_tmp, 1, 10 , 1);
    if (verbose) cout<<"=========================>Passed 9 "<<endl;
    meanAngleREF3=myValues.mean;




    //maximum=angleEta5->GetMean(); rms=angleEta5->GetRMS(1); lRange=maximum-rms*0.7; hRange=maximum+rms*0.7;
    //TF1* funAngleEta5=new TF1("funAngleEta5","gaus",lRange,hRange); angleEta5->Fit("funAngleEta5","RQ");
    //meanAngleEta5=funAngleEta5->GetParameter(1);
    //maximum=xTrackChi2->GetMean(); rms=xTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funXTrackChi2=new TF1("funXTrackChi2","gaus",lRange,hRange); xTrackChi2->Fit("funXTrackChi2","RQ");
    meanXChi2=xTrackChi2->GetMean();
    //maximum=yTrackChi2->GetMean(); rms=yTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funYTrackChi2=new TF1("funYTrackChi2","gaus",lRange,hRange); yTrackChi2->Fit("funYTrackChi2","RQ");
    meanYChi2=yTrackChi2->GetMean();
    
    totalAngleREF2 += aREF2REF1;
   // totalAngleUVA3 += aUVA3REF2;
    totalAngleREF3 += aREF3REF1;
    fout3<<sigmag1xcl<<"\t"<<sigmag1ycl<<"\t"<<sigmag2xcl<<"\t"<<sigmag2ycl<<"\t"<</*sigmaUVA3X<<"\t"<<sigmaUVA3Y<<*/"\t"<<sigmag3xcl<<"\t"<<sigmag3ycl<<"\t"<<totalAngleREF2<<"\t"<</*totalAngleUVA3<<*/"\t"<<totalAngleREF3<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
    cout<<sigmag1xcl<<"\t"<<sigmag1ycl<<"\t"<<sigmag2xcl<<"\t"<<sigmag2ycl<<"\t"<</*sigmaUVA3X<<"\t"<<sigmaUVA3Y<<*/"\t"<<sigmag3xcl<<"\t"<<sigmag3ycl<<"\t"<<totalAngleREF2<<"\t"<</*totalAngleUVA3<<*/"\t"<<totalAngleREF3<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
    
    f->Write();
    f->Close();
    //delete funPosEta5; delete funPosg1ycl; delete funPosUVA3Y; delete funPosg3ycl; delete funPosg2ycl;
    
    double factor = -0.2;
    shiREF1X = meanREF1X*factor; shiREF1Y = meanREF1Y*factor; 
    shiREF2X = meanREF2X*factor; shiREF2Y = meanREF2Y*factor; 
    shiREF3X = meanREF3X*factor; shiREF3Y = meanREF3Y*factor; 
    factor=0.2;
    
    aREF2REF1 = meanAngleREF2*factor;
    aREF3REF1 = meanAngleREF3*factor;
   // aEta5REF2 = meanAngleEta5*factor;
   // if(iterNb>0) break; // only cylce once.
    if((meanREF1X>=-0.05 && meanREF1X<=0.05) && (meanREF1Y>=-0.05 && meanREF1Y<=0.05))
    if((meanREF2X>=-0.05 && meanREF2X<=0.05) && (meanREF2Y>=-0.05 && meanREF2Y<=0.05))
    if((meanREF3X>=-0.05 && meanREF3X<=0.05) && (meanREF3Y>=-0.05 && meanREF3Y<=0.05))
    if(meanAngleREF3>=-0.05 && meanAngleREF3<=0.05 && meanAngleREF2>=-0.05 && meanAngleREF2<=0.05)
          {
            cout<<"find it...iterating "<<iterNb<<" times."<<endl;
            break;
          }
  // break;
    if(iterNb==50) break;

 }//while(1)
 fout.close();
 fout1.close();
 fout2.close();
} // entire script

  /* double shiREF1X =61.91, shiREF1Y =55.68;
  double shiREF2X =62.36, shiREF2Y =55.83;
  double shiREF3X =62.72, shiREF3Y =56.06;
  */
int AlignTrackers_shift_rotate(string name, double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2Y, double shiREF3X, double shiREF3Y ){
	
//  string name={"Position"}; 
 cout<<"Name of input file = "<<name<<endl;
  name={"Position"}; 
cout<<"Start of program"<<endl;
for(int i=0;i<1;i++) tracking(name, shiREF1X, shiREF1Y, shiREF2X, shiREF2Y, shiREF3X, shiREF3Y);  
return 0;
}

double CalculateCosTheta1(double x, double y, double x1,double y1){
	//double cosineTheta = ( x*x1 + y*y1 )/(x*x+y*y);
	double sineTheta = (x1*y - x*y1)/(x*x + y*y);
	//if(cosineTheta>1) cosineTheta=2-cosineTheta;
	//cout<<sineTheta<<endl;
	return asin(sineTheta);
}


