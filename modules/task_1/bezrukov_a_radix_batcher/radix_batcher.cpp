// Copyright 2023 Bezrukov Aleksandr
#include "../../../modules/task_1/bezrukov_a_radix_batcher/radix_batcher.h"

// Unused is this lab
int partner(int nodeIndex, int mergeStage, int mergeStageStep) {
    if (mergeStageStep > mergeStage)
        throw "ERROR";

    if (mergeStageStep == 1) {
        return nodeIndex ^ (1 << (mergeStage - 1));
    } else {
        int scale = 1 << (mergeStage - mergeStageStep);  // difference between nodes for stage n stageStep n.s
        int box = 1 << mergeStageStep;
        int sn = nodeIndex / scale - (nodeIndex / scale / box) * box;
        if (sn == 0 || sn == box - 1)
            return nodeIndex;
        else if (sn % 2 == 0)
            return nodeIndex - scale;
        else
            return nodeIndex + scale;
    }
}
