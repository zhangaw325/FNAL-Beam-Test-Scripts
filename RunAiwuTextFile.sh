IRunNo=$1
FRunNo=$2
RunCounter=$IRunNo
#PathOfInputData=/afs/cern.ch/work/p/pbarria/public/TB_H2_OCT_2014/beamdata
#PathOfInputData=/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/Ntuples/H2TestBeam/R306_R407
#PathOfInputData=/tmp/beamdata
PathOfInputData=/afs/cern.ch/user/r/rasharma/work/GEM/TBA/FNAL-Beam-Test-Scripts
EfficiencyType=0

if [[ $EfficiencyType == 0 ]]; then
	OutputEffFileName="GE11s_Efficiency_Independent.txt"
fi
if [[ $EfficiencyType == 1 ]]; then
	OutputEffFileName="GE11s_Efficiency_If_Hit_2_Trk.txt"
fi
if [[ $EfficiencyType == 2 ]]; then
	OutputEffFileName="GE11s_Efficiency_Hit_all_3_Trk.txt"
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
    for dir in $PathOfInputData/Run$file*; do
    	#perl -spe 's/CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root/$a/' < 
	#echo ${PathOfInputData}$(basename $f)/CRC-$(basename $f)-0.root
	echo "===============================================:"
	echo "Directory name : "$dir
	echo "Base name : "$(basename $dir)
	RunName=$(basename $dir)
	for rootfile in $dir/CRC*.root;do
	    echo "Root file name : "$rootfile
	    ./CreateHeader.sh $rootfile rd51tbgeo
	    root -l -b -q Master_test.C\(\"${rootfile}\",\"${RunName}\",${EfficiencyType}\)
	done
	#./CreateHeader.sh $f rd51tbgeo
	#git checkout AiwuTextFile.h
	#sed -i "s?CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root?${f}?g" AiwuTextFile.h
	#root -l -b -q RunAiwuTextFile.C
    done
    ((++RunCounter))
done
cp ${OutputEffFileName} GE11s_Effeciency_Info_R${IRunNo}_R$FRunNo.txt
mv GE11s_Effeciency_Info_R${IRunNo}_R$FRunNo.txt EfficiencyTxtFiles/
