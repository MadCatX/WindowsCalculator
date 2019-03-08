// Copyright (c) Microsoft Corporation. All rights reserved.

#include "pch_cross_platform.h"
#include "Header Files/Number.h"

using namespace std;

namespace CalcEngine
{
    Number::Number() noexcept :
        Number(1, 0, { 0 })
    {}

    Number::Number(int32_t sign, int32_t exp, vector<uint32_t> const& mantissa) noexcept :
        m_sign{ sign },
        m_exp{ exp },
        m_mantissa{ mantissa }
    {}

    Number::Number(PNUMBER p) noexcept :
        m_sign{ p->sign },
        m_exp{ p->exp },
        m_mantissa{}
    {
        m_mantissa.reserve(p->cdigit);
        copy(p->mant, p->mant + p->cdigit, back_inserter(m_mantissa));
    }

    PNUMBER Number::ToPNUMBER() const
    {
        PNUMBER ret = _createnum(static_cast<ULONG>(this->Mantissa().size()) + 1);
        ret->sign = this->Sign();
        ret->exp = this->Exp();
        ret->cdigit = static_cast<long>(this->Mantissa().size());

        MANTTYPE *ptrRet = ret->mant;
        for (auto const& digit : this->Mantissa())
        {
            *ptrRet++ = digit;
        }

        return ret;
    }

    int32_t const& Number::Sign() const
    {
        return m_sign;
    }

    int32_t const& Number::Exp() const
    {
        return m_exp;
    }

    vector<uint32_t> const& Number::Mantissa() const
    {
        return m_mantissa;
    }

    bool Number::IsZero() const
    {
        for (auto const& digit : Mantissa())
        {
            if (digit != 0)
            {
                return false;
            }
        }
        return true;
    }
}
