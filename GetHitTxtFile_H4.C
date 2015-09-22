/*
 * BUG: Not reading the first event
 *
 * Need to implement EfficiencyType variable
 *
 */

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "ClassReadTree.cc"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include <vector>
#include <iostream>
using namespace std;
void GetHitTxtFile_H4(const char* inputfile, string RunName , int EfficiencyType , int TrkOnly )//main programme
{

    /*
     * EfficiencyType : If want to calculate efficiency of each GE11's independently
     *			Using trigger from hardware only put it equal to 0
     *
     *			If want to trigger it using two of the reference tracker 
     *			put it = 1
     *
     *			if want to trigger it only when it passes from all three reference
     *			tracker then put it = 2
     */

    TChain* t = new TChain("rd51tbgeo");
    t->Add(inputfile);
    //t->Add("CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root");
    
    ClassReadTree CRC(t);
    
    Long64_t nentries = t->GetEntries();
    cout<< "Total "<<nentries<<endl;

    string outputtxtfile = "HitTxtFiles/"+RunName+".txt";
    std::ofstream file_out(outputtxtfile);
    std::ofstream file_outEff;
    string outputEfficiencyFile;
    if (EfficiencyType == 0 ) outputEfficiencyFile = "Independent";
    if (EfficiencyType == 1 ) outputEfficiencyFile = "If_Hit_2_Trk";
    if (EfficiencyType == 2 ) outputEfficiencyFile = "Hit_all_3_Trk";

    outputEfficiencyFile = "GE11s_Efficiency_"+outputEfficiencyFile+".txt";

    file_outEff.open(outputEfficiencyFile, std::ios_base::app);
    if (!file_out)
    {
	std::cout << "error: Could not open the file Hit_Position_Info.txt" << std::endl;
    }
    if (!file_outEff)
    {
	std::cout << "error: Could not open the file Hit_Position_Info.txt" << std::endl;
    }
       

    //================================   initialize some of variables   ======================================================
    Long64_t nbytes = 0, nb = 0;
    bool verbose = 0;
//    bool TrkOnly = 1;

    int count_ngeoch_occ = 0;
    int EventNb = 0;
    int g1x_Hit_count = 0 ;
    int g1y_Hit_count = 0 ;
    int g2x_Hit_count = 0 ;
    int g2y_Hit_count = 0 ;
    int g3x_Hit_count = 0 ;
    int g3y_Hit_count = 0 ;
    int g1_Hit_count = 0 ;   
    int g2_Hit_count = 0 ;
    int g3_Hit_count = 0 ;   
    int LC1_Hit_count = 0 ;
    int LC2_Hit_count = 0 ;
    int LC3_Hit_count = 0 ;
    int Trk_count = 0;

    //================================   Event Loop Starts   ======================================================
    for( int jentry = 0 ; jentry < t->GetEntries() ; jentry++)//	Event Loop Starts
    //for( int jentry = 0 ; jentry < 8 ; jentry++)//	Event Loop Starts
    {
	Long64_t ientry = t->LoadTree(jentry);
	if (ientry < 0) break;
	t->GetEntry(jentry);
	//============================= count number of actual clusters for each Tracker and Large GEMs   =======================================
	/*    
	 *    This loops added because presently Aiwu's framework can only accepts those events for which
	 *    there are only cluster in each tracker and GEM for each event
	 */
	//=========   Check Number of Clusters For g1xcl  ============================
	int NumCluster_g1x = 0;
	//cout<<"CRC. kMax = "<<CRC.kMaxg1xcl<<endl;
	for(int nbcl=0;nbcl<CRC.kMaxg1xcl;nbcl++)
	{
	    if (verbose)
		cout<<CRC.g1xcl_geoposch[nbcl]<<endl;
	    if (CRC.g1xcl_geoposch[nbcl]==0)
		break;
	    NumCluster_g1x += 1;
	} 
	if (NumCluster_g1x != 0 ) 
	{
	    g1x_Hit_count++;
	}
	
	if (verbose)
	    cout<<"Actual number of clusters = "<<NumCluster_g1x<<endl;

	//=========   END:: Check Number of Clusters For g1xcl    ============================
	//=========   Check Number of Clusters For g1ycl  ============================
	int NumCluster_g1y = 0;
	for(int nbcl=0;nbcl<CRC.kMaxg1ycl;nbcl++)
	{
	    if (verbose)
		cout<<CRC.g1ycl_geoposch[nbcl]<<endl;
	    if (CRC.g1ycl_geoposch[nbcl]==0)
		break;
	    NumCluster_g1y += 1;
	}
	if (NumCluster_g1y !=0 )
	{
	    g1y_Hit_count++;
	}
	
	if (NumCluster_g1x !=0 && NumCluster_g1y !=0)
	{       
	    g1_Hit_count++;
	}
	
	if (verbose)
	    cout<<"Actual number of clusters = "<<NumCluster_g1y<<endl;
    
        //=========   END:: Check Number of Clusters For g1ycl    ============================

	//=========   Check Number of Clusters For g2xcl  ============================
      //
      //
      int NumCluster_g2x = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg2xcl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g2xcl_geoposch[nbcl]<<endl;
          if (CRC.g2xcl_geoposch[nbcl]==0)
              break;
          NumCluster_g2x += 1;
}
if (NumCluster_g2x !=0 )
{
           g2x_Hit_count++;
}
 
      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g2x<<endl;
        // if (NumCluster_g2x != 1) 
        //  continue;

      //
      //
      //=========   END:: Check Number of Clusters For g2xcl    ============================

      //=========   Check Number of Clusters For g2ycl  ============================
      //
      //
      int NumCluster_g2y = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg2ycl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g2ycl_geoposch[nbcl]<<endl;
          if (CRC.g2ycl_geoposch[nbcl]==0)
              break;
          NumCluster_g2y += 1;
}
 if (NumCluster_g2y !=0 )
{
           g2y_Hit_count++;
}
 
