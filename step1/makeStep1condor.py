import os,sys,shutil,datetime,time
import getpass
from ROOT import *

start_time = time.time()

shift = sys.argv[1]

#IO directories must be full paths
relbase   = '/home/ssagir/CMSSW_7_4_7/'
inputDir  = '/mnt/hadoop/users/ssagir/LJMet_1lepTT_080116/'+shift+'/'
outputDir = '/user_data/ssagir/LJMet_1lep_111716_step1/'+shift+'/'

runDir=os.getcwd()
# Can change the file directory if needed
#if '' not in shift: runDirPost = ''
#else: runDirPost = shift+'Files'
runDirPost = ''
print 'Files from',runDirPost

gROOT.ProcessLine('.x compileStep1.C')

cTime=datetime.datetime.now()
date='%i_%i_%i_%i_%i_%i'%(cTime.year,cTime.month,cTime.day,cTime.hour,cTime.minute,cTime.second)

condorDir=outputDir+'/condorLogs/'

dirList = [
	'X53X53_M-1000_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1000_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1100_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1100_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1200_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1200_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1300_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1300_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1400_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1400_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1500_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1500_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1600_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-1600_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-700_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-700_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-800_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-800_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-900_LH_TuneCUETP8M1_13TeV-madgraph-pythia8',
	'X53X53_M-900_RH_TuneCUETP8M1_13TeV-madgraph-pythia8',

	'ChargedHiggs_HplusTB_HplusToTB_M-180_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-200_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-220_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-250_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-300_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-350_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-400_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-450_13TeV_amcatnlo_pythia8',
	'ChargedHiggs_HplusTB_HplusToTB_M-500_13TeV_amcatnlo_pythia8',
	
    'WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
    'TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8',
    'TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8',
    'WW_TuneCUETP8M1_13TeV-pythia8',						      
    'WZ_TuneCUETP8M1_13TeV-pythia8',						      
    'ZZ_TuneCUETP8M1_13TeV-pythia8',						      
    'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
    'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1',		      
    'ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1',		      
    'ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1',		      
    'ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',		      
    'ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',		      
    'TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',		      
    'TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',			      
    'TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',					      
    'TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8',			      
  
    'QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',			      
    'QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',              	      
  
    'WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
    'WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',    
    'WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
    'WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
    'WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
    'WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
    'WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 
    ]

if shift == 'nominal':
    # These don't need to be run for shifted directories
    #dirList.append('ST_tW_top_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1')
    #dirList.append('ST_tW_top_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1')	      
    #dirList.append('ST_tW_antitop_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1')	      
    #dirList.append('ST_tW_antitop_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1')      
    dirList.append('TT_TuneCUETP8M1_13TeV-powheg-scaledown-pythia8')
    dirList.append('TT_TuneCUETP8M1_13TeV-powheg-scaleup-pythia8')
#     dirList.append('SingleElectron_PRB')
#     dirList.append('SingleMuon_PRB')
#     dirList.append('SingleElectron_PRC')
#     dirList.append('SingleMuon_PRC')
#     dirList.append('SingleElectron_PRD')
#     dirList.append('SingleMuon_PRD')
    dirList.append('SingleElectron_PRH')
    dirList.append('SingleMuon_PRH')
    dirList.append('SingleElectron_RRBCDEFG')
    dirList.append('SingleMuon_RRBCDEFG')

#calculate # of jobs to be submitted:
totJobs = 0
for sample in dirList:
    for file in os.popen('ls '+inputDir+sample): totJobs+=1
for file in os.popen('ls '+inputDir+'TT_TuneCUETP8M1_13TeV-powheg-pythia8'): totJobs+=1

