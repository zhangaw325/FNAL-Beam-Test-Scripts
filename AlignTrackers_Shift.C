#include <vector>
#include "doubleGausFit_withHistParameter.C"
void AlignTrackers_Shift(){
  string thestring = "Position";
  string txtfilename = thestring + ".txt";
  string shiftHead = "shiftParameters_";
  string residualHead = "residuals_";
  string ResidualRHead="Residual_";
  string foutname = shiftHead+thestring+"_alignTrackers.txt";
  string fout1name = residualHead+thestring+"_alignTrackers.txt";

  Bool_t verbose = false;

  fstream fin(txtfilename.c_str(),ios::in);
  if(!fin){cout<<"file not read"<<endl; return;}
  fstream fout(foutname.c_str(),ios::out);
  fstream fout1(fout1name.c_str(),ios::out);
  double pREF2X=0.0, pREF2Y=0.0;
  double pREF3X=0.0, pREF3Y=0.0;
  double pREF1X=0.0, pREF1Y=0.0;

  vector<double> vpREF2X; vector<double> vpREF2Y;
  vector<double> vpREF3X; vector<double> vpREF3Y;
  vector<double> vpREF1X; vector<double> vpREF1Y;

  Int_t nbLines=0;
  while(fin>>pREF2X>>pREF2Y>>pREF3X>>pREF3Y>>pREF1X>>pREF1Y/*>>pEta5*/){
    vpREF2X.push_back(pREF2X); vpREF2Y.push_back(pREF2Y); vpREF3X.push_back(pREF3X); vpREF3Y.push_back(pREF3Y);
    vpREF1X.push_back(pREF1X); vpREF1Y.push_back(pREF1Y);
    if (verbose)
	cout<<pREF2X<<"\t"<<pREF2Y<<"\t"<<pREF3X<<"\t"<<pREF3Y<<"\t"<<pREF1X<<"\t"<<pREF1Y<<endl;
    nbLines++;
  }
  fin.close();
  /*
  REF2X:
      [-30,-20]: -22.98, 1.089, -28.29, -3.209, -37.22, 14.88, -46.62, -2.411, 29.84
      [-20,-15]: -17.07, 0.4154, -22.27, -3.92, -31.12, 14.55, -40.55, -2.637, 29.48
  */
  double shiREF2X=62.36	, shiREF2Y=55.83;
  double shiREF3X=62.72	, shiREF3Y=56.06;
  double shiUVA3X=62.72 , shiUVA3Y=56.06;
  double shiREF1X=61.91 , shiREF1Y=55.68;
  //double shiZZ1=0,   shiZZ2=0;
  //double shiEta5=30.1;


  double meanREF2X=0.0, meanREF2Y=0.0;
  double meanREF3X=0.0, meanREF3Y=0.0;
  double meanUVA3X=0.0, meanUVA3Y=0.0;
  double meanREF1X=0.0, meanREF1Y=0.0;
  //double meanZZ1=0.0, meanZZ2=0.0;
  //double meanEta5=0;

  Int_t iterNb=0;
  while(1){
    char rootfile[50]; sprintf(rootfile,"_iter_%i.root",iterNb);
    string outputrootname=ResidualRHead+thestring+rootfile;
    TFile* f = new TFile(outputrootname.c_str(),"recreate");  
    iterNb++;
    char name2X[15];sprintf(name2X,"posREF2X_%i",iterNb); char name2Y[15];sprintf(name2Y,"posREF2Y_%i",iterNb);
    char name3X[15];sprintf(name3X,"posREF3X_%i",iterNb); char name3Y[15];sprintf(name3Y,"posREF3Y_%i",iterNb);
    char name1X[15];sprintf(name1X,"posREF1X_%i",iterNb); char name1Y[15];sprintf(name1Y,"posREF1Y_%i",iterNb);
    if (verbose)
	cout<<name1X<<"\t"<<name2X<<"\t"<<name3X<<endl;
    TH1F* hpREF2X = new TH1F(name2X,"",500,-10,110); hpREF2X->SetXTitle("mm"); hpREF2X->SetYTitle("Frequency");hpREF2X->SetLabelSize(0.045,"XY");hpREF2X->SetTitleSize(0.045,"XY");
    TH1F* hpREF2Y = new TH1F(name2Y,"",500,-10,110); hpREF2Y->SetXTitle("mm"); hpREF2Y->SetYTitle("Frequency");hpREF2Y->SetLabelSize(0.045,"XY");hpREF2Y->SetTitleSize(0.045,"XY");  
    TH1F* hpREF3X = new TH1F(name3X,"",500,-10,110); hpREF3X->SetXTitle("mm"); hpREF3X->SetYTitle("Frequency");hpREF3X->SetLabelSize(0.045,"XY");hpREF3X->SetTitleSize(0.045,"XY");
    TH1F* hpREF3Y = new TH1F(name3Y,"",500,-10,110); hpREF3Y->SetXTitle("mm"); hpREF3Y->SetYTitle("Frequency");hpREF3Y->SetLabelSize(0.045,"XY");hpREF3Y->SetTitleSize(0.045,"XY");  
    TH1F* hpREF1X = new TH1F(name1X,"",500,-10,110); hpREF1X->SetXTitle("mm"); hpREF1X->SetYTitle("Frequency");hpREF1X->SetLabelSize(0.045,"XY");hpREF1X->SetTitleSize(0.045,"XY");
    TH1F* hpREF1Y = new TH1F(name1Y,"",500,-10,110); hpREF1Y->SetXTitle("mm"); hpREF1Y->SetYTitle("Frequency");hpREF1Y->SetLabelSize(0.045,"XY");hpREF1Y->SetTitleSize(0.045,"XY");  
    char nameRes2X[20];sprintf(nameRes2X,"residualREF2X_%i",iterNb);char nameRes2Y[20];sprintf(nameRes2Y,"residualREF2Y_%i",iterNb);
    char nameRes3X[20];sprintf(nameRes3X,"residualREF3X_%i",iterNb);char nameRes3Y[20];sprintf(nameRes3Y,"residualREF3Y_%i",iterNb);
    char nameRes1X[20];sprintf(nameRes1X,"residualREF1X_%i",iterNb);char nameRes1Y[20];sprintf(nameRes1Y,"residualREF1Y_%i",iterNb);
    if (verbose)
	cout<<nameRes1X<<"\t"<<nameRes2X<<"\t"<<nameRes3X<<endl;

    TH1F* residualREF2X = new TH1F(nameRes2X,"",800,-8,8); residualREF2X->SetXTitle("Residual [mm]"); residualREF2X->SetYTitle("Frequency");residualREF2X->SetLabelSize(0.045,"XY");residualREF2X->SetTitleSize(0.045,"XY");
    TH1F* residualREF2Y = new TH1F(nameRes2Y,"",800,-8,8); residualREF2Y->SetXTitle("Residual [mm]"); residualREF2Y->SetYTitle("Frequency");residualREF2Y->SetLabelSize(0.045,"XY");residualREF2Y->SetTitleSize(0.045,"XY");
    TH1F* residualREF3X = new TH1F(nameRes3X,"",800,-8,8); residualREF3X->SetXTitle("Residual [mm]"); residualREF3X->SetYTitle("Frequency");residualREF3X->SetLabelSize(0.045,"XY");residualREF3X->SetTitleSize(0.045,"XY");
    TH1F* residualREF3Y = new TH1F(nameRes3Y,"",800,-8,8); residualREF3Y->SetXTitle("Residual [mm]"); residualREF3Y->SetYTitle("Frequency");residualREF3Y->SetLabelSize(0.045,"XY");residualREF3Y->SetTitleSize(0.045,"XY");
    TH1F* residualREF1X = new TH1F(nameRes1X,"",800,-8,8); residualREF1X->SetXTitle("mm"); residualREF1X->SetYTitle("Frequency");residualREF1X->SetLabelSize(0.045,"XY");residualREF1X->SetTitleSize(0.045,"XY");
    TH1F* residualREF1Y = new TH1F(nameRes1Y,"",800,-8,8); residualREF1Y->SetXTitle("mm"); residualREF1Y->SetYTitle("Frequency");residualREF1Y->SetLabelSize(0.045,"XY");residualREF1Y->SetTitleSize(0.045,"XY");
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
    char nameDyUVA3REF3[20]; sprintf(nameDyUVA3REF3,"UVA3Y_REF3Y_%i",iterNb);
    char nameDyREF1UVA3[20]; sprintf(nameDyREF1UVA3,"REF1Y_UVA3Y_%i",iterNb);
    TH1F* dxUVA3REF3 = new TH1F(nameDxUVA3REF3,"",400,-4,4); dxUVA3REF3->SetXTitle("Delta_X_UVA3X_REF3X [mm]"); dxUVA3REF3->SetYTitle("Frequency"); dxUVA3REF3->SetLabelSize(0.045,"XY"); dxUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dxREF1UVA3 = new TH1F(nameDxREF1UVA3,"",400,-4,4); dxREF1UVA3->SetXTitle("Delta_X_REF1X_UVA3X [mm]"); dxREF1UVA3->SetYTitle("Frequency"); dxREF1UVA3->SetLabelSize(0.045,"XY"); dxUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dyUVA3REF3 = new TH1F(nameDyUVA3REF3,"",400,-4,4); dyUVA3REF3->SetXTitle("Delta_Y_UVA3Y_REF3Y [mm]"); dyUVA3REF3->SetYTitle("Frequency"); dyUVA3REF3->SetLabelSize(0.045,"XY"); dyUVA3REF3->SetTitleSize(0.045,"XY");
    TH1F* dyREF1UVA3 = new TH1F(nameDyREF1UVA3,"",400,-4,4); dyREF1UVA3->SetXTitle("Delta_Y_REF1Y_UVA3Y [mm]"); dyREF1UVA3->SetYTitle("Frequency"); dyREF1UVA3->SetLabelSize(0.045,"XY"); dxUVA3REF3->SetTitleSize(0.045,"XY");
    */
    //delta-y up: 200,-4,4
    //TH1F* deltayZZ = new TH1F("deltaY","",200,-4,4); deltayZZ->SetXTitle("Position difference [mm]");deltayZZ->SetYTitle("Frequency");
    //deltayZZ->SetLabelSize(0.045,"XY");deltayZZ->SetTitleSize(0.045,"XY");
    //cout<<"shift: "<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<"\t"<<shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<shiREF1X<<"\t"<<shiREF1Y<<"\t"<<shiEta5<<endl;
    fout<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<"\t"<<shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<shiREF1X<<"\t"<<shiREF1Y<<endl;
    if (verbose)
    cout<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<"\t"<<shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<shiREF1X<<"\t"<<shiREF1Y<<endl;
    int nnnn=0;
    for(Int_t i=0;i<vpREF2X.size();i++){
      vpREF2X[i] = vpREF2X[i] - shiREF2X; vpREF2Y[i] = vpREF2Y[i] - shiREF2Y;      
      vpREF3X[i] = vpREF3X[i] - shiREF3X; vpREF3Y[i] = vpREF3Y[i] - shiREF3Y;
      vpREF1X[i] = vpREF1X[i] - shiREF1X; vpREF1Y[i] = vpREF1Y[i] - shiREF1Y;
      hpREF2X->Fill(vpREF2X[i]); hpREF2Y->Fill(vpREF2Y[i]);
      hpREF3X->Fill(vpREF3X[i]); hpREF3Y->Fill(vpREF3Y[i]);
      hpREF1X->Fill(vpREF1X[i]); hpREF1Y->Fill(vpREF1Y[i]);
      
      if (verbose)
	  cout<<i<<"\t"<<vpREF1X[i]<<"\t"<<vpREF1Y[i]<<"\t"<<vpREF2X[i]<<"\t"<<vpREF2Y[i]<<"\t"<<vpREF3X[i]<<"\t"<<vpREF3Y[i]<<endl;

      TGraph* g1 = new TGraph();
      g1->SetPoint(0,100,     vpREF2X[i]);
      g1->SetPoint(1,380.,vpREF3X[i]);
      g1->SetPoint(3,830.,vpREF1X[i]);
      TF1* f1 = new TF1("line1","[0]+[1]*x",0,3200);
      g1->Fit("line1","Q");
      double intercept1 = f1->GetParameter(0);
      double slope1     = f1->GetParameter(1);
      double MeasuredREF2X = intercept1 + slope1*100.;
      double MeasuredREF3X = intercept1 + slope1*380.;
      double MeasuredREF1X = intercept1 + slope1*830.;
      residualREF2X->Fill(MeasuredREF2X-vpREF2X[i]);
      residualREF3X->Fill(MeasuredREF3X-vpREF3X[i]);
      residualREF1X->Fill(MeasuredREF1X-vpREF1X[i]);
      delete f1; delete g1;

      TGraph* g2 = new TGraph();
      g2->SetPoint(0,100.,     vpREF2Y[i]);
      g2->SetPoint(1,380.,vpREF3Y[i]);
      // exclusive
       g2->SetPoint(3,830.,vpREF1Y[i]);
      // inclusive


      //g2->SetPoint(4,3169.5,vpREF1Y[i]);
      //g2->SetPoint(3,3169.5,vpREF1Y[i]);    
      TF1* f2 = new TF1("line2","[0]+[1]*x",0,3200);
      g2->Fit("line2","Q");
      double intercept2 = f2->GetParameter(0);
      double slope2     = f2->GetParameter(1);
      double MeasuredREF2Y = intercept2 + slope2*100.;
      double MeasuredREF3Y = intercept2 + slope2*380.;
      double MeasuredREF1Y = intercept2 + slope2*830.;
      //double MeasuredZZ1  = intercept2 + slope2*2327.5;
      //double MeasuredZZ2  = intercept2 + slope2*2305.5;
      //double MeasuredEta5 = intercept2 + slope2*2011.5;
      residualREF2Y->Fill(MeasuredREF2Y-vpREF2Y[i]);
      residualREF3Y->Fill(MeasuredREF3Y-vpREF3Y[i]);
      residualREF1Y->Fill(MeasuredREF1Y-vpREF1Y[i]);
      //residualZZ1->Fill(MeasuredZZ1-vpZZ1[i]);
      //residualZZ2->Fill(MeasuredZZ2-vpZZ2[i]);
      //residualEta5->Fill(MeasuredEta5-vpEta5[i]);
      //deltayZZ->Fill(vpZZ1[i]-vpZZ2[i]);
      delete f2; delete g2;
      nnnn++;
      //if(nnnn%1000==0) cout<<nnnn<<"......"<<endl;
      //if(nnnn>1000) break;
    } //for loop
    //cout<<"after for loop"<<endl;
//
//    gStyle->SetOptFit(1111);
//    
//    I2GFvalues myValues;
//    myValues = I2GFmainLoop(residualREF2X,1,10,1);
//    meanREF2X = myValues.mean; //sigmaEta5=myValues.sigma;
//    myValues = I2GFmainLoop(residualREF2Y,1,10,1);
//    meanREF2Y = myValues.mean; //
//    myValues = I2GFmainLoop(residualREF3X,1,10,1);
//    meanREF3X = myValues.mean; //
//    myValues = I2GFmainLoop(residualREF3Y,1,10,1);
//    meanREF3Y = myValues.mean;
//    myValues = I2GFmainLoop(residualREF1X,1,10,1);
//    meanREF1X = myValues.mean; //
//    myValues = I2GFmainLoop(residualREF1Y,1,10,1);
//    meanREF1Y = myValues.mean;
    /*
    double maximum = residualREF2X->GetMean();
    double rms = residualREF2X->GetRMS(1);
    double lRange = maximum - rms*0.75; 
    double hRange = maximum + rms*0.75;
    TF1* funResidualREF2X = new TF1("funResidualREF2X","gaus",lRange,hRange);funResidualREF2X->SetLineColor(kBlue); residualREF2X->Fit("funResidualREF2X","RQ");
    meanREF2X = funResidualREF2X->GetParameter(1);
    maximum = residualREF2Y->GetMean();
    rms = residualREF2Y->GetRMS(1);
    lRange = maximum - rms*0.75; hRange = maximum + rms*0.75;
    TF1* funResidualREF2Y = new TF1("funResidualREF2Y","gaus",lRange,hRange);funResidualREF2Y->SetLineColor(kBlue); residualREF2Y->Fit("funResidualREF2Y","RQ");
    meanREF2Y = funResidualREF2Y->GetParameter(1);
    maximum = residualREF3X->GetMean();
    rms = residualREF3X->GetRMS(1);
    lRange = maximum - rms*0.75; hRange = maximum + rms*0.75;
    TF1* funResidualREF3X = new TF1("funResidualREF3X","gaus",lRange,hRange);funResidualREF3X->SetLineColor(kBlue); residualREF3X->Fit("funResidualREF3X","RQ");
    meanREF3X = funResidualREF3X->GetParameter(1);
    maximum = residualREF3Y->GetMean();
    rms = residualREF3Y->GetRMS(1);
    lRange = maximum - rms*0.75; hRange = maximum + rms*0.75;
    TF1* funResidualREF3Y = new TF1("funResidualREF3Y","gaus",lRange,hRange);funResidualREF3Y->SetLineColor(kBlue); residualREF3Y->Fit("funResidualREF3Y","RQ");
    meanREF3Y = funResidualREF3Y->GetParameter(1);
    maximum = residualUVA3X->GetMean();
    rms = residualUVA3X->GetRMS(1);
    lRange = maximum - rms*0.75; hRange = maximum + rms*0.75;
    TF1* funResidualUVA3X = new TF1("funResidualUVA3X","gaus",lRange,hRange);funResidualUVA3X->SetLineColor(kBlue); residualUVA3X->Fit("funResidualUVA3X","RQ");
    meanUVA3X = funResidualUVA3X->GetParameter(1);
    maximum = residualUVA3Y->GetMean();
    rms = residualUVA3Y->GetRMS(1);
    lRange = maximum - rms*0.75; hRange = maximum + rms*0.75;
    TF1* funResidualUVA3Y = new TF1("funResidualUVA3Y","gaus",lRange,hRange);funResidualUVA3Y->SetLineColor(kBlue); residualUVA3Y->Fit("funResidualUVA3Y","RQ");
    meanUVA3Y = funResidualUVA3Y->GetParameter(1);
    maximum = residualREF1X->GetMean();
    rms = residualREF1X->GetRMS(1);
    lRange = maximum - rms*0.75; hRange = maximum + rms*0.75;
    TF1* funResidualREF1X = new TF1("funResidualREF1X","gaus",lRange,hRange);funResidualREF1X->SetLineColor(kBlue); residualREF1X->Fit("funResidualREF1X","RQ");
    meanREF1X = funResidualREF1X->GetParameter(1);
    maximum = residualREF1Y->GetMean();
    rms = residualREF1Y->GetRMS(1);
    lRange = maximum - rms*0.75; hRange = maximum + rms*0.75;
    TF1* funResidualREF1Y = new TF1("funResidualREF1Y","gaus",lRange,hRange);funResidualREF1Y->SetLineColor(kBlue); residualREF1Y->Fit("funResidualREF1Y","RQ");
    meanREF1Y = funResidualREF1Y->GetParameter(1);
    //maximum = residualEta5->GetMean();
    maximum=residualEta5->GetXaxis()->GetBinCenter(residualEta5->GetMaximumBin());
    rms = residualEta5->GetRMS(1);
    lRange = maximum - rms*0.15; hRange = maximum + rms*0.15;
    TF1* funResidualEta5 = new TF1("funResidualEta5","gaus",lRange,hRange);funResidualEta5->SetLineColor(kBlue); residualEta5->Fit("funResidualEta5","RQ");
    meanEta5 = funResidualEta5->GetParameter(1);
    */
    //maximum = residualZZ1->GetMean();
    /*
    maximum = residualZZ1->GetXaxis()->GetBinCenter(residualZZ1->GetMaximumBin());//cout<<"...."<<maximum<<"...";
    rms = residualZZ1->GetRMS(1);
    lRange = maximum - rms*0.1; hRange = maximum + rms*0.1;
    TF1* funResidualZZ1 = new TF1("funResidualZZ1","gaus",lRange,hRange);funResidualZZ1->SetLineColor(kBlue); residualZZ1->Fit("funResidualZZ1","RQ");
    meanZZ1 = funResidualZZ1->GetParameter(1);
    maximum = residualZZ2->GetXaxis()->GetBinCenter(residualZZ2->GetMaximumBin());//cout<<"...."<<maximum<<"..."<<endl;
    //maximum = residualZZ2->GetMean();
    rms = residualZZ2->GetRMS(1);
    lRange = maximum - rms*0.1; hRange = maximum + rms*0.1;//1.4
    TF1* funResidualZZ2 = new TF1("funResidualZZ2","gaus",lRange,hRange);funResidualZZ2->SetLineColor(kBlue); residualZZ2->Fit("funResidualZZ2","RQ");
    meanZZ2 = funResidualZZ2->GetParameter(1);
    maximum = deltayZZ->GetMean();
    rms = deltayZZ->GetRMS(1);
    lRange = maximum - rms*1.4; hRange = maximum + rms*1.4;//1.4
    TF1* funDeltaYZZ = new TF1("funDeltaYZZ","gaus",lRange,hRange);funDeltaYZZ->SetLineColor(kBlue); deltayZZ->Fit("funDeltaYZZ","RQ");
    */
    cout<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<<"\t"<<meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    fout1<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<<"\t"<<meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    /*    
    maximum = dxREF3X->GetMean(); rms=dxREF3X->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.10*rms;
    TF1* funDxREF3X=new TF1("funDxREF3X","gaus",lRange,hRange); funDxREF3X->SetLineColor(kBlue); dxREF3X->Fit("funDxREF3X","RQ");
    maximum = dxUVA3X->GetMean(); rms=dxUVA3X->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.10*rms;
    TF1* funDxUVA3X=new TF1("funDxUVA3X","gaus",lRange,hRange); funDxUVA3X->SetLineColor(kBlue); dxUVA3X->Fit("funDxUVA3X","RQ");
    maximum = dxREF1X->GetMean(); rms=dxREF1X->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.10*rms;
    TF1* funDxREF1X=new TF1("funDxREF1X","gaus",lRange,hRange); funDxREF1X->SetLineColor(kBlue); dxREF1X->Fit("funDxREF1X","RQ");
    maximum = dyREF3Y->GetMean(); rms=dyREF3Y->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.10*rms;
    TF1* funDyREF3Y=new TF1("funDyREF3Y","gaus",lRange,hRange); funDyREF3Y->SetLineColor(kBlue); dyREF3Y->Fit("funDyREF3Y","RQ");
    maximum = dyUVA3Y->GetMean(); rms=dyUVA3Y->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.10*rms;
    TF1* funDyUVA3Y=new TF1("funDyUVA3Y","gaus",lRange,hRange); funDyUVA3Y->SetLineColor(kBlue); dyUVA3Y->Fit("funDyUVA3Y","RQ");
    maximum = dyREF1Y->GetMean(); rms=dyREF1Y->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.10*rms;
    TF1* funDyREF1Y=new TF1("funDyREF1Y","gaus",lRange,hRange); funDyREF1Y->SetLineColor(kBlue); dyREF1Y->Fit("funDyREF1Y","RQ");
    maximum = dxUVA3REF3->GetMean(); rms=dxUVA3REF3->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.1*rms;
    TF1* funDxUVA3REF3=new TF1("funDxUVA3REF3","gaus",lRange,hRange); funDxUVA3REF3->SetLineColor(kBlue); dxUVA3REF3->Fit("funDxUVA3REF3","RQ");
    maximum = dxREF1UVA3->GetMean(); rms=dxREF1UVA3->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.1*rms;
    TF1* funDxREF1UVA3=new TF1("funDxREF1UVA3","gaus",lRange,hRange); funDxREF1UVA3->SetLineColor(kBlue); dxREF1UVA3->Fit("funDxREF1UVA3","RQ");
    maximum = dyUVA3REF3->GetMean(); rms=dyUVA3REF3->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.1*rms;
    TF1* funDyUVA3REF3=new TF1("funDyUVA3REF3","gaus",lRange,hRange); funDyUVA3REF3->SetLineColor(kBlue); dyUVA3REF3->Fit("funDyUVA3REF3","RQ");
    maximum = dyREF1UVA3->GetMean(); rms=dyREF1UVA3->GetRMS(1); lRange=maximum-rms*1.1; hRange=maximum+1.1*rms;
    TF1* funDyREF1UVA3=new TF1("funDyREF1UVA3","gaus",lRange,hRange); funDyREF1UVA3->SetLineColor(kBlue); dyREF1UVA3->Fit("funDyREF1UVA3","RQ");
    */
    f->Write();
    f->Close();
    //delete funPosEta5; delete funPosREF1Y; delete funPosUVA3Y; delete funPosREF3Y; delete funPosREF2Y;
    //delete funResidualREF2X; delete funResidualREF2Y; delete funResidualREF3X; delete funResidualREF3Y;  
    //delete funResidualUVA3X; delete funResidualUVA3Y; delete funResidualREF1X; delete funResidualREF1Y; delete funResidualEta5; //delete funResidualZZ1;delete funResidualZZ2;
    //delete funDxREF3X; delete funDxUVA3X; delete funDxREF1X; delete funDyREF3Y; delete funDyUVA3Y; delete funDyREF1Y; 
    //delete funDxUVA3REF3; delete funDxREF1UVA3; delete funDyUVA3REF3; delete funDyREF1UVA3;
    double factor = -0.1;
    shiREF2X = meanREF2X*factor; shiREF2Y = meanREF2Y*factor; 
    shiREF3X = meanREF3X*factor; shiREF3Y = meanREF3Y*factor; 
    shiREF1X = meanREF1X*factor; shiREF1Y = meanREF1Y*factor; 
    //shiZZ1 = meanZZ1*factor; shiZZ2 = meanZZ2*factor; 
    //shiEta5 = meanEta5*factor;

    //break;
    if((meanREF2X>=-0.0005 && meanREF2X<=0.0005) && (meanREF2Y>=-0.0005 && meanREF2Y<=0.0005))
      if((meanREF3X>=-0.0005 && meanREF3X<=0.0005) && (meanREF3Y>=-0.0005 && meanREF3Y<=0.0005))
        	if((meanREF1X>=-0.0005 && meanREF1X<=0.0005) && (meanREF1Y>=-0.0005 && meanREF1Y<=0.0005))
          {
            cout<<"find it...iterating "<<iterNb<<" times."<<endl;
            break;
          }
    if(iterNb>500) break;
 }//while(1)
 fout.close();
 fout1.close();
} // entire script
