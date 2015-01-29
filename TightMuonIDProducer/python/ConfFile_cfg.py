import FWCore.ParameterSet.Config as cms

process = cms.Process("MyProcess")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/mc/Phys14DR/TT_Tune4C_13TeV-pythia8-tauola/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/00000/2EEAB8C4-8670-E411-B71F-0025905A48F2.root'
    )
)

process.myProducerLabel = cms.EDProducer('TightMuonIDProducer',
                                         vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                         muons = cms.InputTag("slimmedMuons"),
                                         )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root')
)

  
process.p = cms.Path(process.myProducerLabel)

process.e = cms.EndPath(process.out)
