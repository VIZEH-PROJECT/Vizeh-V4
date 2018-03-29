// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The vizeh developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include <stdio.h> //
#include <assert.h>
#include <boost/assign/list_of.hpp>
using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
#include "chainparamsseeds.h"
/**
 * Main network
 */
//! Convert the pnSeeds6 array into usable address objects.

static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count) {
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof (ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0, uint256("0x00000733bb36aaed4e452ac90bde005df7d76948caf3e71ee25538580dae4f73"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1519564796, // * UNIX timestamp of last checkpoint block
    100000, // * total number of transactions between genesis and last checkpoint
    //   (the tx=... number in the SetBestChain debug.log lines)
    2000 // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of
        (0, uint256("0x00000733bb36aaed4e452ac90bde005df7d76948caf3e71ee25538580dae4f73")); // =
// boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1510533000,
    0,
    250
};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1510533000,
    0,
    100
};

class CMainParams : public CChainParams {
public:

    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0x58;
        pchMessageStart[2] = 0x0a;
        pchMessageStart[3] = 0x5a;
        vAlertPubKey = ParseHex("048a433c16ea5e3203252a55b5e1b1bb0139174066713b57fab6c05b1ddfaa094f199305001b67e5e73da669fe7ce9bc64e777688cabeef1549cd427c85e1b5700");
        nDefaultPort = 28157;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // vizeh starting difficulty is 1 / 2^12 = ~uint256(0) >> 15; // vizeh starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 30; // vizeh: 1 minute
        nTargetSpacing = 30; // vizeh: 1 minute
        nLastPOWBlock = 69999;
        nMaturity = 50;
        nModifierUpdateBlock = 1;
        const char* pszTimestamp = "VIZEH NEXT MONEY REVOLUTION";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*) pszTimestamp, (const unsigned char*) pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("048a433c16ea5e3203252a55b5e1b1bb0139174066713b57fab6c05b1ddfaa094f199305001b67e5e73da669fe7ce9bc64e777688cabeef1549cd427c85e1b5700") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1519564796;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 23814337;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000733bb36aaed4e452ac90bde005df7d76948caf3e71ee25538580dae4f73"));
        assert(genesis.hashMerkleRoot == uint256("0xd5f89b250067e9e3b6639e6f503e91f59a40b5e9d19135db80ff854014a8ae39"));

        vSeeds.push_back(CDNSSeedData("node1.vizeh.com", "node1.vizeh.com"));
        vSeeds.push_back(CDNSSeedData("node2.vizeh.com", "node2.vizeh.com"));
        vSeeds.push_back(CDNSSeedData("node3.vizeh.com", "node3.vizeh.com"));
        vSeeds.push_back(CDNSSeedData("node4.vizeh.com", "node4.vizeh.com"));
		vSeeds.push_back(CDNSSeedData("node5.vizeh.com", "node5.vizeh.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 107);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is 'TBD'
        //base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x13)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nPoolMaxTransactions = 3;
        strSporkKey = "048a433c16ea5e3203252a55b5e1b1bb0139174066713b57fab6c05b1ddfaa094f199305001b67e5e73da669fe7ce9bc64e777688cabeef1549cd427c85e1b5700";
        strObfuscationPoolDummyAddress = "KRjMMjXbVYGjmdp7yaXdQKoqPBU1V2NCZr";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:

    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("041481e13291ee18568f3b19c7b5704d760004d55bca3c1212bed3c96952ab3674f7b2a80d513da3a76ba01668b529f19864ae4edd0c28bfd569fdae72ebd483db");
        nDefaultPort = 21923;
        bnProofOfWorkLimit = ~uint256(0) >> 15;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // vizeh: 1 day
        nTargetSpacing = 1 * 60; // vizeh: 1 minute
        nLastPOWBlock = 12000;
        nMaturity = 10;
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1510533000;
        genesis.nNonce = 920691;
        hashGenesisBlock = genesis.GetHash();

        //assert(hashGenesisBlock == uint256("0x00000fce7c04cd554a8116fc888f0d52c93ee3d61989b5940c351f6c64a160df"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("nanu.ddns.net", "nanu.ddns.net"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet vizeh addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19); // Testnet vizeh script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239); // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet vizeh BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet vizeh BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet vizeh BIP44 coin type is '1' (All coin's testnet default)
        //base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "04a1ef0833644b51f0481773870e6a70e253fb41564bd2ccdfffaa378cd897caf40b134a35bcf7fadbb39af16e0883012484c0f7f8fa308027e9b84e1803a6b483";
        strObfuscationPoolDummyAddress = "xzAdcHiP3R8GMoLhGAdbgaFMDzsTJuyuEj";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:

    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // vizeh: 1 day
        nTargetSpacing = 1 * 60; // vizeh: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 31923;
        //assert(hashGenesisBlock == uint256("0x"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear(); //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:

    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 41923;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear(); //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases

    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) {
        nSubsidyHalvingInterval = anSubsidyHalvingInterval;
    }

    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) {
        fDefaultConsistencyChecks = afDefaultConsistencyChecks;
    }

    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {
        fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks;
    }

    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) {
        fSkipProofOfWorkCheck = afSkipProofOfWorkCheck;
    }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams() {
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine() {
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
