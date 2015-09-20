import sys
import os
import datetime
import argparse
import string

if __name__ == '__main__':
    parser = argparse.ArgumentParser (description = 'Run the Aiwu software')
    parser.add_argument ('-det', '--Det'      , default = 'No'                    , help='No or LC1 or LC2 or LC3')
    parser.add_argument ('-RN' , '--RunNumber', default = '411'                   , help='Enter Run Number')
    parser.add_argument ('-i'  , '--InputFile', default = 'Hit_Position_Info.txt' , help='Name of Input File')
    parser.add_argument ('-l'  , '--Lxplus'   , default = '1'			  , help='if not working on lxplus then put 0')
    args = parser.parse_args ()

if (args.Lxplus):
	print('source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh')
	os.system('source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh')
	print('source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh')
	os.system('source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh')
	#os.system('source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.21/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh')

print '========================================================================='
print 'Start Running SelectTrackerEvents.C...'

print('root -l -b -q SelectTrackerEvents.C\(\\"'+args.InputFile+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')
os.system('root -l -b -q SelectTrackerEvents.C\(\\"'+args.InputFile+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')

print '\n\nSelectTrackerEvents.C DONE...\n\n'

print '\n\n======== Start::CALCULATING SHIFT PARAMETERS    =================================\n\n'

import ROOT
from ROOT import TFile, TH1F, TObject

ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show

RootFile = 'CoarseAligned_'+args.RunNumber+'.root'

print 'Input Root File : ',RootFile
f = TFile(RootFile)

#if ( f = "" ):
#	print 'No input root file found....'
#	sys.exit()

"""
g1x =  TH1F()
g1y =  TH1F()
g2x =  TH1F()
g2y =  TH1F()
g3x =  TH1F()
g3y =  TH1F()
"""
g1x = f.Get("h_Pos_g1xcl")  
g1y = f.Get("h_Pos_g1ycl")  
g2x = f.Get("h_Pos_g1xcl")  
g2y = f.Get("h_Pos_g1ycl")  
g3x = f.Get("h_Pos_g1xcl")  
g3y = f.Get("h_Pos_g1ycl")  

#g1x.Draw()

Mean_g1y = g1x.GetMean()
Mean_g1y = g1y.GetMean()
Mean_g2y = g2x.GetMean()
Mean_g2y = g2y.GetMean()
Mean_g3y = g3x.GetMean()
Mean_g3y = g3y.GetMean()


print '\n\n======== END::CALCULATING SHIFT PARAMETERS    =================================\n\n'

#=====================  START:: Running AlignTrackers_Shift.C	=================================
print '\n\n============ START:: Running AlignTrackers_Shift.C...    ================================\n\n'

print 'This code will align trackers only\n\n'

print('root -l -b -q AlignTrackers_Shift.C\(\\"TrackerOnly_Position_RunNumber411.txt\\",'+args.RunNumber+','+str(g1x.GetMean())+','+str(g1y.GetMean())+','+str(g2x.GetMean()) + ','+str(g2y.GetMean()) +','+str(g3x.GetMean()) +','+str(g3y.GetMean())+'\)')

#os.system('root -l -b -q AlignTrackers_Shift.C\(\\"TrackerOnly_Position_RunNumber'+args.RunNumber+'.txt\\",'+args.RunNumber+','+str(g1x.GetMean())+','+str(g1y.GetMean())+','+str(g2x.GetMean()) + ','+str(g2y.GetMean()) +','+str(g3x.GetMean()) +','+str(g3y.GetMean())+'\)')

print '\n\nAlignTrackers_Shift.C...  DONE'
#=====================  END:: Running AlignTrackers_Shift.C	=================================


#=====================  START:: Running AlignTrackers_shift_rotate.C	=================================

print('root -l -b -q AlignTrackers_shift_rotate.C\(\\"TrackerOnly_Position_RunNumber411.txt\\",'+str(g1x.GetMean())+','+str(g1y.GetMean())+','+str(g2x.GetMean()) + ','+str(g2y.GetMean()) +','+str(g3x.GetMean()) +','+str(g3y.GetMean())+'\)')
os.system('root -l -b -q AlignTrackers_shift_rotate.C\(\\"TrackerOnly_Position_RunNumber411.txt\\",'+str(g1x.GetMean())+','+str(g1y.GetMean())+','+str(g2x.GetMean()) + ','+str(g2y.GetMean()) +','+str(g3x.GetMean()) +','+str(g3y.GetMean())+'\)')


#=====================  END:: Running AlignTrackers_shift_rotate.C	=================================
