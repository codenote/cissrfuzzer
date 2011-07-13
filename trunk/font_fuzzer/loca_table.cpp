#include "loca_table.h"
void gener_loca_table(loca_table &ft, uint16 num_glyphs, uint32 *offset){
     ft.offset=new uint32[num_glyphs+1];
     memcpy(ft.offset,offset,(num_glyphs+1)*4);
     ft.numGlyph=num_glyphs;
};
void loca_table::printTable(char* path){
     ofstream file;
     file.open(path,ios::binary|ios::app);
     for(uint16 i=0;i<=numGlyph;i++){
           file<<(char)(offset[i]>>24)<<(char)((offset[i]>>16)&255);
           file<<(char)((offset[i]>>8)&255)<<(char)(offset[i]%256);             
     };
     int ofs=getSize();
     if(ofs%4!=0){
          for(int i=0;i<4-ofs%4;i++) file<<(char)0;
     }
     file.close();
};
uint32 loca_table::getSize(){
       return 4*(numGlyph+1);
};