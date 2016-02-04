#include "circuit.h"


int main()
{
//TRAN=======================================================================================================
    circuit test;
    test.append_VSRC_DEVICE("V1" , "1" , "0" , 1);
    test.append_RES_DEVICE("R1" , "2" , "1" , 1);
    test.append_IND_DEVICE("L1" , "2" , "1" , 1 , 0);
    test.append_CAP_DEVICE("C1" , "2" , "0" , 1 , 0);

    test.organize_address();

    test.tran_simulation(0.1, 15);

////DC=======================================================================================================
//    circuit test;
//    test.append_VSRC_DEVICE("V1" , "vdd" , "0" , 3.3);
//    test.append_VSRC_DEVICE("V2" , "vin" , "0" , 1);
//    test.append_MOS_DEVICE("M1" , "vout" , "vin" , "0" , "nch" , 1 , 1);
//    test.append_MOS_DEVICE("M2" , "vout" , "vin" , "vdd" , "pch" , 2 , 1);
//    test.append_MOS_DEVICE("M3" , "vout2" , "vout" , "0" , "nch" , 1 , 1);
//    test.append_MOS_DEVICE("M4" , "vout2" , "vout" , "vdd" , "pch" , 2 , 1);
//    test.append_MOS_DEVICE("M5" , "vout3" , "vout2" , "0" , "nch" , 1 , 1);
//    test.append_MOS_DEVICE("M6" , "vout3" , "vout2" , "vdd" , "pch" , 2 , 1);
//
//    test.organize_address();
//    test.display_char_node();
//
//    test.dc_simulation("V2" , 0 , 3.300001 , 0.1);

////AC=======================================================================================================
//    circuit test;
//    test.append_VSRC_DEVICE("V1" , "1" , "0" , 1);
//    test.append_RES_DEVICE("R1" , "2" , "1" , 1);
//    test.append_IND_DEVICE("L1" , "2" , "1" , 1 , 0);
//    test.append_CAP_DEVICE("C1" , "2" , "0" , 1 , 0);
//
//    test.organize_address();
//
//    //test.ac_simulation("V1" , 0.00001/(2*3.1415926535) , 100000/(2*3.1415926535) , 9*10);
//    test.ac_simulation("V1" , 1/(2*3.1415926535) , 100000/(2*3.1415926535) , 4*10);
//    //test.ac_simulation("V1", 1/(2*3.1415926535) , 1/(2*3.1415926535) , 10);

////Analog=======================================================================================================
//    circuit test;
//    test.append_VSRC_DEVICE("V1" , "vdd" , "0" , 3.3);
//    test.append_VSRC_DEVICE("V2" , "vin" , "0" , 1.5);
//    //test.append_RES_DEVICE("R1" , "vdd" , "vout" , 1000);
//    //test.append_CONT_VC_DEVICE("G1" , "vout" , "0" , "vin" , "0" , 1 , 0);
//    test.append_MOS_DEVICE("M1" , "vout" , "vin" , "0" , "nch" , 1 , 1);
//    test.append_MOS_DEVICE("M2" , "vout" , "vin" , "vdd" , "pch" , 2 , 1);
//    test.append_CAP_DEVICE("C1" , "vout" , "vin" , 0.00000001 , 0);
//    test.append_CAP_DEVICE("C2" , "vout" , "0" , 0.000001 , 0);
//
//    test.organize_address();
//    //test.ac_simulation("V2" , 0.01/(2*3.1415926535) , 1000000000000/(2*3.1415926535) , 13*10);
//    test.ac_simulation("V2" , 0.01/(2*3.1415926535) , 10/(2*3.1415926535) , 1000);

////Control Source=============================================================================================
//    circuit test;
//    test.append_RES_DEVICE("R1" , "1" , "0" , 1);
//    test.append_RES_DEVICE("R3" , "1" , "2" , 3);
//    test.append_RES_DEVICE("R4" , "2" , "0" , 4);
//    test.append_RES_DEVICE("R8" , "3" , "4" , 8);
//    test.append_VSRC_DEVICE("Vs6" , "3" , "2" , 6);
//    test.append_ISRC_DEVICE("Is5" , "0" , "2" , 5);
//    test.append_CONT_VC_DEVICE("Gs2" , "1" , "0" , "3" , "0" , 2 , 0);
//    test.append_CONT_VC_DEVICE("Es7" , "4" , "0" , "3" , "0" , 7 , 1);
//
//
//    test.organize_address();
//    test.dc_simulation("Vs6" , 1 , 2.01 , 1);

////Diode=============================================================================================
//    circuit test;
//    test.append_VSRC_DEVICE("V1" , "1" , "0" , 1);
//    test.append_DIODE_DEVICE("D1" , "1" , "2" , 40);
//    test.append_RES_DEVICE("R1" , "2" , "0" , 1);
//
//
//    test.organize_address();
//    test.dc_simulation("V1" , -10 , 10 , 0.1);



    return 0;
}
