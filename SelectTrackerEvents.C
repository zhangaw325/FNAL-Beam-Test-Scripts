<<<<<<< HEAD
 //this v0 is only used to output histograms with number of strips > 1
=======
 //this v-1 is only used to output histograms with number of strips > 1
>>>>>>> 5d7268b3e60e2b10a5792ea5ed123ef88fef4f96
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

<<<<<<< HEAD
    bool verbose = 0;
=======
    bool verbose = 1;
>>>>>>> 5d7268b3e60e2b10a5792ea5ed123ef88fef4f96
    
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
    vector <double> Strip_g2xcl, Strip_g2ycl, Strip_g3xcl, Strip_g3ycl, Strip_g1xcl, Strip_g1ycl;
    vector <double> Strip_sCMSNS2LC1, Strip_sCMSNS2LC2, Strip_sCMSNS2LC3;

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
    Strip_g2xcl.clear();
    Strip_g2ycl.clear();
    Strip_g3xcl.clear();
    Strip_g3ycl.clear();
    Strip_g1xcl.clear();
    Strip_g1ycl.clear();
    Strip_sCMSNS2LC1.clear();
    Strip_sCMSNS2LC2.clear();
    Strip_sCMSNS2LC3.clear();
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
	    //cout<<"det name = "<<firstString<<"\tnbHits = "<<nbHits << "\t charge = "<< charge << "\t position = "<< position << "\t strip = "<<strip<<endl;
	for(int i=0;i<nbHits;i++)
	{
	    fin>>aSingleStrip>>aSingleCharge;
	}
	    if(firstString.EqualTo("sCMSNS2LC1"))
	      {
		NHits_sCMSNS2LC1.push_back(nbHits);
		Pos_sCMSNS2LC1.push_back(position);
		Chrg_sCMSNS2LC1.push_back(charge);
		Strip_sCMSNS2LC1.push_back(strip);
	      }
	    if(firstString.EqualTo("sCMSNS2LC2"))
              {
                NHits_sCMSNS2LC2.push_back(nbHits);
                Pos_sCMSNS2LC2.push_back(position);
                Chrg_sCMSNS2LC2.push_back(charge);
                Strip_sCMSNS2LC2.push_back(strip);
              }
	    if(firstString.EqualTo("sCMSNS2LC3"))
              {
                NHits_sCMSNS2LC3.push_back(nbHits);
                Pos_sCMSNS2LC3.push_back(position);
                Chrg_sCMSNS2LC3.push_back(charge);
                Strip_sCMSNS2LC3.push_back(strip);
              }
	    if(firstString.EqualTo("g1xcl"))
	      {
		NHits_g1xcl.push_back(nbHits);
		Pos_g1xcl.push_back(position);
		Chrg_g1xcl.push_back(charge);
		Strip_g1xcl.push_back(strip);
	      }
	    if(firstString.EqualTo("g1ycl"))
	      {
		NHits_g1ycl.push_back(nbHits);
		Pos_g1ycl.push_back(position);
		Chrg_g1ycl.push_back(charge);
		Strip_g1ycl.push_back(strip);
	      }
	    if(firstString.EqualTo("g2xcl"))
              {
                NHits_g2xcl.push_back(nbHits);
                Pos_g2xcl.push_back(position);
                Chrg_g2xcl.push_back(charge);
                Strip_g2xcl.push_back(strip);
              }
            if(firstString.EqualTo("g2ycl"))
              {
                NHits_g2ycl.push_back(nbHits);
                Pos_g2ycl.push_back(position);
                Chrg_g2ycl.push_back(charge);
                Strip_g2ycl.push_back(strip);
              }
	    if(firstString.EqualTo("g3xcl"))
              {
                NHits_g3xcl.push_back(nbHits);
                Pos_g3xcl.push_back(position);
                Chrg_g3xcl.push_back(charge);
                Strip_g3xcl.push_back(strip);
              }
            if(firstString.EqualTo("g3ycl"))
              {
                NHits_g3ycl.push_back(nbHits);
                Pos_g3ycl.push_back(position);
                Chrg_g3ycl.push_back(charge);
                Strip_g3ycl.push_back(strip);
              }

	    if (verbose)
	    {
		cout<< aSingleStrip << "\t" << aSingleCharge << "\t";
		//cout<<"aSingleStrip = " << aSingleStrip << "\taSingleCharge = "<< aSingleCharge ;
	    }
	//}
	    if (verbose)
	cout<<endl;
    }

    
    TString outputfile = Form("Position.txt");
    TString rootfile = Form("CoarseAligned.root");
    fstream fout(outputfile.Data(),ios::out);
    TFile* f = new TFile(rootfile.Data(),"recreate");

    TH1F* h_Pos_g2xcl=new TH1F("h_Pos_g2xcl","",100, -10, 110);h_Pos_g2xcl->SetXTitle("Cluster position [mm]");h_Pos_g2xcl->SetYTitle("Frequency");h_Pos_g2xcl->SetTitleSize(0.04,"XY");h_Pos_g2xcl->SetLabelSize(0.04,"XY");									
    TH1F* h_Pos_g2ycl=new TH1F("h_Pos_g2ycl","",100, -10, 110);h_Pos_g2ycl->SetXTitle("Cluster position [mm]");h_Pos_g2ycl->SetYTitle("Frequency");h_Pos_g2ycl->SetTitleSize(0.04,"XY");h_Pos_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g3xcl=new TH1F("h_Pos_g3xcl","",100, -10, 110);h_Pos_g3xcl->SetXTitle("Cluster position [mm]");h_Pos_g3xcl->SetYTitle("Frequency");h_Pos_g3xcl->SetTitleSize(0.04,"XY");h_Pos_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g3ycl=new TH1F("h_Pos_g3ycl","",100, -10, 110);h_Pos_g3ycl->SetXTitle("Cluster position [mm]");h_Pos_g3ycl->SetYTitle("Frequency");h_Pos_g3ycl->SetTitleSize(0.04,"XY");h_Pos_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g1xcl=new TH1F("h_Pos_g1xcl","",100, -10, 110);h_Pos_g1xcl->SetXTitle("Cluster position [mm]");h_Pos_g1xcl->SetYTitle("Frequency");h_Pos_g1xcl->SetTitleSize(0.04,"XY");h_Pos_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g1ycl=new TH1F("h_Pos_g1ycl","",100, -10, 110);h_Pos_g1ycl->SetXTitle("Cluster position [mm]");h_Pos_g1ycl->SetYTitle("Frequency");h_Pos_g1ycl->SetTitleSize(0.04,"XY");h_Pos_g1ycl->SetLabelSize(0.04,"XY");
