import ROOT
from ROOT import TFile, TH1F, TObject

ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show

output = open('Residual_Tracker.dat', 'w')

for i in range(0, 62):
	RootFile = 'Residual_Position_iter_'+str(i)+'_R406.root'
	#print 'Input ROOT file : ',RootFile
	#f = TFile("Residual_Position_iter_0_R406.root")
	f = TFile(RootFile)
	g1xhist= 'residual_g1xcl_'+str(i+1)
	g1x=f.Get(g1xhist)
	g2xhist= 'residual_g2xcl_'+str(i+1)
	g2x=f.Get(g2xhist)
	g3xhist= 'residual_g3xcl_'+str(i+1)
	g3x=f.Get(g3xhist)
	g1yhist= 'residual_g1ycl_'+str(i+1)
	g1y=f.Get(g1yhist)
	g2yhist= 'residual_g2ycl_'+str(i+1)
	g2y=f.Get(g2yhist)
	g3yhist= 'residual_g3ycl_'+str(i+1)
	g3y=f.Get(g3yhist)
	print >> output, i,'\t',g1x.GetMean(),"\t",g1y.GetMean(),"\t",g2x.GetMean(),"\t",g2y.GetMean(),"\t",g3x.GetMean(),"\t",g3y.GetMean()

output.close()

