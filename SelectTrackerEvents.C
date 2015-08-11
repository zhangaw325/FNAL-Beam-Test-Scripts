//this v0 is only used to output histograms with number of strips > 1
#include <TString.h>
#include <iostream>
#include <vector>
void main(){
  //  const int NN = 2000000; //number of events
  fstream fin("Hit_Position_Info.txt",ios::in);
  //number of hits
  vector <int> NHitsEta1,NHitsEta2,NHitsEta3,NHitsEta4,NHitsEta5,NHitsEta6,NHitsEta7,NHitsEta8;
  vector <int> NHitsZZ1,NHitsZZ2;
  vector <int> NHitsREF2X,NHitsREF2Y,NHitsREF3X,NHitsREF3Y,NHitsUVA3X,NHitsUVA3Y,NHitsREF1X,NHitsREF1Y;
  //positions on detectors
  vector <double> pREF2X,pREF2Y,pREF3X,pREF3Y,pUVA3X,pUVA3Y,pREF1X,pREF1Y;
  vector <double> pEta1,pEta2,pEta3,pEta4,pEta5,pEta6,pEta7,pEta8,pZZ1,pZZ2;
  //charges in detectors
  vector <double> qREF2X,qREF2Y,qREF23X,qREF3Y,qUVA3X,qUVA3Y,qREF1X,qREF1Y;
  vector <double> qEta1,qEta2,qEta3,qEta4,qEta5,qEta6,qEta7,qEta8,qZZ1,qZZ2;
  vector <double> sREF2X,sREF2Y,sREF3X,sREF3Y,sUVA3X,sUVA3Y,sREF1X,sREF1Y;
  vector <double> sEta1,sEta2,sEta3,sEta4,sEta5,sEta6,sEta7,sEta8,sZZ1,sZZ2;

  /*
  //number of hits
  vector <int> NHitsEta1[NN],NHitsEta2[NN],NHitsEta3[NN],NHitsEta4[NN],NHitsEta5[NN],NHitsEta6[NN],NHitsEta7[NN],NHitsEta8[NN];
  vector <int> NHitsZZ1[NN],NHitsZZ2[NN];
  vector <int> NHitsREF2X[NN],NHitsREF2Y[NN],NHitsREF3X[NN],NHitsREF3Y[NN],NHitsUVA3X[NN],NHitsUVA3Y[NN],NHitsREF1X[NN],NHitsREF1Y[NN];
  //positions on detectors
  double pREF2X[NN],pREF2Y[NN],pREF3X[NN],pREF3Y[NN],pUVA3X[NN],pUVA3Y[NN],pREF1X[NN],pREF1Y[NN];
  double pEta1[NN],pEta2[NN],pEta3[NN],pEta4[NN],pEta5[NN],pEta6[NN],pEta7[NN],pEta8[NN],pZZ1[NN],pZZ2[NN];
  //charges in detectors
  double qREF2X[NN],qREF2Y[NN],qREF3X[NN],qREF3Y[NN],qUVA3X[NN],qUVA3Y[NN],qREF1X[NN],qREF1Y[NN];
  double qEta1[NN],qEta2[NN],qEta3[NN],qEta4[NN],qEta5[NN],qEta6[NN],qEta7[NN],qEta8[NN],qZZ1[NN],qZZ2[NN];
  double sREF2X[NN],sREF2Y[NN],sREF3X[NN],sREF3Y[NN],sUVA3X[NN],sUVA3Y[NN],sREF1X[NN],sREF1Y[NN];
  double sEta1[NN],sEta2[NN],sEta3[NN],sEta4[NN],sEta5[NN],sEta6[NN],sEta7[NN],sEta8[NN],sZZ1[NN],sZZ2[NN];
  //initialize all the variables
  for(int i=0;i<NN;i++){
    NHitsEta1[i]=NHitsEta2[i]=NHitsEta3[i]=NHitsEta4[i]=NHitsEta5[i]=NHitsEta6[i]=NHitsEta7[i]=NHitsEta8[i]=NHitsZZ1[i]=NHitsZZ2[i]=0;
    NHitsREF2X[i]=NHitsREF2Y[i]=NHitsREF3X[i]=NHitsREF3Y[i]=NHitsUVA3X[i]=NHitsUVA3Y[i]=NHitsREF1X[i]=NHitsREF1Y[i]=0;
    pREF2X[i]=pREF2Y[i]=pREF3X[i]=pREF3Y[i]=pUVA3X[i]=pUVA3Y[i]=pREF1X[i]=pREF1Y[i]=pEta1[i]=pEta2[i]=pEta3[i]=pEta4[i]=pEta5[i]=pEta6[i]=pEta7[i]=pEta8[i]=pZZ1[i]=pZZ2[i]=1000.0;
    qREF2X[i]=qREF2Y[i]=qREF3X[i]=qREF3Y[i]=qUVA3X[i]=qUVA3Y[i]=qREF1X[i]=qREF1Y[i]=qEta1[i]=qEta2[i]=qEta3[i]=qEta4[i]=qEta5[i]=qEta6[i]=qEta7[i]=qEta8[i]=qZZ1[i]=qZZ2[i]=1000.0;
    sREF2X[i]=sREF2Y[i]=sREF3X[i]=sREF3Y[i]=sUVA3X[i]=sUVA3Y[i]=sREF1X[i]=sREF1Y[i]=sEta1[i]=sEta2[i]=sEta3[i]=sEta4[i]=sEta5[i]=sEta6[i]=sEta7[i]=sEta8[i]=sZZ1[i]=sZZ2[i]=0.0;
  }*/

  //read the file, write values to array
  int evtNb=0;
  int count=0;
  TString firstString;
  int nbHits;
  double charge,position,strip;
  int aSingleStrip; double aSingleCharge;
  while(fin.good()) {
    fin>>firstString;
    if(firstString.EqualTo("EventNb")){
      fin>>count;
      evtNb++;
      if(evtNb%5000==0) cout<<"event number "<<evtNb<<endl;
      continue;
    }
    fin>>nbHits>>charge>>position>>strip;
    for(int i=0;i<nbHits;i++){fin>>aSingleStrip>>aSingleCharge;}

    if(firstString.EqualTo("sCMSNS2LC1"))
      {
	NHitsEta1.push_back(nbHits);
	qEta1.push_back(charge);
	pEta1.push_back(position);
	sEta1.push_back(strip);
      }
    if(firstString.EqualTo("sCMSNS2LC2"))
      {
        NHitsEta2.push_back(nbHits);
        qEta2.push_back(charge);
        pEta2.push_back(position);
        sEta2.push_back(strip);
      }
    if(firstString.EqualTo("sCMSNS2LC3"))
      {
        NHitsEta3.push_back(nbHits);
        qEta3.push_back(charge);
        pEta3.push_back(position);
        sEta3.push_back(strip);
      }
    if(firstString.EqualTo("g1xcl"))
      {
	NHitsREF1X.push_back(nbHits);
	qREF1X.push_back(charge);
	pREF1X.push_back(position);
	sREF1X.push_back(strip);
      }
    if(firstString.EqualTo("g1ycl"))
      {
        NHitsREF1Y.push_back(nbHits);
	qREF1Y.push_back(charge);
	pREF1Y.push_back(position);
	sREF1Y.push_back(strip);
      }
    if(firstString.EqualTo("g2xcl"))
   {
     NHitsREF2X.push_back(nbHits);    
     qREF2X.push_back(charge);
     pREF2X.push_back(position);
     sREF2X.push_back(strip);
   }
    if(firstString.EqualTo("g2ycl"))
      {
	NHitsREF2Y.push_back(nbHits);
      qREF2Y.push_back(charge);
      pREF2Y.push_back(position);
      sREF2Y.push_back(strip);
    }
  if(firstString.EqualTo("g3xcl"))
    {
      NHitsREF3X.push_back(nbHits);
      qREF3X.push_back(charge);
      pREF3X.push_back(position);
      sREF3X.push_back(strip);
    }
  if(firstString.EqualTo("g3ycl"))
    {
      NHitsREF3Y.push_back(nbHits);
      qREF3Y.push_back(charge);
      pREF3Y.push_back(position);
      sREF3Y.push_back(strip);
    }



  /* if(firstString.EqualTo("ETA01")) { NHitsEta1[evtNb-1]=nbHits; qEta1[evtNb-1]=charge; pEta1[evtNb-1]=position; sEta1[evtNb-1]=strip; }
    if(firstString.EqualTo("ETA02")) { NHitsEta2[evtNb-1]=nbHits; qEta2[evtNb-1]=charge; pEta2[evtNb-1]=position; sEta2[evtNb-1]=strip;}
    if(firstString.EqualTo("ETA03")) { NHitsEta3[evtNb-1]=nbHits; qEta3[evtNb-1]=charge; pEta3[evtNb-1]=position; sEta3[evtNb-1]=strip;}
    if(firstString.EqualTo("ETA04")) { NHitsEta4[evtNb-1]=nbHits; qEta4[evtNb-1]=charge; pEta4[evtNb-1]=position; sEta4[evtNb-1]=strip;}
    if(firstString.EqualTo("ETA05")) { NHitsEta5[evtNb-1]=nbHits; qEta5[evtNb-1]=charge; pEta5[evtNb-1]=position; sEta5[evtNb-1]=strip;}
    if(firstString.EqualTo("ETA06")) { NHitsEta6[evtNb-1]=nbHits; qEta6[evtNb-1]=charge; pEta6[evtNb-1]=position; sEta6[evtNb-1]=strip;}
    if(firstString.EqualTo("ETA07")) { NHitsEta7[evtNb-1]=nbHits; qEta7[evtNb-1]=charge; pEta7[evtNb-1]=position; sEta7[evtNb-1]=strip;}
    if(firstString.EqualTo("ETA08")) { NHitsEta8[evtNb-1]=nbHits; qEta8[evtNb-1]=charge; pEta8[evtNb-1]=position; sEta8[evtNb-1]=strip;}
    if(firstString.EqualTo("ZZ01M")) { NHitsZZ1[evtNb-1]=nbHits; qZZ1[evtNb-1]=charge; pZZ1[evtNb-1]=position; sZZ1[evtNb-1]=strip;}
    if(firstString.EqualTo("ZZ02S")) { NHitsZZ2[evtNb-1]=nbHits; qZZ2[evtNb-1]=charge; pZZ2[evtNb-1]=position; sZZ2[evtNb-1]=strip;}
    if(firstString.EqualTo("REF2X")) { NHitsREF2X[evtNb-1]=nbHits; qREF2X[evtNb-1]=charge; pREF2X[evtNb-1]=position; sREF2X[evtNb-1]=strip;}
    if(firstString.EqualTo("REF2Y")) { NHitsREF2Y[evtNb-1]=nbHits; qREF2Y[evtNb-1]=charge; pREF2Y[evtNb-1]=position; sREF2Y[evtNb-1]=strip;}
    if(firstString.EqualTo("REF3X")) { NHitsREF3X[evtNb-1]=nbHits; qREF3X[evtNb-1]=charge; pREF3X[evtNb-1]=position; sREF3X[evtNb-1]=strip;}
    if(firstString.EqualTo("REF3Y")) { NHitsREF3Y[evtNb-1]=nbHits; qREF3Y[evtNb-1]=charge; pREF3Y[evtNb-1]=position; sREF3Y[evtNb-1]=strip;}
    if(firstString.EqualTo("UVA3X")) { NHitsUVA3X[evtNb-1]=nbHits; qUVA3X[evtNb-1]=charge; pUVA3X[evtNb-1]=position; sUVA3X[evtNb-1]=strip;}
    if(firstString.EqualTo("UVA3Y")) { NHitsUVA3Y[evtNb-1]=nbHits; qUVA3Y[evtNb-1]=charge; pUVA3Y[evtNb-1]=position; sUVA3Y[evtNb-1]=strip;}
    if(firstString.EqualTo("REF1X")) { NHitsREF1X[evtNb-1]=nbHits; qREF1X[evtNb-1]=charge; pREF1X[evtNb-1]=position; sREF1X[evtNb-1]=strip;}
    if(firstString.EqualTo("REF1Y")) { NHitsREF1Y[evtNb-1]=nbHits; qREF1Y[evtNb-1]=charge; pREF1Y[evtNb-1]=position; sREF1Y[evtNb-1]=strip;}
    } //end reading file */
  //
  TString outputfile = Form("Position.txt");
  //TString outputSfile = Form("Strips_run001_UVaSBS1_3TimeSamples_scanP22_20131021.txt");
  TString rootfile = Form("CoarseAligned.root");
  fstream fout(outputfile.Data(),ios::out);
  //fstream foutS(outputSfile.Data(),ios::out);
  TFile* f = new TFile(rootfile.Data(),"recreate");

  TH1F* hpREF2X=new TH1F("posREF2X","",500,-50,50);hpREF2X->SetXTitle("Cluster position [mm]");hpREF2X->SetYTitle("Frequency");hpREF2X->SetTitleSize(0.04,"XY");hpREF2X->SetLabelSize(0.04,"XY");
  TH1F* hpREF2Y=new TH1F("posREF2Y","",500,-50,50);hpREF2Y->SetXTitle("Cluster position [mm]");hpREF2Y->SetYTitle("Frequency");hpREF2Y->SetTitleSize(0.04,"XY");hpREF2Y->SetLabelSize(0.04,"XY");
  TH1F* hpREF3X=new TH1F("posREF3X","",500,-50,50);hpREF3X->SetXTitle("Cluster position [mm]");hpREF3X->SetYTitle("Frequency");hpREF3X->SetTitleSize(0.04,"XY");hpREF3X->SetLabelSize(0.04,"XY");
  TH1F* hpREF3Y=new TH1F("posREF3Y","",500,-50,50);hpREF3Y->SetXTitle("Cluster position [mm]");hpREF3Y->SetYTitle("Frequency");hpREF3Y->SetTitleSize(0.04,"XY");hpREF3Y->SetLabelSize(0.04,"XY");
  //  TH1F* hpUVA3X=new TH1F("posUVA3X","",500,-50,50);hpUVA3X->SetXTitle("Cluster position [mm]");hpUVA3X->SetYTitle("Frequency");hpUVA3X->SetTitleSize(0.04,"XY");hpUVA3X->SetLabelSize(0.04,"XY");
  // TH1F* hpUVA3Y=new TH1F("posUVA3Y","",500,-50,50);hpUVA3Y->SetXTitle("Cluster position [mm]");hpUVA3Y->SetYTitle("Frequency");hpUVA3Y->SetTitleSize(0.04,"XY");hpUVA3Y->SetLabelSize(0.04,"XY");
  TH1F* hpREF1X=new TH1F("posREF1X","",500,-50,50);hpREF1X->SetXTitle("Cluster position [mm]");hpREF1X->SetYTitle("Frequency");hpREF1X->SetTitleSize(0.04,"XY");hpREF1X->SetLabelSize(0.04,"XY");
  TH1F* hpREF1Y=new TH1F("posREF1Y","",500,-50,50);hpREF1Y->SetXTitle("Cluster position [mm]");hpREF1Y->SetYTitle("Frequency");hpREF1Y->SetTitleSize(0.04,"XY");hpREF1Y->SetLabelSize(0.04,"XY");
  //TH1F* hpZZ1 =new TH1F("posZZ01M","",500,-50,50);hpZZ1->SetXTitle("Cluster position [mm]");hpZZ1->SetYTitle("Frequency");hpZZ1->SetTitleSize(0.04,"XY");hpZZ1->SetLabelSize(0.04,"XY");//hpZZ1->SetTitle("Number of strips > 0");
  //TH1F* hpZZ2 =new TH1F("posZZ02S","",500,-50,50);hpZZ2->SetXTitle("Cluster position [mm]");hpZZ2->SetYTitle("Frequency");hpZZ2->SetTitleSize(0.04,"XY");hpZZ2->SetLabelSize(0.04,"XY");//hpZZ2->SetTitle("");
  // TH1F* hpEta5 =new TH1F("posEta5","",500,-50,50);hpEta5->SetXTitle("Cluster position [mm]");hpEta5->SetYTitle("Frequency");hpEta5->SetTitleSize(0.04,"XY");hpEta5->SetLabelSize(0.04,"XY");//hpEta5->SetTitle();

  // TH1F* hsREF2X=new TH1F("StripREF2X","",600,-300,300);hsREF2X->SetXTitle("Cluster position in terms of strip");hsREF2X->SetYTitle("Frequency");hsREF2X->SetTitleSize(0.04,"XY");hsREF2X->SetLabelSize(0.04,"XY");
  //  TH1F* hsREF2Y=new TH1F("StripREF2Y","",600,-300,300);hsREF2Y->SetXTitle("Cluster position in terms of strip");hsREF2Y->SetYTitle("Frequency");hsREF2Y->SetTitleSize(0.04,"XY");hsREF2Y->SetLabelSize(0.04,"XY");
  // TH1F* hsREF3X=new TH1F("StripREF3X","",600,-300,300);hsREF3X->SetXTitle("Cluster position in terms of strip");hsREF3X->SetYTitle("Frequency");hsREF3X->SetTitleSize(0.04,"XY");hsREF3X->SetLabelSize(0.04,"XY");
  // TH1F* hsREF3Y=new TH1F("StripREF3Y","",600,-300,300);hsREF3Y->SetXTitle("Cluster position in terms of strip");hsREF3Y->SetYTitle("Frequency");hsREF3Y->SetTitleSize(0.04,"XY");hsREF3Y->SetLabelSize(0.04,"XY");
  //  TH1F* hsUVA3X=new TH1F("StripUVA3X","",600,-300,300);hsUVA3X->SetXTitle("Cluster position in terms of strip");hsUVA3X->SetYTitle("Frequency");hsUVA3X->SetTitleSize(0.04,"XY");hsUVA3X->SetLabelSize(0.04,"XY");
  //  TH1F* hsUVA3Y=new TH1F("StripUVA3Y","",600,-300,300);hsUVA3Y->SetXTitle("Cluster position in terms of strip");hsUVA3Y->SetYTitle("Frequency");hsUVA3Y->SetTitleSize(0.04,"XY");hsUVA3Y->SetLabelSize(0.04,"XY");
  // TH1F* hsREF1X=new TH1F("StripREF1X","",600,-300,300);hsREF1X->SetXTitle("Cluster position in terms of strip");hsREF1X->SetYTitle("Frequency");hsREF1X->SetTitleSize(0.04,"XY");hsREF1X->SetLabelSize(0.04,"XY");
  // TH1F* hsREF1Y=new TH1F("StripREF1Y","",600,-300,300);hsREF1Y->SetXTitle("Cluster position in terms of strip");hsREF1Y->SetYTitle("Frequency");hsREF1Y->SetTitleSize(0.04,"XY");hsREF1Y->SetLabelSize(0.04,"XY");
  //TH1F* hsZZ1 =new TH1F("StripZZ01M","",50,0,50);hsZZ1->SetXTitle("Cluster position in terms of strip");hsZZ1->SetYTitle("Frequency");hsZZ1->SetTitleSize(0.04,"XY");hsZZ1->SetLabelSize(0.04,"XY");//hsZZ1->SetTitle("Number of strips > 0");
  //TH1F* hsZZ2 =new TH1F("StripZZ02S","",50,0,50);hsZZ2->SetXTitle("Cluster position in terms of strip");hsZZ2->SetYTitle("Frequency");hsZZ2->SetTitleSize(0.04,"XY");hsZZ2->SetLabelSize(0.04,"XY");//hsZZ2->SetTitle("");
  // TH1F* hsEta5 =new TH1F("StripEta5","",300,-150,150);  hsEta5->SetXTitle("Cluster position in terms of strip");hsEta5->SetYTitle("Frequency");hsEta5->SetTitleSize(0.04,"XY");hsEta5->SetLabelSize(0.04,"XY");//hsEta5->SetTitle();

  // HVscan_3800V_20131017 parameters
  //double shiREF2X=8.879, shiREF2Y=0.7306, shiREF3X=3.766, shiREF3Y=-3.525, shiUVA3X=-8.219, shiUVA3Y=14.79, shiREF1X=-13.88, shiREF1Y=-1.704;
  //double shiEta5=29.11, shiZZ1=-0.07628, shiZZ2=-0.9252;
  //HVscan_4200V_20131017 parameters
  //double shiREF2X=11.32, shiREF2Y=0.8678, shiREF3X=5.515, shiREF3Y=-3.57, shiUVA3X=-2, shiUVA3Y=14.77, shiREF1X=-11.32, shiREF1Y=-1.946;
  //double shiEta5=29.2, shiZZ1=0.03809, shiZZ2=-0.8961;
  //run001_UVaSBS1_3TimeSamples_scanP22_20131021 parameters
  //double shiREF2X=7.368, shiREF2Y=-0.6013, shiREF3X=1.772, shiREF3Y=-5.018, shiUVA3X=-5.4, shiUVA3Y=13.58, shiREF1X=-15.92, shiREF1Y=-3.058;
  //double shiEta5=-14.03, shiZZ1=0.0, shiZZ2=0.0; // no signals on ZZ
  //double shiREF2X=-0.559, shiREF2Y=1.186, shiREF3X=-5, shiREF3Y=-3.142, shiUVA3X=-13.66, shiUVA3Y=15.16, shiREF1X=-20.63, shiREF1Y=-1.511;
  //double shiEta5=36.79, shiZZ1=0.0, shiZZ2=0.0; // no signals on ZZ
  //Cluster_run002_highstat_10cmZZ3900V_S43950V_CMS3250V_32GeV_20131017_1009pm
 
  int totalEvents=0;
  for(int i=0;i<qEta1->size();i++){
    //set number of hits cut conditions
    Bool_t cutNHitsREF2=kFALSE;
    if(NHitsREF2X->at(i)>0 && NHitsREF2Y->at(i)>0) 
      {
	cutNHitsREF2=kTRUE;
      } //cout<<"REF2 true"<<endl;}
    Bool_t cutNHitsREF3=kFALSE;
    if(NHitsREF3X->at(i)>0 && NHitsREF3Y->at(i)>0) 
      {
	cutNHitsREF3=kTRUE;
      }//cout<<"REF3 true"<<endl;}
    //  Bool_t cutNHitsUVA3=kFALSE; if(NHitsUVA3X[i]>0 && NHitsUVA3Y[i]>0) {cutNHitsUVA3=kTRUE;}//cout<<"UVA3 true"<<endl;}
    
    Bool_t cutNHitsREF1=kFALSE;
    if(NHitsREF1X->at(i)>0 && NHitsREF1Y->at(i)>0) 
      {
	cutNHitsREF1=kTRUE;
      }//cout<<"REF1 true"<<endl;}
    Bool_t cutNHitsEta1=kFALSE; if(NHitsEta1->at(i)>0) {cutNHitsEta1=kTRUE;}
    Bool_t cutNHitsEta2=kFALSE; if(NHitsEta2->at(i)>0) {cutNHitsEta2=kTRUE;}
    Bool_t cutNHitsEta3=kFALSE; if(NHitsEta3->at(i)>0) {cutNHitsEta3=kTRUE;}
    // Bool_t cutNHitsEta4=kFALSE; if(NHitsEta4[i]>0) {cutNHitsEta4=kTRUE;}//cout<<pEta4[i]<<endl;}
    // Bool_t cutNHitsEta5=kFALSE; if(NHitsEta5[i]>0) {cutNHitsEta5=kTRUE;}//cout<<pEta5[i]<<endl;}
    // Bool_t cutNHitsEta6=kFALSE; if(NHitsEta6[i]>0) cutNHitsEta6=kTRUE;
    // Bool_t cutNHitsEta7=kFALSE; if(NHitsEta7[i]>0) cutNHitsEta7=kTRUE;
    // Bool_t cutNHitsEta8=kFALSE; if(NHitsEta8[i]>0) cutNHitsEta8=kTRUE;
    // Bool_t cutNHitsZZ1=kFALSE; if(NHitsZZ1[i]>0) cutNHitsZZ1=kTRUE;
    // Bool_t cutNHitsZZ2=kFALSE; if(NHitsZZ2[i]>0) cutNHitsZZ2=kTRUE;
    // set position cut condition
    // Bool_t cutpREF2X=kFALSE; if(pREF2X[i]>=0.0 && pREF2X[i]<=10.0) cutpREF2X=kTRUE;
    // Bool_t cutpZZ1=kFALSE;   if(pZZ1[i]>=0.0) cutpZZ1=kTRUE;
    // Bool_t cutpZZ2=kFALSE;   if(pZZ2[i]>=0.0) cutpZZ2=kTRUE;
    Bool_t cutpREF2X=kFALSE; if(pREF2X->at(i)>=7.5 && pREF2X->at(i)<=7.9) {cutpREF2X=kTRUE;}
    Bool_t cutpREF1X=kFALSE; if(pREF1X->at(i)>=-44 && pREF1X->at(i)<=-42) {cutpREF1X=kTRUE;}
    Bool_t cutpREF3X=kFALSE; if(pREF3X->at(i)>=54 && pREF3X->at(i)<=56) {cutpREF3X=kTRUE;}
    // Bool_t cutpUVA3X=kFALSE; if(pUVA3X[i]>=50 && pUVA3X[i]<=52) cutpUVA3X=kTRUE;
    Bool_t cutpREF2Y=kFALSE; if(pREF2Y->at(i)>=-10 && pREF2Y->at(i)<=-5) {cutpREF2Y=kTRUE;}
    Bool_t cutpREF1Y=kFALSE; if(pREF1Y->at(i)>=-4 && pREF1Y->at(i)<=8) {cutpREF1Y=kTRUE;}
    // Bool_t cutpZZ1=kFALSE; if(pZZ1[i]>=0 && pZZ1[i]<=2) cutpZZ1=kTRUE;
    // Bool_t cutpEta5=kFALSE; if(pEta5[i]>=28.7 && pEta5[i]<=29.5) cutpEta5=kTRUE;
    
    //then combine the cut conditions & fill histograms
    Bool_t trigger=kFALSE; if(cutNHitsREF2==kTRUE && cutNHitsREF3==KTRUE && cutNHitsREF1==kTRUE ) {trigger=kTRUE;}
    if(trigger ){
        totalEvents++;
        fout<<pREF2X->at(i)<<"\t"<<pREF2Y->at(i)<<"\t"<<pREF3X->at(i)<<"\t"<<pREF3Y->at(i)<<"\t"<<pREF1X[i]<<"\t"<<pREF1Y[i]<<endl;
        hpREF2X->Fill(pREF2X->at(i)); 
	hpREF2Y->Fill(pREF2Y->at(i));
	hpREF3X->Fill(pREF3X->at(i)); 
	hpREF3Y->Fill(pREF3Y->at(i));
	hpREF1X->Fill(pREF1X->at(i));
        hpREF1Y->Fill(pREF1Y->at(i));
	//  hpUVA3X->Fill(pUVA3X[i]); hpUVA3Y->Fill(pUVA3Y[i]); hpREF1X->Fill(pREF1X[i]); hpREF1Y->Fill(pREF1Y[i]);
        //hpZZ1->Fill(pZZ1[i]-shiZZ1); hpZZ2->Fill(pZZ2[i]-shiZZ2);
        //hpEta5->Fill(pEta5[i]-shiEta5);
        
	// foutS<<sREF2X[i]-shisREF2X<<"\t"<<sREF2Y[i]-shisREF2Y<<"\t"<<sREF3X[i]-shisREF3X<<"\t"<<sREF3Y[i]-shisREF3Y<<"\t"<<sUVA3X[i]-shisUVA3X<<"\t"<<sUVA3Y[i]-shisUVA3Y<<"\t"
       //     <<sREF1X[i]-shisREF1X<<"\t"<<sREF1Y[i]-shisREF1Y<<"\t"<<sEta5[i]-shisEta5<<endl;//"\t"<<pEta5[i]-shiEta5<<endl;
       // hsREF2X->Fill(sREF2X[i]-shisREF2X); hsREF2Y->Fill(sREF2Y[i]-shisREF2Y); hsREF3X->Fill(sREF3X[i]-shisREF3X); hsREF3Y->Fill(sREF3Y[i]-shisREF3Y);
       // hsUVA3X->Fill(sUVA3X[i]-shisUVA3X); hsUVA3Y->Fill(sUVA3Y[i]-shisUVA3Y); hsREF1X->Fill(sREF1X[i]-shisREF1X); hsREF1Y->Fill(sREF1Y[i]-shisREF1Y);
        //hsZZ1->Fill(sZZ1[i]-shisZZ1); hsZZ2->Fill(sZZ2[i]-shisZZ2);
       // hsEta5->Fill(sEta5[i]-shisEta5);
    }
  }//end for-loop through array
  fout.close();
  //foutS.close();
  f->Write();
  f->Close();
  cout<<"total events "<<totalEvents<<endl;
}//end of file
