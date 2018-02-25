#if !defined(__Vibrato_hdr__)
#define __Vibrato_hdr__

#include "ErrorDef.h"

// forward declaration
class CLfo;
template <class T>
class CRingBuffer;

/*
 * brief explanation about your class-interface design
 */

class CVibrato
{
public:
    CVibrato (float fSampleRateInHz, float fWidthInSecs, int iNumChannels);
    virtual ~CVibrato ();

    Error_t resetInstance();

    /*! list of parameters for the vibrato */
    enum VibratoParam_t
    {
        kLFORate,                     //!< LFO rate in Hz
    };

    Error_t setParam (VibratoParam_t eParam, float fParamValue);

    Error_t process( float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames );

protected:
    CRingBuffer<float>  **m_ppCRingBuffer;
    int m_iNumChannels;
    float m_fSampleRateInHz;
    float m_fWidthInSecs;
    float m_fDelayInSecs;
    int m_iDelayInSamples;
    int m_iWidthInSamples;
    int m_iMaxDelayInSamples;
private:


};

#endif // #if !defined(__Vibrato_hdr__)