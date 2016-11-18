import os,sys,shutil,datetime,time
import getpass
from ROOT import *

start_time = time.time()

shift = sys.argv[1]

#IO directories must be full paths
relbase   = '/home/ssagir/CMSSW_7_4_7/'
inputDir  = '/user_data/ssagir/LJMet_1lep_111716_step1hadds/'+shift+'/'
outputDir = '/user_data/ssagir/LJMet_1lep_111816_step2preSel/'+shift+'/'

runDir=os.getcwd()

gROOT.ProcessLine('.x compileStep2.C')

cTime=datetime.datetime.now()
date='%i_%i_%i_%i_%i_%i'%(cTime.year,cTime.month,cTime.day,cTime.hour,cTime.minute,cTime.second)

condorDir=outputDir+'/condorLogs/'

print 'Starting submission'
count=0

rootfiles = os.popen('ls '+inputDir)

os.system('mkdir -p '+outputDir)
os.system('mkdir -p '+condorDir)

for file in rootfiles:
    rawname = file[:-6]
    count+=1
    dict={'RUNDIR':runDir, 'CONDORDIR':condorDir, 'INPUTDIR':inputDir, 'FILENAME':rawname, 'CMSSWBASE':relbase, 'OUTPUTDIR':outputDir}
    jdfName=condorDir+'/%(FILENAME)s.job'%dict
    print jdfName
    jdf=open(jdfName,'w')
    jdf.write(
"""universe = vanilla
Executable = %(RUNDIR)s/makeStep2.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
request_memory = 3072
Transfer_Input_Files = %(RUNDIR)s/makeStep2.C, %(RUNDIR)s/step2.cc, %(RUNDIR)s/step2.h, %(RUNDIR)s/step2_cc.d, %(RUNDIR)s/step2_cc.so
Output = %(FILENAME)s.out
Error = %(FILENAME)s.err
Log = %(FILENAME)s.log
Notification = Never
Arguments = %(FILENAME)s.root %(FILENAME)s.root %(INPUTDIR)s %(OUTPUTDIR)s

Queue 1"""%dict)
    jdf.close()
    os.chdir('%s/'%(condorDir))
    os.system('condor_submit %(FILENAME)s.job'%dict)
    os.system('sleep 0.5')                                
    os.chdir('%s'%(runDir))
    print count, "jobs submitted!!!"

print("--- %s minutes ---" % (round(time.time() - start_time, 2)/60))

