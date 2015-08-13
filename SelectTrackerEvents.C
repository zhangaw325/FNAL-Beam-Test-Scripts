 //this v0 is only used to output histograms with number of strips > 1
#include <TString.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
void SelectTrackerEvents()
{
    fstream fin("Hit_Position_Info.txt",ios::in);

    bool verbose = 1;
    
    //number of hits
    vector <int> NHits_g2xcl, NHits_g2ycl, NHits_g3xcl, NHits_g3ycl, NHits_g1xcl, NHits_g1ycl;
    vector <int> NHits_sCMSNS2LC1, NHits_sCMSNS2LC2, NHits_sCMSNS2LC3;
    
    //positions on detectors
    vector <double> Pos_g2xcl, Pos_g2ycl, Pos_g3xcl, Pos_g3ycl, Pos_g1xcl, Pos_g1ycl;
    vector <double> Pos_sCMSNS2LC1, Pos_sCMSNS2LC2, Pos_sCMSNS2LC3;

    //charges in detectors
    vector <double> Chrg_g2xcl, Chrg_g2ycl, Chrg_g3xcl, Chrg_g3ycl, Chrg_g1xcl, Chrg_g1ycl;
    vector <double> Chrg_sCMSNS2LC1, Chrg_sCMSNS2LC2, Chrg_sCMSNS2LC3;
   
    //strips in detectors
    vector <double> Strp_g2xcl, Strp_g2ycl, Strp_g3xcl, Strp_g3ycl, Strp_g1xcl, Strp_g1ycl;
    vector <double> Strp_sCMSNS2LC1, Strp_sCMSNS2LC2, Strp_sCMSNS2LC3;

    //initialize all the variables
    NHits_g2xcl.clear();
    NHits_g2ycl.clear();
    NHits_g3xcl.clear();
    NHits_g3ycl.clear();
    NHits_g1xcl.clear();
    NHits_g1ycl.clear();
    NHits_sCMSNS2LC1.clear();
    NHits_sCMSNS2LC2.clear();
    NHits_sCMSNS2LC3.clear();
    Pos_g2xcl.clear();
    Pos_g2ycl.clear();
    Pos_g3xcl.clear();
    Pos_g3ycl.clear();
    Pos_g1xcl.clear();
    Pos_g1ycl.clear();
    Pos_sCMSNS2LC1.clear();
    Pos_sCMSNS2LC2.clear();
    Pos_sCMSNS2LC3.clear();
    Chrg_g2xcl.clear();
    Chrg_g2ycl.clear();
    Chrg_g3xcl.clear();
    Chrg_g3ycl.clear();
    Chrg_g1xcl.clear();
    Chrg_g1ycl.clear();
    Chrg_sCMSNS2LC1.clear();
    Chrg_sCMSNS2LC2.clear();
    Chrg_sCMSNS2LC3.clear();
    Strp_g2xcl.clear();
    Strp_g2ycl.clear();
    Strp_g3xcl.clear();
    Strp_g3ycl.clear();
    Strp_g1xcl.clear();
    Strp_g1ycl.clear();
    Strp_sCMSNS2LC1.clear();
    Strp_sCMSNS2LC2.clear();
    Strp_sCMSNS2LC3.clear();
    //read the file, write values to array
    
    int evtNb=0;
    int count=0;
    TString firstString;
    int nbHits;
    double charge,position,strip;
    int aSingleStrip; double aSingleCharge;
    while(fin.good()) 
    {
	fin>>firstString;
	if(firstString.EqualTo("EventNb"))
	{
	    fin>>count;
	    evtNb++;
	    if (verbose)
		cout<<"evnt nb = "<<evtNb<< "\t firstString = "<< firstString << "\t count = "<< count <<endl;	    
	    if(evtNb%5000==0) 
		cout<<"event number "<<evtNb<<endl;
	    continue;
	}
	//if (evtNb++ > 1) continue;	// Just added this line to read only one event
	fin>>nbHits>>charge>>position>>strip;
	if (verbose)
	    cout<<"nbHits = "<<nbHits << "\t charge = "<< charge << "\t position = "<< position << "\t strip = "<<strip<<endl;
	for(int i=0;i<nbHits;i++)
	{
	    fin>>aSingleStrip>>aSingleCharge;
	    if(firstString.EqualTo("sCMSNS2LC1"))
	      {
		NHits_sCMSNS2LC1.push_back(nbHits);
		Pos_sCMSNS2LC1.push_back(charge);
		Chrg_sCMSNS2LC1.push_back(position);
		Strp_sCMSNS2LC1.push_back(strip);
	      }
	    if(firstString.EqualTo("sCMSNS2LC2"))
              {
                NHits_sCMSNS2LC2.push_back(nbHits);
                Pos_sCMSNS2LC2.push_back(charge);
                Chrg_sCMSNS2LC2.push_back(position);
                Strp_sCMSNS2LC2.push_back(strip);
              }
	    if(firstString.EqualTo("sCMSNS2LC3"))
              {
                NHits_sCMSNS2LC3.push_back(nbHits);
                Pos_sCMSNS2LC3.push_back(charge);
                Chrg_sCMSNS2LC3.push_back(position);
                Strp_sCMSNS2LC3.push_back(strip);
              }
	    if(firstString.EqualTo("g1xcl"))
	      {
		NHits_g1xcl.push_back(nbHits);
		Pos_g1xcl.push_back(charge);
		Chrg_g1xcl.push_back(position);
		Strp_g1xcl.push_back(strip);
	      }
	    if(firstString.EqualTo("g1ycl"))
	      {
		NHits_g1ycl.push_back(nbHits);
		Pos_g1ycl.push_back(charge);
		Chrg_g1ycl.push_back(position);
		Strp_g1ycl.push_back(strip);
	      }
	    if(firstString.EqualTo("g2xcl"))
              {
                NHits_g2xcl.push_back(nbHits);
                Pos_g2xcl.push_back(charge);
                Chrg_g2xcl.push_back(position);
                Strp_g2xcl.push_back(strip);
              }
            if(firstString.EqualTo("g2ycl"))
              {
                NHits_g2ycl.push_back(nbHits);
                Pos_g2ycl.push_back(charge);
                Chrg_g2ycl.push_back(position);
                Strp_g2ycl.push_back(strip);
              }
	    if(firstString.EqualTo("g3xcl"))
              {
                NHits_g3xcl.push_back(nbHits);
                Pos_g3xcl.push_back(charge);
                Chrg_g3xcl.push_back(position);
                Strp_g3xcl.push_back(strip);
              }
            if(firstString.EqualTo("g3ycl"))
              {
                NHits_g3ycl.push_back(nbHits);
                Pos_g3ycl.push_back(charge);
                Chrg_g3ycl.push_back(position);
                Strp_g3ycl.push_back(strip);
              }

	    if (verbose)
	    {
		cout<< aSingleStrip << "\t" << aSingleCharge << "\t";
		//cout<<"aSingleStrip = " << aSingleStrip << "\taSingleCharge = "<< aSingleCharge ;
	    }
	}
	cout<<endl;
    }

    
    TString outputfile = Form("Position.txt");
    TString rootfile = Form("CoarseAligned.root");
    fstream fout(outputfile.Data(),ios::out);
    TFile* f = new TFile(rootfile.Data(),"recreate");

    TH1F* h_Pos_g2xcl=new TH1F("h_Pos_g2xcl","",500,-50,50);h_Pos_g2xcl->SetXTitle("Cluster position [mm]");h_Pos_g2xcl->SetYTitle("Frequency");h_Pos_g2xcl->SetTitleSize(0.04,"XY");h_Pos_g2xcl->SetLabelSize(0.04,"XY");									
    TH1F* h_Pos_g2ycl=new TH1F("h_Pos_g2ycl","",500,-50,50);h_Pos_g2ycl->SetXTitle("Cluster position [mm]");h_Pos_g2ycl->SetYTitle("Frequency");h_Pos_g2ycl->SetTitleSize(0.04,"XY");h_Pos_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g3xcl=new TH1F("h_Pos_g3xcl","",500,-50,50);h_Pos_g3xcl->SetXTitle("Cluster position [mm]");h_Pos_g3xcl->SetYTitle("Frequency");h_Pos_g3xcl->SetTitleSize(0.04,"XY");h_Pos_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g3ycl=new TH1F("h_Pos_g3ycl","",500,-50,50);h_Pos_g3ycl->SetXTitle("Cluster position [mm]");h_Pos_g3ycl->SetYTitle("Frequency");h_Pos_g3ycl->SetTitleSize(0.04,"XY");h_Pos_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g1xcl=new TH1F("h_Pos_g1xcl","",500,-50,50);h_Pos_g1xcl->SetXTitle("Cluster position [mm]");h_Pos_g1xcl->SetYTitle("Frequency");h_Pos_g1xcl->SetTitleSize(0.04,"XY");h_Pos_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g1ycl=new TH1F("h_Pos_g1ycl","",500,-50,50);h_Pos_g1ycl->SetXTitle("Cluster position [mm]");h_Pos_g1ycl->SetYTitle("Frequency");h_Pos_g1ycl->SetTitleSize(0.04,"XY");h_Pos_g1ycl->SetLabelSize(0.04,"XY");
    //    cout << " ####################" <<endl;

	int totalEvents = 0;
	for(int i=0; i<nbHits; i++){
	//set number of hits cut conditions                                                                                                     
	Bool_t cutNHits_g2 = false;
	if(NHits_g2xcl.at(i)>0 && NHits_g2ycl.at(i)>0)
	  {	
	    cutNHits_g2 = true;
	  }
	Bool_t cutNHits_g3 = false;
        if(NHits_g3xcl.at(i)>0 && NHits_g3ycl.at(i)>0)
          {
            cutNHits_g3 = true;
          }
	Bool_t cutNHits_g1 = false;
        if(NHits_g1xcl.at(i)>0 && NHits_g1ycl.at(i)>0)
          {
            cutNHits_g1 = true;
          }
	Bool_t cutNHits_LC1 = false;
	if(NHits_sCMSNS2LC1.at(i) > 0) cutNHits_LC1 = true;

	Bool_t cutNHits_LC2 = false;
        if(NHits_sCMSNS2LC2.at(i) > 0) cutNHits_LC2 = true;

	Bool_t cutNHits_LC3 = false;
        if(NHits_sCMSNS2LC3.at(i) > 0) cutNHits_LC3 = true;

	//set position cut consitions
	Bool_t cutPos_g2X = false;
        if(Pos_g2xcl.at(i)>=7.5 && Pos_g2xcl.at(i)<=7.9)
          {
            cutPos_g2X = true;
          }
	Bool_t cutPos_g2Y = false;
        if(Pos_g2ycl.at(i)>=-10 && Pos_g2ycl.at(i)<=-5)
          {
            cutPos_g2Y = true;
          }
	Bool_t cutPos_g3X = false;
	if(Pos_g3xcl.at(i)>=54 && Pos_g3xcl.at(i)<=56)
          {
            cutPos_g3X = true;
          }
	Bool_t cutPos_g1X = false;
	if(Pos_g1xcl.at(i)>=-44 && Pos_g1xcl.at(i)<=-42)
          {
            cutPos_g1X = true;
          }
	Bool_t cutPos_g1Y = false;
        if(Pos_g1ycl.at(i)>=-4 && Pos_g1ycl.at(i)<=8)
          {
            cutPos_g1Y = true;
          }
	//	cout << "######################"<<endl;
	
	//then combine the cut conditions & fill histograms
	Bool_t trigger=false;
	if(cutNHits_g2==true && cutNHits_g3==true && cutNHits_g1==true)
	  {
	    trigger = true;
	  }
	if(trigger){
	  totalEvents++;
	  fout<<Pos_g2xcl.at(i)<<"\t"<<Pos_g2ycl.at(i)<<"\t"<<Pos_g3xcl.at(i)<<"\t"<<Pos_g3ycl.at(i)<<"\t"<<Pos_g1xcl.at(i)<<"\t"<<Pos_g1ycl.at(i)<<endl;
	  h_Pos_g2xcl->Fill(Pos_g2xcl.at(i));
	  h_Pos_g2ycl->Fill(Pos_g2ycl.at(i));
	  h_Pos_g3xcl->Fill(Pos_g3xcl.at(i));
	  h_Pos_g3ycl->Fill(Pos_g3ycl.at(i));
	  h_Pos_g1xcl->Fill(Pos_g1xcl.at(i));
	  h_Pos_g1ycl->Fill(Pos_g1ycl.at(i));
	}
	}
       	fout.close();
	f->Write();
	f->Close();
}
   															       																				  
																	       							      																	

						 





