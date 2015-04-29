void main(){
  fstream fin1("fitPara_vs_X.txt",ios::in);
  fstream fin2("allX_vs_Y.txt",ios::in);
  float y,x1,x2; // for fitPara_vs_X.txt
  float x,y1,y2;
  TGraph* g1 = new TGraph(); g1->SetName("sigma_vs_X");
  TGraph* g2 = new TGraph(); g2->SetName("chi2_vs_X");
  TGraph* g3 = new TGraph(); g3->SetName("mean_vs_Y");
  TGraph* g4 = new TGraph(); g4->SetName("chi2_vs_Y");
  int n1=0;
  int n2=0;
  while(fin1>>y>>x1>>x2){
  	
    if(y>=-37 && y<=-20){
      g1->SetPoint(n1,x1,y);
      g2->SetPoint(n1,x2,y);
    //cout<<y<<"\t"<<x1<<"\t"<<x2<<endl;
    n1++;
    }
  }
  fin1.close();
  while(fin2>>x>>y1>>y2){
    g3->SetPoint(n2,x,y1);
    g4->SetPoint(n2,x,y2);
    n2++;
  }
  fin2.close();

  TCanvas* c = new TCanvas();
  g4->GetXaxis()->SetTitle("X offset [mm]"); g4->GetXaxis()->SetTitleSize(0.05); g4->GetXaxis()->SetLabelSize(0.05);
  g4->GetYaxis()->SetTitle("Y offset [mm]"); g4->GetYaxis()->SetTitleSize(0.05); g4->GetYaxis()->SetLabelSize(0.05);
  g1->SetMarkerStyle(24); g1->SetMarkerColor(kBlack);
  g2->SetMarkerStyle(25); g2->SetMarkerColor(kRed);
  g3->SetMarkerStyle(26); g3->SetMarkerColor(kBlue);
  g4->SetMarkerStyle(27); g4->SetMarkerColor(kPink);
  g4->GetYaxis()->SetRangeUser(-38,-20);
  g4->GetXaxis()->SetRangeUser(-1910,-1810);
  g4->Draw("AP");
  g2->Draw("P");
  g3->Draw("P");
  g1->Draw("P");

  TLegend* leg = new TLegend(0.5,0.5,0.9,0.9);
  leg->SetHeader("Minimizing from: ");
  leg->AddEntry(g1,"residual sigma vs X","lp");
  leg->AddEntry(g2,"#chi^{2} vs X","lp");
  leg->AddEntry(g3,"residual mean vs Y","lp");
  leg->AddEntry(g4,"#chi^{2} vs Y","lp");
  leg->Draw();
}
