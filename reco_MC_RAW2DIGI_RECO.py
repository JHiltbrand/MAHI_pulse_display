# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: reco_MC --filein file:step2.root --mc --eventcontent RECOSIM --conditions 106X_upgrade2018_realistic_v11_L1v1 --step RAW2DIGI,RECO --nThreads 4 --geometry DB:Extended --era Run2_2018 -n 100 --no_exec
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
from Configuration.AlCa.GlobalTag import GlobalTag

process = cms.Process('RECO', eras.Run3_2025)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')

process.load('Configuration.EventContent.EventContent_cff')
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
	    "file://pickevents.root"
    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Output definition
process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:reco_MC_RAW2DIGI_RECO.root'),
    outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition
process.TFileService = cms.Service("TFileService", fileName = cms.string("mahidebugger.root") )

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '150X_dataRun3_Prompt_v1', '')

process.hbheprereco.saveInfos    = cms.bool(True)

process.load("RecoLocalCalo.HcalRecAlgos.test.mahiDebugger_cfi")

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.hcalDigis)
process.reconstruction_step = cms.Path(process.hbheprereco)
process.flat_step = cms.Path(process.mahiDebugger)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.flat_step)
