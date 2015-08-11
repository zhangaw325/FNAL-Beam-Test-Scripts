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

    //initialize all the variables
    NHits_g2xcl.clear();

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
	    if (verbose)
	    {
		cout<< aSingleStrip << "\t" << aSingleCharge << "\t";
		//cout<<"aSingleStrip = " << aSingleStrip << "\taSingleCharge = "<< aSingleCharge ;
	    }
	}
	cout<<endl;
    }
}