if (NumCluster_g2x !=0 && NumCluster_g2y !=0)
    {       g2_Hit_count++;
}

      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g2y<<endl;
        // if (NumCluster_g2y != 1) 
        //  continue;


      //=========   END:: Check Number of Clusters For g2ycl    ============================

      //=========   Check Number of Clusters For g3xcl  ============================
      //
      //
      int NumCluster_g3x = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg3xcl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g3xcl_geoposch[nbcl]<<endl;
          if (CRC.g3xcl_geoposch[nbcl]==0)
              break;
          NumCluster_g3x += 1;

}
if (NumCluster_g3x !=0 )
{
           g3x_Hit_count++;
}
 
      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g3x<<endl;
        // if (NumCluster_g3x != 1) 
        //  continue;

      //=========   END:: Check Number of Clusters For g3xcl    ============================

      //=========   Check Number of Clusters For g3ycl  ============================
      //
      //
      int NumCluster_g3y = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg3ycl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g3ycl_geoposch[nbcl]<<endl;
          if (CRC.g3ycl_geoposch[nbcl]==0)
              break;
          NumCluster_g3y += 1;
}
 if (NumCluster_g3y !=0 )
{
           g3y_Hit_count++;
}
 if (NumCluster_g3x !=0 && NumCluster_g3y !=0)
    {       g3_Hit_count++;
}

      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g3y<<endl;

  //=========   END:: Check Number of Clusters For g3ycl    ============================
      //=========   Check Number of Clusters For GE11_IV_GIF     ============================
      int NumCluster_LC1 = 0;
      for(int nbcl=0;nbcl<CRC.kMaxGE11_IV_GIF;nbcl++)
      {
          if (verbose)
              cout<<CRC.GE11_IV_GIF_geoposch[nbcl]<<endl;
          if (CRC.GE11_IV_GIF_geoposch[nbcl]==0)
              break;
          NumCluster_LC1 += 1;
      }
      if (EfficiencyType == 0)
      	{
	if (NumCluster_LC1 !=0)   LC1_Hit_count++;
	}
      if (EfficiencyType == 1)
      {
      	if (((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g2x !=0 && NumCluster_g2y !=0)) || ((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0)) || ((NumCluster_g2x !=0 && NumCluster_g2y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0)))
	{
		if (NumCluster_LC1 !=0) 
		LC1_Hit_count++;
		Trk_count++;
        }
      }
      if (EfficiencyType == 2)
      {
      	if ((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g2x !=0 && NumCluster_g2y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0))
	{
		if (NumCluster_LC1 !=0)
		LC1_Hit_count++;
		Trk_count++;
        }
      }

      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_LC1<<endl;

      //=========   END:: Check Number of Clusters For GE11_IV_GIF       ============================

      //=========   Check Number of Clusters For GE11_IV     ============================

      int NumCluster_LC2 = 0;
      for(int nbcl=0;nbcl<CRC.kMaxGE11_IV;nbcl++)
      {
          if (verbose)
              cout<<CRC.GE11_IV_geoposch[nbcl]<<endl;
          if (CRC.GE11_IV_geoposch[nbcl]==0)
              break;
          NumCluster_LC2 += 1;
      }

      if (EfficiencyType == 0)
      	{
	if (NumCluster_LC2 !=0)   LC2_Hit_count++;
	}
      if (EfficiencyType == 1)
      {
      	if (((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g2x !=0 && NumCluster_g2y !=0)) || ((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0)) || ((NumCluster_g2x !=0 && NumCluster_g2y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0)))
	{
		if (NumCluster_LC2 !=0) 
		LC2_Hit_count++;
		//Trk_count++;
	}
      }
      if (EfficiencyType == 2)
      {
      	if ((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g2x !=0 && NumCluster_g2y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0))
	{
		if (NumCluster_LC2 !=0)
		LC2_Hit_count++;
		//Trk_count++;
	}
      }
      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_LC2<<endl;

      //=========   END:: Check Number of Clusters For GE11_IV       ============================

     //=========   Check Number of Clusters For sCMSNS2LC3     ============================
      int NumCluster_LC3 = 0;
      for(int nbcl=0;nbcl<CRC.kMaxsCMSNS2LC3;nbcl++)
      {
          if (verbose)
              cout<<CRC.sCMSNS2LC3_geoposch[nbcl]<<endl;
          if (CRC.sCMSNS2LC3_geoposch[nbcl]==0)
              break;
          NumCluster_LC3 += 1;
      }
      if (EfficiencyType == 0)
      	{
	if (NumCluster_LC3 !=0)   LC3_Hit_count++;
	}
      if (EfficiencyType == 1)
      {
      	if (((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g2x !=0 && NumCluster_g2y !=0)) || ((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0)) || ((NumCluster_g2x !=0 && NumCluster_g2y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0)))
	{	
		if (NumCluster_LC3 !=0) 
		LC3_Hit_count++;
		//Trk_count++;
	}
      }
      if (EfficiencyType == 2)
      {
      	if ((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g2x !=0 && NumCluster_g2y !=0) && (NumCluster_g3x !=0 && NumCluster_g3y !=0))
	{	
		if (NumCluster_LC3 !=0)
		LC3_Hit_count++;
		//Trk_count++;
	}
      }
      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_LC3<<endl;

      //
      //=========   END:: Check Number of Clusters For sCMSNS2LC3       ============================   

     //cout<<"EventNb "<<jentry<<endl;
    bool Trigger = 0;

    if (TrkOnly)
{
        if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1)
        {   Trigger = 1; }      
}
    else
{
        if (NumCluster_g1x == 1 &&  NumCluster_g1y ==1 && NumCluster_g2x == 1 && NumCluster_g2y==1 && NumCluster_g3x ==1 && NumCluster_g3y == 1 && NumCluster_LC1 == 1 && NumCluster_LC2 == 1 && NumCluster_LC3 == 1)
        { Trigger = 1; }
}

    if (Trigger)
        {
          EventNb += 1;
          if (verbose)
              cout<<"EventNb "<<EventNb<<endl;
              //cout<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;
              //cout<<"EventNb "<<jentry<<endl;
//          file_out<<"EventNb "<<EventNb<<endl;
file_out<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;
      
}


  //================================   Reference Tracker 1 (CRC.g1xcl)   ======================================================
      int channelFired = 0;             //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
