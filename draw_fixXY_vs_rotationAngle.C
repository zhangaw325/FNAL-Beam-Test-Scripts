void draw_fixedXY_vs_rotation()
{
	double Xoffset = -1897.246972;
	double Yoffset = 6.600484;
	char filename[300]; sprintf(filename,"Iteration_Position_Cluster_run004_CMSScan_eta5_32GeV_20131017_0248am_inclusive_X_%.2f.txt",Xoffset);
	char rootfilename[300]; sprintf(rootfilename,"Iteration_Position_Cluster_run004_CMSScan_eta5_32GeV_20131017_0248am_inclusive_X_%.2f.root",Xoffset);
	char outRootFile[300]; sprintf(outRootFile,"Iteration_Position_Cluster_run004_CMSScan_eta5_32GeV_20131017_0248am_inclusive_X_%.2f.root",Xoffset);
	fstream fin(filename,ios::in);
	fstream fout("X_-1897.25_Y_6.6_vs_angle.txt",ios::out|ios::app);
	TFile* file = new TFile(outRootFile,"recreate");
	double angle,x,y, meanEta5, sigmaEta5, chi2r, chi2phi, totalChi2;
	TGraph* gMeanEta5VsY = new TGraph(); gMeanEta5VsY->SetTitle("Y_vs_residualMeanEta5"); gMeanEta5VsY->SetName("Y_vs_residualMeanEta5");
	TGraph* gSigmaEta5VsY = new TGraph(); gSigmaEta5VsY->SetTitle("Y_vs_residualSigmaEta5"); gSigmaEta5VsY->SetName("Y_vs_residualSigmaEta5");
	TGraph* gChi2rVsY = new TGraph(); gChi2rVsY->SetTitle("Y_vs_rChi2"); gChi2rVsY->SetName("Y_vs_rChi2");
	TGraph* gChi2phiVsY = new TGraph(); gChi2phiVsY->SetTitle("Y_vs_phiChi2"); gChi2phiVsY->SetName("Y_vs_phiChi2");
	int n=0;
	while(fin>>angle>>x>>y>>meanEta5>>sigmaEta5>>chi2r>>chi2phi>>totalChi2){
		gMeanEta5VsY->SetPoint(n,angle,meanEta5);   
		gSigmaEta5VsY->SetPoint(n,angle,sigmaEta5); 
		gChi2rVsY->SetPoint(n,angle,chi2r);       gChi2phiVsY->SetPoint(n,angle,chi2phi);		
		n++;
	}
	fin.close();
	gMeanEta5VsY->GetXaxis()->SetTitle("Rotation angle [rad]");  gMeanEta5VsY->GetYaxis()->SetTitle("Residual mean Eta5 [rad]");   gMeanEta5VsY->SetMarkerStyle(8);
	gMeanEta5VsY->GetXaxis()->SetTitleSize(0.05); gMeanEta5VsY->GetXaxis()->SetLabelSize(0.05); gMeanEta5VsY->GetYaxis()->SetTitleSize(0.05); gMeanEta5VsY->GetYaxis()->SetLabelSize(0.05);
	gSigmaEta5VsY->GetXaxis()->SetTitle("Rotation angle [rad]"); gSigmaEta5VsY->GetYaxis()->SetTitle("Residual sigma Eta5 [rad]"); gSigmaEta5VsY->SetMarkerStyle(8);
	gSigmaEta5VsY->GetXaxis()->SetTitleSize(0.05); gSigmaEta5VsY->GetXaxis()->SetLabelSize(0.05); gSigmaEta5VsY->GetYaxis()->SetTitleSize(0.05); gSigmaEta5VsY->GetYaxis()->SetLabelSize(0.05);
	
	gChi2rVsY->GetXaxis()->SetTitle("Rotation angle [rad]");    gChi2rVsY->GetYaxis()->SetTitle("Track #chi^{2} in r");         gChi2rVsY->SetMarkerStyle(8);
	gChi2rVsY->GetXaxis()->SetTitleSize(0.05); gChi2rVsY->GetXaxis()->SetLabelSize(0.05); gChi2rVsY->GetYaxis()->SetTitleSize(0.05); gChi2rVsY->GetYaxis()->SetLabelSize(0.05);
	gChi2phiVsY->GetXaxis()->SetTitle("Rotation angle [rad]");  gChi2phiVsY->GetYaxis()->SetTitle("Track #chi^{2} in #phi");    gChi2phiVsY->SetMarkerStyle(8);
	gChi2phiVsY->GetXaxis()->SetTitleSize(0.05); gChi2phiVsY->GetXaxis()->SetLabelSize(0.05); gChi2phiVsY->GetYaxis()->SetTitleSize(0.05); gChi2phiVsY->GetYaxis()->SetLabelSize(0.05);
	
	//gStyle->SetOptFit(0111); TF1* f1 = new TF1("fun","pol1",-50,50); TF1* fChi2phi = new TF1("fChi2phi","pol2",-50,50);
	TCanvas* cEta5 = new TCanvas(); cEta5->SetName("residualEta5"); cEta5->Divide(1,2);
	cEta5->cd(1); gMeanEta5VsY->Draw("AP");
	//gMeanZZ1VsY->Fit(f1,"RQ"); fout<<f1->GetParameter(0)<<"\t"<<f1->GetParameter(1)<<"\t";
	cEta5->cd(2); gSigmaEta5VsY->Draw("AP");
	char cEta5png[30]; sprintf(cEta5png,"./ResEta2_X_%.2f_Y_%.2f.png",Xoffset,Yoffset);
	cEta5->SaveAs(cEta5png);
	cEta5->Write(); cEta5->Close();
	
	TCanvas* cChi2 = new TCanvas(); cChi2->SetName(""); //cChi2->Divide(1,2);
	//cChi2->cd(1); gChi2rVsY->Draw("AP");
	cChi2->cd(); gChi2phiVsY->Draw("AP");
	//gChi2phiVsY->Fit(fChi2phi,"RQ");
	//fout<<offset<<"\t"<<-1.0*fChi2phi->GetParameter(1)/(fChi2phi->GetParameter(2)*2.0)<<endl;
	char cChi2png[30]; sprintf(cChi2png,"./Chi2_X_%.2f_Y_%.2f.png",Xoffset,Yoffset);
	cChi2->SaveAs(cChi2png);
	cChi2->Write(); //cChi2->Close();
	
	file->Close();
	fout.close();
}

