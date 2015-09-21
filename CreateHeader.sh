echo "root -l -b -q CreatMakeClass.C++\(\"${1}\"\)"
root -l -b -q CreatMakeClass.C\(\"${1}\",\"${2}\"\)

python HeaderExtracter.py 
python AppendInHeader.py


sed -i 's/tree=0/tree/' ClassReadTree.cc
sed -i 's/virtual Int_t    Cut(Long64_t entry);//' ClassReadTree.cc
sed -i 's/virtual Int_t    GetEntry(Long64_t entry);//' ClassReadTree.cc
sed -i 's/virtual Long64_t LoadTree(Long64_t entry);//' ClassReadTree.cc
sed -i 's/virtual void     Loop();//' ClassReadTree.cc
sed -i 's/virtual Bool_t   Notify();//' ClassReadTree.cc
sed -i 's/virtual void     Show(Long64_t entry = -1);//' ClassReadTree.cc
sed -i 's/Notify();//' ClassReadTree.cc

rm ClassReadTree.h ClassReadTree.C
