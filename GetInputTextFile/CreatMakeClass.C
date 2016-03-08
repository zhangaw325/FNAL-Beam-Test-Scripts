/*
 * =====================================================================================
 *
 *       Filename:  CreatMakeClass.C
 *
 *    Description:  This will create a .C and .h file using make class using the given input root file
 *
 *        Version:  1.0
 *        Created:  Sunday 09 August 2015 07:49:31  CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  CERN
 *
 * =====================================================================================
 */

#include <iostream>
#include "TROOT.h"


void CreatMakeClass(const char * RootFile, const char * treeName)
{
    TFile * f1 = new TFile(RootFile,"READ");
    //TFile * f1 = new TFile("PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_105_RA2AnalysisTree.root","READ");

    TTree * t1 = (TTree*)f1->Get(treeName);

    //gROOT->ProcessLine("PreSelection->MakeClass(\"makerootmacro\")");
    t1->MakeClass("ClassReadTree");
}
