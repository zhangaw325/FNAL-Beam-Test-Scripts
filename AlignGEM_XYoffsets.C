//#include <exception.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TMath.h>
#include <string>
#include <TString.h>

#include "doubleGausFit_withHistParameter.C"

//vector<double> DefaultVector; // just used to free memory from vectors.
int tracking(string thestring, double iterNbX, double iterNbY){
  double PI=TMath::Pi();
  //string thestring = "Position_REF2X_42_48";
  string txtfilename = thestring + ".txt";
  string residualHead = "rPhi_residual_";
  string residualMeanHead = "rPhi_residualMean_";
  string residualSigmaHead="rPhi_residualSigma_";
  string chi2Head = "rPhi_trackChi2_";
  string iterHead = "Iteration_";

  //fstream fout2("myresidual.txt",ios::out); 
  double pREF1X=0.0, pREF1Y=0.0;
  double pREF2X=0.0, pREF2Y=0.0;
  double pREF3X=0.0, pREF3Y=0.0;
  //double pZZ1=0.0, pZZ2=0.0;
  double pEta5=0.0;
  const int NNNNN = 6447;
  double vpREF1X[NNNNN]; double vpREF1Y[NNNNN];
  double vpREF2X[NNNNN]; double vpREF2Y[NNNNN];
  double vpREF3X[NNNNN]; double vpREF3Y[NNNNN];
  //vector<double> vpZZ1; vector<double> vpZZ2;
  double vpEta5[NNNNN];
  double shiREF1X=-9.92822, shiREF1Y=-0.68756;
  double shiREF2X=12.26791212, shiREF2Y=2.02708225;
  double shiREF3X=7.4824985, shiREF3Y=-2.35562;
  double shiEta5=0.0;//0.01509;
  double preshiREF1X=-2265, preshiREF1Y=-32;  
  double preshiREF2X=-2265, preshiREF2Y=-32;  //2127.4275
  double preshiREF3X=-2265, preshiREF3Y=-32;
  double aREF2REF1=0.0056995;//start angle: 0.01197;
  double aREF3REF1=-0.044254312;//-0.0171;//start angle: 0.008273;
  double aEta5REF1=0.0;//0.008098; 
  double tempREF2X, tempREF2Y, tempREF3X, tempREF3Y, tempUVA3X, tempUVA3Y, tempREF1X, tempREF1Y, tempEta5;
  double meanREF2X=0.0, meanREF2Y=0.0, meanREF3X=0.0, meanREF3Y=0.0, meanUVA3X=0.0, meanUVA3Y=0.0, meanREF1X=0.0, meanREF1Y=0.0, meanEta5=0.0;
  double sigmaREF2X=0.0,sigmaREF2Y=0.0,sigmaREF3X=0.0,sigmaREF3Y=0.0,sigmaUVA3X=0.0,sigmaUVA3Y=0.0,sigmaREF1X=0.0,sigmaREF1Y=0.0,sigmaEta5=0.0;
  double meanXChi2=0.0,meanYChi2=0.0, totalChi2=0.0; // chi square of tracks.
  double maximum=0.0, rms=0.0, lRange=0.0, hRange=0.0;  

  TH1D* hpREF1X = 0;
  TH1D* hpREF1Y = 0;  
  TH1D* hpREF2X = 0;
  TH1D* hpREF2Y = 0;
  TH1D* hpREF3X = 0;
  TH1D* hpREF3Y = 0; 
  TH1D* hpEta5  = 0;
  
  TH1D* residualREF1X = 0;
  TH1D* residualREF1Y = 0;
  TH1D* residualREF2X = 0;
  TH1D* residualREF2Y = 0;
  TH1D* residualREF3X = 0;
  TH1D* residualREF3Y = 0;
  TH1D* residualEta5 = 0;
  
  TH1D* angleREF2=0;
  TH1D* angleREF3=0;
  TH1D* angleEta5=0;
  TH1D* xTrackChi2=0;
  TH1D* yTrackChi2=0;
  
  preshiREF1X = -1810-iterNbX;// - iterNbX*2;
  preshiREF2X = preshiREF1X; preshiREF3X=preshiREF1X;
  preshiREF1Y = -40.0 + iterNbY*0.2;
  preshiREF2Y = preshiREF1Y;  preshiREF3Y = preshiREF1Y;
  
  char cp1x[20]; sprintf(cp1x,"%.2f",preshiREF1X);
  char cp1y[20]; sprintf(cp1y,"%.2f",preshiREF1Y);

  string fout1name = iterHead + thestring + "_inclusive_X_" + cp1x + ".txt"; //TString::Itoa(preshiREF2X,10).Data()
  //string fout3name = residualSigmaHead+ thestring + "_inclusive_X_" + cp2x + ".txt"; //TString::Itoa(preshiREF2X,10).Data()
  //string fout2name = chi2Head + thestring + "_inclusive_X_" + cp2x  + ".txt"; //TString::Itoa(preshiREF2X,10).Data()
  fstream fout1(fout1name.c_str(),ios::out|ios::app);
  //fstream fout3(fout3name.c_str(),ios::out|ios::app);
  //fstream fout2(fout2name.c_str(),ios::out|ios::app);
   	
      fstream fin(txtfilename.c_str(),ios::in);
      //if(!fin){cout<<"file not read"<<endl; return;}
      //else cout<<"processing "<<txtfilename<<endl;
        
      cout<<iterNbX<<"\t"<<iterNbY<<"\tX "<<preshiREF1X<<"\tY "<<preshiREF1Y<<endl;
      
      int nbLines=0;
      while(fin>>pREF1X>>pREF1Y>>pREF2X>>pREF2Y>>pREF3X>>pREF3Y>>pEta5){
        vpREF2X[nbLines]=pREF2X; vpREF2Y[nbLines]=pREF2Y; vpREF3X[nbLines]=pREF3X; vpREF3Y[nbLines]=pREF3Y;
        vpREF1X[nbLines]=pREF1X; vpREF1Y[nbLines]=pREF1Y;
        vpEta5[nbLines]=pEta5;
        //shift
        vpREF2X[nbLines] -= shiREF2X; vpREF2Y[nbLines] -= shiREF2Y;
        vpREF3X[nbLines] -= shiREF3X; vpREF3Y[nbLines] -= shiREF3Y;
        vpREF1X[nbLines] -= shiREF1X; vpREF1Y[nbLines] -= shiREF1Y; 
//        vpEta5[nbLines] ;
        //rotate
        tempREF2X=vpREF2X[nbLines]; tempREF2Y=vpREF2Y[nbLines]; tempREF3X=vpREF3X[nbLines]; tempREF3Y=vpREF3Y[nbLines]; 
        tempREF1X=vpREF1X[nbLines]; tempREF1Y=vpREF1Y[nbLines]; 
        vpREF2X[nbLines]=tempREF2X*cos(aREF2REF1)-tempREF2Y*sin(aREF2REF1);
        vpREF2Y[nbLines]=tempREF2X*sin(aREF2REF1)+tempREF2Y*cos(aREF2REF1);
        vpREF3X[nbLines]=tempREF3X*cos(aREF3REF1)-tempREF3Y*sin(aREF3REF1);
        vpREF3Y[nbLines]=tempREF3X*sin(aREF3REF1)+tempREF3Y*cos(aREF3REF1);
    
        vpEta5[nbLines] -= aEta5REF1;

        //change origin, move in X and Y
        vpREF2X[nbLines] -= preshiREF2X; vpREF2Y[nbLines] -= preshiREF2Y;
        vpREF3X[nbLines] -= preshiREF3X; vpREF3Y[nbLines] -= preshiREF3Y;
        vpREF1X[nbLines] -= preshiREF1X; vpREF1Y[nbLines] -= preshiREF1Y; 

        //transfer to (r,phi) position
        double rREF1 = sqrt(vpREF1X[nbLines]*vpREF1X[nbLines]+vpREF1Y[nbLines]*vpREF1Y[nbLines]);
        double phiREF1 = 0.0; if(vpREF1X[nbLines]!=0.0) phiREF1 = atan(vpREF1Y[nbLines]/vpREF1X[nbLines]);
        double rREF2 = sqrt(vpREF2X[nbLines]*vpREF2X[nbLines]+vpREF2Y[nbLines]*vpREF2Y[nbLines]);
        double phiREF2 = 0.0; if(vpREF2X[nbLines]!=0.0) phiREF2 = atan(vpREF2Y[nbLines]/vpREF2X[nbLines]);
        double rREF3 = sqrt(vpREF3X[nbLines]*vpREF3X[nbLines]+vpREF3Y[nbLines]*vpREF3Y[nbLines]);
        double phiREF3 = 0.0; if(vpREF3X[nbLines]!=0.0) phiREF3 = atan(vpREF3Y[nbLines]/vpREF3X[nbLines]);
 
        //asignment new r, phi position values to the vector. Note that from now on the vectors vp.. cantains r and phi values
        vpREF1X[nbLines]=rREF1; vpREF1Y[nbLines]=phiREF1;    
        vpREF2X[nbLines]=rREF2; vpREF2Y[nbLines]=phiREF2;
        vpREF3X[nbLines]=rREF3; vpREF3Y[nbLines]=phiREF3;
    
        nbLines++;
        //if(nbLines%10000==0) cout<<nbLines<<endl;
      }
      fin.close();
      //end of reading file

      char rootfile[50]; sprintf(rootfile,"_X_%.2f_Y_%.2f_inclusive_doubleGaussian.root",preshiREF2X,preshiREF2Y);
      string newhead = "./RootFiles/";
      string outputrootname=newhead+residualHead+thestring+rootfile;
//      TFile* f = new TFile(outputrootname.c_str(),"recreate");
/*
      char name2X[50];sprintf(name2X,"rREF2_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y); char name2Y[50];sprintf(name2Y,"phiREF2_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char name3X[50];sprintf(name3X,"rREF3_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y); char name3Y[50];sprintf(name3Y,"phiREF3_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameu3X[50];sprintf(nameu3X,"rUVA3_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameu3Y[50];sprintf(nameu3Y,"phiUVA3_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char name1X[50];sprintf(name1X,"rREF1_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y); char name1Y[50];sprintf(name1Y,"phiREF1_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameEta5[50];sprintf(nameEta5,"phiEta5_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y); 
      hpREF2X = new TH1D(name2X,"",1500,1950,2100); hpREF2X->SetXTitle("r [mm]"); hpREF2X->SetYTitle("Frequency");hpREF2X->SetLabelSize(0.05,"XY");hpREF2X->SetTitleSize(0.05,"XY");
       hpREF2Y = new TH1D(name2Y,"",200,-0.1,0.1); hpREF2Y->SetXTitle("#phi [rad]"); hpREF2Y->SetYTitle("Frequency");hpREF2Y->SetLabelSize(0.05,"XY");hpREF2Y->SetTitleSize(0.05,"XY");  
       hpREF3X = new TH1D(name3X,"",1500,1950,2100); hpREF3X->SetXTitle("r [mm]"); hpREF3X->SetYTitle("Frequency");hpREF3X->SetLabelSize(0.05,"XY");hpREF3X->SetTitleSize(0.05,"XY");
       hpREF3Y = new TH1D(name3Y,"",200,-0.1,0.1); hpREF3Y->SetXTitle("#phi [rad]"); hpREF3Y->SetYTitle("Frequency");hpREF3Y->SetLabelSize(0.05,"XY");hpREF3Y->SetTitleSize(0.05,"XY");  
       hpUVA3X = new TH1D(nameu3X,"",1500,1950,2100); hpUVA3X->SetXTitle("r [mm]"); hpUVA3X->SetYTitle("Frequency");hpUVA3X->SetLabelSize(0.05,"XY");hpUVA3X->SetTitleSize(0.05,"XY");
       hpUVA3Y = new TH1D(nameu3Y,"",200,-0.1,0.1); hpUVA3Y->SetXTitle("#phi [rad]"); hpUVA3Y->SetYTitle("Frequency");hpUVA3Y->SetLabelSize(0.05,"XY");hpUVA3Y->SetTitleSize(0.05,"XY");  
       hpREF1X = new TH1D(name1X,"",1500,1950,2100); hpREF1X->SetXTitle("r [mm]"); hpREF1X->SetYTitle("Frequency");hpREF1X->SetLabelSize(0.05,"XY");hpREF1X->SetTitleSize(0.05,"XY");
       hpREF1Y = new TH1D(name1Y,"",200,-0.1,0.1); hpREF1Y->SetXTitle("#phi [rad]"); hpREF1Y->SetYTitle("Frequency");hpREF1Y->SetLabelSize(0.05,"XY");hpREF1Y->SetTitleSize(0.05,"XY");  
       hpEta5 = new TH1D(nameEta5,"",200,-0.1,0.1); hpEta5->SetXTitle("#phi [rad]"); hpEta5->SetYTitle("Frequency"); hpEta5->SetLabelSize(0.05,"XY");hpEta5->SetTitleSize(0.05,"XY");
*/
      char nameRes1X[50];sprintf(nameRes1X,"residualREF1_r_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameRes1Y[50];sprintf(nameRes1Y,"residualREF1_phi_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameRes2X[50];sprintf(nameRes2X,"residualREF2_r_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameRes2Y[50];sprintf(nameRes2Y,"residualREF2_phi_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameRes3X[50];sprintf(nameRes3X,"residualREF3_r_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameRes3Y[50];sprintf(nameRes3Y,"residualREF3_phi_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
    //char nameResZZ1[50];sprintf(nameResZZ1,"residualZZ1_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameResZZ2[50];sprintf(nameResZZ2,"residualZZ2_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameResEta5[50];sprintf(nameResEta5,"residualEta5_phi_X_%.1f_Y_%.1f",preshiREF1X, preshiREF1Y);
      residualREF1X = new TH1D(nameRes1X,"",1000,-2,2); residualREF1X->SetXTitle("Residual in r [mm]"); residualREF1X->SetYTitle("Frequency");residualREF1X->SetLabelSize(0.05,"XY");residualREF1X->SetTitleSize(0.05,"XY");
      residualREF1Y = new TH1D(nameRes1Y,"",1000,-0.005,0.005); residualREF1Y->SetXTitle("Residual in #phi [rad]"); residualREF1Y->SetYTitle("Frequency");residualREF1Y->SetLabelSize(0.05,"XY");residualREF1Y->SetTitleSize(0.05,"XY");
      residualREF2X = new TH1D(nameRes2X,"",1000,-2,2); residualREF2X->SetXTitle("Residual in r [mm]"); residualREF2X->SetYTitle("Frequency");residualREF2X->SetLabelSize(0.05,"XY");residualREF2X->SetTitleSize(0.05,"XY");
      residualREF2Y = new TH1D(nameRes2Y,"",1000,-0.005,0.005); residualREF2Y->SetXTitle("Residual in #phi [rad]"); residualREF2Y->SetYTitle("Frequency");residualREF2Y->SetLabelSize(0.05,"XY");residualREF2Y->SetTitleSize(0.05,"XY");
      residualREF3X = new TH1D(nameRes3X,"",1000,-2,2); residualREF3X->SetXTitle("Residual in r [mm]"); residualREF3X->SetYTitle("Frequency");residualREF3X->SetLabelSize(0.05,"XY");residualREF3X->SetTitleSize(0.05,"XY");
      residualREF3Y = new TH1D(nameRes3Y,"",1000,-0.005,0.005); residualREF3Y->SetXTitle("Residual in #phi [rad]"); residualREF3Y->SetYTitle("Frequency");residualREF3Y->SetLabelSize(0.05,"XY");residualREF3Y->SetTitleSize(0.05,"XY");
      residualEta5 = new TH1D(nameResEta5,"",1000,-0.02,0.02); residualEta5->SetXTitle("Residual in #phi [rad]"); residualEta5->SetYTitle("Frequency");residualEta5->SetLabelSize(0.05,"XY");residualEta5->SetTitleSize(0.05,"XY");
/*    
      char nameAngleREF3[50]; sprintf(nameAngleREF3,"angleREF3_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameAngleUVA3[50]; sprintf(nameAngleUVA3,"angleUVA3_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameAngleREF1[50]; sprintf(nameAngleREF1,"angleREF1_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameAngleEta5[50]; sprintf(nameAngleEta5,"angleEta5_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
       angleREF3 = new TH1D(nameAngleREF3,"Rotation angle distribution of REF3 and REF2",1000,-0.005,0.005); angleREF3->SetXTitle("Angle [rad]"); angleREF3->SetYTitle("Frequency");
       angleUVA3 = new TH1D(nameAngleUVA3,"Rotation angle distribution of UVA3 and REF2",1000,-0.005,0.005); angleUVA3->SetXTitle("Angle [rad]"); angleUVA3->SetYTitle("Frequency");
       angleREF1 = new TH1D(nameAngleREF1,"Rotation angle distribution of REF1 and REF2",1000,-0.005,0.005); angleREF1->SetXTitle("Angle [rad]"); angleREF1->SetYTitle("Frequency");
       angleEta5 = new TH1D(nameAngleEta5,"Rotation Eta5 and REF2",500,-0.2,0.2);
*/    
      char nameChi2X[50]; sprintf(nameChi2X,"XTrackChi2_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameChi2Y[50]; sprintf(nameChi2Y,"YTrackChi2_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
       xTrackChi2 = new TH1D(nameChi2X,"Chi square of tracks in X projection",1000,0,0.2); xTrackChi2->SetXTitle("#chi^{2} of track in r"); xTrackChi2->SetYTitle("Frequency");
       xTrackChi2->SetTitleSize(0.04,"XY"); xTrackChi2->SetLabelSize(0.04,"XY");
       yTrackChi2 = new TH1D(nameChi2Y,"Chi square of tracks in Y projection",1000,0,0.00002); yTrackChi2->SetXTitle("#chi^{2} of track in #phi"); yTrackChi2->SetYTitle("Frequency");
       yTrackChi2->SetTitleSize(0.04,"XY"); yTrackChi2->SetLabelSize(0.04,"XY");
    
      //fill histograms first
/*
      for(Int_t i=0;i<NNNNN;i++){
      	hpREF2X->Fill(vpREF2X[i]); hpREF2Y->Fill(vpREF2Y[i]);
      	hpREF3X->Fill(vpREF3X[i]); hpREF3Y->Fill(vpREF3Y[i]);
      	hpUVA3X->Fill(vpUVA3X[i]); hpUVA3Y->Fill(vpUVA3Y[i]);
      	hpREF1X->Fill(vpREF1X[i]); hpREF1Y->Fill(vpREF1Y[i]);
      	hpEta5->Fill(vpEta5[i]);
    	
        angleREF3->Fill(vpREF3Y[i]-vpREF2Y[i]);
        angleUVA3->Fill(vpUVA3Y[i]-vpREF2Y[i]);
        angleREF1->Fill(vpREF1Y[i]-vpREF2Y[i]);
        angleEta5->Fill(vpEta5[i]-vpREF2Y[i]);
      }
*/      
/*
      I2GFvalues myValues;
      myValues = I2GFmainLoop(angleREF3,1,10,1);  double meanAngleREF3 = myValues.mean;
      myValues = I2GFmainLoop(angleUVA3,1,10,1);  double meanAngleUVA3 = myValues.mean;
      myValues = I2GFmainLoop(angleREF1,1,10,1);  double meanAngleREF1 = myValues.mean;
      myValues = I2GFmainLoop(angleEta5,1,10,1);  double meanAngleEta5 = myValues.mean;
*//* 
      double maximum = angleREF3->GetXaxis()->GetBinCenter(angleREF3->GetMaximumBin());   
      double rms = angleREF3->GetRMS(1); 
      double lRange = maximum - rms*2; 
      double hRange = maximum + rms*2;
      TF1* funAngleREF3 = new TF1("funAngleREF3","gaus",lRange,hRange); angleREF3->Fit("funAngleREF3","RQ");
      double meanAngleREF3=funAngleREF3->GetParameter(1);
      maximum = angleUVA3->GetXaxis()->GetBinCenter(angleUVA3->GetMaximumBin());
      rms = angleUVA3->GetRMS(1);
      lRange = maximum - rms*2; hRange = maximum + rms*2;
      TF1* funAngleUVA3 = new TF1("funAngleUVA3","gaus",lRange,hRange); angleUVA3->Fit("funAngleUVA3","RQ");
      double meanAngleUVA3=funAngleUVA3->GetParameter(1);
      maximum = angleREF1->GetXaxis()->GetBinCenter(angleREF1->GetMaximumBin());
      rms = angleREF1->GetRMS(1);
      lRange = maximum - rms*2; hRange = maximum + rms*2;
      TF1* funAngleREF1 = new TF1("funAngleREF1","gaus",lRange,hRange); angleREF1->Fit("funAngleREF1","RQ");
      double meanAngleREF1=funAngleREF1->GetParameter(1);
      maximum = angleEta5->GetXaxis()->GetBinCenter(angleEta5->GetMaximumBin());
      rms = angleEta5->GetRMS(1);
      lRange = maximum - rms*2; hRange = maximum + rms*2;
      TF1* funAngleEta5 = new TF1("funAngleEta5","gaus",lRange,hRange); angleEta5->Fit("funAngleEta5","RQ");
      double meanAngleEta5=funAngleEta5->GetParameter(1);
      delete funAngleREF3; delete funAngleUVA3; delete funAngleREF1; delete funAngleEta5;
*/
      //track fitting
      for(Int_t i=0;i<NNNNN;i++){
        
        double rREF1=vpREF1X[i], phiREF1=vpREF1Y[i];//-meanAngleREF1;
        double rREF2=vpREF2X[i], phiREF2=vpREF2Y[i];
        double rREF3=vpREF3X[i], phiREF3=vpREF3Y[i];//-meanAngleREF3;
        double phiEta5=vpEta5[i];//-meanAngleEta5;

        //fill track in r direction
        TGraph* g1 = new TGraph();
        g1->SetPoint(0,100, rREF1);
        g1->SetPoint(1,380, rREF2);
        g1->SetPoint(2,880, rREF3);
        g1->GetXaxis()->SetRangeUser(0,900);
        TF1* f1 = new TF1("line1","pol1",0,900);
        g1->Fit("line1","Q");
        double intercept1 = f1->GetParameter(0);
        double slope1     = f1->GetParameter(1);
        double MeasuredREF1X = intercept1 + slope1*100;
        double MeasuredREF2X = intercept1 + slope1*380;
        double MeasuredREF3X = intercept1 + slope1*880;
        residualREF2X->Fill(MeasuredREF2X-rREF2);
        residualREF3X->Fill(MeasuredREF3X-rREF3);
        residualUVA3X->Fill(MeasuredUVA3X-rUVA3);
        residualREF1X->Fill(MeasuredREF1X-rREF1);
        xTrackChi2->Fill(f1->GetChisquare());
        totalChi2 += f1->GetChisquare();
        delete f1; delete g1;
      
        //fill track in phi direction
        TGraph* g2 = new TGraph();
        g2->SetPoint(0,0,     phiREF2);
        g2->SetPoint(1,1143.5,phiREF3);
        g2->SetPoint(2,2011.5,phiEta5);
        g2->SetPoint(3,2686.5,phiUVA3);
        g2->SetPoint(4,3169.5,phiREF1);
        g2->GetXaxis()->SetRangeUser(-1000,3300);
        // inclusive
        //g2->SetPoint(2,2305.5,vpZZ2[i]); //inclusive 1
        //g2->SetPoint(2,2327.5,vpZZ1[i]);  //inclusive 2
        TF1* f2 = new TF1("line2","pol1",0,3200);
        g2->Fit("line2","Q");
        double intercept2 = f2->GetParameter(0);
        double slope2     = f2->GetParameter(1);
        double MeasuredREF2Y = intercept2 + slope2*0.0;
        double MeasuredREF3Y = intercept2 + slope2*1143.5;
        double MeasuredUVA3Y = intercept2 + slope2*2686.5;
        double MeasuredREF1Y = intercept2 + slope2*3169.5;
        //double MeasuredZZ1  = intercept2 + slope2*2327.5;
        //double MeasuredZZ2  = intercept2 + slope2*2305.5;
        double MeasuredEta5 = intercept2 + slope2*2011.5;
        residualREF2Y->Fill((MeasuredREF2Y-phiREF2));
        residualREF3Y->Fill((MeasuredREF3Y-phiREF3));
        residualUVA3Y->Fill((MeasuredUVA3Y-phiUVA3));
        residualREF1Y->Fill((MeasuredREF1Y-phiREF1));
        residualEta5->Fill((MeasuredEta5-phiEta5));
        //residualZZ1->Fill(MeasuredZZ1-vpZZ1[i]);
        //residualZZ2->Fill(MeasuredZZ2-vpZZ2[i]);
        yTrackChi2->Fill(f2->GetChisquare());
        totalChi2 += f2->GetChisquare();
        delete f2; delete g2;
  
        //nnnn++;
      } //end for loop of filling histograms and fitting tracks
#if 0
      //cout<<"after for loop"<<endl;
      //going to fit residual histograms
      gStyle->SetOptFit(1111);
    
/*
      myValues = I2GFmainLoop(residualREF2X,1,10,1);  meanREF2X = myValues.mean; sigmaREF2X=myValues.sigma;
      myValues = I2GFmainLoop(residualREF2Y,1,10,1);  meanREF2Y = myValues.mean; sigmaREF2Y=myValues.sigma;
      myValues = I2GFmainLoop(residualREF3X,1,10,1);  meanREF3X = myValues.mean; sigmaREF3X=myValues.sigma;
      myValues = I2GFmainLoop(residualREF3Y,1,10,1);  meanREF3Y = myValues.mean; sigmaREF3Y=myValues.sigma;
      myValues = I2GFmainLoop(residualUVA3X,1,10,1);  meanUVA3X = myValues.mean; sigmaUVA3X=myValues.sigma;
      myValues = I2GFmainLoop(residualUVA3Y,1,10,1);  meanUVA3Y = myValues.mean; sigmaUVA3Y=myValues.sigma;
      myValues = I2GFmainLoop(residualREF1X,1,10,1);  meanREF1X = myValues.mean; sigmaREF1X=myValues.sigma;
      myValues = I2GFmainLoop(residualREF1Y,1,10,1);  meanREF1Y = myValues.mean; sigmaREF1Y=myValues.sigma;
*/      
      I2GFvalues myValues;
      myValues = I2GFmainLoop(residualEta5,1,10,1);
      meanEta5 = myValues.mean; sigmaEta5=myValues.sigma;
/*
      maximum = residualEta5->GetXaxis()->GetBinCenter(residualEta5->GetMaximumBin());
      rms = residualEta5->GetRMS(1);
      lRange = maximum - rms*1.5; hRange = maximum + rms*1.5;
      TF1* funResidualEta5 = new TF1("funResidualEta5","gaus",lRange,hRange); residualEta5->Fit("funResidualEta5","RQ");
      meanEta5=funResidualEta5->GetParameter(1);
      sigmaEta5=funResidualEta5->GetParameter(2);
      delete funResidualEta5;
*/
      meanXChi2=xTrackChi2->GetMean();
      meanYChi2=yTrackChi2->GetMean();
      

      f->Write();
      f->Close();

      fout1<<preshiREF2X<<"\t"<<preshiREF2Y<<"\t"<<meanEta5<<"\t"<<sigmaEta5<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<"\t"<<totalChi2<<endl;
      //fout3<<preshiREF2X<<"\t"<<preshiREF2Y<<"\t"<<sigmaREF2X<<"\t"<<sigmaREF2Y<<"\t"<<sigmaREF3X<<"\t"<<sigmaREF3Y<<"\t"<<sigmaUVA3X<<"\t"<<sigmaUVA3Y<<"\t"<<sigmaREF1X<<"\t"<<sigmaREF1Y<<"\t"<<sigmaEta5<<endl;
      //fout2<<preshiREF2X<<"\t"<<preshiREF2Y<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
      //clear the vectors for next loop
      //vpREF2X.clear(); vpREF2Y.clear();
      //vpREF3X.clear(); vpREF3Y.clear();
      //vpUVA3X.clear(); vpUVA3Y.clear();
      //vpREF1X.clear(); vpREF1Y.clear();
      //vpEta5.clear();
      //vpREF2X.swap(DefaultVector); vpREF2Y.swap(DefaultVector); vpREF3X.swap(DefaultVector); vpREF3Y.swap(DefaultVector); 
      //vpUVA3X.swap(DefaultVector); vpUVA3Y.swap(DefaultVector); vpREF1X.swap(DefaultVector); vpREF1Y.swap(DefaultVector); vpEta5.swap(DefaultVector);
    
     // cout<<residualEta5->GetEntries()<<"TTTTTTTTTTTT"<<endl;
     //gDirectory->GetList()->Delete();
      //hpREF2X=NULL; hpREF2Y=NULL; hpREF3X=NULL; hpREF3Y=NULL;
      //hpUVA3X=NULL; hpUVA3Y=NULL; hpREF1X=NULL; hpREF1Y=NULL;
      //residualREF2X=NULL; residualREF2Y=NULL; residualREF3X=NULL; residualREF3Y=NULL;
      //residualUVA3X=NULL; residualUVA3Y=NULL; residualREF1X=NULL; residualREF1Y=NULL;
      //residualEta5=NULL;
      //funResidualEta5=NULL;
      //angleREF3=NULL; angleUVA3=NULL; angleREF1=NULL; angleEta5=NULL;

      //myValues.fit_func=NULL; 
     // delete myValues.fit_func;
     // f=NULL; delete f;
   //}//for-loop instead of while(1)
   //   delete hpREF2X; delete hpREF2Y; delete hpREF3X; delete hpREF3Y;
   //   delete hpUVA3X; delete hpUVA3Y; delete hpREF1X; delete hpREF1Y;
   //   delete residualREF2X; delete residualREF2Y; delete residualREF3X; delete residualREF3Y;
   //   delete residualUVA3X; delete residualUVA3Y; delete residualREF1X; delete residualREF1Y;
   //   delete residualEta5;
      //delete funResidualEta5;
   //   delete angleREF3; delete angleUVA3; delete angleREF1;
   //   delete angleEta5;
  //}
 fout1.close();
#endif
 //fout3.close();
 //fout2.close();
 return 0;
} // entire script

int AlignGEM_XYoffsets(){
	
  string name[1]={
  	"Position_Cluster_run017_HVScan_4150V_32GeV_20131017_1254pm_all"
  };
  //for(int i=0;i<1;i++)
  for(int iterNbX=0;iterNbX<=50;iterNbX++)
    for(int iterNbY=0;iterNbY<101;iterNbY++)
    {
     tracking(name[0],iterNbX, iterNbY);
    }
  return 0;
}

double CalculateCosTheta1(double x, double y, double x1,double y1){
	//double cosineTheta = ( x*x1 + y*y1 )/(x*x+y*y);
	double sineTheta = (x1*y - x*y1)/(x*x + y*y);
	//if(cosineTheta>1) cosineTheta=2-cosineTheta;
	//cout<<sineTheta<<endl;
	return asin(sineTheta);
}
