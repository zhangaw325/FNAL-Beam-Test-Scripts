source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
IRunNo=$1
FRunNo=$2
RunCounter=$IRunNo
#PathOfInputData=/afs/cern.ch/work/p/pbarria/public/TB_H2_OCT_2014/beamdata
PathOfInputData=/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/Ntuples/H2TestBeam/R306_R407
#PathOfInputData=/home/ramkrishna/TEMP/FNAL_BT
#PathOfInputData=/afs/cern.ch/user/r/rasharma/work/GEM/TBA/FNAL-Beam-Test-Scripts
    #/*
    # * EfficiencyType : If want to calculate efficiency of each GE11's independently
    # *			Using trigger from hardware only put it equal to 0
    # *
    # *			If want to trigger it using two of the reference tracker 
    # *			put it = 1
    # *
    # *			if want to trigger it only when it passes from all three reference
    # *			tracker then put it = 2
    # */
EfficiencyType=2

    #/*
    # * TrkOnly	    : If you want output text file in which there are hit iff there is 
    # *		      hit only in all three tracker then put this = 1
    # *		    
    # *		      If you want to get hit iff there is hit in all tracker as well
    # *		      as in GE11's then put this = 0
    # */
TrkOnly=1

if [[ $EfficiencyType == 0 ]]; then
	OutputEffFileName="GE11s_Efficiency_Independent.txt"
	info="Independent"
fi
if [[ $EfficiencyType == 1 ]]; then
	OutputEffFileName="GE11s_Efficiency_If_Hit_2_Trk.txt"
	info="HitOnly2Trk"
fi
if [[ $EfficiencyType == 2 ]]; then
	OutputEffFileName="GE11s_Efficiency_Hit_all_3_Trk.txt"
	info="HitAll3Trk"
fi

function make_dir
{
#	------------------------------------------------------------------------
#	It Checks IF the output data directory exists or not
#	No Arguments
#	------------------------------------------------------------------------

	if [ -d "${1}" ]; then
		echo "Directory ${1} Exists......."
	else
		mkdir ${1}
		echo "Directory ${1} Created................."
	fi
}	# end of make_dir


rm GE11s_Effeciency_Info.txt

make_dir HitTxtFiles
make_dir RootFiles
make_dir ResidualFiles
make_dir ShiftParameterFiles
make_dir EfficiencyTxtFiles

echo -e "RunName\t\t\t\t\t\t\t\t GE11_IV_GIF \t GE11_IV \t GE11_V" > ${OutputEffFileName}
while [ $RunCounter -le $FRunNo ]
do
    if [[(($RunCounter -le 9))]]; then
        file=000$RunCounter
    else
        if [[(($RunCounter -le 99))]]; then
            file=00$RunCounter
        else
            if [[(($RunCounter -le 999))]]; then
                file=0$RunCounter
            else
                file=$RunCounter
            fi
        fi
    fi
    for dir in $PathOfInputData/Run$file*; do	    # Start of dir for loop
    	#perl -spe 's/CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root/$a/' < 
	#echo ${PathOfInputData}$(basename $f)/CRC-$(basename $f)-0.root
	echo "===============================================:"
	echo "Directory name : "$dir
	echo "Base name : "$(basename $dir)
	RunName=$(basename $dir)
	for rootfile in $dir/CRC*.root;do	# Start of rootfile for loop
	    echo "Root file name : "$rootfile
	    ./CreateHeader.sh $rootfile rd51tbgeo
	    if [[ $RunCounter -le 1587 ]]; then
	    	root -l -b -q GetHitTxtFile_H2.C\(\"${rootfile}\",\"${RunName}\",${EfficiencyType},${TrkOnly}\)
	    else
	    	root -l -b -q GetHitTxtFile_H4.C\(\"${rootfile}\",\"${RunName}\",${EfficiencyType},${TrkOnly}\)
	    fi
	done	# END of rootfile for loop
    done	# END of dir for loop
    ((++RunCounter))	# increment counter for while loop
done			# while loop ends
cp ${OutputEffFileName} GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt
mv GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt EfficiencyTxtFiles/
