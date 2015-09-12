#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TAxis.h>
#include "doubleGausFit_withHistParameter.C"
//int  main(){
  void  AlignTrackers_Shift(){
  string thestring = "Position";
  string txtfilename = thestring + ".txt";
  string shiftHead = "shiftParameters_";
  string residualHead = "residuals_";
  string ResidualRHead="Residual_";
  string foutname = shiftHead+thestring+"_alignTrackers.txt";
  string fout1name = residualHead+thestring+"_alignTrackers.txt";
  fstream fin(txtfilename.c_str(),ios::in);
  if(!fin){cout<<"file not read"<<endl; }
  fstream fout(foutname.c_str(),ios::out);
  fstream fout1(fout1name.c_str(),ios::out);
  double Pos_g2xcl=0.0, Pos_g2ycl=0.0;
  double Pos_g3xcl=0.0, Pos_g3ycl=0.0;
  double Pos_g1xcl=0.0, Pos_g1ycl=0.0;
  std::vector<double> vPos_g2xcl; std::vector<double> vPos_g2ycl;
  std::vector<double> vPos_g3xcl; std::vector<double> vPos_g3ycl;
  std::vector<double> vPos_g1xcl; std::vector<double> vPos_g1ycl;

  Int_t nbLines=0;
  while(fin>>Pos_g2xcl>>Pos_g2ycl>>Pos_g3xcl>>Pos_g3ycl>>Pos_g1xcl>>Pos_g1ycl){//pUVA3X>>pUVA3Y>>pREF1X>>pREF1Y/*>>pEta5*/){
    vPos_g2xcl.push_back(Pos_g2xcl); vPos_g2ycl.push_back(Pos_g2ycl); 
    vPos_g3xcl.push_back(Pos_g3xcl); vPos_g3ycl.push_back(Pos_g3ycl);
    vPos_g1xcl.push_back(Pos_g1xcl); vPos_g1ycl.push_back(Pos_g1ycl);
    nbLines++;
  } // getting input
  fin.close();

  double shi_g2xcl=62.36, shi_g2ycl=55.83;
  double shi_g3xcl=62.72, shi_g3ycl=56.06;
  double shi_g1xcl=61.91, shi_g1ycl=55.68;


  double mean_g2xcl=0.0, mean_g2ycl=0.0;
  double mean_g3xcl=0.0, mean_g3ycl=0.0;
  double mean_g1xcl=0.0, mean_g1ycl=0.0;


  Int_t iterNb=0;
  while(1){
    char rootfile[50]; sprintf(rootfile,"_iter_%i.root",iterNb);
    string outputrootname=ResidualRHead+thestring+rootfile;
    TFile* f = new TFile(outputrootname.c_str(),"recreate");  
    iterNb++;
    char name2X[15];sprintf(name2X,"Pos_g2xcl_%i",iterNb); char name2Y[15];sprintf(name2Y,"Pos_g2ycl_%i",iterNb);
    char name3X[15];sprintf(name3X,"Pos_g3xcl_%i",iterNb); char name3Y[15];sprintf(name3Y,"Pos_g3ycl_%i",iterNb);
    char name1X[15];sprintf(name1X,"Pos_g1xcl_%i",iterNb); char name1Y[15];sprintf(name1Y,"Pos_g1xcl_%i",iterNb);
    TH1F* h_Pos_g2xcl = new TH1F(name2X,"",100,-10,110); h_Pos_g2xcl->SetXTitle("Cluster position [mm]"); h_Pos_g2xcl->SetYTitle("Frequency");h_Pos_g2xcl->SetLabelSize(0.045,"XY");h_Pos_g2xcl->SetTitleSize(0.045,"XY");
    TH1F* h_Pos_g2ycl = new TH1F(name2Y,"",100,-10,110); h_Pos_g2ycl->SetXTitle(" Cluster position [mm]"); h_Pos_g2ycl->SetYTitle("Frequency");h_Pos_g2ycl->SetLabelSize(0.045,"XY");h_Pos_g2ycl->SetTitleSize(0.045,"XY");  
    TH1F* h_Pos_g1xcl = new TH1F(name3X,"",100,-10,110); h_Pos_g1xcl->SetXTitle("Cluster position [mm]"); h_Pos_g1xcl->SetYTitle("Frequency");h_Pos_g1xcl->SetLabelSize(0.045,"XY");h_Pos_g1xcl->SetTitleSize(0.045,"XY");
    TH1F* h_Pos_g1ycl = new TH1F(name3Y,"",100,-10,110); h_Pos_g1ycl->SetXTitle("Cluster position [mm]"); h_Pos_g1ycl->SetYTitle("Frequency");h_Pos_g1ycl->SetLabelSize(0.045,"XY");h_Pos_g1ycl->SetTitleSize(0.045,"XY");  


    TH1F* h_Pos_g3xcl = new TH1F(name1X,"",100,-10,110); h_Pos_g3xcl->SetXTitle("Cluster position [mm]"); h_Pos_g3xcl->SetYTitle("Frequency");h_Pos_g3xcl->SetLabelSize(0.045,"XY");h_Pos_g3xcl->SetTitleSize(0.045,"XY");
    TH1F* h_Pos_g3ycl = new TH1F(name1Y,"",100,-10,110); h_Pos_g3ycl->SetXTitle(" Cluster position [mm]"); h_Pos_g3ycl->SetYTitle("Frequency");h_Pos_g3ycl->SetLabelSize(0.045,"XY");h_Pos_g3ycl->SetTitleSize(0.045,"XY");  

    char nameRes2X[20];sprintf(nameRes2X,"residual_g2xcl_%i",iterNb);char nameRes2Y[20];sprintf(nameRes2Y,"residual_g2ycl_%i",iterNb);
    char nameRes3X[20];sprintf(nameRes3X,"residual_g3xcl_%i",iterNb);char nameRes3Y[20];sprintf(nameRes3Y,"residual_g3ycl_%i",iterNb);

    char nameRes1X[20];sprintf(nameRes1X,"residual_g1xcl_%i",iterNb);char nameRes1Y[20];sprintf(nameRes1Y,"residual_g1ycl_%i",iterNb);


    TH1F* h_residual_g2xcl = new TH1F(nameRes2X,"",800,-8,8); h_residual_g2xcl->SetXTitle("Residual [mm]"); h_residual_g2xcl->SetYTitle("Frequency");h_residual_g2xcl->SetLabelSize(0.045,"XY");h_residual_g2xcl->SetTitleSize(0.045,"XY");
    TH1F* h_residual_g2ycl = new TH1F(nameRes2Y,"",800,-8,8); h_residual_g2ycl->SetXTitle("Residual [mm]"); h_residual_g2ycl->SetYTitle("Frequency");h_residual_g2ycl->SetLabelSize(0.045,"XY");h_residual_g2ycl->SetTitleSize(0.045,"XY");
    TH1F* h_residual_g3xcl = new TH1F(nameRes3X,"",800,-8,8); h_residual_g3xcl->SetXTitle("Residual [mm]"); h_residual_g3xcl->SetYTitle("Frequency");h_residual_g3xcl->SetLabelSize(0.045,"XY");h_residual_g3xcl->SetTitleSize(0.045,"XY");
    TH1F* h_residual_g3ycl = new TH1F(nameRes3Y,"",800,-8,8); h_residual_g3ycl->SetXTitle("Residual [mm]"); h_residual_g3ycl->SetYTitle("Frequency");h_residual_g3ycl->SetLabelSize(0.045,"XY");h_residual_g3ycl->SetTitleSize(0.045,"XY");

    TH1F* h_residual_g1xcl = new TH1F(nameRes1X,"",800,-8,8); h_residual_g1xcl->SetXTitle("Residual [mm]"); h_residual_g1xcl->SetYTitle("Frequency");h_residual_g1xcl->SetLabelSize(0.045,"XY");h_residual_g1xcl->SetTitleSize(0.045,"XY");
    TH1F* h_residual_g1ycl = new TH1F(nameRes1Y,"",800,-8,8); h_residual_g1ycl->SetXTitle("Residual [mm]"); h_residual_g1ycl->SetYTitle("Frequency");h_residual_g1ycl->SetLabelSize(0.045,"XY");h_residual_g1ycl->SetTitleSize(0.045,"XY");

    fout<<shi_g2xcl<<"\t"<<shi_g2ycl<<"\t"<<shi_g3xcl<<"\t"<<shi_g3ycl<<"\t"<<shi_g1xcl<<"\t"<<shi_g1ycl<<endl;

    int nnnn=0;
    TGraph* g1 = new TGraph();
    TF1* f1 = new TF1("line1","[0]+[1]*x",0,3200);
    TGraph* g2 = new TGraph();
    TF1* f2 = new TF1("line2","[0]+[1]*x",0,3200);

    for(unsigned int i=0;i<vPos_g2xcl.size();i++){
      vPos_g2xcl[i] = vPos_g2xcl[i] - shi_g2xcl; vPos_g2ycl[i] = vPos_g2ycl[i] - shi_g2ycl;      
      vPos_g3xcl[i] = vPos_g3xcl[i] - shi_g3xcl; vPos_g3ycl[i] = vPos_g3ycl[i] - shi_g3ycl;
      vPos_g1xcl[i] = vPos_g1xcl[i] - shi_g1xcl; vPos_g1ycl[i] = vPos_g1ycl[i] - shi_g1ycl;

      h_Pos_g2xcl->Fill(vPos_g2xcl[i]); h_Pos_g2ycl->Fill(vPos_g2ycl[i]);
      h_Pos_g3xcl->Fill(vPos_g3xcl[i]); h_Pos_g3ycl->Fill(vPos_g3ycl[i]);
      h_Pos_g1xcl->Fill(vPos_g1xcl[i]); h_Pos_g1ycl->Fill(vPos_g1ycl[i]);


      //      TGraph* g1 = new TGraph();
      g1->SetPoint(0,0,     vPos_g1xcl[i]);
      g1->SetPoint(1,380,vPos_g2xcl[i]);
      g1->SetPoint(2,830,vPos_g3xcl[i]);
      //      TF1* f1 = new TF1("line1","[0]+[1]*x",0,3200);
      g1->Fit("line1","Q");
      double intercept1 = f1->GetParameter(0);
      double slope1     = f1->GetParameter(1);
      double Measured_g1xcl = intercept1 + slope1*0.0;
      double Measured_g2xcl = intercept1 + slope1*380;
      double Measured_g3xcl = intercept1 + slope1*830;
      h_residual_g2xcl->Fill(Measured_g2xcl-vPos_g2xcl[i]);
      h_residual_g3xcl->Fill(Measured_g3xcl-vPos_g3xcl[i]);
      h_residual_g1xcl->Fill(Measured_g1xcl-vPos_g1xcl[i]);
      delete f1; delete g1;

      //      TGraph* g2 = new TGraph();
      g2->SetPoint(0,0,     vPos_g1ycl[i]);
      g2->SetPoint(1,380,vPos_g2ycl[i]);
      // exclusive
      // g2->SetPoint(2,2686.5,vpUVA3Y[i]);
      g2->SetPoint(2,830,vPos_g3ycl[i]);
      // inclusive

       //      TF1* f2 = new TF1("line2","[0]+[1]*x",0,3200);
      g2->Fit("line2","Q");
      double intercept2 = f2->GetParameter(0);
      double slope2     = f2->GetParameter(1);
      double Measured_g1ycl = intercept2 + slope2*0.0;
      double Measured_g2ycl = intercept2 + slope2*380;
      double Measured_g3ycl = intercept2 + slope2*830;

      h_residual_g2ycl->Fill(Measured_g2ycl-vPos_g2ycl[i]);
      h_residual_g3ycl->Fill(Measured_g3ycl-vPos_g3ycl[i]);

      h_residual_g1ycl->Fill(Measured_g1ycl-vPos_g1ycl[i]);
      delete f2; delete g2;
      nnnn++;

    }//for loop g2xcl size

    gStyle->SetOptFit(1111);
    
    I2GFvalues myValues;
    myValues = I2GFmainLoop(h_residual_g2xcl,1,10,1);
    mean_g2xcl = myValues.mean; //sigmaEta5=myValues.sigma;
    myValues = I2GFmainLoop(h_residual_g2ycl,1,10,1);
    mean_g2ycl = myValues.mean; //
    myValues = I2GFmainLoop(h_residual_g3xcl,1,10,1);
    mean_g3xcl = myValues.mean; //
    myValues = I2GFmainLoop(h_residual_g3ycl,1,10,1);
    mean_g3ycl = myValues.mean;

    myValues = I2GFmainLoop(h_residual_g1xcl,1,10,1);
    mean_g1xcl = myValues.mean; //
    myValues = I2GFmainLoop(h_residual_g1ycl,1,10,1);
    mean_g1ycl = myValues.mean;
    
    cout<<"residual mean: "<<mean_g2xcl<<"\t"<<mean_g2ycl<<"\t"<<mean_g3xcl<<"\t"<<mean_g3ycl<<"\t"<<mean_g1xcl<<"\t"<<mean_g1ycl<<endl;
    
    fout1<<"residual mean: "<<mean_g2xcl<<"\t"<<mean_g2ycl<<"\t"<<mean_g3xcl<<"\t"<<mean_g3ycl<<"\t"<<mean_g1xcl<<"\t"<<mean_g1ycl<<endl;
    
    f->Write();
    f->Close();
    
    double factor = -0.1;
    shi_g2xcl = mean_g2xcl*factor; shi_g2ycl = mean_g2ycl*factor; 
    shi_g3xcl = mean_g3xcl*factor; shi_g3ycl = mean_g3ycl*factor; 
    
    shi_g1xcl = mean_g1xcl*factor; shi_g1ycl = mean_g1ycl*factor; 
    
    
    if((mean_g2xcl>=-0.0005 && mean_g2xcl<=0.0005) && (mean_g2ycl>=-0.0005 && mean_g2ycl<=0.0005))
      if((mean_g3xcl>=-0.0005 && mean_g3xcl<=0.0005) && (mean_g3ycl>=-0.0005 && mean_g3ycl<=0.0005))

        	if((mean_g1xcl>=-0.0005 && mean_g1xcl<=0.0005) && (mean_g1ycl>=-0.0005 && mean_g1ycl<=0.0005))
          {
            cout<<"find it...iterating "<<iterNb<<" times."<<endl;
            break;
          }
  
    if(iterNb>500) break;
  }//while(1)
 fout.close();
 fout1.close();
 // return 0;
} // entire script
