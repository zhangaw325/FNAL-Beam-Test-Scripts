#include <vector.h>
#include "doubleGausFit_withHistParameter.C"

void tracking(string thestring){
  //string thestring = "Position_REF2X_42_48";
  string txtfilename = thestring + ".txt";
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
  double pREF1X=0.0, pREF1Y=0.0;
  double pREF2X=0.0, pREF2Y=0.0;
  double pREF3X=0.0, pREF3Y=0.0;
  //double pZZ1=0.0, pZZ2=0.0;
  //double pEta5=0.0;
  vector<double> vpREF1X; vector<double> vpREF1Y;
  vector<double> vpREF2X; vector<double> vpREF2Y;
  vector<double> vpREF3X; vector<double> vpREF3Y;
  //vector<double> vpZZ1; vector<double> vpZZ2;
  //vector<double> vpEta5;
  Int_t nbLines=0;
  while(fin>>pREF1X>>pREF1Y>>pREF2X>>pREF2Y>>pREF3X>>pREF3Y/*>>pEta5*/){
    vpREF2X.push_back(pREF2X); vpREF2Y.push_back(pREF2Y); vpREF3X.push_back(pREF3X); vpREF3Y.push_back(pREF3Y);
    vpREF1X.push_back(pREF1X); vpREF1Y.push_back(pREF1Y);
    //vpZZ1.push_back(pZZ1); vpZZ2.push_back(pZZ2);
    //vpEta5.push_back(pEta5);
    nbLines++;
  }
  fin.close();
  /*
  REF2X:
      [-30,-20]: -22.98, 1.089, -28.29, -3.209, -37.22, 14.88, -46.62, -2.411, 29.84
      [-20,-15]: -17.07, 0.4154, -22.27, -3.92, -31.12, 14.55, -40.55, -2.637, 29.48
  */
  /* coarse alignment parameters
  double shiREF2X=10.72, shiREF2Y=1.048;
  double shiREF3X=6.162, shiREF3Y=-3.395;
  double shiUVA3X=-1.489, shiUVA3Y=15.05;
  double shiREF1X=-10.46, shiREF1Y=-1.496;
  //double shiZZ1=0,   shiZZ2=0;
  double shiEta5=29.5;
 */
 //fine alignment parameters
 /*
  double shiREF2X=3.656, shiREF2Y=1.865;
  double shiREF3X=-1.781, shiREF3Y=-2.415;
  double shiUVA3X=-8.389, shiUVA3Y=15.779;
  double shiREF1X=-17.504, shiREF1Y=-0.844;
  double aREF3REF2=0.009499;
  double aUVA3REF2=-0.004731;
  double aREF1REF2=-0.02473;
  */
  
  double shiREF2X=12.26791212, shiREF2Y=2.02708225;
  double shiREF3X=7.4824985, shiREF3Y=-2.35562;
  double shiUVA3X=-0.7097, shiUVA3Y=15.75778;
  double shiREF1X=-9.92822, shiREF1Y=-0.68756;
  double shiEta5=29.47;
  double aREF3REF2=-0.02;//0.0037;//0.01254602;//start angle: 0.01197;
  double aUVA3REF2=-0.004971;//-0.017;//0.00203396;//0.02807;//start angle: 0.01102
  double aREF1REF2=-0.02446;//-0.0486;//-0.0171;//start angle: 0.008273;
  
  //double aEta5REF2;
  double tempREF2X, tempREF2Y, tempREF3X, tempREF3Y, tempUVA3X, tempUVA3Y, tempREF1X, tempREF1Y, tempEta5;

  double meanREF2X=0.0, meanREF2Y=0.0;
  double meanREF3X=0.0, meanREF3Y=0.0;
  double meanUVA3X=0.0, meanUVA3Y=0.0;
  double meanREF1X=0.0, meanREF1Y=0.0;
  //double meanZZ1=0.0, meanZZ2=0.0;
  //double meanEta5=0;
  double meanAngleREF3=0.0;
  double meanAngleUVA3=0.0;
  double meanAngleREF1=0.0;
  //double meanAngleEta5=0.0;
  double sigmaREF2X=0.0,sigmaREF2Y=0.0,sigmaREF3X=0.0,sigmaREF3Y=0.0,sigmaUVA3X=0.0,sigmaUVA3Y=0.0,sigmaREF1X=0.0,sigmaREF1Y=0.0;
  double totalAngleREF3=0.0, totalAngleUVA3=0.0, totalAngleREF1=0.0;
  double meanXChi2=0.0,meanYChi2=0.0; // chi square for tracks.

  Int_t iterNb=0;
  while(1){
    char rootfile[50]; sprintf(rootfile,"_iter%i_exclusive.root",iterNb);
    string outputrootname=ResidualRHead+thestring+rootfile;
    TFile* f = new TFile(outputrootname.c_str(),"recreate");
    iterNb++;
    char name2X[15];sprintf(name2X,"posREF2X_%i",iterNb); char name2Y[15];sprintf(name2Y,"posREF2Y_%i",iterNb);
    char name3X[15];sprintf(name3X,"posREF3X_%i",iterNb); char name3Y[15];sprintf(name3Y,"posREF3Y_%i",iterNb);
    char nameu3X[15];sprintf(nameu3X,"posUVA3X_%i",iterNb);char nameu3Y[15];sprintf(nameu3Y,"posUVA3Y_%i",iterNb);
    char name1X[15];sprintf(name1X,"posREF1X_%i",iterNb); char name1Y[15];sprintf(name1Y,"posREF1Y_%i",iterNb);
    //char nameZZ1[15];sprintf(nameZZ1,"pos10cmZZ1_%i",iterNb); char nameZZ2[15];sprintf(nameZZ2,"pos10cmZZ2_%i",iterNb);
    //char nameEta5[15];sprintf(nameEta5,"posEta5_%i",iterNb); 
    TH1F* hpREF2X = new TH1F(name2X,"",500,-50,50); hpREF2X->SetXTitle("mm"); hpREF2X->SetYTitle("Frequency");hpREF2X->SetLabelSize(0.045,"XY");hpREF2X->SetTitleSize(0.045,"XY");
    TH1F* hpREF2Y = new TH1F(name2Y,"",500,-50,50); hpREF2Y->SetXTitle("mm"); hpREF2Y->SetYTitle("Frequency");hpREF2Y->SetLabelSize(0.045,"XY");hpREF2Y->SetTitleSize(0.045,"XY");  
    TH1F* hpREF3X = new TH1F(name3X,"",500,-50,50); hpREF3X->SetXTitle("mm"); hpREF3X->SetYTitle("Frequency");hpREF3X->SetLabelSize(0.045,"XY");hpREF3X->SetTitleSize(0.045,"XY");
    TH1F* hpREF3Y = new TH1F(name3Y,"",500,-50,50); hpREF3Y->SetXTitle("mm"); hpREF3Y->SetYTitle("Frequency");hpREF3Y->SetLabelSize(0.045,"XY");hpREF3Y->SetTitleSize(0.045,"XY");  
    TH1F* hpUVA3X = new TH1F(nameu3X,"",500,-50,50); hpUVA3X->SetXTitle("mm"); hpUVA3X->SetYTitle("Frequency");hpUVA3X->SetLabelSize(0.045,"XY");hpUVA3X->SetTitleSize(0.045,"XY");
    TH1F* hpUVA3Y = new TH1F(nameu3Y,"",500,-50,50); hpUVA3Y->SetXTitle("mm"); hpUVA3Y->SetYTitle("Frequency");hpUVA3Y->SetLabelSize(0.045,"XY");hpUVA3Y->SetTitleSize(0.045,"XY");  
    TH1F* hpREF1X = new TH1F(name1X,"",500,-50,50); hpREF1X->SetXTitle("mm"); hpREF1X->SetYTitle("Frequency");hpREF1X->SetLabelSize(0.045,"XY");hpREF1X->SetTitleSize(0.045,"XY");
    TH1F* hpREF1Y = new TH1F(name1Y,"",500,-50,50); hpREF1Y->SetXTitle("mm"); hpREF1Y->SetYTitle("Frequency");hpREF1Y->SetLabelSize(0.045,"XY");hpREF1Y->SetTitleSize(0.045,"XY");  
    //TH1F* hpZZ1 = new TH1F(nameZZ1,"",600,-150,150); hpZZ1->SetXTitle("mm"); hpZZ1->SetYTitle("Frequency"); hpZZ1->SetLabelSize(0.045,"XY");hpZZ1->SetTitleSize(0.045,"XY");
    //TH1F* hpZZ2 = new TH1F(nameZZ2,"",600,-150,150); hpZZ2->SetXTitle("mm"); hpZZ2->SetYTitle("Frequency"); hpZZ2->SetLabelSize(0.045,"XY");hpZZ2->SetTitleSize(0.045,"XY");
    //TH1F* hpEta5 = new TH1F(nameEta5,"",600,-150,150); hpEta5->SetXTitle("mm"); hpEta5->SetYTitle("Frequency"); hpEta5->SetLabelSize(0.045,"XY");hpEta5->SetTitleSize(0.045,"XY");
    char nameRes2X[20];sprintf(nameRes2X,"residualREF2X_%i",iterNb);char nameRes2Y[20];sprintf(nameRes2Y,"residualREF2Y_%i",iterNb);
    char nameRes3X[20];sprintf(nameRes3X,"residualREF3X_%i",iterNb);char nameRes3Y[20];sprintf(nameRes3Y,"residualREF3Y_%i",iterNb);
    char nameResu3X[20];sprintf(nameResu3X,"residualUVA3X_%i",iterNb);char nameResu3Y[20];sprintf(nameResu3Y,"residualUVA3Y_%i",iterNb);
    char nameRes1X[20];sprintf(nameRes1X,"residualREF1X_%i",iterNb);char nameRes1Y[20];sprintf(nameRes1Y,"residualREF1Y_%i",iterNb);
    //char nameResZZ1[20];sprintf(nameResZZ1,"residualZZ1_%i",iterNb);char nameResZZ2[20];sprintf(nameResZZ2,"residualZZ2_%i",iterNb);
    //char nameResEta5[20];sprintf(nameResEta5,"residualEta5_%i",iterNb);
    TH1F* residualREF2X = new TH1F(nameRes2X,"",200,-2,2); residualREF2X->SetXTitle("Residual [mm]"); residualREF2X->SetYTitle("Frequency");residualREF2X->SetLabelSize(0.045,"XY");residualREF2X->SetTitleSize(0.045,"XY");
    TH1F* residualREF2Y = new TH1F(nameRes2Y,"",200,-2,2); residualREF2Y->SetXTitle("Residual [mm]"); residualREF2Y->SetYTitle("Frequency");residualREF2Y->SetLabelSize(0.045,"XY");residualREF2Y->SetTitleSize(0.045,"XY");
    TH1F* residualREF3X = new TH1F(nameRes3X,"",200,-2,2); residualREF3X->SetXTitle("Residual [mm]"); residualREF3X->SetYTitle("Frequency");residualREF3X->SetLabelSize(0.045,"XY");residualREF3X->SetTitleSize(0.045,"XY");
    TH1F* residualREF3Y = new TH1F(nameRes3Y,"",200,-2,2); residualREF3Y->SetXTitle("Residual [mm]"); residualREF3Y->SetYTitle("Frequency");residualREF3Y->SetLabelSize(0.045,"XY");residualREF3Y->SetTitleSize(0.045,"XY");
    TH1F* residualUVA3X = new TH1F(nameResu3X,"",200,-2,2); residualUVA3X->SetXTitle("Residual [mm]"); residualUVA3X->SetYTitle("Frequency");residualUVA3X->SetLabelSize(0.045,"XY");residualUVA3X->SetTitleSize(0.045,"XY");
    TH1F* residualUVA3Y = new TH1F(nameResu3Y,"",200,-2,2); residualUVA3Y->SetXTitle("Residual [mm]"); residualUVA3Y->SetYTitle("Frequency");residualUVA3Y->SetLabelSize(0.045,"XY");residualUVA3Y->SetTitleSize(0.045,"XY");
    TH1F* residualREF1X = new TH1F(nameRes1X,"",200,-2,2); residualREF1X->SetXTitle("mm"); residualREF1X->SetYTitle("Frequency");residualREF1X->SetLabelSize(0.045,"XY");residualREF1X->SetTitleSize(0.045,"XY");
    TH1F* residualREF1Y = new TH1F(nameRes1Y,"",200,-2,2); residualREF1Y->SetXTitle("mm"); residualREF1Y->SetYTitle("Frequency");residualREF1Y->SetLabelSize(0.045,"XY");residualREF1Y->SetTitleSize(0.045,"XY");
    //TH1F* residualZZ1 = new TH1F(nameResZZ1,"",320,-16,16); residualZZ1->SetXTitle("Residual [mm]"); residualZZ1->SetYTitle("Frequency");residualZZ1->SetLabelSize(0.045,"XY");residualZZ1->SetTitleSize(0.045,"XY");
    //TH1F* residualZZ2 = new TH1F(nameResZZ2,"",320,-16,16); residualZZ2->SetXTitle("Residual [mm]"); residualZZ2->SetYTitle("Frequency");residualZZ2->SetLabelSize(0.045,"XY");residualZZ2->SetTitleSize(0.045,"XY");
    //TH1F* residualEta5 = new TH1F(nameResEta5,"",320,-16,16); residualEta5->SetXTitle("Residual [mm]"); residualEta5->SetYTitle("Frequency");residualEta5->SetLabelSize(0.045,"XY");residualEta5->SetTitleSize(0.045,"XY");
    /*
    char nameDxREF3X[20]; sprintf(nameDxREF3X,"REF3X_REF2X_%i",iterNb); char nameDyREF3Y[20]; sprintf(nameDyREF3Y,"REF3Y_REF2Y_%i",iterNb); 
    char nameDxUVA3X[20]; sprintf(nameDxUVA3X,"UVA3X_REF2X_%i",iterNb); char nameDyUVA3Y[20]; sprintf(nameDyUVA3Y,"UVA3Y_REF2Y_%i",iterNb); 
    char nameDxREF1X[20]; sprintf(nameDxREF1X,"REF1X_REF2X_%i",iterNb); char nameDyREF1Y[20]; sprintf(nameDyREF1Y,"REF1Y_REF2Y_%i",iterNb); 
    TH1F* dxREF3X = new TH1F(nameDxREF3X,"",400,-4,4); dxREF3X->SetXTitle("Delta_X_REF3X_REF2X [mm]"); dxREF3X->SetYTitle("Frequency");dxREF3X->SetLabelSize(0.045,"XY"); dxREF3X->SetTitleSize(0.045,"XY");
    TH1F* dxUVA3X = new TH1F(nameDxUVA3X,"",400,-4,4); dxUVA3X->SetXTitle("Delta_X_UVA3X_REF2X [mm]"); dxUVA3X->SetYTitle("Frequency");dxUVA3X->SetLabelSize(0.045,"XY"); dxUVA3X->SetTitleSize(0.045,"XY");
    TH1F* dxREF1X = new TH1F(nameDxREF1X,"",400,-4,4); dxREF1X->SetXTitle("Delta_X_REF1X_REF2X [mm]"); dxREF1X->SetYTitle("Frequency");dxREF1X->SetLabelSize(0.045,"XY"); dxREF1X->SetTitleSize(0.045,"XY");
    TH1F* dyREF3Y = new TH1F(nameDyREF3Y,"",400,-4,4); dyREF3Y->SetXTitle("Delta_Y_REF3Y_REF2Y [mm]"); dyREF3Y->SetYTitle("Frequency");dyREF3Y->SetLabelSize(0.045,"XY"); dyREF3Y->SetTitleSize(0.045,"XY");
    TH1F* dyUVA3Y = new TH1F(nameDyUVA3Y,"",400,-4,4); dyUVA3Y->SetXTitle("Delta_Y_UVA3Y_REF2Y [mm]"); dyUVA3Y->SetYTitle("Frequency");dyUVA3Y->SetLabelSize(0.045,"XY"); dyUVA3Y->SetTitleSize(0.045,"XY");
    TH1F* dyREF1Y = new TH1F(nameDyREF1Y,"",400,-4,4); dyREF1Y->SetXTitle("Delta_Y_REF1Y_REF2Y [mm]"); dyREF1Y->SetYTitle("Frequency");dyREF1Y->SetLabelSize(0.045,"XY"); dyREF1Y->SetTitleSize(0.045,"XY");
    
    char nameDxUVA3REF3[20]; sprintf(nameDxUVA3REF3,"UVA3X_REF3X_%i",iterNb);
    char nameDxREF1UVA3[20]; sprintf(nameDxREF1UVA3,"REF1X_UVA3X_%i",iterNb);
    char nameDxREF1REF3[20]; sprintf(nameDxREF1REF3,"REF1X_REF3X_%i",iterNb);
    char nameDyUVA3REF3[20]; sprintf(nameDyUVA3REF3,"UVA3Y_REF3Y_%i",iterNb);
    char nameDyREF1UVA3[20]; sprintf(nameDyREF1UVA3,"REF1Y_UVA3Y_%i",iterNb);
    char nameDyREF1REF3[20]; sprintf(nameDyREF1REF3,"REF1Y_REF3Y_%i",iterNb);
    TH1F* dxUVA3REF3 = new TH1F(nameDxUVA3REF3,"",400,-4,4); dxUVA3REF3->SetXTitle("Delta_X_UVA3X_REF3X [mm]"); dxUVA3REF3->SetYTitle("Frequency"); dxUVA3REF3->SetLabelSize(0.045,"XY"); dxUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dxREF1UVA3 = new TH1F(nameDxREF1UVA3,"",400,-4,4); dxREF1UVA3->SetXTitle("Delta_X_REF1X_UVA3X [mm]"); dxREF1UVA3->SetYTitle("Frequency"); dxREF1UVA3->SetLabelSize(0.045,"XY"); dxUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dxREF1REF3 = new TH1F(nameDxREF1REF3,"",400,-4,4); dxREF1REF3->SetXTitle("Delta_X_REF1X_REF3X [mm]"); dxREF1REF3->SetYTitle("Frequency"); dxREF1REF3->SetLabelSize(0.045,"XY"); dxREF1REF3->SetTitleSize(0.045,"XY");
    TH1F* dyUVA3REF3 = new TH1F(nameDyUVA3REF3,"",400,-4,4); dyUVA3REF3->SetXTitle("Delta_Y_UVA3Y_REF3Y [mm]"); dyUVA3REF3->SetYTitle("Frequency"); dyUVA3REF3->SetLabelSize(0.045,"XY"); dyUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dyREF1UVA3 = new TH1F(nameDyREF1UVA3,"",400,-4,4); dyREF1UVA3->SetXTitle("Delta_Y_REF1Y_UVA3Y [mm]"); dyREF1UVA3->SetYTitle("Frequency"); dyREF1UVA3->SetLabelSize(0.045,"XY"); dyREF1UVA3->SetTitleSize(0.045,"XY");
    TH1F* dyREF1REF3 = new TH1F(nameDyREF1REF3,"",400,-4,4); dyREF1REF3->SetXTitle("Delta_Y_REF1Y_REF3Y [mm]"); dyREF1REF3->SetYTitle("Frequency"); dyREF1REF3->SetLabelSize(0.045,"XY"); dyREF1REF3->SetTitleSize(0.045,"XY");
    */
    TH1F* angleREF3 = new TH1F("angleREF3","Rotation angle distribution of REF3 and REF2",1000,-0.5,0.5); angleREF3->SetXTitle("Angle [radian]"); angleREF3->SetYTitle("Frequency");
    //TH1F* angleREF3_2 = new TH1F("angleREF3","Get From Delta_y",2000,-0.5,3.5); angleREF3_2->SetXTitle("Rotation angle of ERF3 and REF2 [radian]"); angleREF3_2->SetYTitle("Frequency");
    TH1F* angleUVA3 = new TH1F("angleUVA3","Rotation angle distribution of UVA3 and REF2",1000,-0.5,0.5); angleUVA3->SetXTitle("Angle [radian]"); angleUVA3->SetYTitle("Frequency");
    //TH1F* angleUVA3_2 = new TH1F("angleUVA3_2","Get From Delta_y",2000,-0.5,3.5); angleUVA3_2->SetXTitle("Rotation angle of UVA3 and REF2 [radian]"); angleUVA3_2->SetYTitle("Frequency");
    TH1F* angleREF1 = new TH1F("angleREF1","Rotation angle distribution of REF1 and REF2",1000,-0.5,0.5); angleREF1->SetXTitle("Angle [radian]"); angleREF1->SetYTitle("Frequency");
    //TH1F* angleREF1_2 = new TH1F("angleREF1_2","Get From Delta_y",2000,-0.5,3.5); angleREF1_2->SetXTitle("Rotation angle of ERF1 and REF2 [radian]"); angleREF1_2->SetYTitle("Frequency");
    //TH1F* angleEta5 = new TH1F("angleEta5","Rotation Eta5 and REF2",1000,-0.5,0.5);
    //delta-y up: 200,-4,4
    //TH1F* deltayZZ = new TH1F("deltaY","",200,-4,4); deltayZZ->SetXTitle("Position difference [mm]");deltayZZ->SetYTitle("Frequency");
    //deltayZZ->SetLabelSize(0.045,"XY");deltayZZ->SetTitleSize(0.045,"XY");
    //cout<<"shift: "<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<"\t"<<shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<shiREF1X<<"\t"<<shiREF1Y<<endl;
    
    TH1F* xTrackChi2 = new TH1F("XTrackChi2","Chi square of tracks in X projection",1000,0,0.2); xTrackChi2->SetXTitle("#chi^{2} of track in X"); xTrackChi2->SetYTitle("Frequency");
    xTrackChi2->SetTitleSize(0.04,"XY"); xTrackChi2->SetLabelSize(0.04,"XY");
    TH1F* yTrackChi2 = new TH1F("YTrackChi2","Chi square of tracks in Y projection",1000,0,0.2); yTrackChi2->SetXTitle("#chi^{2} of track in Y"); yTrackChi2->SetYTitle("Frequency");
    yTrackChi2->SetTitleSize(0.04,"XY"); yTrackChi2->SetLabelSize(0.04,"XY");
    
    fout<<"shift: "<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<"\t"<<shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<shiREF1X<<"\t"<<shiREF1Y<<endl;
    fout2<<"rotation: "<<aREF3REF2<<"\t"<<aUVA3REF2<<"\t"<<aREF1REF2<<endl;
    int nnnn=0;
    for(Int_t i=0;i<vpREF2X.size();i++){
    	//shift
      vpREF2X[i] = vpREF2X[i] - shiREF2X; vpREF2Y[i] = vpREF2Y[i] - shiREF2Y;      
      vpREF3X[i] = vpREF3X[i] - shiREF3X; vpREF3Y[i] = vpREF3Y[i] - shiREF3Y;
      vpUVA3X[i] = vpUVA3X[i] - shiUVA3X; vpUVA3Y[i] = vpUVA3Y[i] - shiUVA3Y;
      vpREF1X[i] = vpREF1X[i] - shiREF1X; vpREF1Y[i] = vpREF1Y[i] - shiREF1Y;
     // vpZZ1[i] = vpZZ1[i] - shiZZ1; vpZZ2[i] = vpZZ2[i] - shiZZ2;
      //vpEta5[i] = vpEta5[i] - shiEta5; 
      tempREF2X=vpREF2X[i]; tempREF2Y=vpREF2Y[i]; tempREF3X=vpREF3X[i]; tempREF3Y=vpREF3Y[i]; 
      tempUVA3X=vpUVA3X[i]; tempUVA3Y=vpUVA3Y[i]; tempREF1X=vpREF1X[i]; tempREF1Y=vpREF1Y[i]; 
      //tempEta5=vpEta5[i];
      //rotate back
      vpREF3X[i]=tempREF3X*cos(aREF3REF2)-tempREF3Y*sin(aREF3REF2);
      vpREF3Y[i]=tempREF3X*sin(aREF3REF2)+tempREF3Y*cos(aREF3REF2);
      vpUVA3X[i]=tempUVA3X*cos(aUVA3REF2)-tempUVA3Y*sin(aUVA3REF2);
      vpUVA3Y[i]=tempUVA3X*sin(aUVA3REF2)+tempUVA3Y*cos(aUVA3REF2);
      vpREF1X[i]=tempREF1X*cos(aREF1REF2)-tempREF1Y*sin(aREF1REF2);
      vpREF1Y[i]=tempREF1X*sin(aREF1REF2)+tempREF1Y*cos(aREF1REF2);
      //vpEta5[i]=tempREF2X*sin(aEta5REF2)+tempEta5*cos(aEta5REF2);
      
      hpREF2X->Fill(vpREF2X[i]); hpREF2Y->Fill(vpREF2Y[i]);
      hpREF3X->Fill(vpREF3X[i]); hpREF3Y->Fill(vpREF3Y[i]);
      hpUVA3X->Fill(vpUVA3X[i]); hpUVA3Y->Fill(vpUVA3Y[i]);
      hpREF1X->Fill(vpREF1X[i]); hpREF1Y->Fill(vpREF1Y[i]);
      //hpZZ1->Fill(vpZZ1[i]); hpZZ2->Fill(vpZZ2[i]);
      //hpEta5->Fill(vpEta5[i]); //cout<<vpEta5[i]<<endl;
      /*
      dxREF3X->Fill(vpREF3X[i]-vpREF2X[i]); dyREF3Y->Fill(vpREF3Y[i]-vpREF2Y[i]);
      dxUVA3X->Fill(vpUVA3X[i]-vpREF2X[i]); dyUVA3Y->Fill(vpUVA3Y[i]-vpREF2Y[i]);
      dxREF1X->Fill(vpREF1X[i]-vpREF2X[i]); dyREF1Y->Fill(vpREF1Y[i]-vpREF2Y[i]);
      dxUVA3REF3->Fill(vpUVA3X[i]-vpREF3X[i]); dyUVA3REF3->Fill(vpUVA3Y[i]-vpREF3Y[i]);
      dxREF1UVA3->Fill(vpREF1X[i]-vpUVA3X[i]); dyREF1UVA3->Fill(vpREF1Y[i]-vpUVA3Y[i]);
      dxREF1REF3->Fill(vpREF1X[i]-vpREF3X[i]); dyREF1REF3->Fill(vpREF1Y[i]-vpREF3Y[i]);
      */
      TGraph* g1 = new TGraph();
      g1->SetPoint(0,0,     vpREF2X[i]);
      g1->SetPoint(1,1143.5,vpREF3X[i]);
      g1->SetPoint(2,2686.5,vpUVA3X[i]);
      g1->SetPoint(3,3169.5,vpREF1X[i]);
      TF1* f1 = new TF1("line1","[0]+[1]*x",0,3200);
      g1->Fit("line1","Q");
      double intercept1 = f1->GetParameter(0);
      double slope1     = f1->GetParameter(1);
      double MeasuredREF2X = intercept1 + slope1*0.0;
      double MeasuredREF3X = intercept1 + slope1*1143.5;
      double MeasuredUVA3X = intercept1 + slope1*2686.5;
      double MeasuredREF1X = intercept1 + slope1*3169.5;
      residualREF2X->Fill(MeasuredREF2X-vpREF2X[i]);
      residualREF3X->Fill(MeasuredREF3X-vpREF3X[i]);
      residualUVA3X->Fill(MeasuredUVA3X-vpUVA3X[i]);
      residualREF1X->Fill(MeasuredREF1X-vpREF1X[i]);
      xTrackChi2->Fill(f1->GetChisquare());
      //cout<<f1->GetChisquare()<<"\t";
      delete f1; delete g1;

      TGraph* g2 = new TGraph();
      g2->SetPoint(0,0,     vpREF2Y[i]);
      g2->SetPoint(1,1143.5,vpREF3Y[i]);
      // exclusive
      g2->SetPoint(2,2686.5,vpUVA3Y[i]);
      g2->SetPoint(3,3169.5,vpREF1Y[i]);
      // inclusive
      //g2->SetPoint(2,2305.5,vpZZ2[i]); //inclusive 1
      //g2->SetPoint(2,2327.5,vpZZ1[i]);  //inclusive 2
      //g2->SetPoint(3,2686.5,vpUVA3Y[i]);


      //g2->SetPoint(4,3169.5,vpREF1Y[i]);
      //g2->SetPoint(3,3169.5,vpREF1Y[i]);    
      TF1* f2 = new TF1("line2","[0]+[1]*x",0,3200);
      g2->Fit("line2","Q");
      double intercept2 = f2->GetParameter(0);
      double slope2     = f2->GetParameter(1);
      double MeasuredREF2Y = intercept2 + slope2*0.0;
      double MeasuredREF3Y = intercept2 + slope2*1143.5;
      double MeasuredUVA3Y = intercept2 + slope2*2686.5;
      double MeasuredREF1Y = intercept2 + slope2*3169.5;
      //double MeasuredZZ1  = intercept2 + slope2*2327.5;
      //double MeasuredZZ2  = intercept2 + slope2*2305.5;
      //double MeasuredEta5 = intercept2 + slope2*2011.5;
      residualREF2Y->Fill(MeasuredREF2Y-vpREF2Y[i]);
      residualREF3Y->Fill(MeasuredREF3Y-vpREF3Y[i]);
      residualUVA3Y->Fill(MeasuredUVA3Y-vpUVA3Y[i]);
      residualREF1Y->Fill(MeasuredREF1Y-vpREF1Y[i]);
      //residualZZ1->Fill(MeasuredZZ1-vpZZ1[i]);
      //residualZZ2->Fill(MeasuredZZ2-vpZZ2[i]);
      //residualEta5->Fill(MeasuredEta5-vpEta5[i]);
      //deltayZZ->Fill(vpZZ1[i]-vpZZ2[i]);
      yTrackChi2->Fill(f2->GetChisquare());
      //cout<<f2->GetChisquare()<<endl;
      delete f2; delete g2;
      
      double cosineREF3 = CalculateCosTheta1(vpREF2X[i],vpREF2Y[i],vpREF3X[i],vpREF3Y[i]);
      double cosineUVA3 = CalculateCosTheta1(vpREF2X[i],vpREF2Y[i],vpUVA3X[i],vpREF3Y[i]);
      double cosineREF1 = CalculateCosTheta1(vpREF2X[i],vpREF2Y[i],vpREF1X[i],vpREF3Y[i]);
     // double cosineEta5 = CalculateCosTheta1(vpREF2X[i],vpREF2Y[i],vpREF2X[i],vpEta5[i]);
      angleREF3->Fill(cosineREF3);   //angleREF3_2->Fill(cosineREF3_2);
      angleUVA3->Fill(cosineUVA3); //angleUVA3_2->Fill(cosineUVA3_2);
      angleREF1->Fill(cosineREF1); //angleREF1_2->Fill(cosineREF1_2);
      //angleEta5->Fill(cosineEta5);
      
      nnnn++;
      //if(nnnn%1000==0) cout<<nnnn<<"......"<<endl;
      //if(nnnn>1000) break;
    } //for loop
    //cout<<"after for loop"<<endl;
    gStyle->SetOptFit(1111);

    I2GFvalues myValues;
    myValues = I2GFmainLoop(residualREF2X, 1, 10 , 1);
    meanREF2X = myValues.mean; sigmaREF2X=myValues.sigma;
    myValues = I2GFmainLoop(residualREF2Y, 1, 10 , 1);
    meanREF2Y = myValues.mean; sigmaREF2Y=myValues.sigma;
    myValues = I2GFmainLoop(residualREF3X, 1, 10 , 1);
    meanREF3X = myValues.mean; sigmaREF3X=myValues.sigma;
    myValues = I2GFmainLoop(residualREF3Y, 1, 10 , 1);
    meanREF3Y = myValues.mean; sigmaREF3Y=myValues.sigma;
    myValues = I2GFmainLoop(residualUVA3X, 1, 10 , 1);
    meanUVA3X = myValues.mean; sigmaUVA3X=myValues.sigma;
    myValues = I2GFmainLoop(residualUVA3Y, 1, 10 , 1);
    meanUVA3Y = myValues.mean; sigmaUVA3Y=myValues.sigma;
    myValues = I2GFmainLoop(residualREF1X, 1, 10 , 1);
    meanREF1X = myValues.mean; sigmaREF1X=myValues.sigma;
    myValues = I2GFmainLoop(residualREF1Y, 1, 10 , 1);
    meanREF1Y = myValues.mean; sigmaREF1Y=myValues.sigma;

    cout<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<<meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    fout1<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<<meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    /*
    myValues = I2GFmainLoop(dxREF3X, 1, 10 , 1);
    myValues = I2GFmainLoop(dxUVA3X, 1, 10 , 1);
    myValues = I2GFmainLoop(dxREF1X, 1, 10 , 1);
    myValues = I2GFmainLoop(dyREF3Y, 1, 10 , 1);
    myValues = I2GFmainLoop(dyUVA3Y, 1, 10 , 1);
    myValues = I2GFmainLoop(dyREF1Y, 1, 10 , 1);
    myValues = I2GFmainLoop(dxUVA3REF3, 1, 10 , 1);
    myValues = I2GFmainLoop(dxREF1UVA3, 1, 10 , 1);
    myValues = I2GFmainLoop(dxREF1REF3, 1, 10 , 1);
    myValues = I2GFmainLoop(dyUVA3REF3, 1, 10 , 1);
    myValues = I2GFmainLoop(dyREF1UVA3, 1, 10 , 1);
    myValues = I2GFmainLoop(dyREF1REF3, 1, 10 , 1);
    */
    myValues = I2GFmainLoop(angleREF3, 1, 10 , 1);
    meanAngleREF3=myValues.mean;
    myValues = I2GFmainLoop(angleUVA3, 1, 10 , 1);
    meanAngleUVA3=myValues.mean;
    myValues = I2GFmainLoop(angleREF1, 1, 10 , 1);
    meanAngleREF1=myValues.mean;
    //maximum=angleEta5->GetMean(); rms=angleEta5->GetRMS(1); lRange=maximum-rms*0.7; hRange=maximum+rms*0.7;
    //TF1* funAngleEta5=new TF1("funAngleEta5","gaus",lRange,hRange); angleEta5->Fit("funAngleEta5","RQ");
    //meanAngleEta5=funAngleEta5->GetParameter(1);
    //maximum=xTrackChi2->GetMean(); rms=xTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funXTrackChi2=new TF1("funXTrackChi2","gaus",lRange,hRange); xTrackChi2->Fit("funXTrackChi2","RQ");
    meanXChi2=xTrackChi2->GetMean();
    //maximum=yTrackChi2->GetMean(); rms=yTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funYTrackChi2=new TF1("funYTrackChi2","gaus",lRange,hRange); yTrackChi2->Fit("funYTrackChi2","RQ");
    meanYChi2=yTrackChi2->GetMean();
    
    totalAngleREF3 += aREF3REF2;
    totalAngleUVA3 += aUVA3REF2;
    totalAngleREF1 += aREF1REF2;
    fout3<<sigmaREF2X<<"\t"<<sigmaREF2Y<<"\t"<<sigmaREF3X<<"\t"<<sigmaREF3Y<<"\t"<<sigmaUVA3X<<"\t"<<sigmaUVA3Y<<"\t"<<sigmaREF1X<<"\t"<<sigmaREF1Y<<"\t"<<totalAngleREF3<<"\t"<<totalAngleUVA3<<"\t"<<totalAngleREF1<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
    
    f->Write();
    f->Close();
    //delete funPosEta5; delete funPosREF1Y; delete funPosUVA3Y; delete funPosREF3Y; delete funPosREF2Y;
    
    double factor = -0.2;
    //shiREF2X = meanREF2X*factor; shiREF2Y = meanREF2Y*factor; 
    //shiREF3X = meanREF3X*factor; shiREF3Y = meanREF3Y*factor; 
    //shiUVA3X = meanUVA3X*factor; shiUVA3Y = meanUVA3Y*factor; 
    //shiREF1X = meanREF1X*factor; shiREF1Y = meanREF1Y*factor; 
    //shiZZ1 = meanZZ1*factor; shiZZ2 = meanZZ2*factor; 
    //shiEta5 = meanEta5*factor;
    factor=0.2;
    shiREF2X=0.0; shiREF2Y=0.0;
    shiREF3X=0.0; shiREF3Y=0.0;
    shiUVA3X=0.0; shiUVA3Y=0.0;
    shiREF1X=0.0; shiREF1Y=0.0;
    
    aREF3REF2 = 0.001 ;
    aUVA3REF2 = 0.0;
    aREF1REF2 = 0.0;
    //aUVA3REF2 = meanAngleUVA3*factor;
    //aREF1REF2 = meanAngleREF1*factor;
   // aEta5REF2 = meanAngleEta5*factor;
   // if(iterNb>0) break; // only cylce once.
    //if((meanREF2X>=-0.001 && meanREF2X<=0.001) && (meanREF2Y>=-0.001 && meanREF2Y<=0.001))
    //  if((meanREF3X>=-0.001 && meanREF3X<=0.001) && (meanREF3Y>=-0.001 && meanREF3Y<=0.001))
    //    if((meanUVA3X>=-0.001 && meanUVA3X<=0.001) && (meanUVA3Y>=-0.001 && meanUVA3Y<=0.001))
    //    	if((meanREF1X>=-0.001 && meanREF1X<=0.001) && (meanREF1Y>=-0.001 && meanREF1Y<=0.001) && meanEta5<=0.005)
    //if(meanAngleREF3>=-0.001 && meanAngleREF3<=0.001 && meanAngleUVA3>=-0.001 && meanAngleUVA3<=0.001 && meanAngleREF1>=-0.001 && meanAngleREF1<=0.001)
    //      {
    //        cout<<"find it...iterating "<<iterNb<<" times."<<endl;
    //        break;
    //      }
  // break;
    if(iterNb==41) break;
 }//while(1)
 fout.close();
 fout1.close();
 fout2.close();
} // entire script

void main(){
	
  string name[1]={
  	"Position"
  };
  for(int i=0;i<1;i++) tracking(name[i]);
  
}

double CalculateCosTheta1(double x, double y, double x1,double y1){
	//double cosineTheta = ( x*x1 + y*y1 )/(x*x+y*y);
	double sineTheta = (x1*y - x*y1)/(x*x + y*y);
	//if(cosineTheta>1) cosineTheta=2-cosineTheta;
	//cout<<sineTheta<<endl;
	return asin(sineTheta);
}
