#include "step1.cc"

void testStep1(){
  
  TString inputFile="/mnt/hadoop/users/ssagir/LJMet_1lepTT_080116/nominal/X53X53_M-700_LH_TuneCUETP8M1_13TeV-madgraph-pythia8/X53X53_M-700_LH_TuneCUETP8M1_13TeV-madgraph-pythia8_1.root";
  
  TString outputFile="test.root";
  
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  
  step1 t(inputFile,outputFile);
  t.Loop();
}


