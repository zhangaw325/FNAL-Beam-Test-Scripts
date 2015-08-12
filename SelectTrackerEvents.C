//this v0 is only used to output histograms with number of strips > 1
#include <TString.h>
#include <iostream>
#include <vector>
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
		cout<<"evnt nb = "<<evtNb<< "\tfirstString = "<< firstString << "\t count = "<< count <<endl;	    
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
}