<<<<<<< HEAD
=======
    TH1F* h_Pos_sCMSNS2LC1=new TH1F("h_Pos_sCMSNS2LC1","",100, 0, 100);h_Pos_sCMSNS2LC1->SetXTitle("Cluster position [mm]");h_Pos_sCMSNS2LC1->SetYTitle("Frequency");h_Pos_sCMSNS2LC1->SetTitleSize(0.04,"XY");h_Pos_sCMSNS2LC1->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_sCMSNS2LC2=new TH1F("h_Pos_sCMSNS2LC2","",100, 0, 100);h_Pos_sCMSNS2LC2->SetXTitle("Cluster position [mm]");h_Pos_sCMSNS2LC2->SetYTitle("Frequency");h_Pos_sCMSNS2LC2->SetTitleSize(0.04,"XY");h_Pos_sCMSNS2LC2->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_sCMSNS2LC3=new TH1F("h_Pos_sCMSNS2LC3","",100, 0, 100);h_Pos_sCMSNS2LC3->SetXTitle("Cluster position [mm]");h_Pos_sCMSNS2LC3->SetYTitle("Frequency");h_Pos_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_Pos_sCMSNS2LC3->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g2xcl=new TH1F("h_Strip_g2xcl","",100, 0, 300);h_Strip_g2xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g2xcl->SetYTitle("Frequency");h_Strip_g2xcl->SetTitleSize(0.04,"XY");h_Strip_g2xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g2ycl=new TH1F("h_Strip_g2ycl","",100, 0,300);h_Strip_g2ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g2ycl->SetYTitle("Frequency");h_Strip_g2ycl->SetTitleSize(0.04,"XY");h_Strip_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g3xcl=new TH1F("h_Strip_g3xcl","",100, 0, 300);h_Strip_g3xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g3xcl->SetYTitle("Frequency");h_Strip_g3xcl->SetTitleSize(0.04,"XY");h_Strip_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g3ycl=new TH1F("h_Strip_g3ycl","",100, 0, 300);h_Strip_g3ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g3ycl->SetYTitle("Frequency");h_Strip_g3ycl->SetTitleSize(0.04,"XY");h_Strip_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g1xcl=new TH1F("h_Strip_g1xcl","",100, 0, 300);h_Strip_g1xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g1xcl->SetYTitle("Frequency");h_Strip_g1xcl->SetTitleSize(0.04,"XY");h_Strip_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g1ycl=new TH1F("h_Strip_g1ycl","",100, 0, 300);h_Strip_g1ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g1ycl->SetYTitle("Frequency");h_Strip_g1ycl->SetTitleSize(0.04,"XY");h_Strip_g1ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g1xcl=new TH1F("h_NHits_g1xcl","",500, -10, 10);h_NHits_g1xcl->SetXTitle("Number of Hits");h_NHits_g1xcl->SetYTitle("Frequency");h_NHits_g1xcl->SetTitleSize(0.04,"XY");h_NHits_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g1ycl=new TH1F("h_NHits_g1ycl","",500, -10, 10);h_NHits_g1ycl->SetXTitle("Number of Hits");h_NHits_g1ycl->SetYTitle("Frequency");h_NHits_g1ycl->SetTitleSize(0.04,"XY");h_NHits_g1ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g2xcl=new TH1F("h_NHits_g2xcl","",500, -10, 10);h_NHits_g2xcl->SetXTitle("Number of Hits");h_NHits_g2xcl->SetYTitle("Frequency");h_NHits_g2xcl->SetTitleSize(0.04,"XY");h_NHits_g2xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g2ycl=new TH1F("h_NHits_g2ycl","",500, -10, 10);h_NHits_g2ycl->SetXTitle("Number of Hits");h_NHits_g2ycl->SetYTitle("Frequency");h_NHits_g2ycl->SetTitleSize(0.04,"XY");h_NHits_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g3xcl=new TH1F("h_NHits_g3xcl","",500, -10, 10);h_NHits_g3xcl->SetXTitle("Number of Hits");h_NHits_g3xcl->SetYTitle("Frequency");h_NHits_g3xcl->SetTitleSize(0.04,"XY");h_NHits_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g3ycl=new TH1F("h_NHits_g3ycl","",500, -10, 10);h_NHits_g3ycl->SetXTitle("Number of Hits");h_NHits_g3ycl->SetYTitle("Frequency");h_NHits_g3ycl->SetTitleSize(0.04,"XY");h_NHits_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_sCMSNS2LC1=new TH1F("h_NHits_sCMSNS2LC1","",500, -10, 10);h_NHits_sCMSNS2LC1->SetXTitle("Number of Hits");h_NHits_sCMSNS2LC1->SetYTitle("Frequency");h_NHits_sCMSNS2LC1->SetTitleSize(0.04,"XY");h_NHits_sCMSNS2LC1->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_sCMSNS2LC2=new TH1F("h_NHits_sCMSNS2LC2","",500, -10, 10);h_NHits_sCMSNS2LC2->SetXTitle("Number of Hits");h_NHits_sCMSNS2LC2->SetYTitle("Frequency");h_NHits_sCMSNS2LC2->SetTitleSize(0.04,"XY");h_NHits_sCMSNS2LC2->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_sCMSNS2LC3=new TH1F("h_NHits_sCMSNS2LC3","",500, -10, 10);h_NHits_sCMSNS2LC3->SetXTitle("Number of Hits");h_NHits_sCMSNS2LC3->SetYTitle("Freqency");h_NHits_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_NHits_sCMSNS2LC3->SetLabelSize(0.04,"XY");