print 'Starting submission'
count=0
for sample in dirList:
    os.system('mkdir -p '+outputDir+sample)
    os.system('mkdir -p '+condorDir+sample)
    relPath = sample

    rootfiles = [x for x in os.listdir(inputDir+sample) if '.root' in x]
    for file in rootfiles:
        rawfile = file[:-5]
        count+=1
        dict={'RUNDIR':runDir, 'POST':runDirPost, 'RELPATH':relPath, 'CONDORDIR':condorDir, 'INPUTDIR':inputDir, 'FILENAME':rawfile, 'CMSSWBASE':relbase, 'OUTPUTDIR':outputDir}
        jdfName=condorDir+'/%(RELPATH)s/%(FILENAME)s.job'%dict
        print jdfName
        jdf=open(jdfName,'w')
        jdf.write(
"""universe = vanilla
Executable = %(RUNDIR)s/makeStep1.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
request_memory = 3072
Transfer_Input_Files = %(RUNDIR)s/makeStep1.C, %(RUNDIR)s/%(POST)s/step1.cc, %(RUNDIR)s/%(POST)s/step1.h, %(RUNDIR)s/%(POST)s/scaleFactors.h, %(RUNDIR)s/%(POST)s/step1_cc.d, %(RUNDIR)s/%(POST)s/step1_cc.so
Output = %(FILENAME)s.out
Error = %(FILENAME)s.err
Log = %(FILENAME)s.log
Notification = Never
Arguments = %(FILENAME)s.root %(FILENAME)s.root %(INPUTDIR)s/%(RELPATH)s %(OUTPUTDIR)s/%(RELPATH)s

Queue 1"""%dict)
        jdf.close()
        os.chdir('%s/%s'%(condorDir,relPath))
        os.system('condor_submit %(FILENAME)s.job'%dict)
        os.system('sleep 0.5')                                
        os.chdir('%s'%(runDir))
        print count, '/', totJobs, "jobs submitted!!!"

sample = 'TT_TuneCUETP8M1_13TeV-powheg-pythia8'
TTOutList = ['Mtt0to700','Mtt700to1000','Mtt1000toInf']

rootfiles = [x for x in os.listdir(inputDir+sample) if '.root' in x]
relPath = sample        
for outlabel in TTOutList:
    os.system('mkdir -p '+outputDir+sample+'_'+outlabel)
    os.system('mkdir -p '+condorDir+sample+'_'+outlabel)

    for file in rootfiles:
        rawname = file[:-5]
        count+=1
        dict={'RUNDIR':runDir, 'POST':runDirPost, 'RELPATH':relPath, 'LABEL':outlabel, 'CONDORDIR':condorDir, 'INPUTDIR':inputDir, 'FILENAME':rawname, 'CMSSWBASE':relbase, 'OUTPUTDIR':outputDir}
        jdfName=condorDir+'/%(RELPATH)s_%(LABEL)s/%(FILENAME)s_%(LABEL)s.job'%dict
        print jdfName
        jdf=open(jdfName,'w')
        jdf.write(
"""universe = vanilla
Executable = %(RUNDIR)s/makeStep1.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
request_memory = 3072
Transfer_Input_Files = %(RUNDIR)s/makeStep1.C, %(RUNDIR)s/%(POST)s/step1.cc, %(RUNDIR)s/%(POST)s/step1.h, %(RUNDIR)s/%(POST)s/scaleFactors.h, %(RUNDIR)s/%(POST)s/step1_cc.d, %(RUNDIR)s/%(POST)s/step1_cc.so
Output = %(FILENAME)s_%(LABEL)s.out
Error = %(FILENAME)s_%(LABEL)s.err
Log = %(FILENAME)s_%(LABEL)s.log
Notification = Never
Arguments = %(FILENAME)s.root %(FILENAME)s_%(LABEL)s.root %(INPUTDIR)s/%(RELPATH)s %(OUTPUTDIR)s/%(RELPATH)s_%(LABEL)s

Queue 1"""%dict)
        jdf.close()
        os.chdir('%s/%s_%s'%(condorDir,relPath,outlabel))
        os.system('condor_submit %(FILENAME)s_%(LABEL)s.job'%dict)
        os.system('sleep 0.5')                                
        os.chdir('%s'%(runDir))
        print count, '/', totJobs, "jobs submitted!!!"

print("--- %s minutes ---" % (round(time.time() - start_time, 2)/60))

