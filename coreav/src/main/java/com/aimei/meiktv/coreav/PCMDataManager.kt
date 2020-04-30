package com.aimei.meiktv.coreav

import java.util.*
import java.util.concurrent.ConcurrentLinkedQueue

object PCMDataManager {

    var pcmLinkList: ConcurrentLinkedQueue<PCMData> = ConcurrentLinkedQueue()
    var nodataLinkList: ConcurrentLinkedQueue<PCMData> = ConcurrentLinkedQueue()
    var soxPCMLinkList:ConcurrentLinkedQueue<PCMData> = ConcurrentLinkedQueue()

    //性能测试
    var dataLinkList1 = Collections.synchronizedList(LinkedList<PCMData>())

    fun obtainNoPCMData(): PCMData {
        if(nodataLinkList.size>0)
        return nodataLinkList.poll()
        return PCMData()
    }

    fun putPCMData(data: PCMData) {
            pcmLinkList.add(data)
//        dataLinkList1.add(data)
    }



    fun getSoxPCMData(): PCMData? {
            if(soxPCMLinkList.size>0)
                return soxPCMLinkList.poll()
            return null
//        if(dataLinkList1.size>0)
//       return dataLinkList1.removeAt(0)
//        return null
    }


    fun putSoxPCMData(data:PCMData){
        soxPCMLinkList.add(data)
    }

    fun getPCMData():PCMData?{
        if(pcmLinkList.size>0)
            return pcmLinkList.poll()
        return null
    }

    fun putNoData(data: PCMData) {
        nodataLinkList.add(data);
    }

    fun  clearData(){
        pcmLinkList.clear()
    }
}