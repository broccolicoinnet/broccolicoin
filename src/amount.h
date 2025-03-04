// Copyright (c) 2009-2010 Florins Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_AMOUNT_H
#define BITCOIN_AMOUNT_H

#include "serialize.h"

#include <stdlib.h>
#include <string>

/** Amount in florinss (Can be negative) */
typedef int64_t CAmount;

static const CAmount COIN = 100000000;
static const CAmount CENT = 1000000;

extern const std::string CURRENCY_UNIT;

/** No amount larger than this (in florins) is valid.
 *
 * Note that this constant is *not* the total money supply, which in Bitcoin
 * currently happens to be less than 21,000,000 BTC for various reasons, but
 * rather a sanity check. As this sanity check is used by consensus-critical
 * validation code, the exact value of the MAX_MONEY constant is consensus
 * critical; in unusual circumstances like a(nother) overflow bug that allowed
 * for the creation of coins out of thin air modification could lead to a fork.
 * */
static const CAmount MAX_MONEY = 10000000000 * COIN; // Broccolicoin: maximum of 100B coins (given some randomness), max transaction 10,000,000,000
inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }

/**
 * Fee rate in florinss per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nFlorinssPerK; // unit is florinss-per-1,000-bytes
public:
    /** Fee rate of 0 florinss per kB */
    CFeeRate() : nFlorinssPerK(0) { }
    explicit CFeeRate(const CAmount& _nFlorinssPerK): nFlorinssPerK(_nFlorinssPerK) { }
    /** Constructor for a fee rate in florinss per kB. The size in bytes must not exceed (2^63 - 1)*/
    CFeeRate(const CAmount& nFeePaid, size_t nBytes);
    CFeeRate(const CFeeRate& other) { nFlorinssPerK = other.nFlorinssPerK; }
    /**
     * Return the fee in florinss for the given size in bytes.
     */
    CAmount GetFee(size_t nBytes) const;
    /**
     * Return the fee in florinss for a size of 1000 bytes
     */
    CAmount GetFeePerK() const { return GetFee(1000); }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nFlorinssPerK < b.nFlorinssPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nFlorinssPerK > b.nFlorinssPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nFlorinssPerK == b.nFlorinssPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nFlorinssPerK <= b.nFlorinssPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nFlorinssPerK >= b.nFlorinssPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nFlorinssPerK += a.nFlorinssPerK; return *this; }
    std::string ToString() const;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(nFlorinssPerK);
    }
};

#endif //  BITCOIN_AMOUNT_H
