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

print 'Start Running SelectTrackerEvents.C...'

os.system('root -l -b -q SelectTrackerEvents.C\(\\"'+args.InputFile+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')

print 'SelectTrackerEvents.C DONE...'

print 'Start Running AlignTrackers_Shift.C...'



