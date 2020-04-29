package com.aimei.meiktv.coreav

import java.util.*
import java.util.concurrent.ConcurrentLinkedQueue

object PCMDataManager {

    var dataLinkList: ConcurrentLinkedQueue<PCMData> = ConcurrentLinkedQueue()
    var nodataLinkList: ConcurrentLinkedQueue<PCMData> = ConcurrentLinkedQueue()

    //性能测试
    var dataLinkList1 = Collections.synchronizedList(LinkedList<PCMData>())

    fun obtainNoPCMData(): PCMData {
        if(nodataLinkList.size>0)
        return nodataLinkList.poll()
        return PCMData()
    }

    fun putData(data: PCMData) {

            dataLinkList.add(data)

//        dataLinkList1.add(data)

    }

    fun getData(): PCMData? {

            if(dataLinkList.size>0)
                return dataLinkList.poll()
            return null


//        if(dataLinkList1.size>0)
//       return dataLinkList1.removeAt(0)
//        return null
    }

    fun putNoData(data: PCMData) {
        nodataLinkList.add(data);
    }

    fun  clearData(){
        dataLinkList.clear()
    }
}