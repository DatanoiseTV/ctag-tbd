#include <atomic>
#include "ctagSoundProcessor.hpp"
#include "mifx/pitch_shifter.h"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorMIPShft : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &);

            virtual ~ctagSoundProcessorMIPShft();

            ctagSoundProcessorMIPShft();

            virtual const char *GetCStrID() const;

        private:
            void setParamValueInternal(const string &id, const string &key, const int val) override;
            void loadPresetInternal() override;

// autogenerated code here
// sectionHpp
const string id = "MIPShft";
void setIsStereo(){isStereo = true;}
atomic<int32_t> ratio, cv_ratio;
atomic<int32_t> size, cv_size;
// sectionHpp


            // private attributes could go here
            mifx::PitchShifter fx;
            float *fx_buffer;
        };
    }
}