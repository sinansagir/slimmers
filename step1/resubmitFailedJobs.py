#!/usr/bin/python

import os,sys,pickle

inputDir = '/user_data/ssagir/LJMet_1lep_111716_step1/'

shifts = [x for x in os.walk(inputDir).next()[1]]
samplesDone = {}
for shift in shifts: samplesDone[shift] = []
if os.path.exists(os.getcwd()+'/samplesDone.p'): samplesDone.update(pickle.load(open('samplesDone.p','rb')))
i=0
for shift in shifts:
	#if shift=='nominal': continue
	#if 'down' not in shift: continue
	samples = [x for x in os.walk(inputDir+'/'+shift+'/condorLogs').next()[1]]
	for sample in samples:
		#if sample!='WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8': continue
		#if 'WJetsToLNu_HT-' not in sample: continue
		#if 'X53X53_M-' not in sample: continue
		print "SAMPLE("+shift+"):",sample
		if sample in samplesDone[shift]: continue
		files = [x for x in os.listdir(inputDir+'/'+shift+'/condorLogs/'+sample) if '.job' in x]
		sampleDone = True
		for file in files:
			relPath = file.replace(inputDir,'')
			jFile = inputDir+'/'+shift+'/condorLogs/'+sample+'/'+file
			lFile = inputDir+'/'+shift+'/condorLogs/'+sample+'/'+file.replace('.job','.log')
			eFile = inputDir+'/'+shift+'/condorLogs/'+sample+'/'+file.replace('.job','.err')
			oFile = inputDir+'/'+shift+'/condorLogs/'+sample+'/'+file.replace('.job','.out')
			rFile = file.replace('.job','.root')
			#statement1 = os.path.exists(rFile)
			#statement2 = True
			#if statement1: statement2 = os.path.getsize(rFile)>1000
			isOutFileExist = False
			isOutFileOK = False
			isErrFileExist = False
			isThereError = False
			isLogFileExist = False
			isJobDone = False
			isJobFailed = False
			
			if os.path.exists(oFile): isLogFileExist = True
			if isLogFileExist: 
				logFdata = open(lFile).read()
				if 'Normal termination' in logFdata: 
					isJobDone = True
					if 'Normal termination (return value 0)' not in logFdata: isJobFailed = True
					
			if os.path.exists(oFile): isOutFileExist = True
			if isOutFileExist: 
				outFdata = open(oFile).read()
				if 'DONE' in outFdata and rFile in outFdata: isOutFileOK = True
			
			if os.path.exists(eFile): isErrFileExist = True
			if isErrFileExist: 
				errFdata = open(eFile).read()
				if 'error' in errFdata or 'Error' in errFdata: isThereError = True
				if isThereError and len(errFdata.split('\n'))>25: isThereError = False
				if len(errFdata.split('\n'))==4: isThereError = False # temporary

			statement = isOutFileExist and isOutFileOK
			statement = statement and isErrFileExist and not isThereError 
			statement = statement and isLogFileExist and isJobDone and not isJobFailed
			#print isOutFileExist,isOutFileOK,isErrFileExist,not isThereError,isLogFileExist,isJobDone
			if not statement:
				sampleDone = statement
				print "        FILE:",file
				if not (isLogFileExist and isJobDone):
					print "              --Job has not finished!"
				elif isJobFailed:
					print "              --Job failed!"
# 					print "RESUBMITTING ..."
# 					os.chdir(inputDir+'/'+shift+'/'+sample)
# 					os.system('rm ' + lFile)
# 					os.system('rm ' + eFile)
# 					os.system('rm ' + oFile)
# 					os.system('condor_submit ' + jFile)
				elif not (isOutFileExist and isOutFileOK):
					print "              --Problem in out file!"
				elif not (isErrFileExist and not isThereError):
					print "              --There is error!"
# 				print "RESUBMITTING ..."
# 				os.chdir(inputDir+'/'+shift+'/'+sample)
# 				os.system('rm ' + lFile)
# 				os.system('rm ' + eFile)
# 				os.system('rm ' + oFile)
# 				os.system('condor_submit ' + jFile)
				i+=1
		if sampleDone: samplesDone[shift].append(sample)

pickle.dump(samplesDone,open(os.getcwd()+'/samplesDone.p','wb'))
print i, "jobs resubmitted!!!"

