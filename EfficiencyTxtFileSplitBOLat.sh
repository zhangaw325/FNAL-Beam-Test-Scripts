source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
IRunNo=$1
FRunNo=$2
ILat=15
FLat=30
RunCounter=$IRunNo
info="HitAll3Trk"

echo "file(s) of interest:"
rm EfficiencyTxtFiles/FilesToAnalyze.txt
echo "GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt" >> EfficiencyTxtFiles/FilesToAnalyze.txt

while [ $ILat -le $FLat ]
do
	rm EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
	grep "Lat$ILat" EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt >> EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
	outputFile=EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
	outputFile_short=EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt

	if [[ $(stat -c%s "$outputFile") -le 46 ]]; then
		rm $outputFile
	else
		echo "vim $outputFile"
		echo "GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt" >> EfficiencyTxtFiles/FilesToAnalyze.txt
	fi

	ILat=$[$ILat+1]
done 	# End of while loop

cp EfficiencyTxtFiles/FilesToAnalyze.txt EfficiencyTxtFiles/FilesToAnalyze_R${IRunNo}_R${FRunNo}.txt

echo "To Make Efficiency Curves Execute In Terminal:"
echo "./analyzeEff.sh"
