#include "hhea_table.h"
void gener_hhea_table(hhea_table &hh, uint16 hmetrixNum){
           //if exists 'OS/2' table parametrs 0-2 would be taken from there
           hh.version=0x00010000;
           hh.ascend=rand()%40;
           hh.descend=-(rand()%40);
           hh.lineGap=rand()%50;
           //parameters 3-5 must be consistent with 'hmtx' table!
           hh.advanceWidthMax=0;
           hh.minLeftSideBearing=0;
           hh.minRightSideBearing=0;
           hh.xMaxExtent=0;
           hh.caretSlopeRise=rand()%256;
           hh.caretSlopeRun=0;//for consistence with other simplificatiob
           hh.caretOffset=rand()%256;
           for(int i=0;i<3;i++) hh.reserved[i]=0;
           hh.metricDataFormat=0;
           hh.numberOfHMetrics=hmetrixNum;
};
uint32 hhea_table::getSize(){return 36;}; //this table has fixed size
void gener_hhea_table_header(TableDirectoryNod &tdn,uint32 offSet){
                  tdn.tag=0x68686561;
                  tdn.length=36;
                  tdn.offset=offSet;
};
void hhea_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     cout<<"good file: "<<file.good()<<endl;
     //before writing each elemental strucrure divides into bytes, then writing to file
     file<<(char)0<<(char)1<<(char)0<<(char)0;//version
     file<<(char)(ascend>>8)<<(char)(ascend%256);
     file<<(char)(descend>>8)<<(char)(descend%256);
     file<<(char)(lineGap>>8)<<(char)(lineGap%256);
     file<<(char)(advanceWidthMax>>8)<<(char)(advanceWidthMax%256);
     file<<(char)(minLeftSideBearing>>8)<<(char)(minLeftSideBearing%256);
     file<<(char)(minRightSideBearing>>8)<<(char)(minRightSideBearing%256);
     file<<(char)(xMaxExtent>>8)<<(char)(xMaxExtent%256);
     file<<(char)(caretSlopeRise>>8)<<(char)(caretSlopeRise%256);
     file<<(char)(caretSlopeRun>>8)<<(char)(caretSlopeRun%256);
     file<<(char)(caretOffset>>8)<<(char)(caretOffset%256);
     //following 10 bytes reserved as 0
     for(int i=0;i<10;i++) file<<(char)0;
     file<<(char)(numberOfHMetrics>>8)<<(char)(numberOfHMetrics%256);
     file.close();
};
