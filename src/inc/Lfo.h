#if !defined(__Lfo_hdr__)
#define __Lfo_hdr__

#define _USE_MATH_DEFINES
#include <math.h>

#include "ErrorDef.h"
#include "Synthesis.h"

#define PI 3.14159265

/*
 * `CLfo` is a wavetable LFO
 * If initialized with 20 Hz at sample rate 44000Hz, then we need to
 * create a `CRingBuffer` class that contains exactly one cycle of the
 * low frequency sin
 */

class CLfo
{
    float m_fLfoRateInHz;
    float m_fSampleRateInHz;
    int m_iWavetableLengthInSamples;
public:
    CLfo(float fLfoRateInHz, float fSampleRateInHz):
        m_fLfoRateInHz(fLfoRateInHz),
        m_fSampleRateInHz(fSampleRateInHz),
        m_iWavetableLengthInSamples(static_cast<int>(round((1/m_fLfoRateInHz) * m_fSampleRateInHz))),  // Number of samples to hold one complete cycle of the LFO
        // m_pCRingBuffer(*m_iWavetableLengthInSamples)

    {
        assert(fLfoRateInHz < 30F); // Otherwise this is not an LFO!



        for (int n = 0; n < m_iWavetableLengthInSamples; n++) {
            float fSinValue = static_cast<float>(sin(m_fLfoRateInHz * 2 * PI * n));  // MATLAB: MOD=sin(M*2*pi*n) where M=MODFREQ
            m_pCRingBuffer->putPostInc(fSinValue);
        }
    }

private:
    CRingBuffer<float>  * m_pCRingBuffer;
};

#endif // __Lfo_hdr__
