// Copyright 2023 Bezrukov Aleksandr
#include "../../../modules/task_2/bezrukov_a_radix_batcher/radix_batcher.h"

int companion(int mStage, int mStageStep, int ndeIndex) {
    if (mStageStep > mStage) throw std::runtime_error("Exx");

    if (mStageStep == 1) {
        return ndeIndex ^ (1 << (mStage - 1));
    } else {
        int scale = 1 << (mStage - mStageStep);
        int box = 1 << mStageStep;
        int sn = (ndeIndex / scale) - (ndeIndex / scale / box) * box;
        if (sn == box - 1 || sn == 0)
            return ndeIndex;
        else if (sn % 2 == 0)
            return - scale + ndeIndex;
        else
            return scale + ndeIndex;
    }
}
