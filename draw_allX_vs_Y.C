void draw_oneX_vs_Y(double offset)
{
	double Xoffset = offset;
	char filename[100]; sprintf(filename,"Iteration_Position_Cluster_run017_HVScan_4150V_32GeV_20131017_1254pm_all_inclusive_X_%.2f.txt",Xoffset);
	//char rootfilename[100]; sprintf(rootfilename,"Iteration_Position_run017_HVScan_4150V_32GeV_20131017_1254pm_inclusive_X_%.2f.root",Xoffset);
	char outRootFile[100]; sprintf(outRootFile,"Iteration_Position_Cluster_run017_HVScan_4150V_32GeV_20131017_1254pm_all_inclusive_X_%.2f.root",Xoffset);
	fstream fin(filename,ios::in);
	cout<<filename<<endl;
	fstream fout("allX_vs_Y.txt",ios::out|ios::app);
	TFile* file = new TFile(outRootFile,"recreate");
	double x,y, meanZZ1, sigmaZZ1, chi2r, chi2phi, totalChi2;
	TGraph* gMeanZZ1VsY = new TGraph(); gMeanZZ1VsY->SetTitle("Y_vs_residualMeanCMSZZ_Eta5"); gMeanZZ1VsY->SetName("Y_vs_residualMeanCMSZZ_Eta5");
	TGraph* gSigmaZZ1VsY = new TGraph(); gSigmaZZ1VsY->SetTitle("Y_vs_residualSigmaCMSZZ_Eta5"); gSigmaZZ1VsY->SetName("Y_vs_residualSigmaCMSZZ_Eta5");
	TGraph* gChi2rVsY = new TGraph(); gChi2rVsY->SetTitle("#chi^{2} in r vs. Y offset"); gChi2rVsY->SetName("rChi2_vs_Y");
	TGraph* gChi2phiVsY = new TGraph(); gChi2phiVsY->SetTitle("#chi^{2} in #phi vs. Y offset"); gChi2phiVsY->SetName("phiChi2_vs_Y");
	//TGraph* gTotalChi2VsY = new TGraph(); gTotalChi2VsY->SetTitle("total #chi^{2} vs. Y offset");
	int n=0;
	while(fin>>x>>y>>meanZZ1>>sigmaZZ1>>chi2r>>chi2phi>>totalChi2){
		gMeanZZ1VsY->SetPoint(n,y,meanZZ1);   
		gSigmaZZ1VsY->SetPoint(n,y,sigmaZZ1); 
		gChi2rVsY->SetPoint(n,y,chi2r);       gChi2phiVsY->SetPoint(n,y,chi2phi);	 
                //gTotalChi2VsY->SetPoint(n,y,totalChi2);	
		n++;
	}
	fin.close();
	gMeanZZ1VsY->GetXaxis()->SetTitle("Y offset [mm]");  gMeanZZ1VsY->GetYaxis()->SetTitle("Residual mean Eta5 [rad]");   gMeanZZ1VsY->SetMarkerStyle(21); gMeanZZ1VsY->SetMarkerSize(0.60);
	gMeanZZ1VsY->GetXaxis()->SetTitleSize(0.05); gMeanZZ1VsY->GetXaxis()->SetLabelSize(0.05); gMeanZZ1VsY->GetYaxis()->SetTitleSize(0.05); gMeanZZ1VsY->GetYaxis()->SetLabelSize(0.05);
	gSigmaZZ1VsY->GetXaxis()->SetTitle("Y offset [mm]"); gSigmaZZ1VsY->GetYaxis()->SetTitle("Residual sigma Eta5 [rad]"); gSigmaZZ1VsY->SetMarkerStyle(21); gSigmaZZ1VsY->SetMarkerSize(0.60);
	gSigmaZZ1VsY->GetXaxis()->SetTitleSize(0.05); gSigmaZZ1VsY->GetXaxis()->SetLabelSize(0.05); gSigmaZZ1VsY->GetYaxis()->SetTitleSize(0.05); gSigmaZZ1VsY->GetYaxis()->SetLabelSize(0.05);
	gChi2rVsY->GetXaxis()->SetTitle("Y offset [mm]");    gChi2rVsY->GetYaxis()->SetTitle("Track #chi^{2} in r");         gChi2rVsY->SetMarkerStyle(21); gChi2rVsY->SetMarkerSize(0.60);
	gChi2rVsY->GetXaxis()->SetTitleSize(0.05); gChi2rVsY->GetXaxis()->SetLabelSize(0.05); gChi2rVsY->GetYaxis()->SetTitleSize(0.05); gChi2rVsY->GetYaxis()->SetLabelSize(0.05);
	gChi2phiVsY->GetXaxis()->SetTitle("Y offset [mm]");  gChi2phiVsY->GetYaxis()->SetTitle("Track #chi^{2} in #phi");    gChi2phiVsY->SetMarkerStyle(21); gChi2phiVsY->SetMarkerSize(0.60);
	gChi2phiVsY->GetXaxis()->SetTitleSize(0.05); gChi2phiVsY->GetXaxis()->SetLabelSize(0.05); gChi2phiVsY->GetYaxis()->SetTitleSize(0.05); gChi2phiVsY->GetYaxis()->SetLabelSize(0.05);
	//gTotalChi2VsY->GetXaxis()->SetTitle("Y offset [mm]");gTotalChi2VsY->GetXaxis()->SetTitleSize(0.05); gTotalChi2VsY->GetXaxis()->SetLabelSize(0.05);
	//gTotalChi2VsY->GetYaxis()->SetTitle("Total #Chi^{2}");gTotalChi2VsY->GetYaxis()->SetTitleSize(0.05); gTotalChi2VsY->GetYaxis()->SetLabelSize(0.05);
	//gTotalChi2VsY->SetMarkerStyle(21); gTotalChi2VsY->SetMarkerSize(0.60);
	
	gStyle->SetOptFit(0111); //TF1* f1 = new TF1("fun","pol1",-50,50); TF1* fChi2phi = new TF1("fChi2phi","pol2",-50,50);
	TCanvas* mycan = new TCanvas(); mycan->SetName("mycanvans"); mycan->Divide(2,2);
	mycan->cd(1); gMeanZZ1VsY->Draw("AP");
	TF1* fMean = new TF1("fMean","pol1",-35,-20); gMeanZZ1VsY->Fit(fMean,"RQ");
	fout<<offset<<"\t"<<-1.0*fMean->GetParameter(0)/fMean->GetParameter(1);
	mycan->cd(2); gSigmaZZ1VsY->Draw("AP");
  mycan->cd(3); gChi2rVsY->Draw("AP");
  mycan->cd(4); gChi2phiVsY->Draw("AP");
  TF1* f1 = new TF1("funChi2phi","pol2",-35,-20); gChi2phiVsY->Fit(f1,"RQ");
  fout<<"\t"<<-1.0*f1->GetParameter(1)/(2.0*f1->GetParameter(2))<<endl;
  //mycan->cd(5); gTotalChi2VsY->Draw("AP");
  //TF1* f2 = new TF1("funTotalChi2","pol2",-40,0); gTotalChi2VsY->Fit(f2,"RQ");
  //fout<<"\t"<<-1.0*f2->GetParameter(1)/(2.0*f2->GetParameter(2))<<endl;

	char pngname[40]; sprintf(pngname,"./Vs_Y/X_%.2f.png",offset);
	mycan->SaveAs(pngname);

	//fout<<offset<<"\t"<<-1.0*fChi2phi->GetParameter(1)/(fChi2phi->GetParameter(2)*2.0)<<endl;

	mycan->Write(); mycan->Close();
	
	file->Close();
	fout.close();
}

int main(){
	for(int i=0;i<101;i++)
	  draw_oneX_vs_Y(-1810.0-1.0*i);
}