//cout<<"final "<<jentry<<endl;
          if (verbose)
              cout<<"g1xcl\t";
          file_out<<"g1xcl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
          {
              if (CRC.g1xcl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g1xcl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1xcl_geoposX[0]<<"\t"<<CRC.g1xcl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1xcl_geoposX[0]<<"\t"<<CRC.g1xcl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
          {
              if (CRC.g1xcl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g1xcl_ngeoch[nch];chfird++)
              {
                  if((CRC.g1xcl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
int g1x = jentry ;
          file_out<<std::endl;
  }
   //================================   END::   Reference Tracker 1 (CRC.g1xcl)   ======================================================

   //================================   Reference Tracker 1 (CRC.g1ycl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g1ycl\t";
          file_out<<"g1ycl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg1ycl;nch++)
          {
              if (CRC.g1ycl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g1ycl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1ycl_geoposY[0]<<"\t"<<CRC.g1ycl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1ycl_geoposY[0]<<"\t"<<CRC.g1ycl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
          {
              if (CRC.g1ycl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g1ycl_ngeoch[nch];chfird++)
              {
                  if((CRC.g1ycl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
 }


   //================================   END::   Reference Tracker 1 (CRC.g1ycl)   ======================================================    


   //================================   Reference Tracker 1 (CRC.g2xcl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
         if (verbose)
              cout<<"g2xcl\t";
          file_out<<"g2xcl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg2xcl;nch++)
          {
              if (CRC.g2xcl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g2xcl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2xcl_geoposX[0]<<"\t"<<CRC.g2xcl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2xcl_geoposX[0]<<"\t"<<CRC.g2xcl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;

          for(Int_t nch=0;nch<CRC.kMaxg2xcl;nch++)
          {
              if (CRC.g2xcl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g2xcl_ngeoch[nch];chfird++)
              {
                  if((CRC.g2xcl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
   }
   //================================   END::   Reference Tracker 1 (CRC.g2xcl)   ======================================================       
   
   //================================   Reference Tracker 1 (CRC.g2ycl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g2ycl\t";
          file_out<<"g2ycl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg2ycl;nch++)
          {
              if (CRC.g2ycl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g2ycl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2ycl_geoposY[0]<<"\t"<<CRC.g2ycl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2ycl_geoposY[0]<<"\t"<<CRC.g2ycl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg2ycl;nch++)
          {
              if (CRC.g2ycl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g2ycl_ngeoch[nch];chfird++)
              {
                  if((CRC.g2ycl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
 }
   //================================   END::   Reference Tracker 1 (CRC.g2ycl)   ======================================================    
   //================================   Reference Tracker 1 (CRC.g3xcl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g3xcl\t";
          file_out<<"g3xcl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3xcl;nch++)
          {
              if (CRC.g3xcl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g3xcl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3xcl_geoposX[0]<<"\t"<<CRC.g3xcl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3xcl_geoposX[0]<<"\t"<<CRC.g3xcl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3xcl;nch++)
          {
              if (CRC.g3xcl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g3xcl_ngeoch[nch];chfird++)
              {
                  if((CRC.g3xcl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
 }
   //================================   END::   Reference Tracker 1 (CRC.g3xcl)   ======================================================      
   
   //================================   Reference Tracker 1 (CRC.g3ycl)   ======================================================

      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g3ycl\t";
          file_out<<"g3ycl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3ycl;nch++)
          {
              if (CRC.g3ycl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g3ycl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3ycl_geoposY[0]<<"\t"<<CRC.g3ycl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3ycl_geoposY[0]<<"\t"<<CRC.g3ycl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3ycl;nch++)
          {
              if (CRC.g3ycl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g3ycl_ngeoch[nch];chfird++)
              {
                  if((CRC.g3ycl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
    }
   //================================   END::   Reference Tracker 1 (CRC.g3ycl)   ======================================================    
      
   //================================   GE1/1  1 (GE11_IV_GIF)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"GE11_IV_GIF\t";
          file_out<<"GE11_IV_GIF\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxGE11_IV_GIF;nch++)
          {
                  //cout<<"GE11_IV_GIF_ngeoch[ "<<nch<<" ] = "<< GE11_IV_GIF_ngeoch[nch]<<endl;
              if (CRC.GE11_IV_GIF_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.GE11_IV_GIF_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.GE11_IV_GIF_geoposX[0]<<"\t"<<CRC.GE11_IV_GIF_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.GE11_IV_GIF_geoposX[0]<<"\t"<<CRC.GE11_IV_GIF_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxGE11_IV_GIF;nch++)
          {
              if (CRC.GE11_IV_GIF_ngeoch[nch]==0)
                  break;
      if (verbose)
      {
                  cout<<"GE11_IV_GIF_ngeoch[ "<<nch<<" ] = "<< CRC.GE11_IV_GIF_ngeoch[nch]<<endl;
                  cout<<"jentry = "<<jentry<<endl;
      }
                  //cin.ignore();
              for (int chfird=0;chfird<CRC.GE11_IV_GIF_ngeoch[nch];chfird++)
              {
                  //file_out<<"\n"<<GE11_IV_GIF_ngeoch[nch]<<"\t"<<"(GE11_IV_GIF_geoch)[ "<< count_ngeoch_occ << " ][ "<<chfird <<" ] = " << (GE11_IV_GIF_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t\n";
                  //if((GE11_IV_GIF_geoch)[count_ngeoch_occ][chfird] == 0)
                  //    break;
                  if (verbose)
                      std::cout<<(CRC.GE11_IV_GIF_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(GE11_IV_GIF_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.GE11_IV_GIF_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
      }
   //================================   END::   GE1/1  1 (GE11_IV_GIF)   ======================================================  

      
   //================================	GE1/1  1 (GE11_IV)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"GE11_IV\t";
          file_out<<"GE11_IV\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<CRC.kMaxGE11_IV;nch++)
	  {
	      if (CRC.GE11_IV_ngeoch[nch]==0)
		  break;
	      channelFired +=CRC.GE11_IV_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.GE11_IV_geoposX[0]<<"\t"<<CRC.GE11_IV_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.GE11_IV_geoposX[0]<<"\t"<<CRC.GE11_IV_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<CRC.kMaxGE11_IV;nch++)
	  {
	      if (CRC.GE11_IV_ngeoch[nch]==0)
		  break;
	      if (verbose)
	      {
	      	cout<<"GE11_IV_ngeoch[ "<<nch<<" ] = "<< CRC.GE11_IV_ngeoch[nch]<<endl;
		cout<<"jentry = "<<jentry<<endl;
	      }
	      for (int chfird=0;chfird<CRC.GE11_IV_ngeoch[nch];chfird++)
	      {
		 // if((GE11_IV_geoch)[count_ngeoch_occ][chfird] == 0)
		    //  break;
		  if (verbose)
		      std::cout<<(CRC.GE11_IV_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  //std::cout<<(GE11_IV_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(CRC.GE11_IV_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
      }
   //================================	END::	GE1/1  1 (GE11_IV)   ======================================================  
      
   //================================	GE1/1  1 (sCMSNS2LC3)   ======================================================
      channelFired = 0;		//==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"sCMSNS2LC3\t";
          file_out<<"sCMSNS2LC3\t";
	  channelFired = 0;
	  for(Int_t nch=0;nch<CRC.kMaxsCMSNS2LC3;nch++)
	  {
	      if (CRC.sCMSNS2LC3_ngeoch[nch]==0)
		  break;
	      channelFired +=CRC.sCMSNS2LC3_ngeoch[nch];
	      //cout<<"Channel Fired = "<<channelFired<<endl;
	  }
	  if (verbose)
	      std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.sCMSNS2LC3_geoposX[1]<<"\t"<<CRC.sCMSNS2LC3_geoposch[0]<<"\t";
	  file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.sCMSNS2LC3_geoposX[1]<<"\t"<<CRC.sCMSNS2LC3_geoposch[0]<<"\t";
	  count_ngeoch_occ = 0;
	  for(Int_t nch=0;nch<CRC.kMaxsCMSNS2LC3;nch++)
	  {
	      if (CRC.sCMSNS2LC3_ngeoch[nch]==0)
		  break;
	      if (verbose)
	      {
 		cout<<"sCMSNS2LC3_ngeoch[ "<<nch<<" ] = "<< CRC.sCMSNS2LC3_ngeoch[nch]<<endl;
		cout<<"jentry = "<<jentry<<endl;
	      }
	      for (int chfird=0;chfird<CRC.sCMSNS2LC3_ngeoch[nch];chfird++)
	      {
		  //if((sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird] == 0)
		     // break;
		  if (verbose)
		      std::cout<<(CRC.sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
		  file_out<<(CRC.sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
	      }
	      count_ngeoch_occ += 1;
	  }
	  if (verbose)
	      std::cout<<std::endl;
	  // std::cout<<std::endl;
	  file_out<<std::endl;
      }
   //================================	END::	GE1/1  1 (sCMSNS2LC3)   ======================================================     
      //====================== Clear few arrays: Those behaving Strange.	===============================
   /*
    * Here we are clearing few arrays because somehow it is giving strange behaviour
    *
    * Problem:	For each event the size of the following arrays or pointer to array
    *		should be different. But once we get get some array of length 5-6 
    *		then the size of the array fixed to 5-6 and then in next event event 
    *		the size of these array is 1-2 but it is fixed to 5-6 and first two
    *		entry remains from present event but then rest are copied from last 
    *		big array.
    */
      std::fill_n(CRC.g1xcl_ngeoch,sizeof CRC.g1xcl_ngeoch/sizeof(CRC.g1xcl_ngeoch[0]),0);
      std::fill_n(CRC.g1ycl_ngeoch,sizeof CRC.g1ycl_ngeoch/sizeof(CRC.g1ycl_ngeoch[0]),0);
      std::fill_n(CRC.g2xcl_ngeoch,sizeof CRC.g2xcl_ngeoch/sizeof(CRC.g2xcl_ngeoch[0]),0);
      std::fill_n(CRC.g2ycl_ngeoch,sizeof CRC.g2ycl_ngeoch/sizeof(CRC.g2ycl_ngeoch[0]),0);
      std::fill_n(CRC.g3xcl_ngeoch,sizeof CRC.g3xcl_ngeoch/sizeof(CRC.g3xcl_ngeoch[0]),0);
      std::fill_n(CRC.g3ycl_ngeoch,sizeof CRC.g3ycl_ngeoch/sizeof(CRC.g3ycl_ngeoch[0]),0);
      std::fill_n(CRC.GE11_IV_GIF_ngeoch,sizeof CRC.GE11_IV_GIF_ngeoch/sizeof(CRC.GE11_IV_GIF_ngeoch[0]),0);
      std::fill_n(CRC.GE11_IV_ngeoch,sizeof CRC.GE11_IV_ngeoch/sizeof(CRC.GE11_IV_ngeoch[0]),0);
      std::fill_n(CRC.sCMSNS2LC3_ngeoch,sizeof CRC.sCMSNS2LC3_ngeoch/sizeof(CRC.sCMSNS2LC3_ngeoch[0]),0);
      std::fill_n(CRC.g1xcl_geoposch,sizeof  CRC.g1xcl_geoposch/sizeof(CRC.g1xcl_geoposch[0]),0);
      std::fill_n(CRC.g1ycl_geoposch,sizeof  CRC.g1ycl_geoposch/sizeof(CRC.g1ycl_geoposch[0]),0);
      std::fill_n(CRC.g2xcl_geoposch,sizeof  CRC.g2xcl_geoposch/sizeof(CRC.g2xcl_geoposch[0]),0);
      std::fill_n(CRC.g2ycl_geoposch,sizeof  CRC.g2ycl_geoposch/sizeof(CRC.g2ycl_geoposch[0]),0);
      std::fill_n(CRC.g3xcl_geoposch,sizeof  CRC.g3xcl_geoposch/sizeof(CRC.g3xcl_geoposch[0]),0);
      std::fill_n(CRC.g3ycl_geoposch,sizeof  CRC.g3ycl_geoposch/sizeof(CRC.g3ycl_geoposch[0]),0);
      std::fill_n(CRC.GE11_IV_GIF_geoposch,sizeof CRC.GE11_IV_GIF_geoposch/sizeof(CRC.GE11_IV_GIF_geoposch[0]),0);
      std::fill_n(CRC.GE11_IV_geoposch,sizeof CRC.GE11_IV_geoposch/sizeof(CRC.GE11_IV_geoposch[0]),0);
      std::fill_n(CRC.sCMSNS2LC3_geoposch,sizeof CRC.sCMSNS2LC3_geoposch/sizeof(CRC.sCMSNS2LC3_geoposch[0]),0);
      std::fill_n(CRC.g1xcl_geoposX,sizeof  CRC.g1xcl_geoposX/sizeof(CRC.g1xcl_geoposX[0]),0);
      std::fill_n(CRC.g2xcl_geoposX,sizeof  CRC.g2xcl_geoposX/sizeof(CRC.g2xcl_geoposX[0]),0);
      std::fill_n(CRC.g3xcl_geoposX,sizeof  CRC.g3xcl_geoposX/sizeof(CRC.g3xcl_geoposX[0]),0);
      std::fill_n(CRC.g1ycl_geoposY,sizeof  CRC.g1ycl_geoposY/sizeof(CRC.g1ycl_geoposY[0]),0);
      std::fill_n(CRC.g2ycl_geoposY,sizeof  CRC.g2ycl_geoposY/sizeof(CRC.g2ycl_geoposY[0]),0);
      std::fill_n(CRC.g3ycl_geoposY,sizeof  CRC.g3ycl_geoposY/sizeof(CRC.g3ycl_geoposY[0]),0);
      std::fill_n(CRC.GE11_IV_GIF_geoposY,sizeof CRC.GE11_IV_GIF_geoposY/sizeof(CRC.GE11_IV_GIF_geoposY[0]),0);
      std::fill_n(CRC.GE11_IV_geoposY,sizeof CRC.GE11_IV_geoposY/sizeof(CRC.GE11_IV_geoposY[0]),0);
      std::fill_n(CRC.sCMSNS2LC3_geoposY,sizeof CRC.sCMSNS2LC3_geoposY/sizeof(CRC.sCMSNS2LC3_geoposY[0]),0);
    //
    //Trying to use some shortcut method to delete the memory but did not succeed so apply simple method
    //
    //memset(CRC.g1xcl_geoch, 0, sizeof(CRC.g1xcl_geoch[0][0]) * count_ngeoch_occ * 12);
    //memset(CRC.g1xcl_geoch, sizeof(int)*count_ngeoch_occ*12);
    //delete[] g1xcl_geoch; g1xcl_geoch = NULL;
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
    {
	if (CRC.g1xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g1xcl_ngeoch[nch];chfird++)
    {
	if((CRC.g1xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g1xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg1ycl;nch++)
    {
	if (CRC.g1ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g1ycl_ngeoch[nch];chfird++)
    {
	if((CRC.g1ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g1ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg2xcl;nch++)
    {
	if (CRC.g2xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g2xcl_ngeoch[nch];chfird++)
    {
	if((CRC.g2xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g2xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg2ycl;nch++)
    {
	if (CRC.g2ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g2ycl_ngeoch[nch];chfird++)
    {
	if((CRC.g2ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g2ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg3xcl;nch++)
    {
	if (CRC.g3xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g3xcl_ngeoch[nch];chfird++)
    {
	if((CRC.g3xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g3xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg3ycl;nch++)
    {
	if (CRC.g3ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g3ycl_ngeoch[nch];chfird++)
    {
	if((CRC.g3ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g3ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxGE11_IV_GIF;nch++)
    {
	if (CRC.GE11_IV_GIF_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.GE11_IV_GIF_ngeoch[nch];chfird++)
    {
	if((CRC.GE11_IV_GIF_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.GE11_IV_GIF_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxGE11_IV;nch++)
    {
	if (CRC.GE11_IV_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.GE11_IV_ngeoch[nch];chfird++)
    {
	if((CRC.GE11_IV_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.GE11_IV_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxGE11_IV_GIF;nch++)
    {
	if (CRC.sCMSNS2LC3_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.sCMSNS2LC3_ngeoch[nch];chfird++)
    {
	if((CRC.sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.sCMSNS2LC3_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================    
    //====================== END::  Clear few arrays: Those behaving Strange.	===============================	


	  //file_out<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;

	
    }// End Event Loop

if (EfficiencyType == 0)
{
file_outEff << RunName <<"\t"<<
           setw(5) <<  (float)LC1_Hit_count/(float)nentries<<" "<<
           setw(5) <<  (float)LC2_Hit_count/(float)nentries<<" "<<
          setw(5)  <<  (float)LC3_Hit_count/(float)nentries<<"\n";
cout << RunName <<"\t"<<
           setw(5) <<  (float)LC1_Hit_count/(float)nentries<<" "<<
           setw(5) <<  (float)LC2_Hit_count/(float)nentries<<" "<<
          setw(5)  <<  (float)LC3_Hit_count/(float)nentries<<"\n";
cout<<"LC1 count = "<<LC1_Hit_count<<"\t"<<"Trk Count = "<<Trk_count<<endl;	  
}
if (EfficiencyType == 1)
{
file_outEff << RunName <<"\t"<<
           setw(5) <<  (float)LC1_Hit_count/(float)Trk_count<<" "<<
           setw(5) <<  (float)LC2_Hit_count/(float)Trk_count<<" "<<
          setw(5)  <<  (float)LC3_Hit_count/(float)Trk_count<<"\n";	  
cout << RunName <<"\t"<<
           setw(5) <<  (float)LC1_Hit_count/(float)Trk_count<<" "<<
           setw(5) <<  (float)LC2_Hit_count/(float)Trk_count<<" "<<
          setw(5)  <<  (float)LC3_Hit_count/(float)Trk_count<<"\n";	  

cout<<"LC1 count = "<<LC1_Hit_count<<"\t"<<"Trk Count = "<<Trk_count<<endl;	  
}
if (EfficiencyType == 2)
{
file_outEff << RunName <<"\t"<<
           setw(5) <<  (float)LC1_Hit_count/(float)Trk_count<<" "<<
           setw(5) <<  (float)LC2_Hit_count/(float)Trk_count<<" "<<
          setw(5)  <<  (float)LC3_Hit_count/(float)Trk_count<<"\n";
cout << RunName <<"\t"<<
           setw(5) <<  (float)LC1_Hit_count/(float)Trk_count<<" "<<
           setw(5) <<  (float)LC2_Hit_count/(float)Trk_count<<" "<<
          setw(5)  <<  (float)LC3_Hit_count/(float)Trk_count<<"\n";
cout<<"LC1 count = "<<LC1_Hit_count<<"\t"<<"Trk Count = "<<Trk_count<<endl;	  
}
if (verbose)
{
cout<<"g1x_Hit=============> "<<g1x_Hit_count<<"\tnentries = "<<nentries<<endl;
cout<<"efficiency_g1x "<<(float) g1x_Hit_count/(float) nentries<<endl;

cout<<"g1y_Hits=============> "<<g1y_Hit_count<<endl;
cout<<"efficiency_g1y "<<(float) g1y_Hit_count/(float) nentries<<endl;

cout<<"g2x_Hits=============> "<<g2x_Hit_count<<endl;
cout<<"efficiency_g2x "<<(float) g2x_Hit_count/(float) nentries<<endl;

cout<<"g2y_Hits=============> "<<g2y_Hit_count<<endl;
cout<<"efficiency_g2y "<<(float) g2y_Hit_count/(float) nentries<<endl;
cout<<"g3x_Hits=============> "<<g3x_Hit_count<<endl;
cout<<"efficiency_g3x "<<(float) g3x_Hit_count/(float) nentries<<endl;

cout<<"g3y_Hits=============> "<<g3y_Hit_count<<endl;
cout<<"efficiency_g3y "<<(float) g3y_Hit_count/(float) nentries<<endl;
cout<<"g1_Hits=============> "<<g1_Hit_count<<endl;
cout<<"efficiency_g1 "<<(float) g1_Hit_count/(float) nentries<<endl;
cout<<"g2_Hits=============> "<<g2_Hit_count<<endl;
cout<<"efficiency_g2 "<<(float) g2_Hit_count/(float) nentries<<endl;
cout<<"g3_Hits=============> "<<g3_Hit_count<<endl;
cout<<"efficiency_g3 "<<(float) g3_Hit_count/(float) nentries<<endl;
cout<<"LC1_Hits=============> "<<LC1_Hit_count<<endl;
cout<<"efficiency_LC1 "<<(float) LC1_Hit_count/(float) nentries<<endl;
cout<<"LC2_Hits=============> "<<LC2_Hit_count<<endl;
cout<<"efficiency_LC2 "<<(float) LC2_Hit_count/(float) nentries<<endl;
cout<<"LC3_Hits=============> "<<LC3_Hit_count<<endl;
cout<<"efficiency_LC3 "<<(float) LC3_Hit_count/(float) nentries<<endl;
}

}
