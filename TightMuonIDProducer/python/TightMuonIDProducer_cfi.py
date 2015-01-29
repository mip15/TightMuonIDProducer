import FWCore.ParameterSet.Config as cms

TightMuonIDProducer = cms.EDProducer("TightMuonIDProducer",
                                vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                muons = cms.InputTag("slimmedMuons"),
                                )
