#include "hmtx_table.h"
void gener_hmtx_table(hmtx_table &hmt,uint16 numOflhm, uint16 numGlyphs){
           hmt.numOfLongHorMmetrics=numOflhm;
           hmt.numGlyfs=numGlyphs;
           hmt.hMetrics=new longHorMetric[numOflhm];
           for(int i=0;i<numOflhm;i++) {
                   hmt.hMetrics[i].advanceWidth=rand()%50;
                   hmt.hMetrics[i].lsb=(rand()%50)-25;
           }
           hmt.lsb=new short[numGlyphs-numOflhm];
           for(int i=0;i<numGlyphs-numOflhm;i++) {
                   hmt.lsb[i]=(rand()%50)-25;
           }
};
uint32 hmtx_table::getSize(){
       return (2*numOfLongHorMmetrics+2*numGlyfs);
};
void gener_hmtx_table_header(TableDirectoryNod &tdn,hmtx_table hmt,uint32 offSet){
                  tdn.tag=0x686d7478;
                  tdn.length=hmt.getSize();
                  tdn.offset=offSet;
};
uint16 getMaxAdvance(hmtx_table &hmt){
       uint16 max=0;
       for(uint16 i=0;i<hmt.numOfLongHorMmetrics;i++)
            if(hmt.hMetrics[i].advanceWidth>max) max=hmt.hMetrics[i].advanceWidth;
       return max;    
};
short getMinlsb(hmtx_table &hmt){ //finding minimal left side bearing
       short min=hmt.hMetrics[0].lsb;
       for(uint16 i=0;i<hmt.numOfLongHorMmetrics;i++)
           if(hmt.hMetrics[i].lsb<min) min=hmt.hMetrics[i].lsb;
       for(uint16 i=0;i<hmt.numGlyfs-hmt.numOfLongHorMmetrics;i++)   
           if(hmt.lsb[i]<min) min=hmt.lsb[i];
       return min;
};
void hmtx_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     for(uint16 i=0;i<numOfLongHorMmetrics;i++){
                //writting longHorMetric info
                file<<(char)(hMetrics[i].advanceWidth>>8)<<(char)(hMetrics[i].advanceWidth%256);
                file<<(char)(hMetrics[i].lsb>>8)<<(char)(hMetrics[i].lsb%256);                
     };
     for(uint16 i=0;i<numGlyfs-numOfLongHorMmetrics;i++){
                //writting lsb info
                file<<(char)(lsb[i]>>8)<<(char)(lsb[i]%256);              
     };
     int ofs=getSize();
     if(ofs%4!=0){
          for(int i=0;i<4-ofs%4;i++) file<<(char)0;
     }
     file.close();
};