>>>>>>> 5d7268b3e60e2b10a5792ea5ed123ef88fef4f96
    //    cout << " ####################" <<endl;

	int totalEvents = 0;
	for(int i=0; i<evtNb; i++){
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
        if(Pos_g2xcl.at(i)>=0. && Pos_g2xcl.at(i)<=120.)
          {
            cutPos_g2X = true;
          }
	Bool_t cutPos_g2Y = false;
        if(Pos_g2ycl.at(i)>=0 && Pos_g2ycl.at(i)<=120)
          {
            cutPos_g2Y = true;
          }
	Bool_t cutPos_g3X = false;
	if(Pos_g3xcl.at(i)>=0 && Pos_g3xcl.at(i)<=120)
          {
            cutPos_g3X = true;
          }
	Bool_t cutPos_g1X = false;
	if(Pos_g1xcl.at(i)>=0 && Pos_g1xcl.at(i)<=120)
          {
            cutPos_g1X = true;
          }
	Bool_t cutPos_g1Y = false;
        if(Pos_g1ycl.at(i)>=0 && Pos_g1ycl.at(i)<=120)
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
<<<<<<< HEAD
=======
	  h_Pos_sCMSNS2LC1->Fill(Pos_sCMSNS2LC1.at(i));
	  h_Pos_sCMSNS2LC2->Fill(Pos_sCMSNS2LC2.at(i));
	  h_Pos_sCMSNS2LC3->Fill(Pos_sCMSNS2LC3.at(i));
	  h_Strip_g2xcl->Fill(Strip_g2xcl.at(i));
	  h_Strip_g2ycl->Fill(Strip_g2ycl.at(i));
	  h_Strip_g3xcl->Fill(Strip_g3xcl.at(i));
	  h_Strip_g3ycl->Fill(Strip_g3ycl.at(i));
	  h_Strip_g1xcl->Fill(Strip_g1xcl.at(i));
	  h_Strip_g1ycl->Fill(Strip_g1ycl.at(i));
	  h_NHits_g2xcl->Fill(NHits_g2xcl.at(i));
	  h_NHits_g2ycl->Fill(NHits_g2ycl.at(i));
	  h_NHits_g3xcl->Fill(NHits_g3xcl.at(i));
	  h_NHits_g3ycl->Fill(NHits_g3ycl.at(i));
	  h_NHits_g1xcl->Fill(NHits_g1xcl.at(i));
	  h_NHits_g1ycl->Fill(NHits_g1ycl.at(i));
	  h_NHits_sCMSNS2LC1->Fill(NHits_sCMSNS2LC1.at(i));
	  h_NHits_sCMSNS2LC2->Fill(NHits_sCMSNS2LC2.at(i));
	  h_NHits_sCMSNS2LC3->Fill(NHits_sCMSNS2LC3.at(i));
>>>>>>> 5d7268b3e60e2b10a5792ea5ed123ef88fef4f96
	  cout<<"totalEvents = "<<totalEvents<<endl;
	}
	}
       	fout.close();
	f->Write();
	f->Close();
}
