package com.aimei.meiktv.coreav


class AudioEffectHandler {

    var isstop = false

    fun process(){
        Thread(Runnable {
            isstop = false
            while (!isstop){
                var data = PCMDataManager.getPCMData()
                if(data!=null){
                    data.rawData = data.rawData?.let { AudioEffect.doprocess(it, data.size) }
                    PCMDataManager.putSoxPCMData(data)
                }
                Thread.sleep(10)
            }
        }).start()
    }
    fun stop() {
        isstop = true;
        PCMDataManager.clearData()
    }
}