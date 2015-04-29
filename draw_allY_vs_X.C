//#include "setGraphStyle.C"

void draw_allY_vs_X(){
	string head="Iteration_Position_Cluster_run017_HVScan_4150V_32GeV_20131017_1254pm_all_inclusive_X_";
	TFile* file = new TFile("Iteration_Position_Sector1_20131013_0443am_inclusive_X.root","recreate");
	const int NN = 101; // Y from -40 to 0, in setp of 0.5, so number of points is (100)/2+1=51.
	const int MM = 101; // X from 1350 to 1552, in step of 2, (1552-1350)/2+1=102
	TCanvas* mycan[NN];
	TGraph* gMeanEta5[NN];
	TGraph* gSigmaEta5[NN];
	TGraph* gChi2r[NN];
	TGraph* gChi2phi[NN];
	//TGraph* gTotalChi2[NN];
	
	string filename[MM];
	
	double x,y,meanEta5,sigmaEta5,chi2r,chi2phi,totalChi2;
	for(int i=0; i<NN; i++){	  
	  gMeanEta5[i]=new TGraph(); gSigmaEta5[i]=new TGraph();
	  gChi2r[i]=new TGraph(); gChi2phi[i]=new TGraph();	  
	  //gTotalChi2[i]=new TGraph();
	}

  for(int i=0;i<MM;i++){  
  	char strX[20]; sprintf(strX,"%.2f",-1810-1.0*i);
	  filename[i] = head + strX + ".txt" ;
	  fstream fin(filename[i].c_str(),ios::in);
	  //cout<<filename[i]<<endl;
	  while(fin>>x>>y>>meanEta5>>sigmaEta5>>chi2r>>chi2phi>>totalChi2){
	  	float k = (y+40)/0.2;  // j is the point numebr of Y
                int j=k;
	  	cout<<filename[i]<<"\t"<<j<<endl;
	  	gMeanEta5[j]->SetPoint(i,x,meanEta5); gSigmaEta5[j]->SetPoint(i,x,sigmaEta5);
	  	gChi2r[j]->SetPoint(i,x,chi2r); gChi2phi[j]->SetPoint(i,x,chi2phi);
	  	//gTotalChi2[j]->SetPoint(i,x,totalChi2);
	  }
	  fin.close();
	}
	
	fstream fout1("fitPara_vs_X.txt",ios::out);
	gStyle->SetOptFit(0111);
	//TF1* fitSigmaZZ1 = new TF1("fitSigmaZZ1","pol2",1400,1520);
	TF1* fitSigma = new TF1("fitSigma","pol2",-1910,-1830);
        TF1* fitChi2 = new TF1("fitChi2","pol2",-1910,-1830);
	for(int i=0; i<NN; i++){
		double temp = -40+0.2*i;
		gMeanEta5[i]->GetXaxis()->SetTitle("X offset [mm]"); gMeanEta5[i]->GetYaxis()->SetTitle("Residual mean CMS SS sector 5 [rad]");
		gSigmaEta5[i]->GetXaxis()->SetTitle("X offset [mm]"); gSigmaEta5[i]->GetYaxis()->SetTitle("Residual sigma CMS SS sector 5 [rad]");
		gChi2r[i]->GetXaxis()->SetTitle("X offset [mm]"); gChi2r[i]->GetYaxis()->SetTitle("Track #chi^{2} in r");
		gChi2phi[i]->GetXaxis()->SetTitle("X offset [mm]"); gChi2phi[i]->GetYaxis()->SetTitle("Track #chi^{2} in #phi");
//		gTotalChi2[i]->GetXaxis()->SetTitle("X offset [mm]"); gTotalChi2[i]->GetYaxis()->SetTitle("Total #chi^{2}");
		
		setGraphStyle(gMeanEta5[i]); setGraphStyle(gSigmaEta5[i]);
		setGraphStyle(gChi2r[i]); setGraphStyle(gChi2phi[i]);
		//setGraphStyle(gTotalChi2[i]);
		
	  char canName[20]; sprintf(canName,"canvas_Y_%.1f",-40+0.2*i);
	  mycan[i]=new TCanvas(); mycan[i]->SetName(canName); mycan[i]->Divide(2,2);	
		mycan[i]->cd(1); gMeanEta5[i]->Draw("AP"); 
		mycan[i]->cd(2); gSigmaEta5[i]->Draw("AP"); gSigmaEta5[i]->Fit(fitSigma,"RQ");
		mycan[i]->cd(3); gChi2r[i]->Draw("AP");
                mycan[i]->cd(4); gChi2phi[i]->Draw("AP"); gChi2phi[i]->Fit(fitChi2,"RQ");
		//mycan[i]->cd(5); gTotalChi2[i]->Draw("AP"); 
		mycan[i]->Write();
		char canvaspng[40]; sprintf(canvaspng,"./Vs_X/all_Y_%d_%.1f.png",i,-40+0.2*i);
		mycan[i]->SaveAs(canvaspng); mycan[i]->Close();
		
		fout1<<-40+0.2*i<<"\t"<<-1.0*fitSigma->GetParameter(1)/(2.0*fitSigma->GetParameter(2))
                                <<"\t"<<-1.0*fitChi2->GetParameter(1)/(2.0*fitChi2->GetParameter(2))<<endl;

	}
	fout1.close();

	file->Close();

}
