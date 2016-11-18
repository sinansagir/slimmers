#include "step2.cc"

void makeSingleStep2(){

  TString inputFile="/user_data/ssagir/LJMet_1lep_111716_step1hadds/nominal/X53X53_M-800_LH_TuneCUETP8M1_13TeV-madgraph-pythia8_hadd.root";

  TString outputFile="X53.root";

  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");

  step2 t(inputFile,outputFile);
  t.Loop();
}





