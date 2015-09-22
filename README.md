# FNAL-Beam-Test-Scripts
note: doubleGausFit_withHistParameter.C contains the function to do double Gausian fit. The scritps that need it already have it included.

step 1: select events.

  use SelectTrackerEvents.C, can be changed to include selecting GEM events

step 2: alignment of trackers.

  use AlignTrackers_Shift.C, AlignTrackers_shift_rotate.C, AlignTrackers_optimizeRotation.C

  each script has iterations, for the third script, when optimizing rotation angles, optimize one detector one time,

  in other words, the iteration quantity is the angle for one tracker, the other angles are fixed

step 3: alignment GEM detector to trackers

  use AlignGEM_XYoffsets.C,

  after this script, will get some text files, then

  draw_allX_vs_Y.C, draw_allY_vs_X.C, draw_XY_Offsets.C can be used for them

  use AlignGEM_rotate.C, and draw_fixXY_vs_rotationAngle.C

then resolution can be calculated with AlignGEM_rotate.C by setting all X,Y offsets and angle, and do not doing iteration.  

##Environment Setting for Lxplus
This code is check for only root version 6.04. So, its recommended that one should run this on root 6.04.

Lxplus setting for root 6.04:

    For tcsh shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.csh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.csh

    For bash shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

