#include "stdafx.h"
#include "SaveData.h"

SaveData* SaveDataV1::VersionUp()
{
  
    SaveDataV2* newData = new SaveDataV2();
    newData->highScore = highScore;
    //newData->gold
    return newData;
}
