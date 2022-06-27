bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{
  //cout<<"!";
int ***mas;
uint16_t format,shirina,vysota,kodirivka,potok,vysota_naooborot;


  ofstream file_out;
  file_out.open(dstFileName,ios::binary);
  ifstream file_in;
  file_in.open(srcFileName,ios::binary);
    if(!file_in){
      file_in.close(); 
      file_out.close();
      return false;
    }

    file_in.seekg(0, ios::end); 
    int size = file_in.tellg(); 
    file_in.seekg(0, ios::beg);

if(!file_in.read((char*)&kodirivka,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}//schityvanie kodirovka

if(!file_in.read((char*)&shirina,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}//schityvanie vysota
if(!file_in.read((char*)&vysota,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}//schityvanie shirina
//cout<<shirina;
if(!file_in.read((char*)&format,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}//schityvanie shirina

if(!file_out.write((char*)&kodirivka,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}
if(!file_out.write((char*)&shirina,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}
if(!file_out.write((char*)&vysota,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}
if(!file_out.write((char*)&format,sizeof(uint16_t))){
       file_in.close(); 
      file_out.close();
      return false; 
}



if((kodirivka!=ENDIAN_LITTLE)&&(kodirivka!=ENDIAN_BIG)){
        file_in.close(); 
      file_out.close();
      return false;  
}
if(vysota==0){
        file_in.close(); 
      file_out.close();
      return false;  
}
if(shirina==0){
        file_in.close(); 
      file_out.close();
      return false;  
}
if(kodirivka==0x4d4d){       
format = (unsigned short int) ((((format & 0xFF00) >> 8) + ((format & 0x00FF) << 8)));
vysota = (unsigned short int) ((((vysota & 0xFF00) >> 8) + ((vysota & 0x00FF) << 8)));
shirina = (unsigned short int) ((((shirina & 0xFF00) >> 8) + ((shirina & 0x00FF) << 8)));
}
//cout<<(format>>2)<<" "<<(format&3)<<" "<<vysota<<endl;
//cout<<kodirivka<<" "<<vysota<<" "<<shirina<<" "<<format<<" "<<(format&3)<<" " << (format>>2)<<endl;
/*if(((format &3)!=3) | (format &3)!=2|(format &3)!=0){
  file_in.close();
  file_out.close();
  return false;
}*/
//cout<<"1";
if(((format>>2)!=4)&&((format>>2)!=3)&&((format>>2)!=0)){
file_in.close();
file_out.close();
return false;
}
if(((format&3)!=0)&&((format&3)!=2)&&((format&3)!=3)){
 file_in.close();
file_out.close();
return false;
}



if((format>>2)==3){
  int her;
  if((format&3)==0){
    her=1;
  }
  if((format&3)==2){
    her=3;
  }
  if((format&3)==3){
    her=4;
  }
  //cout<<size<<endl<<((her*vysota*shirina)+8)<<endl;
  if(((her*vysota*shirina)+8)!=size){
    file_in.close();
    file_out.close();
    return false;   
  }
}

if((format>>2)==4){
  int her;
  if((format&3)==0){
    her=1;
  }
  if((format&3)==2){
    her=3;
  }
  if((format&3)==3){
    her=4;
  }
  //cout<<size<<endl<<((her*vysota*shirina)+8)<<endl;
  if(((her*vysota*shirina*2)+8)!=size){
    file_in.close();
    file_out.close();
    return false;   
  }
}





mas=new int **[vysota];
for(int i=0;i<vysota;i++){
  mas[i]=new int*[shirina];
  for(int j=0;j<shirina;j++){
    mas[i][j]=new int[4];
  }
}
//cout<<(format&3)<<endl;
if((format>>2)==3){
      for(int i=0;i<vysota;i++){//kopirovanie
        for(int j=0;j<shirina;j++){
          if((format &3)>=0){
                if(!file_in.read((char*)&potok,sizeof(char))){
                                          for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }

                mas[i][j][0]=potok;
          }
          if((format &3)>=2){
                if(!file_in.read((char*)&potok,sizeof(char))){
                                          for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }
                mas[i][j][1]=potok;
                if(!file_in.read((char*)&potok,sizeof(char))){
                                          for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }
                mas[i][j][2]=potok;              
          }
          if((format &3)==3){
                if(!file_in.read((char*)&potok,sizeof(char))){
                                          for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }
                mas[i][j][3]=potok;          
          }
          
        }
      }
}
if((format>>2)==4){
      for(int i=0;i<vysota;i++){//kopirovanie
        for(int j=0;j<shirina;j++){
          if((format &3)>=0){
                if(!file_in.read((char*)&potok,2)){
                        for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }
                mas[i][j][0]=potok;
          }
          if((format &3)>=2){
                if(!file_in.read((char*)&potok,2)){
                                          for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }
                mas[i][j][1]=potok;
                if(!file_in.read((char*)&potok,2)){
                                          for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }
                mas[i][j][2]=potok;              
          }
          if((format &3)==3){
                if(!file_in.read((char*)&potok,2)){
                                          for (int i = 0; i < vysota; i++) {
                                    for (int j = 0; j < shirina; j++) {
                                        delete [] mas[i][j];
                                    }
                                    delete [] mas[i];
                                }
                                delete [] mas;
                                file_in.close();
                            file_out.close();
                              return 0;
                }
                mas[i][j][3]=potok;          
          }
          
        }
      }
}









if(file_in.eof()){
      for (int i = 0; i < vysota; i++) {
        for (int j = 0; j < shirina; j++) {
            delete [] mas[i][j];
        }
        delete [] mas[i];
    }
    delete [] mas;
    file_in.close();
file_out.close();
  return 0;
}

/////////////////////////
/*for(int i=0;i<vysota;i++){//kopirovanie
  //cout<<"dfdfdf\n";
  for(int j=0;j<shirina;j++){
    sum=0;
    if((format &3)>=0){
      //cout<<"1\n";
          cout<<mas[i][j][0]<<"-";     
    }
    if((format &3)>=2){
           cout<<mas[i][j][1]<<"-";
           cout<<mas[i][j][2]<<"-"; 
    }
    if((format &3)==3){
           cout<<mas[i][j][3]<<"-";  
    }
    cout<<sum<<" ";
    
  }
  cout<<endl;
}
cout<<endl;*/
////////////////////////////////////////




//cout<<"1\n";
if(flipVertical){
vysota_naooborot=vysota-1;
  for(int i=0;i<vysota/2;i++){//swap verh i niz
    for(int j=0;j<shirina;j++){
      if((format &3)>=0){
            potok=mas[i][j][0];
            mas[i][j][0]=mas[vysota_naooborot][j][0];
            mas[vysota_naooborot][j][0]=potok;          
      }
      if((format &3)>=2){
            potok=mas[i][j][1];
            mas[i][j][1]=mas[vysota_naooborot][j][1];
            mas[vysota_naooborot][j][1]=potok; 
            potok=mas[i][j][2];
            mas[i][j][2]=mas[vysota_naooborot][j][2];
            mas[vysota_naooborot][j][2]=potok;           
      }
      if((format &3)==3){
            potok=mas[i][j][3];
            mas[i][j][3]=mas[vysota_naooborot][j][3];
            mas[vysota_naooborot][j][3]=potok;      
      }
    }
    vysota_naooborot--;
  }
}






if(flipHorizontal){
for(int i=0;i<vysota;i++){//swap levo pravo
  vysota_naooborot=shirina-1;
  for(int j=0;j<shirina/2;j++){
      if((format&3)>=0){
            potok=mas[i][j][0];
            mas[i][j][0]=mas[i][vysota_naooborot][0];
            mas[i][vysota_naooborot][0]=potok;          
      }
      if((format&3)>=2){
            potok=mas[i][j][1];
            mas[i][j][1]=mas[i][vysota_naooborot][1];
            mas[i][vysota_naooborot][1]=potok;   
            potok=mas[i][j][2];
            mas[i][j][2]=mas[i][vysota_naooborot][2];
            mas[i][vysota_naooborot][2]=potok;          
      }
      if((format&3)==3){
            potok=mas[i][j][3];
            mas[i][j][3]=mas[i][vysota_naooborot][3];
            mas[i][vysota_naooborot][3]=potok;   
      }
      vysota_naooborot--;
    }
  }
}


//////////////////////////////////////////////
/*
for(int i=0;i<vysota;i++){//kopirovanie
  //cout<<"dfdfdf\n";
  for(int j=0;j<shirina;j++){
    sum=0;
    if((format &3)>=0){
      //cout<<"1\n";
          cout<<mas[i][j][0]<<"-";     
    }
    if((format &3)>=2){
           cout<<mas[i][j][1]<<"-";
           cout<<mas[i][j][2]<<"-"; 
    }
    if((format &3)==3){
           cout<<mas[i][j][3]<<"-";  
    }
    cout<<sum<<" ";
    
  }
  cout<<endl;
}
cout<<endl;*/
/////////////////////////////////////////////////
//cout<<"\n\n\n\n\n";
if((format>>2)==3){
    for(int i=0;i<vysota;i++){//kopirovanie
      //cout<<"dfdfdf\n";
      for(int j=0;j<shirina;j++){
        if((format &3)>=0){
          //cout<<"1\n";
              potok=mas[i][j][0];
              file_out.write((char*)&potok,sizeof(char));        
        }
        if((format &3)>=2){
              potok=mas[i][j][1];
              file_out.write((char*)&potok,sizeof(char));
              potok=mas[i][j][2];
              file_out.write((char*)&potok,sizeof(char));         
        }
        if((format &3)==3){
              potok=mas[i][j][3];
              file_out.write((char*)&potok,sizeof(char));      
        }
        
      }
    }
}
if((format>>2)==4){
    for(int i=0;i<vysota;i++){//kopirovanie
      //cout<<"dfdfdf\n";
      for(int j=0;j<shirina;j++){
        if((format &3)>=0){
          //cout<<"1\n";
              potok=mas[i][j][0];

              file_out.write((char*)&potok,2);        
        }
        if((format &3)>=2){
              potok=mas[i][j][1];

              file_out.write((char*)&potok,2);
              potok=mas[i][j][2];

              file_out.write((char*)&potok,2);         
        }
        if((format &3)==3){
              potok=mas[i][j][3];

              file_out.write((char*)&potok,2);      
        }
        
      }
    }
}

    for (int i = 0; i < vysota; i++) {
        for (int j = 0; j < shirina; j++) {
            delete [] mas[i][j];
        }
        delete [] mas[i];
    }
    delete [] mas;
//cout<<"\n\n\n\n\n";
if(file_out.fail()){
file_in.close();
file_out.close();
return false;
}


file_in.close();
file_out.close();

return true;
}