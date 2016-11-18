#!/bin/bash

infilename=${1}
outfilename=${2}
inputDir=${3}
outputDir=${4}

scratch=${PWD}
macroDir=${PWD}

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc491

scramv1 project CMSSW CMSSW_7_4_14
cd CMSSW_7_4_14
eval `scramv1 runtime -sh`
cd -

export PATH=$PATH:$macroDir

root -l -b -q makeStep1.C\(\"$macroDir\",\"$inputDir/$infilename\",\"$outputDir/$outfilename\"\)
