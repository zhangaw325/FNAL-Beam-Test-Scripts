//#include <exception.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TMath.h>
#include <string>
#include <TString.h>

#include "doubleGausFit_withHistParameter.C"

//vector<double> DefaultVector; // just used to free memory from vectors.
int tracking(string thestring, double iterNbX, double iterNbY, double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2Y, double shiREF3X, double shiREF3Y, double shiEta5, double Trk1Pos, double Trk2Pos, double Trk3Pos, double GEMPos , double aREF2REF1, double aREF3REF1 ){
  double PI=TMath::Pi();
  string txtfilename = thestring ;
  //string txtfilename = thestring + ".txt";
  thestring = "PostionLC1";
  string residualHead = "rPhi_residual_";
  string residualMeanHead = "rPhi_residualMean_";
  string residualSigmaHead="rPhi_residualSigma_";
  string chi2Head = "rPhi_trackChi2_";
  string iterHead = "Iteration_";

  //fstream fout2("myresidual.txt",ios::out); 
  double pREF1X=0.0, pREF1Y=0.0;
  double pREF2X=0.0, pREF2Y=0.0;
  double pREF3X=0.0, pREF3Y=0.0;
  double pEta5=0.0;
  
  /* 
    double shiREF1X=-9.92822, shiREF1Y=-0.68756;
    double shiREF2X=12.26791212, shiREF2Y=2.02708225;
    double shiREF3X=7.4824985, shiREF3Y=-2.35562;
    double shiEta5=0.0;//0.01509;
    double preshiREF1X=-2265, preshiREF1Y=-32;
    double preshiREF2X=-2265, preshiREF2Y=-32;  //2127.4275
    double preshiREF3X=-2265, preshiREF3Y=-32;
    */
    double preshiREF1X=-2590.0, preshiREF1Y=-455.;
    double preshiREF2X=-2590.0, preshiREF2Y=-455.;  //2127.4275
    double preshiREF3X=-2590.0, preshiREF3Y=-455.;
//    double aREF2REF1=0.0056995;//start angle: 0.01197;
//    double aREF3REF1=-0.044254312;//-0.0171;//start angle: 0.008273;
    double aEta5REF1=0.0;//0.008098;
    double tempREF2X, tempREF2Y, tempREF3X, tempREF3Y, tempREF1X, tempREF1Y, tempEta5;
    double meanREF2X=0.0, meanREF2Y=0.0, meanREF3X=0.0, meanREF3Y=0.0, meanREF1X=0.0, meanREF1Y=0.0, meanEta5=0.0;
    double sigmaREF2X=0.0,sigmaREF2Y=0.0,sigmaREF3X=0.0,sigmaREF3Y=0.0, sigmaREF1X=0.0,sigmaREF1Y=0.0,sigmaEta5=0.0;
    double meanXChi2=0.0,meanYChi2=0.0, totalChi2=0.0; // chi square of tracks.
    double maximum=0.0, rms=0.0, lRange=0.0, hRange=0.0;
    
    TH1F* hpREF1X = 0;
    TH1F* hpREF1Y = 0;
    TH1F* hpREF2X = 0;
    TH1F* hpREF2Y = 0;
    TH1F* hpREF3X = 0;
    TH1F* hpREF3Y = 0;
    TH1F* hpEta5  = 0;
    
    TH1F* residualREF1X = 0;
    TH1F* residualREF1Y = 0;
    TH1F* residualREF2X = 0;
    TH1F* residualREF2Y = 0;
    TH1F* residualREF3X = 0;
    TH1F* residualREF3Y = 0;
    TH1F* residualEta5 = 0;
    
    TH1F* angleREF2=0;
    TH1F* angleREF3=0;
    TH1F* angleEta5=0;
    TH1F* xTrackChi2=0;
    TH1F* yTrackChi2=0;
    
    preshiREF1X = -2580.-iterNbX;// - iterNbX*2;
    preshiREF2X = preshiREF1X; preshiREF3X=preshiREF1X;
    preshiREF1Y = -445. + iterNbY*0.2;
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
 
    struct DATA
    {
        double  vpREF1X, vpREF1Y, vpREF2X, vpREF2Y, vpREF3X, vpREF3Y, vpEta5;
    };
    
    vector<DATA>* v = new vector<DATA>;
    DATA d;
    
    while(fin>>pREF1X>>pREF1Y>>pREF2X>>pREF2Y>>pREF3X>>pREF3Y>>pEta5)
    {
        d.vpREF1X = pREF1X;
        d.vpREF1Y = pREF1Y;
        d.vpREF2X = pREF2X;
        d.vpREF2Y = pREF2Y;
        d.vpREF3X = pREF3X;
        d.vpREF3Y = pREF3Y;
        d.vpEta5  = pEta5;

        //shift
        d.vpREF1X -= shiREF1X; d.vpREF1Y -= shiREF1Y;
        d.vpREF2X -= shiREF2X; d.vpREF2Y -= shiREF2Y;
        d.vpREF3X -= shiREF3X; d.vpREF3Y -= shiREF3Y;
        
        //rotate
	tempREF1X = d.vpREF1X;	tempREF1Y = d.vpREF1Y;
	tempREF2X = d.vpREF2X;	tempREF2Y = d.vpREF2Y;
	tempREF3X = d.vpREF3X;	tempREF3Y = d.vpREF3Y;

        d.vpREF2X = tempREF2X*cos(aREF2REF1) - tempREF2Y*sin(aREF2REF1);
        d.vpREF2Y = tempREF2X*sin(aREF2REF1) + tempREF2Y*cos(aREF2REF1);
        d.vpREF3X = tempREF3X*cos(aREF3REF1) - tempREF3Y*sin(aREF3REF1);
        d.vpREF3Y = tempREF3X*sin(aREF3REF1) + tempREF3Y*cos(aREF3REF1);

        d.vpEta5 -= aEta5REF1;
        
        //change origin, move in X and Y
        d.vpREF1X -= preshiREF1X; d.vpREF1Y -= preshiREF1Y;
        d.vpREF2X -= preshiREF2X; d.vpREF2Y -= preshiREF2Y;
        d.vpREF3X -= preshiREF3X; d.vpREF3Y -= preshiREF3Y;
        
        //transfer to (r,phi) position
        double rREF1	= sqrt(d.vpREF1X*d.vpREF1X+d.vpREF1Y*d.vpREF1Y);
        double phiREF1	= 0.0; if(d.vpREF1X != 0.0) phiREF1 = atan(d.vpREF1Y/d.vpREF1X);
        double rREF2	= sqrt(d.vpREF2X*d.vpREF2X+d.vpREF2Y*d.vpREF2Y);
        double phiREF2	= 0.0; if(d.vpREF2X != 0.0) phiREF2 = atan(d.vpREF2Y/d.vpREF2X);
        double rREF3	= sqrt(d.vpREF3X*d.vpREF3X+d.vpREF3Y*d.vpREF3Y);
        double phiREF3	= 0.0; if(d.vpREF3X != 0.0) phiREF3 = atan(d.vpREF3Y/d.vpREF3X);
        
        //asignment new r, phi position values to the vector. Note that from now on the vectors vp.. cantains r and phi values
        d.vpREF1X = rREF1;
        d.vpREF1Y = phiREF1;
        d.vpREF2X = rREF2;
        d.vpREF2Y = phiREF2;
        d.vpREF3X = rREF3;
        d.vpREF3Y = phiREF3;
        
        v->push_back(d);
    }
    
      fin.close();
      //end of reading file

      char rootfile[50]; sprintf(rootfile,"_X_%.2f_Y_%.2f_inclusive_doubleGaussian.root",preshiREF2X,preshiREF2Y);
      string newhead = "./RootFiles/";
      string outputrootname=newhead+residualHead+thestring+rootfile;
      TFile* f = new TFile(outputrootname.c_str(),"recreate");

      char nameRes1X[50];sprintf(nameRes1X,"residualREF1_r_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameRes1Y[50];sprintf(nameRes1Y,"residualREF1_phi_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameRes2X[50];sprintf(nameRes2X,"residualREF2_r_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameRes2Y[50];sprintf(nameRes2Y,"residualREF2_phi_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameRes3X[50];sprintf(nameRes3X,"residualREF3_r_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);char nameRes3Y[50];sprintf(nameRes3Y,"residualREF3_phi_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameResEta5[50];sprintf(nameResEta5,"residualEta5_phi_X_%.1f_Y_%.1f",preshiREF1X, preshiREF1Y);

      residualREF1X = new TH1F(nameRes1X,"",1000,-8,8); residualREF1X->SetXTitle("Residual in r [mm]"); residualREF1X->SetYTitle("Frequency");residualREF1X->SetLabelSize(0.05,"XY");residualREF1X->SetTitleSize(0.05,"XY");
      residualREF1Y = new TH1F(nameRes1Y,"",1000,-20,20); residualREF1Y->SetXTitle("Residual in #phi [rad]"); residualREF1Y->SetYTitle("Frequency");residualREF1Y->SetLabelSize(0.05,"XY");residualREF1Y->SetTitleSize(0.05,"XY");
      residualREF2X = new TH1F(nameRes2X,"",1000,-8,8); residualREF2X->SetXTitle("Residual in r [mm]"); residualREF2X->SetYTitle("Frequency");residualREF2X->SetLabelSize(0.05,"XY");residualREF2X->SetTitleSize(0.05,"XY");
      residualREF2Y = new TH1F(nameRes2Y,"",1000,-20,20); residualREF2Y->SetXTitle("Residual in #phi [rad]"); residualREF2Y->SetYTitle("Frequency");residualREF2Y->SetLabelSize(0.05,"XY");residualREF2Y->SetTitleSize(0.05,"XY");
      residualREF3X = new TH1F(nameRes3X,"",1000,-8,8); residualREF3X->SetXTitle("Residual in r [mm]"); residualREF3X->SetYTitle("Frequency");residualREF3X->SetLabelSize(0.05,"XY");residualREF3X->SetTitleSize(0.05,"XY");
      residualREF3Y = new TH1F(nameRes3Y,"",1000,-20,40); residualREF3Y->SetXTitle("Residual in #phi [rad]"); residualREF3Y->SetYTitle("Frequency");residualREF3Y->SetLabelSize(0.05,"XY");residualREF3Y->SetTitleSize(0.05,"XY");
      residualEta5 = new TH1F(nameResEta5,"",1000,-20,20); residualEta5->SetXTitle("Residual in #phi [rad]"); residualEta5->SetYTitle("Frequency");residualEta5->SetLabelSize(0.05,"XY");residualEta5->SetTitleSize(0.05,"XY");


      char nameChi2X[50]; sprintf(nameChi2X,"XTrackChi2_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
      char nameChi2Y[50]; sprintf(nameChi2Y,"YTrackChi2_X_%.1f_Y_%.1f",preshiREF2X, preshiREF2Y);
       xTrackChi2 = new TH1F(nameChi2X,"Chi square of tracks in X projection",1000,0,0.2); xTrackChi2->SetXTitle("#chi^{2} of track in r"); xTrackChi2->SetYTitle("Frequency");
       xTrackChi2->SetTitleSize(0.04,"XY"); xTrackChi2->SetLabelSize(0.04,"XY");
       yTrackChi2 = new TH1F(nameChi2Y,"Chi square of tracks in Y projection",1000,0,0.00002); yTrackChi2->SetXTitle("#chi^{2} of track in #phi"); yTrackChi2->SetYTitle("Frequency");
       yTrackChi2->SetTitleSize(0.04,"XY"); yTrackChi2->SetLabelSize(0.04,"XY");
    
      //fill histograms first
    
    for(unsigned int i=0; i < v->size(); i++)
    {
        d=v->at(i);

        //fill track in r direction
        TGraph* g1 = new TGraph();
        g1->SetPoint(0,Trk1Pos, d.vpREF1X);
        g1->SetPoint(1,Trk2Pos, d.vpREF2X);
        g1->SetPoint(2,Trk3Pos, d.vpREF3X);
        g1->GetXaxis()->SetRangeUser(0,900);
        TF1* f1 = new TF1("line1","pol1",0,900);
        g1->Fit("line1","Q");
        double intercept1 = f1->GetParameter(0);
        double slope1     = f1->GetParameter(1);
        double MeasuredREF1X = intercept1 + slope1*Trk1Pos;
        double MeasuredREF2X = intercept1 + slope1*Trk2Pos;
        double MeasuredREF3X = intercept1 + slope1*Trk3Pos;

        residualREF2X->Fill(MeasuredREF2X-d.vpREF2X);
        residualREF3X->Fill(MeasuredREF3X-d.vpREF3X);
        residualREF1X->Fill(MeasuredREF1X-d.vpREF1X);
        xTrackChi2->Fill(f1->GetChisquare());
        totalChi2 += f1->GetChisquare();
        delete f1; delete g1;
      
        //fill track in phi direction
        TGraph* g2 = new TGraph();
        g2->SetPoint(0,Trk1Pos ,d.vpREF1Y);
        g2->SetPoint(1,Trk2Pos ,d.vpREF2Y);
        g2->SetPoint(2,Trk3Pos ,d.vpREF3Y);
        g2->SetPoint(3,GEMPos  ,d.vpEta5);		// need to modify z-position of GE11
        g2->GetXaxis()->SetRangeUser(0,2200);
        // inclusive
        TF1* f2 = new TF1("line2","pol1",0,2200);
        g2->Fit("line2","Q");
        double intercept2 = f2->GetParameter(0);
        double slope2     = f2->GetParameter(1);
        double MeasuredREF1Y = intercept2 + slope2*Trk1Pos;
        double MeasuredREF2Y = intercept2 + slope2*Trk2Pos;
        double MeasuredREF3Y = intercept2 + slope2*Trk3Pos;
        double MeasuredEta5  = intercept2 + slope2*GEMPos;
        residualREF2Y->Fill((MeasuredREF2Y-d.vpREF2Y));
        residualREF3Y->Fill((MeasuredREF3Y-d.vpREF3Y));
        residualREF1Y->Fill((MeasuredREF1Y-d.vpREF1Y));
        residualEta5->Fill((MeasuredEta5-d.vpEta5));
        yTrackChi2->Fill(f2->GetChisquare());
        totalChi2 += f2->GetChisquare();
        delete f2; delete g2;
  
      } //end for loop of filling histograms and fitting tracks
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
      
      TH1F *residualEta5_tmp = (TH1F*) residualEta5->Clone("residualEta5_tmp");

      myValues = I2GFmainLoop(residualEta5_tmp,1,10,1);   meanEta5 = myValues.mean; sigmaEta5=myValues.sigma;
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
 //fout3.close();
 //fout2.close();
 return 0;
} // entire script

void AlignGEM_XYoffsets(string InputTextFile, double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2Y, double shiREF3X, double shiREF3Y , double shiEta5, double Trk1Pos, double Trk2Pos, double Trk3Pos, double GEMPos, double aREF2REF1, double aREF3REF1)
{
//  string name[1]={
//  	"Position_Cluster_run017_HVScan_4150V_32GeV_20131017_1254pm_all"
//  };
  for(int iterNbX=0;iterNbX<=5;iterNbX++)
    for(int iterNbY=0;iterNbY<10;iterNbY++)
  //for(int iterNbX=0;iterNbX<=50;iterNbX++)
    //for(int iterNbY=0;iterNbY<101;iterNbY++)
    {
     tracking(InputTextFile, iterNbX, iterNbY, shiREF1X, shiREF1Y, shiREF2X, shiREF2Y, shiREF3X, shiREF3Y, shiEta5, Trk1Pos, Trk2Pos, Trk3Pos, GEMPos , aREF2REF1, aREF3REF1);
     //tracking(name[0],iterNbX, iterNbY);
    }
//  return 0;
}

double CalculateCosTheta1(double x, double y, double x1,double y1){
	//double cosineTheta = ( x*x1 + y*y1 )/(x*x+y*y);
	double sineTheta = (x1*y - x*y1)/(x*x + y*y);
	//if(cosineTheta>1) cosineTheta=2-cosineTheta;
	//cout<<sineTheta<<endl;
	return asin(sineTheta);
}
