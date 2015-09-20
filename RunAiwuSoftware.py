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
    args = parser.parse_args ()

print '========================================================================='
print 'Start Running SelectTrackerEvents.C...'

print('root -l -b -q SelectTrackerEvents.C\(\\"'+args.InputFile+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')
os.system('root -l -b -q SelectTrackerEvents.C\(\\"'+args.InputFile+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')

print '\n\nSelectTrackerEvents.C DONE...\n\n'

print '\n\n======== Start::CALCULATING SHIFT PARAMETERS    =================================\n\n'


from ROOT import *
f = TFile( 'CoarseAligned.root' )

g1x = f.Get("h_Pos_g1xcl")  
g1y = f.Get("h_Pos_g1ycl")  
g2x = f.Get("h_Pos_g1xcl")  
g2y = f.Get("h_Pos_g1ycl")  
g3x = f.Get("h_Pos_g1xcl")  
g3y = f.Get("h_Pos_g1ycl")  

Mean_g1y = g1x.GetMean()
Mean_g1y = g1y.GetMean()
Mean_g2y = g2x.GetMean()
Mean_g2y = g2y.GetMean()
Mean_g3y = g3x.GetMean()
Mean_g3y = g3y.GetMean()


print '\n\n======== END::CALCULATING SHIFT PARAMETERS    =================================\n\n'


print '\n\n============ START:: Running AlignTrackers_Shift.C...    ================================\n\n'

print 'This code will align trackers only\n\n'

print('root -l -b -q AlignTrackers_Shift.C\(\\"TrackerOnly_Position_RunNumber411.txt\\",'+args.RunNumber+','+str(g1x.GetMean())+','+str(g1y.GetMean())+','+str(g2x.GetMean()) + ','+str(g2y.GetMean()) +','+str(g3x.GetMean()) +','+str(g3y.GetMean())+'\)')

os.system('root -l -b -q AlignTrackers_Shift.C\(\\"TrackerOnly_Position_RunNumber'+args.RunNumber+'.txt\\",'+args.RunNumber+','+str(g1x.GetMean())+','+str(g1y.GetMean())+','+str(g2x.GetMean()) + ','+str(g2y.GetMean()) +','+str(g3x.GetMean()) +','+str(g3y.GetMean())+'\)')

print '\n\nAlignTrackers_Shift.C...  DONE'
