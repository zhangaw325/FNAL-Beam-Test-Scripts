 //this v-1 is only used to output histograms with number of strips > 1
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
    fstream fout_1("Eff.txt",ios::out);

    bool verbose = 0;
   float icut1 =0; float icut2=0; float icut3=0; float icut4=0; float icut5=0; float icut6 =0; float icut7=0; float icut8=0; float icut9=0; float icut10=0; float icut11=0;

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
    fout_1<<"RunNo\tTotal\tcut1\tcut2\tcut3\tcut4\tcut5\tcut6\tcut7\tcut8\tcut9\tcut10\tcut11"<<endl;
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
	//	for(int i=0;i<100;i++)

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
    TH1F* h_Pos_sCMSNS2LC1=new TH1F("h_Pos_sCMSNS2LC1","",100, 0, 100);h_Pos_sCMSNS2LC1->SetXTitle("Cluster position [mm]");h_Pos_sCMSNS2LC1->SetYTitle("Frequency");h_Pos_sCMSNS2LC1->SetTitleSize(0.04,"XY");h_Pos_sCMSNS2LC1->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_sCMSNS2LC2=new TH1F("h_Pos_sCMSNS2LC2","",100, 0, 100);h_Pos_sCMSNS2LC2->SetXTitle("Cluster position [mm]");h_Pos_sCMSNS2LC2->SetYTitle("Frequency");h_Pos_sCMSNS2LC2->SetTitleSize(0.04,"XY");h_Pos_sCMSNS2LC2->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_sCMSNS2LC3=new TH1F("h_Pos_sCMSNS2LC3","",100, 0, 100);h_Pos_sCMSNS2LC3->SetXTitle("Cluster position [mm]");h_Pos_sCMSNS2LC3->SetYTitle("Frequency");h_Pos_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_Pos_sCMSNS2LC3->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g2xcl=new TH1F("h_Strip_g2xcl","",100, -10, 275);h_Strip_g2xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g2xcl->SetYTitle("Frequency");h_Strip_g2xcl->SetTitleSize(0.04,"XY");h_Strip_g2xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g2ycl=new TH1F("h_Strip_g2ycl","",100, -10, 275);h_Strip_g2ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g2ycl->SetYTitle("Frequency");h_Strip_g2ycl->SetTitleSize(0.04,"XY");h_Strip_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g3xcl=new TH1F("h_Strip_g3xcl","",100, -10, 275);h_Strip_g3xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g3xcl->SetYTitle("Frequency");h_Strip_g3xcl->SetTitleSize(0.04,"XY");h_Strip_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g3ycl=new TH1F("h_Strip_g3ycl","",100, -10, 275);h_Strip_g3ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g3ycl->SetYTitle("Frequency");h_Strip_g3ycl->SetTitleSize(0.04,"XY");h_Strip_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g1xcl=new TH1F("h_Strip_g1xcl","",100, -10, 275);h_Strip_g1xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g1xcl->SetYTitle("Frequency");h_Strip_g1xcl->SetTitleSize(0.04,"XY");h_Strip_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g1ycl=new TH1F("h_Strip_g1ycl","",100, -10, 275);h_Strip_g1ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g1ycl->SetYTitle("Frequency");h_Strip_g1ycl->SetTitleSize(0.04,"XY");h_Strip_g1ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_sCMSNS2LC1=new TH1F("h_Strip_sCMSNS2LC1","",100, -10, 275);h_Strip_sCMSNS2LC1->SetXTitle("Cluster position in terms of strip");h_Strip_sCMSNS2LC1->SetYTitle("Frequency");h_Strip_sCMSNS2LC1->SetTitleSize(0.04,"XY");h_Strip_sCMSNS2LC1->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_sCMSNS2LC2=new TH1F("h_Strip_sCMSNS2LC2","",100, -10, 275);h_Strip_sCMSNS2LC2->SetXTitle("Cluster position in terms of strip");h_Strip_sCMSNS2LC2->SetYTitle("Frequency");h_Strip_sCMSNS2LC2->SetTitleSize(0.04,"XY");h_Strip_sCMSNS2LC2->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_sCMSNS2LC3=new TH1F("h_Strip_sCMSNS2LC3","",100, -10, 275);h_Strip_sCMSNS2LC3->SetXTitle("Cluster position in terms of strip");h_Strip_sCMSNS2LC3->SetYTitle("Frequency");h_Strip_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_Strip_sCMSNS2LC3->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g1xcl=new TH1F("h_NHits_g1xcl","",500, -1, 10);h_NHits_g1xcl->SetXTitle("Number of Hits");h_NHits_g1xcl->SetYTitle("Frequency");h_NHits_g1xcl->SetTitleSize(0.04,"XY");h_NHits_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g1ycl=new TH1F("h_NHits_g1ycl","",500, -1, 10);h_NHits_g1ycl->SetXTitle("Number of Hits");h_NHits_g1ycl->SetYTitle("Frequency");h_NHits_g1ycl->SetTitleSize(0.04,"XY");h_NHits_g1ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g2xcl=new TH1F("h_NHits_g2xcl","",500, -1, 10);h_NHits_g2xcl->SetXTitle("Number of Hits");h_NHits_g2xcl->SetYTitle("Frequency");h_NHits_g2xcl->SetTitleSize(0.04,"XY");h_NHits_g2xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g2ycl=new TH1F("h_NHits_g2ycl","",500, -1, 10);h_NHits_g2ycl->SetXTitle("Number of Hits");h_NHits_g2ycl->SetYTitle("Frequency");h_NHits_g2ycl->SetTitleSize(0.04,"XY");h_NHits_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g3xcl=new TH1F("h_NHits_g3xcl","",500, -1, 10);h_NHits_g3xcl->SetXTitle("Number of Hits");h_NHits_g3xcl->SetYTitle("Frequency");h_NHits_g3xcl->SetTitleSize(0.04,"XY");h_NHits_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g3ycl=new TH1F("h_NHits_g3ycl","",500, -1, 10);h_NHits_g3ycl->SetXTitle("Number of Hits");h_NHits_g3ycl->SetYTitle("Frequency");h_NHits_g3ycl->SetTitleSize(0.04,"XY");h_NHits_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_sCMSNS2LC1=new TH1F("h_NHits_sCMSNS2LC1","",500, -1, 10);h_NHits_sCMSNS2LC1->SetXTitle("Number of Hits");h_NHits_sCMSNS2LC1->SetYTitle("Frequency");h_NHits_sCMSNS2LC1->SetTitleSize(0.04,"XY");h_NHits_sCMSNS2LC1->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_sCMSNS2LC2=new TH1F("h_NHits_sCMSNS2LC2","",500, -1, 10);h_NHits_sCMSNS2LC2->SetXTitle("Number of Hits");h_NHits_sCMSNS2LC2->SetYTitle("Frequency");h_NHits_sCMSNS2LC2->SetTitleSize(0.04,"XY");h_NHits_sCMSNS2LC2->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_sCMSNS2LC3=new TH1F("h_NHits_sCMSNS2LC3","",500, -1, 10);h_NHits_sCMSNS2LC3->SetXTitle("Number of Hits");h_NHits_sCMSNS2LC3->SetYTitle("Freqency");h_NHits_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_NHits_sCMSNS2LC3->SetLabelSize(0.04,"XY");
    //    cout << " ####################" <<endl;
    //////////////////////////////////////////////////////////////////////////////

    //     PROFILE PLOTS

    //////////////////////////////////////////////////////////////////////////////

    //    cout<<"entries before : "<<Pos_g1xcl.size()<<endl;
    TH2F *BeamProfile_Tracker_1=new TH2F("BeamProfile_Tracker_1","",32,0,100,32,0,100);
    TH2F *BeamProfile_Tracker_2=new TH2F("BeamProfile_Tracker_2","",32,0,100,32,0,100);
    TH2F *BeamProfile_Tracker_3=new TH2F("BeamProfile_Tracker_3","",32,0,100,32,0,100);

    //    cout<<"entries : "<<Pos_g1xcl.size()<<endl;
    // int icut1 =0; int icut2=0; int icut3=0; int icut4=0; int icut5=0; int icut6 =0; int icut7=0; int icut8=0; int icut9=0; int icut10=0; int icut11=0;
	int totalEvents = 0;
	for(int i=0; i<evtNb; i++){
	//set number of hits cut conditions    
	  //	  cout<<"entries after: "<<Pos_g1xcl.size()<<endl;                                                                                                 
	Bool_t cutNHits_g2 = false;
	if(NHits_g2xcl.at(i)>0 && NHits_g2ycl.at(i)>0)
	  {	
	    cutNHits_g2 = true;
	    icut1++;
	  }
	Bool_t cutNHits_g3 = false;
        if(NHits_g3xcl.at(i)>0 && NHits_g3ycl.at(i)>0)
          {
            cutNHits_g3 = true;
	    icut2++;
	  }
	
	Bool_t cutNHits_g1 = false;
        if(NHits_g1xcl.at(i)>0 && NHits_g1ycl.at(i)>0)
          {
            cutNHits_g1 = true;
	    icut3++;
	  }
	
	Bool_t cutNHits_LC1 = false;
	if(NHits_sCMSNS2LC1.at(i) > 0) 
	  {
	    cutNHits_LC1 = true;
	    icut4++;
	  }
	
	Bool_t cutNHits_LC2 = false;
        if(NHits_sCMSNS2LC2.at(i) > 0) 
	  {
	    cutNHits_LC2 = true;
	    icut5++;
	  }
	
	Bool_t cutNHits_LC3 = false;
        if(NHits_sCMSNS2LC3.at(i) > 0)
	  {
	    cutNHits_LC3 = true;
	    icut6++;
	  }
	
	//set position cut consitions
	Bool_t cutPos_g2X = false;
        if(Pos_g2xcl.at(i)>=0. && Pos_g2xcl.at(i)<=120.)
          {
            cutPos_g2X = true;
	    icut7++;
	  }
	
	Bool_t cutPos_g2Y = false;
        if(Pos_g2ycl.at(i)>=0 && Pos_g2ycl.at(i)<=120)
          {
            cutPos_g2Y = true;
	    icut8++;
	  }
	
	Bool_t cutPos_g3X = false;
	if(Pos_g3xcl.at(i)>=0 && Pos_g3xcl.at(i)<=120)
          {
            cutPos_g3X = true;
	    icut9++;
	  }
	
	Bool_t cutPos_g1X = false;
	if(Pos_g1xcl.at(i)>=0 && Pos_g1xcl.at(i)<=120)
          {
            cutPos_g1X = true;
	    icut10++;
	  }
	
	Bool_t cutPos_g1Y = false;
        if(Pos_g1ycl.at(i)>=0 && Pos_g1ycl.at(i)<=120)
          {
            cutPos_g1Y = true;
	    icut11++;
	  }
	
	//	cout << "######################"<<endl;
	
	//then combine the cut conditions & fill histograms
	Bool_t trigger=false;
	if(cutNHits_g2==true && cutNHits_g3==true && cutNHits_g1==true )// && cutNHits_LC1==true && cutNHits_LC2==true && cutNHits_LC3==true) 
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
	  if(NHits_sCMSNS2LC1.at(i) > 0){
	    h_Pos_sCMSNS2LC1->Fill(Pos_sCMSNS2LC1.at(i));}
	  if(NHits_sCMSNS2LC2.at(i) > 0){
	    h_Pos_sCMSNS2LC2->Fill(Pos_sCMSNS2LC2.at(i));}
	  if(NHits_sCMSNS2LC3.at(i) > 0){
	    h_Pos_sCMSNS2LC3->Fill(Pos_sCMSNS2LC3.at(i));}
	  h_Strip_g2xcl->Fill(Strip_g2xcl.at(i));
	  h_Strip_g2ycl->Fill(Strip_g2ycl.at(i));
	  h_Strip_g3xcl->Fill(Strip_g3xcl.at(i));
	  h_Strip_g3ycl->Fill(Strip_g3ycl.at(i));
	  h_Strip_g1xcl->Fill(Strip_g1xcl.at(i));
	  h_Strip_g1ycl->Fill(Strip_g1ycl.at(i));
	  if(NHits_sCMSNS2LC1.at(i) > 0){
	    h_Strip_sCMSNS2LC1->Fill(Strip_sCMSNS2LC1.at(i));}
	  if(NHits_sCMSNS2LC2.at(i) > 0){
	    h_Strip_sCMSNS2LC2->Fill(Strip_sCMSNS2LC2.at(i));}
	  if(NHits_sCMSNS2LC3.at(i) > 0){
	    h_Strip_sCMSNS2LC3->Fill(Strip_sCMSNS2LC3.at(i));}
	  h_NHits_g2xcl->Fill(NHits_g2xcl.at(i));
	  h_NHits_g2ycl->Fill(NHits_g2ycl.at(i));
	  h_NHits_g3xcl->Fill(NHits_g3xcl.at(i));
	  h_NHits_g3ycl->Fill(NHits_g3ycl.at(i));
	  h_NHits_g1xcl->Fill(NHits_g1xcl.at(i));
	  h_NHits_g1ycl->Fill(NHits_g1ycl.at(i));
	  h_NHits_sCMSNS2LC1->Fill(NHits_sCMSNS2LC1.at(i));
	  h_NHits_sCMSNS2LC2->Fill(NHits_sCMSNS2LC2.at(i));
	  h_NHits_sCMSNS2LC3->Fill(NHits_sCMSNS2LC3.at(i));
	 
	  //       	  cout<<"totalEvents = "<<totalEvents<<endl;
	//trigger loop
	  //	  for(unsigned int i=0;i<Pos_g1xcl.size();i++){
	    //	    cout<<"chk thi :"<<Pos_g1xcl.at(i)<<endl;

	  
	  BeamProfile_Tracker_1->Fill(Pos_g1xcl.at(i),Pos_g1ycl.at(i)); // BeamProfile_Tracker_1->Draw("colz");
	  BeamProfile_Tracker_2->Fill(Pos_g2xcl.at(i),Pos_g2ycl.at(i)); // BeamProfile_Tracker_2->Draw("colz");
	  BeamProfile_Tracker_3->Fill(Pos_g3xcl.at(i),Pos_g3ycl.at(i)); //  BeamProfile_Tracker_3->Draw("colz");
	  
	  BeamProfile_Tracker_1->Draw("COLZ");
	  BeamProfile_Tracker_2->Draw("COLZ");
	  BeamProfile_Tracker_3->Draw("COLZ");  
	  
	}// trigger loop
	}// no of events
	// BeamProfile_Tracker_1->Write();
	float Eff[11];
       
	  Eff[0] = icut1/evtNb,
	  Eff[1] = icut2/evtNb,
	  Eff[2] = icut3/evtNb,
	  Eff[3] = icut4/evtNb,
	  Eff[4] = icut5/evtNb,
	  Eff[5] = icut6/evtNb,
	  Eff[6] = icut7/evtNb,
	  Eff[7] = icut8/evtNb,
	  Eff[8] = icut9/evtNb,
	  Eff[9] = icut10/evtNb,
	  Eff[10] = icut11/evtNb,
	    /* for(unsigned int i=0; i<11; i++){
	      cout<<"efficiency :"<< Eff[i]<<endl;
	      }*/
	  cout<<"efficiency 1 :"<<Eff[0]<<endl;
	  cout<<"efficiency 2 :"<<Eff[1]<<endl;
	  cout<<"efficiency 3 :"<<Eff[2]<<endl;
	  cout<<"efficiency 4 :"<<Eff[3]<<endl;
	  cout<<"efficiency 5 :"<<Eff[4]<<endl;
	  cout<<"efficiency 6 :"<<Eff[5]<<endl;
	  cout<<"efficiency 7 :"<<Eff[6]<<endl;
	  cout<<"efficiency 8 :"<<Eff[7]<<endl;
	  cout<<"efficiency 9 :"<<Eff[8]<<endl;
	  cout<<"efficiency 10 :"<<Eff[9]<<endl;
	  cout<<"efficiency 11 :"<<Eff[10]<<endl;
	    

	  fout_1<<"\t"<<"\t"<<Eff[0]<<"\t"<<Eff[1]<<"\t"<<Eff[2]<<"\t"<<Eff[3]<<"\t"<<Eff[4]<<"\t"<<Eff[5]<<"\t"<<Eff[6]<<"\t"<<Eff[7]<<"\t"<<Eff[8]<<"\t"<<Eff[9]<<"\t"<<Eff[10]<<endl;
	cout<< "cut1 : "<< icut1<<endl;
	cout<< "cut2 : "<< icut2<<endl;
	cout<< "cut3 : "<< icut3<<endl;
	cout<< "cut4 : "<< icut4<<endl;
	cout<< "cut5 : "<< icut5<<endl;
	cout<< "cut6 : "<< icut6<<endl;
	cout<< "cut7 : "<< icut7<<endl;
	cout<< "cut8 : "<< icut8<<endl;
	cout<< "cut9 : "<< icut9<<endl;
	cout<< "cut10 : "<< icut10<<endl;
	cout<< "cut11 : "<< icut11<<endl;

	fout.close();
	fout_1.close();
	f->Write();
	f->Close();
}//SelectTrackerEvents
