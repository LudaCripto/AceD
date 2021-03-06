// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/block.h"

#include "hash.h"
#include "tinyformat.h"
#include "utilstrencodings.h"
#include "crypto/common.h"

uint256 CBlockHeader::GetHash() const
{
//    return HashX11(BEGIN(nVersion), END(nNonce));
    uint256 thash;
		if(nTime <= 1534130303){ // 2018/04/01 @ 12:00 (UTC)

    thash = HashX11(BEGIN(nVersion), END(nNonce));
	} else {
			thash = HashX16R(BEGIN(nVersion), END(nNonce), hashPrevBlock);
	}
return thash;
}

bool CBlock::IsProofOfStake() const
{
    return (vtx.size() > 1 && vtx[1]->IsCoinStake());
}
bool CBlock::IsProofOfWork() const
{
    return !IsProofOfStake();
}


std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (unsigned int i = 0; i < vtx.size(); i++)
    {
        s << "  " << vtx[i]->ToString() << "\n";
    }
    return s.str();
}
