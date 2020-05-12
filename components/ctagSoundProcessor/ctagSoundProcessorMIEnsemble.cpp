#include "ctagSoundProcessorMIEnsemble.hpp"
#include <iostream>
#include "helpers/ctagFastMath.hpp"

using namespace CTAG::SP;

ctagSoundProcessorMIEnsemble::ctagSoundProcessorMIEnsemble() {
    setIsStereo();
    model = std::make_unique<ctagSPDataModel>(id, isStereo);
    model->LoadPreset(0);

    fx_buffer = (float *) heap_caps_malloc(4096 * sizeof(float),
                                               MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (fx_buffer == NULL) {
        ESP_LOGE("MIChorus", "Could not allocate shared buffer!");
    };

    fx.Init(fx_buffer);
}

void ctagSoundProcessorMIEnsemble::Process(const ProcessData &data) {
    float fAmount = amount / 4095.f;
    float fDepth = depth / 4095.f;
    if(cv_amount != -1){
        fAmount = HELPERS::fastfabs(data.cv[cv_amount]);
    }
    if(cv_depth != -1){
        fDepth = HELPERS::fastfabs(data.cv[cv_depth]);
    }
    fx.set_depth(fDepth);
    fx.set_amount(fAmount);

    float left[bufSz], right[bufSz];
    for(int i=0;i<bufSz;i++){
        left[i] = data.buf[i*2];
        right[i] = data.buf[i*2 + 1];
    }

    fx.Process(left, right, bufSz);

    for(int i=0;i<bufSz;i++){
        data.buf[i*2] = left[i];
        data.buf[i*2 + 1] = right[i];
    }
}

ctagSoundProcessorMIEnsemble::~ctagSoundProcessorMIEnsemble() {
    heap_caps_free(fx_buffer);
}

const char *ctagSoundProcessorMIEnsemble::GetCStrID() const {
    return id.c_str();
}


void ctagSoundProcessorMIEnsemble::setParamValueInternal(const string& id, const string& key, const int val) {
// autogenerated code here
// sectionCpp0
if(id.compare("depth") == 0){
	if(key.compare("current") == 0){
		depth = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_depth = val;
	}
	return;
}
if(id.compare("amount") == 0){
	if(key.compare("current") == 0){
		amount = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_amount = val;
	}
	return;
}
// sectionCpp0

}

void ctagSoundProcessorMIEnsemble::loadPresetInternal() {
// autogenerated code here
// sectionCpp1
depth = model->GetParamValue("depth", "current");
cv_depth = model->GetParamValue("depth", "cv");
amount = model->GetParamValue("amount", "current");
cv_amount = model->GetParamValue("amount", "cv");
// sectionCpp1

}
