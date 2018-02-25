
// standard headers

// project headers
#include "MUSI6106Config.h"

#include "ErrorDef.h"

#include "RingBuffer.h"

#include "Lfo.h"
#include "Vibrato.h"

static const char*  kCMyProjectBuildDate             = __DATE__;

CVibrato::CVibrato(float fSampleRateInHz, float fWidthInSecs, int iNumChannels) :
    m_ppCRingBuffer(0),
    m_iNumChannels(iNumChannels),
    m_fSampleRateInHz(fSampleRateInHz),
    m_fWidthInSecs(fWidthInSecs),
    m_fDelayInSecs(fWidthInSecs), // MATLAB: Delay = Width; % basic delay of input sample in sec
    m_iDelayInSamples(static_cast<int>(round(m_fDelayInSecs*m_fSampleRateInHz))), // MATLAB: DELAY=round(Delay*SAMPLERATE); % basic delay in # samples
    m_iWidthInSamples(static_cast<int>(round(m_fWidthInSecs*m_fSampleRateInHz))),  // MATLAB: WIDTH=round(Width*SAMPLERATE); % basic delay in # samples
    m_iMaxDelayInSamples((2+m_iDelayInSamples+m_iWidthInSamples)*2)  // MATLAB: L=2_DELAY+WIDTH*2; % length of entire delay
{
    assert(m_iWidthInSamples < m_iDelayInSamples);  // MATLAB: if WIDTH>DELAY {raise error}

    // Allocate Memory
    m_ppCRingBuffer = new CRingBuffer<float> * [m_iNumChannels];
    for (int i = 0; i < iNumChannels; ++i) {
        m_ppCRingBuffer[i] = new CRingBuffer<float>(m_iMaxDelayInSamples);
    }
}

CVibrato::~CVibrato()
{
    for (int i = 0; i < m_iNumChannels; ++i) {
        delete m_ppCRingBuffer[i];
    }
    delete [] m_ppCRingBuffer;
    m_ppCRingBuffer = 0;
}

Error_t CVibrato::resetInstance()
{
    for (int i = 0; i < m_iNumChannels; ++i) {
        m_ppCRingBuffer[i]->reset();
    }
    return kNoError;
}


Error_t CVibrato::setParam(VibratoParam_t eParam, float fParamValue)
{

}

Error_t process( float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames )
{

}