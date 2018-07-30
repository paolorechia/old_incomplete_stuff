#!/bin/bash 
# configuration variables

if [ $1 ]
    then
        csv=$1
    else
        csv=temperature.csv
fi;

hdd='/dev/sda'  #uncomment to check HDD temperature (requires sudo)
num_cores=4     #CPU cores

function checkGPU {
    GPUtemp=$(nvidia-smi -q -d temperature | grep Current | cut -f 2 -d':' | cut -f 2 -d ' ')
}

function checkCPU {
    CPUS=$(sensors | grep +  | cut -d "+" -f 2 | cut -d '.' -f 1)
    
    i=0
    let max=$(echo $CPUS | wc -w)
    while [[ $i -lt $max ]]; do
        let j=i+1
        CPU[$i]=$(echo $CPUS | cut -d " " -f "$j")
        let i=$i+1
    done
}

function checkHDD {
    HDDtemp=$(hddtemp $hdd| tr -d '°' | tr -d  ' ' | cut -d ':' -f 3 | cut -d 'C' -f1)
}

function buildCPUHeader {
    i=0
    let max=$(echo $CPUS | wc -w)
    let upperbound=$max-1
    while [[ $i -lt $max ]]; do
        if [[ $i -eq $upperbound ]]
        then
            CPUHeader[$i]=CPU$i
        else
            CPUHeader[$i]=CPU$i,
        fi;
        let i=$i+1
    done 
}
function buildCPUString {
    i=1
    let max=$(echo $CPUS | wc -w)
    CPUString="${CPU[0]}"
    while [[ $i -lt $max ]]; do
        CPUString="$CPUString, ${CPU[$i]}"
        let i=$i+1
    done 
}

checkCPU
buildCPUHeader
header="GPU" 
if [ $CPUHeader[*] ]
    then
        header="$header, ${CPUHeader[*]}"
    else
        header="$header, CPU"
fi;
        
if [ $hdd ]
    then
        hdd_name=$(echo $hdd | cut -d '/' -f3)
        header="$header, $hdd_name"
fi;
header="$header, time"

echo "backing up... $csv"
cp $csv old_$csv
echo "writing new $csv"
echo $header > $csv
seconds=0
period=2
while [ 0 ]; do
    seconds=`expr $seconds + $period`
    sleep $period
    checkGPU
    string=$GPUtemp
    checkCPU
    buildCPUString
    string="$string, $CPUString"
    if [ $hdd ]
        then
        checkHDD
        string="$string, $HDDtemp"
    fi;
    echo  $string, $seconds >> $csv
#    Rscript analyse.r
done
