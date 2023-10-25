rm Results/*
rm Results_du/*
echo "removed the old population and start copying..."

cp ./Population_pool/Results/Net_{0..9999}.txt ./Results
cp ./Population_pool/Results_du/Net_du_{0..9999}.txt ./Results_du
echo "copying done!"
echo "the package started!"
#./Exe/Final.out

echo "simulation finished!"
